/*
 *  linux/fs/isofs/dir.c
 *
 *  (C) 1992, 1993, 1994  Eric Youngdale Modified for ISO9660 filesystem.
 *
 *  (C) 1991  Linus Torvalds - minix filesystem
 *
 *  Steve Beynon		       : Missing last directory entries fixed
 *  (stephen@askone.demon.co.uk)      : 21st June 1996
 * 
 *  isofs directory handling functions
 */
#include <linux/errno.h>
#include <linux/fs.h>
#include <linux/iso_fs.h>
#include <linux/kernel.h>
#include <linux/stat.h>
#include <linux/string.h>
#include <linux/mm.h>
#include <linux/malloc.h>
#include <linux/sched.h>
#include <linux/locks.h>

#include <asm/segment.h>


static int isofs_readdir(struct inode *, struct file *, void *, filldir_t);

static struct file_operations isofs_dir_operations =
{
	NULL,			/* lseek - default */
	NULL,			/* read */
	NULL,			/* write - bad */
	isofs_readdir,		/* readdir */
	NULL,			/* select - default */
	NULL,			/* ioctl - default */
	NULL,			/* no special open code */
	NULL,			/* no special release code */
	NULL			/* fsync */
};

/*
 * directories can handle most operations...
 */
struct inode_operations isofs_dir_inode_operations =
{
	&isofs_dir_operations,	/* default directory file-ops */
	NULL,			/* create */
	isofs_lookup,		/* lookup */
	NULL,			/* link */
	NULL,			/* unlink */
	NULL,			/* symlink */
	NULL,			/* mkdir */
	NULL,			/* rmdir */
	NULL,			/* mknod */
	NULL,			/* rename */
	NULL,			/* readlink */
	NULL,			/* follow_link */
	NULL,			/* readpage */
	NULL,			/* writepage */
	isofs_bmap,		/* bmap */
	NULL,			/* truncate */
	NULL			/* permission */
};

static int parent_inode_number(struct inode * inode, struct iso_directory_record * de)
{
	int inode_number = inode->i_ino;

	if ((inode->i_sb->u.isofs_sb.s_firstdatazone) != inode->i_ino)
		inode_number = inode->u.isofs_i.i_backlink;

	if (inode_number != -1)
		return inode_number;

	/* This should never happen, but who knows.  Try to be forgiving */
	return isofs_lookup_grandparent(inode, find_rock_ridge_relocation(de, inode));
}

static int isofs_name_translate(char * old, int len, char * new)
{
	int i, c;
			
	for (i = 0; i < len; i++) {
		c = old[i];
		if (!c)
			break;
		if (c >= 'A' && c <= 'Z')
			c |= 0x20;	/* lower case */

		/* Drop trailing '.;1' (ISO9660:1988 7.5.1 requires period) */
		if (c == '.' && i == len - 3 && old[i + 1] == ';' && old[i + 2] == '1')
			break;

		/* Drop trailing ';1' */
		if (c == ';' && i == len - 2 && old[i + 1] == '1')
			break;

		/* Convert remaining ';' to '.' */
		if (c == ';')
			c = '.';

		new[i] = c;
	}
	return i;
}

/*
 * This should _really_ be cleaned up some day..
 */
