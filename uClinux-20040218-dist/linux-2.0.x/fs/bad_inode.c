/*
 *  linux/fs/bad_inode.c
 *
 *  Copyright (C) 1997, Stephen Tweedie
 *
 *  Provide stub functions for unreadable inodes
 */

#include <linux/fs.h>
#include <linux/stat.h>
#include <linux/sched.h>

static int return_EIO(void)
{
	return -EIO;
}

#define EIO_ERROR ((void *) (return_EIO))

static struct file_operations bad_file_ops =
{
	EIO_ERROR,		/* lseek */
	EIO_ERROR,		/* read */
	EIO_ERROR,		/* write */
	EIO_ERROR,		/* readdir */
	EIO_ERROR,		/* select */
	EIO_ERROR,		/* ioctl */
	EIO_ERROR,		/* mmap */
	EIO_ERROR,		/* open */
	EIO_ERROR,		/* release */
	EIO_ERROR,		/* fsync */
	EIO_ERROR,		/* fasync */
	EIO_ERROR,		/* check_media_change */
	EIO_ERROR		/* revalidate */
#ifdef MAGIC_ROM_PTR
	,EIO_ERROR		/* romptr */
#endif /* MAGIC_ROM_PTR */
};

static struct inode_operations bad_inode_ops =
{
	&bad_file_ops,		/* default file operations */
	EIO_ERROR,		/* create */
	EIO_ERROR,		/* lookup */
	EIO_ERROR,		/* link */
	EIO_ERROR,		/* unlink */
	EIO_ERROR,		/* symlink */
	EIO_ERROR,		/* mkdir */
	EIO_ERROR,		/* rmdir */
	EIO_ERROR,		/* mknod */
	EIO_ERROR,		/* rename */
	EIO_ERROR,		/* readlink */
	EIO_ERROR,		/* follow_link */
	EIO_ERROR,		/* readpage */
	EIO_ERROR,		/* writepage */
	EIO_ERROR,		/* bmap */
	EIO_ERROR,		/* truncate */
	EIO_ERROR,		/* permission */
	EIO_ERROR		/* smap */
};


/* 
 * When a filesystem is unable to read an inode due to an I/O error in
 * its read_inode() function, it can call make_bad_inode() to return a
 * set of stubs which will return EIO errors as required. 
 *
 * We only need to do limited initialisation: all other fields are
 * preinitialised to zero automatically.
 */
void make_bad_inode(struct inode * inode) 
{
	inode->i_mode = S_IFREG;
	inode->i_flags = S_BAD_INODE;
	inode->i_atime = CURRENT_TIME;
	inode->i_mtime = CURRENT_TIME;
	inode->i_ctime = CURRENT_TIME;
	inode->i_op = &bad_inode_ops;	
}