static int do_isofs_readdir(struct inode *inode, struct file *filp,
		void *dirent, filldir_t filldir,
		char * tmpname, struct iso_directory_record * tmpde)
{
	unsigned long bufsize = ISOFS_BUFFER_SIZE(inode);
	unsigned char bufbits = ISOFS_BUFFER_BITS(inode);
	unsigned int block, offset;
	int inode_number = 0;	/* Quiet GCC */
	struct buffer_head *bh;
	int len;
	int map;
	int high_sierra;
	int first_de = 1;
	char *p = NULL;		/* Quiet GCC */
	struct iso_directory_record *de;

	offset = filp->f_pos & (bufsize - 1);
	block = isofs_bmap(inode, filp->f_pos >> bufbits);
	high_sierra = inode->i_sb->u.isofs_sb.s_high_sierra;

	if (!block)
		return 0;

	if (!(bh = breada(inode->i_dev, block, bufsize, filp->f_pos, inode->i_size)))
		return 0;

	while (filp->f_pos < inode->i_size) {
		int de_len, next_offset;
#ifdef DEBUG
		printk("Block, offset, f_pos: %x %x %x\n",
		       block, offset, filp->f_pos);
	        printk("inode->i_size = %x\n",inode->i_size);
#endif
		/* Next directory_record on next CDROM sector */
		if (offset >= bufsize) {
#ifdef DEBUG
		        printk("offset >= bufsize\n");
#endif
			brelse(bh);
			offset = 0;
			block = isofs_bmap(inode, (filp->f_pos) >> bufbits);
			if (!block)
				return 0;
			bh = breada(inode->i_dev, block, bufsize, filp->f_pos, inode->i_size);
			if (!bh)
				return 0;
			continue;
		}

		de = (struct iso_directory_record *) (bh->b_data + offset);
		if(first_de) inode_number = (block << bufbits) + (offset & (bufsize - 1));

		de_len = *(unsigned char *) de;
#ifdef DEBUG
		printk("de_len = %ld\n", de_len);
#endif
	    

		/* If the length byte is zero, we should move on to the next
		   CDROM sector.  If we are at the end of the directory, we
		   kick out of the while loop. */

		if (de_len == 0) {
			brelse(bh);
			filp->f_pos = ((filp->f_pos & ~(ISOFS_BLOCK_SIZE - 1))
				       + ISOFS_BLOCK_SIZE);
			offset = 0;
			block = isofs_bmap(inode, (filp->f_pos) >> bufbits);
			if (!block)
				return 0;
			bh = breada(inode->i_dev, block, bufsize, filp->f_pos, inode->i_size);
			if (!bh)
				return 0;
			continue;
		}

		/* Make sure that the entire directory record is in the
		   current bh block.
		   If not, put the two halves together in "tmpde" */
		next_offset = offset + de_len;
		if (next_offset > bufsize) {
#ifdef DEBUG
		        printk("next_offset (%x) > bufsize (%x)\n",next_offset,bufsize);
#endif
			next_offset &= (bufsize - 1);
		        memcpy(tmpde, de, bufsize - offset);
			brelse(bh);
			block = isofs_bmap(inode, (filp->f_pos + de_len) >> bufbits);
			if (!block)
		        {
				return 0;
			}
		  
			bh = breada(inode->i_dev, block, bufsize, 
				    filp->f_pos, 
				    inode->i_size);
			if (!bh)
		        {
#ifdef DEBUG
                 		printk("!bh block=%ld, bufsize=%ld\n",block,bufsize); 
 				printk("filp->f_pos = %ld\n",filp->f_pos);
				printk("inode->i_size = %ld\n", inode->i_size);
#endif
				return 0;
			}
		  
			memcpy(bufsize - offset + (char *) tmpde, bh->b_data, next_offset);
			de = tmpde;
		}
		offset = next_offset;

		if(de->flags[-high_sierra] & 0x80) {
			first_de = 0;
			filp->f_pos += de_len;
			continue;
		}
		first_de = 1;

		/* Handle the case of the '.' directory */
		if (de->name_len[0] == 1 && de->name[0] == 0) {
			if (filldir(dirent, ".", 1, filp->f_pos, inode->i_ino) < 0)
				break;
			filp->f_pos += de_len;
			continue;
		}

		len = 0;

		/* Handle the case of the '..' directory */
		if (de->name_len[0] == 1 && de->name[0] == 1) {
			inode_number = parent_inode_number(inode, de);
			if (inode_number == -1)
				break;
			if (filldir(dirent, "..", 2, filp->f_pos, inode_number) < 0)
				break;
			filp->f_pos += de_len;
			continue;
		}

		/* Handle everything else.  Do name translation if there
		   is no Rock Ridge NM field. */
		if (inode->i_sb->u.isofs_sb.s_unhide == 'n') {
			/* Do not report hidden or associated files */
			if (de->flags[-high_sierra] & 5) {
				filp->f_pos += de_len;
				continue;
			}
		}

		map = 1;
		if (inode->i_sb->u.isofs_sb.s_rock) {
			len = get_rock_ridge_filename(de, tmpname, inode);
			if (len != 0) {
				p = tmpname;
				map = 0;
			}
		}
		if (map) {
			if (inode->i_sb->u.isofs_sb.s_joliet_level) {
				len = get_joliet_filename(de, inode, tmpname);
				p = tmpname;
			} else {
				if (inode->i_sb->u.isofs_sb.s_mapping == 'n') {
					len = isofs_name_translate(de->name, de->name_len[0],
								   tmpname);
					p = tmpname;
				} else {
					p = de->name;
					len = de->name_len[0];
				}
			}
		}
		if (len > 0) {
			if (filldir(dirent, p, len, filp->f_pos, inode_number) < 0)
				break;

			dcache_add(inode, p, len, inode_number);
		}
		filp->f_pos += de_len;
		continue;
	}
	brelse(bh);
	return 0;
}

/*
 * Handle allocation of temporary space for name translation and
 * handling split directory entries.. The real work is done by
 * "do_isofs_readdir()".
 */
static int isofs_readdir(struct inode *inode, struct file *filp,
		void *dirent, filldir_t filldir)
{
	int result;
	char * tmpname;
	struct iso_directory_record * tmpde;

	if (!inode || !S_ISDIR(inode->i_mode))
		return -EBADF;

	tmpname = (char *) __get_free_page(GFP_KERNEL);
	if (!tmpname)
		return -ENOMEM;
	tmpde = (struct iso_directory_record *) (tmpname+1024);

	result = do_isofs_readdir(inode, filp, dirent, filldir, tmpname, tmpde);

	free_page((unsigned long) tmpname);
	return result;
}
