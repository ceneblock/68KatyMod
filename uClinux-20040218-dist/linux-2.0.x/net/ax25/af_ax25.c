/*
 *	AX.25 release 035
 *
 *	This code REQUIRES 1.2.1 or higher/ NET3.029
 *
 *	This module:
 *		This module is free software; you can redistribute it and/or
 *		modify it under the terms of the GNU General Public License
 *		as published by the Free Software Foundation; either version
 *		2 of the License, or (at your option) any later version.
 *
 *	History
 *	AX.25 006	Alan(GW4PTS)		Nearly died of shock - it's working 8-)
 *	AX.25 007	Alan(GW4PTS)		Removed the silliest bugs
 *	AX.25 008	Alan(GW4PTS)		Cleaned up, fixed a few state machine problems, added callbacks
 *	AX.25 009	Alan(GW4PTS)		Emergency patch kit to fix memory corruption
 * 	AX.25 010	Alan(GW4PTS)		Added RAW sockets/Digipeat.
 *	AX.25 011	Alan(GW4PTS)		RAW socket and datagram fixes (thanks) - Raw sendto now gets PID right
 *						datagram sendto uses correct target address.
 *	AX.25 012	Alan(GW4PTS)		Correct incoming connection handling, send DM to failed connects.
 *						Use skb->data not skb+1. Support sk->priority correctly.
 *						Correct receive on SOCK_DGRAM.
 *	AX.25 013	Alan(GW4PTS)		Send DM to all unknown frames, missing initialiser fixed
 *						Leave spare SSID bits set (DAMA etc) - thanks for bug report,
 *						removed device registration (it's not used or needed). Clean up for
 *						gcc 2.5.8. PID to AX25_P_
 *	AX.25 014	Alan(GW4PTS)		Cleanup and NET3 merge
 *	AX.25 015	Alan(GW4PTS)		Internal test version.
 *	AX.25 016	Alan(GW4PTS)		Semi Internal version for PI card
 *						work.
 *	AX.25 017	Alan(GW4PTS)		Fixed some small bugs reported by
 *						G4KLX
 *	AX.25 018	Alan(GW4PTS)		Fixed a small error in SOCK_DGRAM
 *	AX.25 019	Alan(GW4PTS)		Clean ups for the non INET kernel and device ioctls in AX.25
 *	AX.25 020	Jonathan(G4KLX)		/proc support and other changes.
 *	AX.25 021	Alan(GW4PTS)		Added AX25_T1, AX25_N2, AX25_T3 as requested.
 *	AX.25 022	Jonathan(G4KLX)		More work on the ax25 auto router and /proc improved (again)!
 *			Alan(GW4PTS)		Added TIOCINQ/OUTQ
 *	AX.25 023	Alan(GW4PTS)		Fixed shutdown bug
 *	AX.25 023	Alan(GW4PTS)		Linus changed timers
 *	AX.25 024	Alan(GW4PTS)		Small bug fixes
 *	AX.25 025	Alan(GW4PTS)		More fixes, Linux 1.1.51 compatibility stuff, timers again!
 *	AX.25 026	Alan(GW4PTS)		Small state fix.
 *	AX.25 027	Alan(GW4PTS)		Socket close crash fixes.
 *	AX.25 028	Alan(GW4PTS)		Callsign control including settings per uid.
 *						Small bug fixes.
 *						Protocol set by sockets only.
 *						Small changes to allow for start of NET/ROM layer.
 *	AX.25 028a	Jonathan(G4KLX)		Changes to state machine.
 *	AX.25 028b	Jonathan(G4KLX)		Extracted ax25 control block
 *						from sock structure.
 *	AX.25 029	Alan(GW4PTS)		Combined 028b and some KA9Q code
 *			Jonathan(G4KLX)		and removed all the old Berkeley, added IP mode registration.
 *			Darryl(G7LED)		stuff. Cross-port digipeating. Minor fixes and enhancements.
 *			Alan(GW4PTS)		Missed suser() on axassociate checks
 *	AX.25 030	Alan(GW4PTS)		Added variable length headers.
 *			Jonathan(G4KLX)		Added BPQ Ethernet interface.
 *			Steven(GW7RRM)		Added digi-peating control ioctl.
 *						Added extended AX.25 support.
 *						Added AX.25 frame segmentation.
 *			Darryl(G7LED)		Changed connect(), recvfrom(), sendto() sockaddr/addrlen to
 *						fall inline with bind() and new policy.
 *						Moved digipeating ctl to new ax25_dev structs.
 *						Fixed ax25_release(), set TCP_CLOSE, wakeup app
 *						context, THEN make the sock dead.
 *			Alan(GW4PTS)		Cleaned up for single recvmsg methods.
 *			Alan(GW4PTS)		Fixed not clearing error on connect failure.
 *	AX.25 031	Jonathan(G4KLX)		Added binding to any device.
 *			Joerg(DL1BKE)		Added DAMA support, fixed (?) digipeating, fixed buffer locking
 *						for "virtual connect" mode... Result: Probably the
 *						"Most Buggiest Code You've Ever Seen" (TM)
 *			HaJo(DD8NE)		Implementation of a T5 (idle) timer
 *			Joerg(DL1BKE)		Renamed T5 to IDLE and changed behaviour:
 *						the timer gets reloaded on every received or transmitted
 *						I frame for IP or NETROM. The idle timer is not active
 *						on "vanilla AX.25" connections. Furthermore added PACLEN
 *						to provide AX.25-layer based fragmentation (like WAMPES)
 *      AX.25 032	Joerg(DL1BKE)		Fixed DAMA timeout error.
 *						ax25_send_frame() limits the number of enqueued
 *						datagrams per socket.
 *	AX.25 033	Jonathan(G4KLX)		Removed auto-router.
 *			Hans(PE1AYX)		Converted to Module.
 *			Joerg(DL1BKE)		Moved BPQ Ethernet to seperate driver.
 *						Fixed 2.0.x specific IP over AX.25 problem.
 *	AX.25 035	Frederic(F1OAT)		Support for pseudo-digipeating.
 *			Jonathan(G4KLX)		Support for packet forwarding.
 *			Jonathan(G4KLX)		Fix wildcard listening parameter setting.
 *
 *	To do:
 *		Restructure the ax25_rcv code to be cleaner/faster and
 *		copy only when needed.
 *		Consider better arbitrary protocol support.
 */

#include <linux/config.h>
#if defined(CONFIG_AX25) || defined(CONFIG_AX25_MODULE)
#include <linux/module.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/socket.h>
#include <linux/in.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/timer.h>
#include <linux/string.h>
#include <linux/sockios.h>
#include <linux/net.h>
#include <net/ax25.h>
#include <linux/inet.h>
#include <linux/netdevice.h>
#include <linux/if_arp.h>
#include <linux/skbuff.h>
#include <net/sock.h>
#include <asm/segment.h>
#include <asm/system.h>
#include <linux/fcntl.h>
#include <linux/termios.h>	/* For TIOCINQ/OUTQ */
#include <linux/mm.h>
#include <linux/interrupt.h>
#include <linux/notifier.h>
#include <linux/proc_fs.h>
#include <linux/stat.h>
#include <linux/firewall.h>

#include <net/ip.h>
#include <net/arp.h>

/*
 *	The null address is defined as a callsign of all spaces with an
 *	SSID of zero.
 */
ax25_address null_ax25_address = {{0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x00}};

ax25_cb *volatile ax25_list = NULL;

/*
 *	ax25 -> ascii conversion
 */
char *ax2asc(ax25_address *a)
{
	static char buf[11];
	char c, *s;
	int n;

	for (n = 0, s = buf; n < 6; n++) {
		c = (a->ax25_call[n] >> 1) & 0x7F;

		if (c != ' ') *s++ = c;
	}

	*s++ = '-';

	if ((n = ((a->ax25_call[6] >> 1) & 0x0F)) > 9) {
		*s++ = '1';
		n -= 10;
	}

	*s++ = n + '0';
	*s++ = '\0';

	if (*buf == '\0' || *buf == '-')
	   return "*";

	return buf;

}

/*
 *	ascii -> ax25 conversion
 */
ax25_address *asc2ax(char *callsign)
{
	static ax25_address addr;
	char *s;
	int n;

	for (s = callsign, n = 0; n < 6; n++) {
		if (*s != '\0' && *s != '-')
			addr.ax25_call[n] = *s++;
		else
			addr.ax25_call[n] = ' ';
		addr.ax25_call[n] <<= 1;
		addr.ax25_call[n] &= 0xFE;
	}

	if (*s++ == '\0') {
		addr.ax25_call[6] = 0x00;
		return &addr;
	}

	addr.ax25_call[6] = *s++ - '0';

	if (*s != '\0') {
		addr.ax25_call[6] *= 10;
		addr.ax25_call[6] += *s++ - '0';
	}

	addr.ax25_call[6] <<= 1;
	addr.ax25_call[6] &= 0x1E;

	return &addr;
}

/*
 *	Compare two ax.25 addresses
 */
int ax25cmp(ax25_address *a, ax25_address *b)
{
	int ct = 0;

	while (ct < 6) {
		if ((a->ax25_call[ct] & 0xFE) != (b->ax25_call[ct] & 0xFE))	/* Clean off repeater bits */
			return 1;
		ct++;
	}

 	if ((a->ax25_call[ct] & 0x1E) == (b->ax25_call[ct] & 0x1E))	/* SSID without control bit */
 		return 0;

 	return 2;			/* Partial match */
}

/*
 *	Compare two AX.25 digipeater paths.
 */
static int ax25digicmp(ax25_digi *digi1, ax25_digi *digi2)
{
	int i;

	if (digi1->ndigi != digi2->ndigi)
		return 1;

	if (digi1->lastrepeat != digi2->lastrepeat)
		return 1;

	for (i = 0; i < digi1->ndigi; i++)
		if (ax25cmp(&digi1->calls[i], &digi2->calls[i]) != 0)
			return 1;

	return 0;
}

/*
 *	Free an allocated ax25 control block. This is done to centralise
 *	the MOD count code.
 */
static void ax25_free_cb(ax25_cb *ax25)
{
	if (ax25->digipeat != NULL) {
		kfree_s(ax25->digipeat, sizeof(ax25_digi));
		ax25->digipeat = NULL;
	}

	kfree_s(ax25, sizeof(ax25_cb));

	MOD_DEC_USE_COUNT;
}

/*
 *	Socket removal during an interrupt is now safe.
 */
static void ax25_remove_socket(ax25_cb *ax25)
{
	ax25_cb *s;
	unsigned long flags;

	save_flags(flags);
	cli();

	if ((s = ax25_list) == ax25) {
		ax25_list = s->next;
		restore_flags(flags);
		return;
	}

	while (s != NULL && s->next != NULL) {
		if (s->next == ax25) {
			s->next = ax25->next;
			restore_flags(flags);
			return;
		}

		s = s->next;
	}

	restore_flags(flags);
}

/*
 *	Kill all bound sockets on a dropped device.
 */
static void ax25_kill_by_device(struct device *dev)
{
	ax25_cb *s;

	for (s = ax25_list; s != NULL; s = s->next) {
		if (s->device == dev) {
			s->device = NULL;
			ax25_disconnect(s, ENETUNREACH);
		}
	}
}

/*
 *	Handle device status changes.
 */
static int ax25_device_event(struct notifier_block *this,unsigned long event, void *ptr)
{
	struct device *dev = (struct device *)ptr;

	/* Reject non AX.25 devices */
	if (dev->type != ARPHRD_AX25)
		return NOTIFY_DONE;

	switch (event) {
		case NETDEV_UP:
			ax25_dev_device_up(dev);
			break;
		case NETDEV_DOWN:
			ax25_kill_by_device(dev);
			ax25_rt_device_down(dev);
			ax25_dev_device_down(dev);
			break;
		default:
			break;
	}

	return NOTIFY_DONE;
}

/*
 *	Add a socket to the bound sockets list.
 */
static void ax25_insert_socket(ax25_cb *ax25)
{
	unsigned long flags;

	save_flags(flags);
	cli();

	ax25->next = ax25_list;
	ax25_list  = ax25;

	restore_flags(flags);
}

/*
 *	Find a socket that wants to accept the SABM we have just
 *	received.
 */
static struct sock *ax25_find_listener(ax25_address *addr, int digi, struct device *dev, int type)
{
	unsigned long flags;
	ax25_cb *s;

	save_flags(flags);
	cli();

	for (s = ax25_list; s != NULL; s = s->next) {
		if ((s->iamdigi && !digi) || (!s->iamdigi && digi))
			continue;
		if (s->sk != NULL && ax25cmp(&s->source_addr, addr) == 0 && s->sk->type == type && s->sk->state == TCP_LISTEN) {
			/* If device is null we match any device */
			if (s->device == NULL || s->device == dev) {
				restore_flags(flags);
				return s->sk;
			}
		}
	}

	restore_flags(flags);
	return NULL;
}

/*
 *	Find an AX.25 socket given both ends.
 */
static struct sock *ax25_find_socket(ax25_address *my_addr, ax25_address *dest_addr, int type)
{
	ax25_cb *s;
	unsigned long flags;

	save_flags(flags);
	cli();

	for (s = ax25_list; s != NULL; s = s->next) {
		if (s->sk != NULL && ax25cmp(&s->source_addr, my_addr) == 0 && ax25cmp(&s->dest_addr, dest_addr) == 0 && s->sk->type == type) {
			restore_flags(flags);
			return s->sk;
		}
	}

	restore_flags(flags);

	return NULL;
}

/*
 *	Find an AX.25 control block given both ends. It will only pick up
 *	floating AX.25 control blocks or non Raw socket bound control blocks.
 */
ax25_cb *ax25_find_cb(ax25_address *src_addr, ax25_address *dest_addr, ax25_digi *digi, struct device *dev)
{
	ax25_cb *s;
	unsigned long flags;

	save_flags(flags);
	cli();

	for (s = ax25_list; s != NULL; s = s->next) {
		if (s->sk != NULL && s->sk->type != SOCK_SEQPACKET)
			continue;
		if (ax25cmp(&s->source_addr, src_addr) == 0 && ax25cmp(&s->dest_addr, dest_addr) == 0 && s->device == dev) {
			if (digi != NULL && digi->ndigi != 0) {
				if (s->digipeat == NULL)
					continue;
				if (ax25digicmp(s->digipeat, digi) != 0)
					continue;
			} else {
				if (s->digipeat != NULL && s->digipeat->ndigi != 0)
					continue;
			}
			restore_flags(flags);
			return s;
		}
	}

	restore_flags(flags);

	return NULL;
}

/*
 *	Look for any matching address - RAW sockets can bind to arbitrary names
 */
static struct sock *ax25_addr_match(ax25_address *addr)
{
	unsigned long flags;
	ax25_cb *s;

	save_flags(flags);
	cli();

	for (s = ax25_list; s != NULL; s = s->next) {
		if (s->sk != NULL && ax25cmp(&s->source_addr, addr) == 0 && s->sk->type == SOCK_RAW) {
			restore_flags(flags);
			return s->sk;
		}
	}

	restore_flags(flags);

	return NULL;
}

static void ax25_send_to_raw(struct sock *sk, struct sk_buff *skb, int proto)
{
	struct sk_buff *copy;

	while (sk != NULL) {
		if (sk->type == SOCK_RAW && sk->protocol == proto && sk->rmem_alloc <= sk->rcvbuf) {
			if ((copy = skb_clone(skb, GFP_ATOMIC)) == NULL)
				return;

			if (sock_queue_rcv_skb(sk, copy) != 0)
				kfree_skb(copy, FREE_READ);
		}

		sk = sk->next;
	}
}

/*
 *	Deferred destroy.
 */
void ax25_destroy_socket(ax25_cb *);

/*
 *	Handler for deferred kills.
 */
static void ax25_destroy_timer(unsigned long data)
{
	ax25_destroy_socket((ax25_cb *)data);
}

/*
 *	This is called from user mode and the timers. Thus it protects itself against
 *	interrupt users but doesn't worry about being called during work.
 *	Once it is removed from the queue no interrupt or bottom half will
 *	touch it and we are (fairly 8-) ) safe.
 */
void ax25_destroy_socket(ax25_cb *ax25)	/* Not static as it's used by the timer */
{
	struct sk_buff *skb;
	unsigned long flags;

	save_flags(flags);
	cli();

	del_timer(&ax25->timer);

	ax25_remove_socket(ax25);
	ax25_clear_queues(ax25);	/* Flush the queues */

	if (ax25->sk != NULL) {
		while ((skb = skb_dequeue(&ax25->sk->receive_queue)) != NULL) {
			if (skb->sk != ax25->sk) {			/* A pending connection */
				skb->sk->dead = 1;	/* Queue the unaccepted socket for death */
				ax25_set_timer(skb->sk->protinfo.ax25);
				skb->sk->protinfo.ax25->state = AX25_STATE_0;
			}

			kfree_skb(skb, FREE_READ);
		}
	}

	if (ax25->sk != NULL) {
		if (ax25->sk->wmem_alloc != 0 || ax25->sk->rmem_alloc != 0) {	/* Defer: outstanding buffers */
			init_timer(&ax25->timer);
			ax25->timer.expires  = jiffies + 10 * HZ;
			ax25->timer.function = ax25_destroy_timer;
			ax25->timer.data     = (unsigned long)ax25;
			add_timer(&ax25->timer);
		} else {
			sk_free(ax25->sk);
			ax25_free_cb(ax25);
		}
	} else {
		ax25_free_cb(ax25);
	}

	restore_flags(flags);
}

/*
 *	Callsign/UID mapper. This is in kernel space for security on multi-amateur machines.
 */

ax25_uid_assoc *ax25_uid_list;

int ax25_uid_policy = 0;

ax25_address *ax25_findbyuid(uid_t uid)
{
	ax25_uid_assoc *a;

	for (a = ax25_uid_list; a != NULL; a = a->next) {
		if (a->uid == uid)
			return &a->call;
	}

	return NULL;
}

static int ax25_uid_ioctl(int cmd, struct sockaddr_ax25 *sax)
{
	ax25_uid_assoc *a;

	switch (cmd) {
		case SIOCAX25GETUID:
			for (a = ax25_uid_list; a != NULL; a = a->next) {
				if (ax25cmp(&sax->sax25_call, &a->call) == 0)
					return a->uid;
			}
			return -ENOENT;

		case SIOCAX25ADDUID:
			if (!suser())
				return -EPERM;
			if (ax25_findbyuid(sax->sax25_uid))
				return -EEXIST;
			if (sax->sax25_uid == 0)
				return -EINVAL;
			a = (ax25_uid_assoc *)kmalloc(sizeof(*a), GFP_KERNEL);
			if (a == NULL)
				return -ENOMEM;
			a->uid  = sax->sax25_uid;
			a->call = sax->sax25_call;
			a->next = ax25_uid_list;
			ax25_uid_list = a;
			return 0;

		case SIOCAX25DELUID: {
			ax25_uid_assoc **l;

			if (!suser())
				return -EPERM;
			l = &ax25_uid_list;
			while ((*l) != NULL) {
				if (ax25cmp(&((*l)->call), &(sax->sax25_call)) == 0) {
					a = *l;
					*l = (*l)->next;
					kfree_s(a, sizeof(*a));
					return 0;
				}

				l = &((*l)->next);
			}
			return -ENOENT;
		}

		default:
			return -EINVAL;
	}

	return -EINVAL;	/*NOTREACHED */
}

/*
 * dl1bke 960311: set parameters for existing AX.25 connections,
 *		  includes a KILL command to abort any connection.
 *		  VERY useful for debugging ;-)
 */
static int ax25_ctl_ioctl(const unsigned int cmd, void *arg)
{
	struct ax25_ctl_struct ax25_ctl;
	struct device *dev;
	ax25_cb *ax25;
	unsigned long flags;
	int err;

	if ((err = verify_area(VERIFY_READ, arg, sizeof(ax25_ctl))) != 0)
		return err;

	memcpy_fromfs(&ax25_ctl, arg, sizeof(ax25_ctl));

	if ((dev = ax25rtr_get_dev(&ax25_ctl.port_addr)) == NULL)
		return -ENODEV;

	if ((ax25 = ax25_find_cb(&ax25_ctl.source_addr, &ax25_ctl.dest_addr, NULL, dev)) == NULL)
		return -ENOTCONN;

	switch (ax25_ctl.cmd) {
		case AX25_KILL:
			ax25_send_control(ax25, AX25_DISC, AX25_POLLON, AX25_COMMAND);
			ax25_disconnect(ax25, ENETRESET);
			ax25_set_timer(ax25);
	  		break;

	  	case AX25_WINDOW:
	  		if (ax25->modulus == AX25_MODULUS) {
	  			if (ax25_ctl.arg < 1 || ax25_ctl.arg > 7)
	  				return -EINVAL;
	  		} else {
	  			if (ax25_ctl.arg < 1 || ax25_ctl.arg > 63)
	  				return -EINVAL;
	  		}
	  		ax25->window = ax25_ctl.arg;
	  		break;

	  	case AX25_T1:
  			if (ax25_ctl.arg < 1)
  				return -EINVAL;
  			ax25->rtt = (ax25_ctl.arg * AX25_SLOWHZ) / 2;
  			ax25->t1  = ax25_ctl.arg * AX25_SLOWHZ;
  			save_flags(flags); cli();
  			if (ax25->t1timer > ax25->t1)
  				ax25->t1timer = ax25->t1;
  			restore_flags(flags);
  			break;

	  	case AX25_T2:
	  		if (ax25_ctl.arg < 1)
	  			return -EINVAL;
	  		save_flags(flags); cli();
	  		ax25->t2 = ax25_ctl.arg * AX25_SLOWHZ;
	  		if (ax25->t2timer > ax25->t2)
	  			ax25->t2timer = ax25->t2;
	  		restore_flags(flags);
	  		break;

	  	case AX25_N2:
	  		if (ax25_ctl.arg < 1 || ax25_ctl.arg > 31)
	  			return -EINVAL;
	  		ax25->n2count = 0;
	  		ax25->n2 = ax25_ctl.arg;
	  		break;

	  	case AX25_T3:
	  		if (ax25_ctl.arg < 0)
	  			return -EINVAL;
	  		save_flags(flags); cli();
	  		ax25->t3 = ax25_ctl.arg * AX25_SLOWHZ;
	  		if (ax25->t3timer != 0)
	  			ax25->t3timer = ax25->t3;
	  		restore_flags(flags);
	  		break;

	  	case AX25_IDLE:
	  		if (ax25_ctl.arg < 0)
	  			return -EINVAL;
			save_flags(flags); cli();
	  		ax25->idle = ax25_ctl.arg * AX25_SLOWHZ * 60;
	  		if (ax25->idletimer != 0)
	  			ax25->idletimer = ax25->idle;
	  		restore_flags(flags);
	  		break;

	  	case AX25_PACLEN:
	  		if (ax25_ctl.arg < 16 || ax25_ctl.arg > 65535)
	  			return -EINVAL;
	  		ax25->paclen = ax25_ctl.arg;
	  		break;

	  	default:
	  		return -EINVAL;
	  }

	  return 0;
}

/*
 *	Fill in a created AX.25 created control block with the default
 *	values for a particular device.
 */
static void ax25_fillin_cb(ax25_cb *ax25, struct device *dev)
{
	ax25->device = dev;

	if (dev != NULL) {
		ax25->rtt     = ax25_dev_get_value(dev, AX25_VALUES_T1) / 2;
		ax25->t1      = ax25_dev_get_value(dev, AX25_VALUES_T1);
		ax25->t2      = ax25_dev_get_value(dev, AX25_VALUES_T2);
		ax25->t3      = ax25_dev_get_value(dev, AX25_VALUES_T3);
		ax25->n2      = ax25_dev_get_value(dev, AX25_VALUES_N2);
		ax25->paclen  = ax25_dev_get_value(dev, AX25_VALUES_PACLEN);
		ax25->idle    = ax25_dev_get_value(dev, AX25_VALUES_IDLE);
		ax25->backoff = ax25_dev_get_value(dev, AX25_VALUES_BACKOFF);

		if (ax25_dev_get_value(dev, AX25_VALUES_AXDEFMODE)) {
			ax25->modulus = AX25_EMODULUS;
			ax25->window  = ax25_dev_get_value(dev, AX25_VALUES_EWINDOW);
		} else {
			ax25->modulus = AX25_MODULUS;
			ax25->window  = ax25_dev_get_value(dev, AX25_VALUES_WINDOW);
		}
	} else {
		ax25->rtt     = AX25_DEF_T1 / 2;
		ax25->t1      = AX25_DEF_T1;
		ax25->t2      = AX25_DEF_T2;
		ax25->t3      = AX25_DEF_T3;
		ax25->n2      = AX25_DEF_N2;
		ax25->paclen  = AX25_DEF_PACLEN;
		ax25->idle    = AX25_DEF_IDLE;
		ax25->backoff = AX25_DEF_BACKOFF;

		if (AX25_DEF_AXDEFMODE) {
			ax25->modulus = AX25_EMODULUS;
			ax25->window  = AX25_DEF_EWINDOW;
		} else {
			ax25->modulus = AX25_MODULUS;
			ax25->window  = AX25_DEF_WINDOW;
		}
	}
}

/*
 * Create an empty AX.25 control block.
 */
static ax25_cb *ax25_create_cb(void)
{
	ax25_cb *ax25;

	if ((ax25 = (ax25_cb *)kmalloc(sizeof(*ax25), GFP_ATOMIC)) == NULL)
		return NULL;

	MOD_INC_USE_COUNT;

	memset(ax25, 0x00, sizeof(*ax25));

	skb_queue_head_init(&ax25->write_queue);
	skb_queue_head_init(&ax25->frag_queue);
	skb_queue_head_init(&ax25->ack_queue);
	skb_queue_head_init(&ax25->reseq_queue);

	init_timer(&ax25->timer);

	ax25_fillin_cb(ax25, NULL);

	ax25->state = AX25_STATE_0;

	return ax25;
}

/*
 *	Find out if we are a DAMA slave for this device and count the
 *	number of connections.
 *
 *	dl1bke 951121
 */
int ax25_dev_is_dama_slave(struct device *dev)
{
	ax25_cb *ax25;
	int count = 0;

	for (ax25 = ax25_list; ax25 != NULL; ax25 = ax25->next) {
		if (ax25->device == dev && ax25->dama_slave) {
			count++;
			break;
		}
	}

	return count;
}

ax25_cb *ax25_send_frame(struct sk_buff *skb, int paclen, ax25_address *src, ax25_address *dest,
	ax25_digi *digi, struct device *dev)
{
	ax25_cb *ax25;

	if (paclen == 0)
		paclen = ax25_dev_get_value(dev, AX25_VALUES_PACLEN);

	/*
	 * Look for an existing connection.
	 */
	if ((ax25 = ax25_find_cb(src, dest, digi, dev)) != NULL) {
		ax25_output(ax25, paclen, skb);
		return ax25;		/* It already existed */
	}

	if ((ax25 = ax25_create_cb()) == NULL)
		return NULL;

	ax25_fillin_cb(ax25, dev);

	ax25->source_addr = *src;
	ax25->dest_addr   = *dest;

	if (digi != NULL) {
		if ((ax25->digipeat = kmalloc(sizeof(ax25_digi), GFP_ATOMIC)) == NULL) {
			ax25_free_cb(ax25);
			return NULL;
		}
		*ax25->digipeat = *digi;
	}

	if (ax25_dev_is_dama_slave(ax25->device))
		dama_establish_data_link(ax25);
	else
		ax25_establish_data_link(ax25);

	ax25_insert_socket(ax25);

	ax25->state = AX25_STATE_1;

	ax25_set_timer(ax25);

	ax25_output(ax25, paclen, skb);

	return ax25;			/* We had to create it */
}

/*
 *	Find the AX.25 device that matches the hardware address supplied.
 */
struct device *ax25rtr_get_dev(ax25_address *addr)
{
	struct device *dev;

	for (dev = dev_base; dev != NULL; dev = dev->next)
		if ((dev->flags & IFF_UP) && dev->type == ARPHRD_AX25 &&
		    ax25cmp(addr, (ax25_address *)dev->dev_addr) == 0)
		     	return dev;

	return NULL;
}

/*
 *	Handling for system calls applied via the various interfaces to an
 *	AX25 socket object
 */
static int ax25_fcntl(struct socket *sock, unsigned int cmd, unsigned long arg)
{
	return -EINVAL;
}

static int ax25_setsockopt(struct socket *sock, int level, int optname,
	char *optval, int optlen)
{
	struct sock *sk = (struct sock *)sock->data;
	int err, opt;

	if (level == SOL_SOCKET)
		return sock_setsockopt(sk, level, optname, optval, optlen);

	if (level != SOL_AX25)
		return -EOPNOTSUPP;

	if (optval == NULL)
		return -EINVAL;

	if ((err = verify_area(VERIFY_READ, optval, sizeof(int))) != 0)
		return err;

	opt = get_fs_long((int *)optval);

	switch (optname) {
		case AX25_WINDOW:
			if (sk->protinfo.ax25->modulus == AX25_MODULUS) {
				if (opt < 1 || opt > 7)
					return -EINVAL;
			} else {
				if (opt < 1 || opt > 63)
					return -EINVAL;
			}
			sk->protinfo.ax25->window = opt;
			return 0;

		case AX25_T1:
			if (opt < 1)
				return -EINVAL;
			sk->protinfo.ax25->rtt = (opt * AX25_SLOWHZ) / 2;
			sk->protinfo.ax25->t1  = opt * AX25_SLOWHZ;
			return 0;

		case AX25_T2:
			if (opt < 1)
				return -EINVAL;
			sk->protinfo.ax25->t2 = opt * AX25_SLOWHZ;
			return 0;

		case AX25_N2:
			if (opt < 1 || opt > 31)
				return -EINVAL;
			sk->protinfo.ax25->n2 = opt;
			return 0;

		case AX25_T3:
			if (opt < 1)
				return -EINVAL;
			sk->protinfo.ax25->t3 = opt * AX25_SLOWHZ;
			return 0;

		case AX25_IDLE:
			if (opt < 0)
				return -EINVAL;
			sk->protinfo.ax25->idle = opt * AX25_SLOWHZ * 60;
			return 0;

		case AX25_BACKOFF:
			if (opt < 0 || opt > 2)
				return -EINVAL;
			sk->protinfo.ax25->backoff = opt;
			return 0;

		case AX25_EXTSEQ:
			sk->protinfo.ax25->modulus = opt ? AX25_EMODULUS : AX25_MODULUS;
			return 0;

		case AX25_PIDINCL:
			sk->protinfo.ax25->pidincl = opt ? 1 : 0;
			return 0;

		case AX25_IAMDIGI:
			sk->protinfo.ax25->iamdigi = opt ? 1 : 0;
			return 0;

		case AX25_PACLEN:
			if (opt < 16 || opt > 65535)
				return -EINVAL;
			sk->protinfo.ax25->paclen = opt;
			return 0;

		default:
			return -ENOPROTOOPT;
	}
}

static int ax25_getsockopt(struct socket *sock, int level, int optname,
	char *optval, int *optlen)
{
	struct sock *sk = (struct sock *)sock->data;
	int val = 0;
	int err;

	if (level == SOL_SOCKET)
		return sock_getsockopt(sk, level, optname, optval, optlen);

	if (level != SOL_AX25)
		return -EOPNOTSUPP;

	switch (optname) {
		case AX25_WINDOW:
			val = sk->protinfo.ax25->window;
			break;

		case AX25_T1:
			val = sk->protinfo.ax25->t1 / AX25_SLOWHZ;
			break;

		case AX25_T2:
			val = sk->protinfo.ax25->t2 / AX25_SLOWHZ;
			break;

		case AX25_N2:
			val = sk->protinfo.ax25->n2;
			break;

		case AX25_T3:
			val = sk->protinfo.ax25->t3 / AX25_SLOWHZ;
			break;

		case AX25_IDLE:
			val = sk->protinfo.ax25->idle / (AX25_SLOWHZ * 60);
			break;

		case AX25_BACKOFF:
			val = sk->protinfo.ax25->backoff;
			break;

		case AX25_EXTSEQ:
			val = (sk->protinfo.ax25->modulus == AX25_EMODULUS);
			break;

		case AX25_PIDINCL:
			val = sk->protinfo.ax25->pidincl;
			break;

		case AX25_IAMDIGI:
			val = sk->protinfo.ax25->iamdigi;
			break;

		case AX25_PACLEN:
			val = sk->protinfo.ax25->paclen;
			break;

		default:
			return -ENOPROTOOPT;
	}

	if ((err = verify_area(VERIFY_WRITE, optlen, sizeof(int))) != 0)
		return err;

	put_user(sizeof(int), optlen);

	if ((err = verify_area(VERIFY_WRITE, optval, sizeof(int))) != 0)
		return err;

	put_user(val, (int *)optval);

	return 0;
}

static int ax25_listen(struct socket *sock, int backlog)
{
	struct sock *sk = (struct sock *)sock->data;

	if (sk->type == SOCK_SEQPACKET && sk->state != TCP_LISTEN) {
		sk->max_ack_backlog = backlog;
		sk->state           = TCP_LISTEN;
		return 0;
	}

	return -EOPNOTSUPP;
}

static void def_callback1(struct sock *sk)
{
	if (!sk->dead)
		wake_up_interruptible(sk->sleep);
}

static void def_callback2(struct sock *sk, int len)
{
	if (!sk->dead)
		wake_up_interruptible(sk->sleep);
}

static int ax25_create(struct socket *sock, int protocol)
{
	struct sock *sk;
	ax25_cb *ax25;

	switch (sock->type) {
		case SOCK_DGRAM:
			if (protocol == 0 || protocol == AF_AX25)
				protocol = AX25_P_TEXT;
			break;
		case SOCK_SEQPACKET:
			switch (protocol) {
				case 0:
				case AF_AX25:	/* For CLX */
					protocol = AX25_P_TEXT;
					break;
				case AX25_P_SEGMENT:
#ifdef CONFIG_INET
				case AX25_P_ARP:
				case AX25_P_IP:
#endif
#ifdef CONFIG_NETROM
				case AX25_P_NETROM:
#endif
#ifdef CONFIG_ROSE
				case AX25_P_ROSE:
#endif
					return -ESOCKTNOSUPPORT;
#ifdef CONFIG_NETROM_MODULE
				case AX25_P_NETROM:
					if (ax25_protocol_is_registered(AX25_P_NETROM))
						return -ESOCKTNOSUPPORT;
#endif
#ifdef CONFIG_ROSE_MODULE
				case AX25_P_ROSE:
					if (ax25_protocol_is_registered(AX25_P_ROSE))
						return -ESOCKTNOSUPPORT;
#endif
				default:
					break;
			}
			break;
		case SOCK_RAW:
			break;
		default:
			return -ESOCKTNOSUPPORT;
	}

	if ((sk = sk_alloc(GFP_ATOMIC)) == NULL)
		return -ENOMEM;

	if ((ax25 = ax25_create_cb()) == NULL) {
		sk_free(sk);
		return -ENOMEM;
	}

	skb_queue_head_init(&sk->receive_queue);
	skb_queue_head_init(&sk->write_queue);
	skb_queue_head_init(&sk->back_log);

	sk->socket        = sock;
	sk->type          = sock->type;
	sk->protocol      = protocol;
	sk->next          = NULL;
	sk->allocation	  = GFP_KERNEL;
	sk->rcvbuf        = SK_RMEM_MAX;
	sk->sndbuf        = SK_WMEM_MAX;
	sk->state         = TCP_CLOSE;
	sk->priority      = SOPRI_NORMAL;
	sk->mtu           = AX25_MTU;	/* 256 */
	sk->zapped        = 1;

	sk->state_change = def_callback1;
	sk->data_ready   = def_callback2;
	sk->write_space  = def_callback1;
	sk->error_report = def_callback1;

	if (sock != NULL) {
		sock->data = (void *)sk;
		sk->sleep  = sock->wait;
	}

	ax25->sk          = sk;
	sk->protinfo.ax25 = ax25;

	return 0;
}

static struct sock *ax25_make_new(struct sock *osk, struct device *dev)
{
	struct sock *sk;
	ax25_cb *ax25;

	if ((sk = sk_alloc(GFP_ATOMIC)) == NULL)
		return NULL;

	if ((ax25 = ax25_create_cb()) == NULL) {
		sk_free(sk);
		return NULL;
	}

	ax25_fillin_cb(ax25, dev);

	sk->type   = osk->type;
	sk->socket = osk->socket;

	switch (osk->type) {
		case SOCK_DGRAM:
			break;
		case SOCK_SEQPACKET:
			break;
		default:
			sk_free(sk);
			ax25_free_cb(ax25);
			return NULL;
	}

	skb_queue_head_init(&sk->receive_queue);
	skb_queue_head_init(&sk->write_queue);
	skb_queue_head_init(&sk->back_log);

	sk->next        = NULL;
	sk->priority    = osk->priority;
	sk->protocol    = osk->protocol;
	sk->rcvbuf      = osk->rcvbuf;
	sk->sndbuf      = osk->sndbuf;
	sk->debug       = osk->debug;
	sk->state       = TCP_ESTABLISHED;
	sk->mtu         = osk->mtu;
	sk->sleep       = osk->sleep;
	sk->zapped      = osk->zapped;

	sk->state_change = def_callback1;
	sk->data_ready   = def_callback2;
	sk->write_space  = def_callback1;
	sk->error_report = def_callback1;

	ax25->modulus = osk->protinfo.ax25->modulus;
	ax25->backoff = osk->protinfo.ax25->backoff;
	ax25->pidincl = osk->protinfo.ax25->pidincl;
	ax25->iamdigi = osk->protinfo.ax25->iamdigi;
	ax25->rtt     = osk->protinfo.ax25->rtt;
	ax25->t1      = osk->protinfo.ax25->t1;
	ax25->t2      = osk->protinfo.ax25->t2;
	ax25->t3      = osk->protinfo.ax25->t3;
	ax25->n2      = osk->protinfo.ax25->n2;
	ax25->idle    = osk->protinfo.ax25->idle;
	ax25->paclen  = osk->protinfo.ax25->paclen;
	ax25->window  = osk->protinfo.ax25->window;

	ax25->source_addr = osk->protinfo.ax25->source_addr;

	if (osk->protinfo.ax25->digipeat != NULL) {
		if ((ax25->digipeat = (ax25_digi *)kmalloc(sizeof(ax25_digi), GFP_ATOMIC)) == NULL) {
			sk_free(sk);
			ax25_free_cb(ax25);
			return NULL;
		}

		*ax25->digipeat = *osk->protinfo.ax25->digipeat;
	}

	sk->protinfo.ax25 = ax25;
	ax25->sk          = sk;

	return sk;
}

static int ax25_dup(struct socket *newsock, struct socket *oldsock)
{
	struct sock *sk = (struct sock *)oldsock->data;

	if (sk == NULL || newsock == NULL)
		return -EINVAL;

	return ax25_create(newsock, sk->protocol);
}

static int ax25_release(struct socket *sock, struct socket *peer)
{
	struct sock *sk = (struct sock *)sock->data;

	if (sk == NULL) return 0;

	if (sk->type == SOCK_SEQPACKET) {
		switch (sk->protinfo.ax25->state) {
			case AX25_STATE_0:
				ax25_disconnect(sk->protinfo.ax25, 0);
				ax25_destroy_socket(sk->protinfo.ax25);
				break;

			case AX25_STATE_1:
				ax25_send_control(sk->protinfo.ax25, AX25_DISC, AX25_POLLON, AX25_COMMAND);
				ax25_disconnect(sk->protinfo.ax25, 0);
				ax25_destroy_socket(sk->protinfo.ax25);
				break;

			case AX25_STATE_2:
				if (sk->protinfo.ax25->dama_slave)
					ax25_send_control(sk->protinfo.ax25, AX25_DISC, AX25_POLLON, AX25_COMMAND);
				else
					ax25_send_control(sk->protinfo.ax25, AX25_DM, AX25_POLLON, AX25_RESPONSE);
				ax25_disconnect(sk->protinfo.ax25, 0);
				ax25_destroy_socket(sk->protinfo.ax25);
				break;

			case AX25_STATE_3:
			case AX25_STATE_4:
				ax25_clear_queues(sk->protinfo.ax25);
				sk->protinfo.ax25->n2count = 0;
				if (!sk->protinfo.ax25->dama_slave) {
					ax25_send_control(sk->protinfo.ax25, AX25_DISC, AX25_POLLON, AX25_COMMAND);
					sk->protinfo.ax25->t3timer = 0;
				} else {
					sk->protinfo.ax25->t3timer = sk->protinfo.ax25->t3;	/* DAMA slave timeout */
				}
				sk->protinfo.ax25->t1timer = sk->protinfo.ax25->t1 = ax25_calculate_t1(sk->protinfo.ax25);
				sk->protinfo.ax25->state   = AX25_STATE_2;
				sk->state                  = TCP_CLOSE;
				sk->shutdown              |= SEND_SHUTDOWN;
				sk->state_change(sk);
				sk->dead                   = 1;
				sk->destroy                = 1;
				break;

			default:
				break;
		}
	} else {
		sk->state       = TCP_CLOSE;
		sk->shutdown   |= SEND_SHUTDOWN;
		sk->state_change(sk);
		sk->dead        = 1;
		ax25_destroy_socket(sk->protinfo.ax25);
	}

	sock->data = NULL;	
	sk->socket = NULL;	/* Not used, but we should do this. **/

	return 0;
}

/*
 *	We support a funny extension here so you can (as root) give any callsign
 *	digipeated via a local address as source. This is a hack until we add
 *	BSD 4.4 ADDIFADDR type support. It is however small and trivially backward
 *	compatible 8)
 */
static int ax25_bind(struct socket *sock, struct sockaddr *uaddr, int addr_len)
{
	struct sock *sk = (struct sock *)sock->data;
	struct full_sockaddr_ax25 *addr = (struct full_sockaddr_ax25 *)uaddr;
	struct device *dev;
	ax25_address *call;

	if (sk->zapped == 0)
		return -EINVAL;

	if (addr_len != sizeof(struct sockaddr_ax25) && addr_len != sizeof(struct full_sockaddr_ax25))
		return -EINVAL;

	if (addr->fsa_ax25.sax25_family != AF_AX25)
		return -EINVAL;

	call = ax25_findbyuid(current->euid);
	if (call == NULL && ax25_uid_policy && !suser())
		return -EACCES;

	if (call == NULL)
		sk->protinfo.ax25->source_addr = addr->fsa_ax25.sax25_call;
	else
		sk->protinfo.ax25->source_addr = *call;

	if (sk->debug)
		printk("AX25: source address set to %s\n", ax2asc(&sk->protinfo.ax25->source_addr));

	if (addr_len == sizeof(struct full_sockaddr_ax25) && addr->fsa_ax25.sax25_ndigis == 1) {
		if (ax25cmp(&addr->fsa_digipeater[0], &null_ax25_address) == 0) {
			dev = NULL;
			if (sk->debug)
				printk("AX25: bound to any device\n");
		} else {
			if ((dev = ax25rtr_get_dev(&addr->fsa_digipeater[0])) == NULL) {
				if (sk->debug)
					printk("AX25: bind failed - no device\n");
				return -EADDRNOTAVAIL;
			}
			if (sk->debug)
				printk("AX25: bound to device %s\n", dev->name);
		}
	} else {
		if ((dev = ax25rtr_get_dev(&addr->fsa_ax25.sax25_call)) == NULL) {
			if (sk->debug)
				printk("AX25: bind failed - no device\n");
			return -EADDRNOTAVAIL;
		}
		if (sk->debug)
			printk("AX25: bound to device %s\n", dev->name);
	}

	ax25_fillin_cb(sk->protinfo.ax25, dev);
	ax25_insert_socket(sk->protinfo.ax25);

	sk->zapped = 0;

	if (sk->debug)
		printk("AX25: socket is bound\n");

	return 0;
}

static int ax25_connect(struct socket *sock, struct sockaddr *uaddr,
	int addr_len, int flags)
{
	struct sock *sk = (struct sock *)sock->data;
	struct full_sockaddr_ax25 *fsa = (struct full_sockaddr_ax25 *)uaddr;
	ax25_digi *digi = NULL;
	int ct = 0, err;

	if (sk->state == TCP_ESTABLISHED && sock->state == SS_CONNECTING) {
		sock->state = SS_CONNECTED;
		return 0;	/* Connect completed during a ERESTARTSYS event */
	}

	if (sk->state == TCP_CLOSE && sock->state == SS_CONNECTING) {
		sock->state = SS_UNCONNECTED;
		return -ECONNREFUSED;
	}

	if (sk->state == TCP_ESTABLISHED && sk->type == SOCK_SEQPACKET)
		return -EISCONN;	/* No reconnect on a seqpacket socket */

	sk->state   = TCP_CLOSE;
	sock->state = SS_UNCONNECTED;

	if (addr_len != sizeof(struct sockaddr_ax25) && addr_len != sizeof(struct full_sockaddr_ax25))
		return -EINVAL;

	if (fsa->fsa_ax25.sax25_family != AF_AX25)
		return -EINVAL;

	if (sk->protinfo.ax25->digipeat != NULL) {
		kfree_s(sk->protinfo.ax25->digipeat, sizeof(ax25_digi));
		sk->protinfo.ax25->digipeat = NULL;
	}

	/*
	 *	Handle digi-peaters to be used.
	 */
	if (addr_len == sizeof(struct full_sockaddr_ax25) && fsa->fsa_ax25.sax25_ndigis != 0) {
		/* Valid number of digipeaters ? */
		if (fsa->fsa_ax25.sax25_ndigis < 1 || fsa->fsa_ax25.sax25_ndigis > AX25_MAX_DIGIS)
			return -EINVAL;

		if ((digi = (ax25_digi *)kmalloc(sizeof(ax25_digi), GFP_KERNEL)) == NULL)
			return -ENOBUFS;

		digi->ndigi      = fsa->fsa_ax25.sax25_ndigis;
		digi->lastrepeat = -1;

		while (ct < fsa->fsa_ax25.sax25_ndigis) {
			if ((fsa->fsa_digipeater[ct].ax25_call[6] & AX25_HBIT) && sk->protinfo.ax25->iamdigi) {
				digi->repeated[ct] = 1;
				digi->lastrepeat   = ct;
			} else {
				digi->repeated[ct] = 0;
			}
			digi->calls[ct] = fsa->fsa_digipeater[ct];
			ct++;
		}
	}

	/*
	 *	Must bind first - autobinding in this may or may not work. If
	 *	the socket is already bound, check to see if the device has
	 *	been filled in, error if it hasn't.
	 */
	if (sk->zapped) {
		if ((err = ax25_rt_autobind(sk->protinfo.ax25, &fsa->fsa_ax25.sax25_call)) < 0)
			return err;
		ax25_fillin_cb(sk->protinfo.ax25, sk->protinfo.ax25->device);
		ax25_insert_socket(sk->protinfo.ax25);
	} else {
		if (sk->protinfo.ax25->device == NULL)
			return -EHOSTUNREACH;
	}

	if (sk->type == SOCK_SEQPACKET && ax25_find_cb(&sk->protinfo.ax25->source_addr, &fsa->fsa_ax25.sax25_call, digi, sk->protinfo.ax25->device) != NULL) {
		if (digi != NULL) kfree_s(digi, sizeof(ax25_digi));
		return -EADDRINUSE;			/* Already such a connection */
	}

	sk->protinfo.ax25->dest_addr = fsa->fsa_ax25.sax25_call;
	sk->protinfo.ax25->digipeat  = digi;

	/* First the easy one */
	if (sk->type != SOCK_SEQPACKET) {
		sock->state = SS_CONNECTED;
		sk->state   = TCP_ESTABLISHED;
		return 0;
	}

	/* Move to connecting socket, ax.25 lapb WAIT_UA.. */
	sock->state        = SS_CONNECTING;
	sk->state          = TCP_SYN_SENT;

	if (ax25_dev_is_dama_slave(sk->protinfo.ax25->device))
		dama_establish_data_link(sk->protinfo.ax25);
	else
		ax25_establish_data_link(sk->protinfo.ax25);

	sk->protinfo.ax25->state = AX25_STATE_1;
	ax25_set_timer(sk->protinfo.ax25);		/* Start going SABM SABM until a UA or a give up and DM */

	/* Now the loop */
	if (sk->state != TCP_ESTABLISHED && (flags & O_NONBLOCK))
		return -EINPROGRESS;

	cli();	/* To avoid races on the sleep */

	/* A DM or timeout will go to closed, a UA will go to ABM */
	while (sk->state == TCP_SYN_SENT) {
		interruptible_sleep_on(sk->sleep);
		if (current->signal & ~current->blocked) {
			sti();
			return -ERESTARTSYS;
		}
	}

	if (sk->state != TCP_ESTABLISHED) {
		/* Not in ABM, not in WAIT_UA -> failed */
		sti();
		sock->state = SS_UNCONNECTED;
		return sock_error(sk);	/* Always set at this point */
	}

	sock->state = SS_CONNECTED;

	sti();

	return 0;
}

static int ax25_socketpair(struct socket *sock1, struct socket *sock2)
{
	return -EOPNOTSUPP;
}

static int ax25_accept(struct socket *sock, struct socket *newsock, int flags)
{
	struct sock *sk;
	struct sock *newsk;
	struct sk_buff *skb;

	if (newsock->data != NULL) {
		sk = (struct sock *)newsock->data;
		ax25_destroy_socket(sk->protinfo.ax25);
	}

	newsock->data = NULL;

	if ((sk = (struct sock *)sock->data) == NULL)
		return -EINVAL;

	if (sk->type != SOCK_SEQPACKET)
		return -EOPNOTSUPP;

	if (sk->state != TCP_LISTEN)
		return -EINVAL;

	/*
	 *	The write queue this time is holding sockets ready to use
	 *	hooked into the SABM we saved
	 */
	do {
		cli();
		if ((skb = skb_dequeue(&sk->receive_queue)) == NULL) {
			if (flags & O_NONBLOCK) {
				sti();
				return -EWOULDBLOCK;
			}
			interruptible_sleep_on(sk->sleep);
			if (current->signal & ~current->blocked) {
				sti();
				return -ERESTARTSYS;
			}
		}
	} while (skb == NULL);

	newsk = skb->sk;
	newsk->pair = NULL;
	newsk->socket = newsock;
	newsk->sleep = newsock->wait;
	sti();

	/* Now attach up the new socket */
	skb->sk = NULL;
	kfree_skb(skb, FREE_READ);
	sk->ack_backlog--;
	newsock->data = newsk;

	return 0;
}

static int ax25_getname(struct socket *sock, struct sockaddr *uaddr,
	int *uaddr_len, int peer)
{
	struct full_sockaddr_ax25 *sax = (struct full_sockaddr_ax25 *)uaddr;
	struct sock *sk = (struct sock *)sock->data;
	unsigned char ndigi, i;

	if (peer != 0) {
		if (sk->state != TCP_ESTABLISHED)
			return -ENOTCONN;

		sax->fsa_ax25.sax25_family = AF_AX25;
		sax->fsa_ax25.sax25_call   = sk->protinfo.ax25->dest_addr;
		sax->fsa_ax25.sax25_ndigis = 0;
		*uaddr_len = sizeof(struct full_sockaddr_ax25);

		if (sk->protinfo.ax25->digipeat != NULL) {
			ndigi = sk->protinfo.ax25->digipeat->ndigi;
			sax->fsa_ax25.sax25_ndigis = ndigi;
			for (i = 0; i < ndigi; i++)
				sax->fsa_digipeater[i] = sk->protinfo.ax25->digipeat->calls[i];
		}
	} else {
		sax->fsa_ax25.sax25_family = AF_AX25;
		sax->fsa_ax25.sax25_call   = sk->protinfo.ax25->source_addr;
		sax->fsa_ax25.sax25_ndigis = 1;
		*uaddr_len = sizeof(struct full_sockaddr_ax25);

		if (sk->protinfo.ax25->device != NULL)
			memcpy(&sax->fsa_digipeater[0], sk->protinfo.ax25->device->dev_addr, AX25_ADDR_LEN);
		else
			sax->fsa_digipeater[0] = null_ax25_address;
	}

	return 0;
}

static int ax25_rcv(struct sk_buff *skb, struct device *dev, ax25_address *dev_addr, struct packet_type *ptype)
{
	struct sock *make;
	struct sock *sk;
	int type = 0;
	ax25_digi dp, reverse_dp;
	struct sk_buff *skbn;
	ax25_cb *ax25;
	ax25_address src, dest;
	ax25_address *next_digi = NULL;
	struct sock *raw;
	int mine = 0;
	int dama;

	/*
	 *	Process the AX.25/LAPB frame.
	 */

	skb->h.raw = skb->data;

#ifdef CONFIG_FIREWALL
	if (call_in_firewall(PF_AX25, skb->dev, skb->h.raw, NULL) != FW_ACCEPT) {
		kfree_skb(skb, FREE_READ);
		return 0;
	}
#endif

	/*
	 *	Parse the address header.
	 */

	if (ax25_parse_addr(skb->data, skb->len, &src, &dest, &dp, &type, &dama) == NULL) {
		kfree_skb(skb, FREE_READ);
		return 0;
	}

	/*
	 *	Ours perhaps ?
	 */
	if (dp.lastrepeat + 1 < dp.ndigi)		/* Not yet digipeated completely */
		next_digi = &dp.calls[dp.lastrepeat + 1];

	/*
	 *	Pull of the AX.25 headers leaving the CTRL/PID bytes
	 */
	skb_pull(skb, size_ax25_addr(&dp));

	/* For our port addresses ? */
	if (ax25cmp(&dest, dev_addr) == 0 && dp.lastrepeat + 1 == dp.ndigi)
		mine = 1;

	/* Also match on any registered callsign from L3/4 */
	if (!mine && ax25_listen_mine(&dest, dev) && dp.lastrepeat + 1 == dp.ndigi)
		mine = 1;

	/* UI frame - bypass LAPB processing */
	if ((*skb->data & ~0x10) == AX25_UI && dp.lastrepeat + 1 == dp.ndigi) {
		skb->h.raw = skb->data + 2;		/* skip control and pid */

		if ((raw = ax25_addr_match(&dest)) != NULL)
			ax25_send_to_raw(raw, skb, skb->data[1]);

		if (!mine && ax25cmp(&dest, (ax25_address *)dev->broadcast) != 0) {
			kfree_skb(skb, FREE_READ);
			return 0;
		}

		/* Now we are pointing at the pid byte */
		switch (skb->data[1]) {
#ifdef CONFIG_INET
			case AX25_P_IP:
				if ((skbn = skb_copy(skb, GFP_ATOMIC)) != NULL) {
					kfree_skb(skb, FREE_READ);
					skb = skbn;
				}
				skb_pull(skb,2);		/* drop PID/CTRL */
				ip_rcv(skb, dev, ptype);	/* Note ptype here is the wrong one, fix me later */
				break;

			case AX25_P_ARP:
				skb_pull(skb,2);
				arp_rcv(skb, dev, ptype);	/* Note ptype here is wrong... */
				break;
#endif
			case AX25_P_TEXT:
				/* Now find a suitable dgram socket */
				if ((sk = ax25_find_socket(&dest, &src, SOCK_DGRAM)) != NULL) {
					if (sk->rmem_alloc >= sk->rcvbuf) {
						kfree_skb(skb, FREE_READ);
					} else {
						/*
						 *	Remove the control and PID.
						 */
						skb_pull(skb, 2);
						if (sock_queue_rcv_skb(sk, skb) != 0)
							kfree_skb(skb, FREE_READ);
					}
				} else {
					kfree_skb(skb, FREE_READ);
				}
				break;

			default:
				kfree_skb(skb, FREE_READ);	/* Will scan SOCK_AX25 RAW sockets */
				break;
		}

		return 0;
	}

	/*
	 *	Is connected mode supported on this device ?
	 *	If not, should we DM the incoming frame (except DMs) or
	 *	silently ignore them. For now we stay quiet.
	 */
	if (ax25_dev_get_value(dev, AX25_VALUES_CONMODE) == 0) {
		kfree_skb(skb, FREE_READ);
		return 0;
	}

	/* LAPB */

	/* AX.25 state 1-4 */

	ax25_digi_invert(&dp, &reverse_dp);

	if ((ax25 = ax25_find_cb(&dest, &src, &reverse_dp, dev)) != NULL) {
		/*
		 *	Process the frame. If it is queued up internally it returns one otherwise we
		 *	free it immediately. This routine itself wakes the user context layers so we
		 *	do no further work
		 */
		if (ax25_process_rx_frame(ax25, skb, type, dama) == 0)
			kfree_skb(skb, FREE_READ);

		return 0;
	}

	/* AX.25 state 0 (disconnected) */

	/* a) received not a SABM(E) */

	if ((*skb->data & ~AX25_PF) != AX25_SABM && (*skb->data & ~AX25_PF) != AX25_SABME) {
		/*
		 *	Never reply to a DM. Also ignore any connects for
		 *	addresses that are not our interfaces and not a socket.
		 */
		if ((*skb->data & ~AX25_PF) != AX25_DM && mine)
			ax25_return_dm(dev, &src, &dest, &dp);

		kfree_skb(skb, FREE_READ);
		return 0;
	}

	/* b) received SABM(E) */

	if (dp.lastrepeat + 1 == dp.ndigi)
		sk = ax25_find_listener(&dest, 0, dev, SOCK_SEQPACKET);
	else
		sk = ax25_find_listener(next_digi, 1, dev, SOCK_SEQPACKET);

	if (sk != NULL) {
		if (sk->ack_backlog == sk->max_ack_backlog || (make = ax25_make_new(sk, dev)) == NULL) {
			if (mine)
				ax25_return_dm(dev, &src, &dest, &dp);

			kfree_skb(skb, FREE_READ);
			return 0;
		}

		ax25 = make->protinfo.ax25;

		skb_queue_head(&sk->receive_queue, skb);

		skb->sk     = make;
		make->state = TCP_ESTABLISHED;
		make->pair  = sk;

		sk->ack_backlog++;
	} else {
		if (!mine) {
			kfree_skb(skb, FREE_READ);
			return 0;
		}

		if ((ax25 = ax25_create_cb()) == NULL) {
			ax25_return_dm(dev, &src, &dest, &dp);
			kfree_skb(skb, FREE_READ);
			return 0;
		}

		ax25_fillin_cb(ax25, dev);
	}

	ax25->source_addr = dest;
	ax25->dest_addr   = src;

	/*
	 *	Sort out any digipeated paths.
	 */
	if (dp.ndigi != 0 && ax25->digipeat == NULL && (ax25->digipeat = kmalloc(sizeof(ax25_digi), GFP_ATOMIC)) == NULL) {
		kfree_skb(skb, FREE_READ);
		ax25_destroy_socket(ax25);
		return 0;
	}

	if (dp.ndigi == 0) {
		if (ax25->digipeat != NULL) {
			kfree_s(ax25->digipeat, sizeof(ax25_digi));
			ax25->digipeat = NULL;
		}
	} else {
		/* Reverse the source SABM's path */
		*ax25->digipeat = reverse_dp;
	}

	if ((*skb->data & ~AX25_PF) == AX25_SABME) {
		ax25->modulus = AX25_EMODULUS;
		ax25->window  = ax25_dev_get_value(dev, AX25_VALUES_EWINDOW);
	} else {
		ax25->modulus = AX25_MODULUS;
		ax25->window  = ax25_dev_get_value(dev, AX25_VALUES_WINDOW);
	}

	ax25->device = dev;

	ax25_send_control(ax25, AX25_UA, AX25_POLLON, AX25_RESPONSE);

	if (dama) ax25_dama_on(ax25);	/* bke 951121 */

	ax25->dama_slave = dama;
	ax25->t3timer    = ax25->t3;
	ax25->idletimer  = ax25->idle;

	ax25->state   = AX25_STATE_3;

	ax25_insert_socket(ax25);

	ax25_set_timer(ax25);

	if (sk != NULL) {
		if (!sk->dead)
			sk->data_ready(sk, skb->len);
	} else {
		kfree_skb(skb, FREE_READ);
	}

	return 0;
}

/*
 *	Receive an AX.25 frame via a SLIP interface.
 */
static int kiss_rcv(struct sk_buff *skb, struct device *dev, struct packet_type *ptype)
{
	skb->sk = NULL;		/* Initially we don't know who it's for */

	if ((*skb->data & 0x0F) != 0) {
		kfree_skb(skb, FREE_READ);	/* Not a KISS data frame */
		return 0;
	}

	skb_pull(skb, AX25_KISS_HEADER_LEN);	/* Remove the KISS byte */

	return ax25_rcv(skb, dev, (ax25_address *)dev->dev_addr, ptype);
}


static int ax25_sendmsg(struct socket *sock, struct msghdr *msg, int len, int noblock, int flags)
{
	struct sock *sk = (struct sock *)sock->data;
	struct sockaddr_ax25 *usax = (struct sockaddr_ax25 *)msg->msg_name;
	int err;
	struct sockaddr_ax25 sax;
	struct sk_buff *skb;
	unsigned char *asmptr;
	int size;
	ax25_digi *dp;
	ax25_digi dtmp;
	int lv;
	int addr_len = msg->msg_namelen;

	if (sk->err)
		return sock_error(sk);

	if (flags || msg->msg_control)
		return -EINVAL;

	if (sk->zapped)
		return -EADDRNOTAVAIL;

	if (sk->shutdown & SEND_SHUTDOWN) {
		send_sig(SIGPIPE, current, 0);
		return -EPIPE;
	}

	if (sk->protinfo.ax25->device == NULL)
		return -ENETUNREACH;

	if (usax != NULL) {
		if (addr_len != sizeof(struct sockaddr_ax25) && addr_len != sizeof(struct full_sockaddr_ax25))
			return -EINVAL;
		if (usax->sax25_family != AF_AX25)
			return -EINVAL;
		if (addr_len == sizeof(struct full_sockaddr_ax25) && usax->sax25_ndigis != 0) {
			int ct           = 0;
			struct full_sockaddr_ax25 *fsa = (struct full_sockaddr_ax25 *)usax;

			/* Valid number of digipeaters ? */
			if (usax->sax25_ndigis < 1 || usax->sax25_ndigis > AX25_MAX_DIGIS)
				return -EINVAL;

			dtmp.ndigi      = usax->sax25_ndigis;

			while (ct < usax->sax25_ndigis) {
				dtmp.repeated[ct] = 0;
				dtmp.calls[ct]    = fsa->fsa_digipeater[ct];
				ct++;
			}

			dtmp.lastrepeat = 0;
		}

		sax = *usax;
		if (sk->type == SOCK_SEQPACKET && ax25cmp(&sk->protinfo.ax25->dest_addr, &sax.sax25_call) != 0)
			return -EISCONN;
		if (usax->sax25_ndigis == 0)
			dp = NULL;
		else
			dp = &dtmp;
	} else {
		if (sk->state != TCP_ESTABLISHED)
			return -ENOTCONN;
		sax.sax25_family = AF_AX25;
		sax.sax25_call   = sk->protinfo.ax25->dest_addr;
		dp = sk->protinfo.ax25->digipeat;
	}

	if (sk->debug)
		printk("AX.25: sendto: Addresses built.\n");

	/* Build a packet */
	if (sk->debug)
		printk("AX.25: sendto: building packet.\n");

	/* Assume the worst case */
	size = len + 3 + size_ax25_addr(dp) + AX25_BPQ_HEADER_LEN;

	if ((skb = sock_alloc_send_skb(sk, size, 0, 0, &err)) == NULL)
		return err;

	skb->sk   = sk;
	skb->free = 1;

	skb_reserve(skb, size - len);

	if (sk->debug)
		printk("AX.25: Appending user data\n");

	/* User data follows immediately after the AX.25 data */
	memcpy_fromiovec(skb_put(skb, len), msg->msg_iov, len);

	/* Add the PID if one is not supplied by the user in the skb */
	if (!sk->protinfo.ax25->pidincl) {
		asmptr  = skb_push(skb, 1);
		*asmptr = sk->protocol;
	}

	if (sk->debug)
		printk("AX.25: Transmitting buffer\n");

	if (sk->type == SOCK_SEQPACKET) {
		/* Connected mode sockets go via the LAPB machine */
		if (sk->state != TCP_ESTABLISHED) {
			kfree_skb(skb, FREE_WRITE);
			return -ENOTCONN;
		}

		ax25_output(sk->protinfo.ax25, sk->protinfo.ax25->paclen, skb);	/* Shove it onto the queue and kick */

		return len;
	} else {
		asmptr = skb_push(skb, 1 + size_ax25_addr(dp));

		if (sk->debug) {
			printk("Building AX.25 Header (dp=%p).\n", dp);
			if (dp != 0)
				printk("Num digipeaters=%d\n", dp->ndigi);
		}

		/* Build an AX.25 header */
		asmptr += (lv = build_ax25_addr(asmptr, &sk->protinfo.ax25->source_addr, &sax.sax25_call, dp, AX25_COMMAND, AX25_MODULUS));

		if (sk->debug)
			printk("Built header (%d bytes)\n",lv);

		skb->h.raw = asmptr;

		if (sk->debug)
			printk("base=%p pos=%p\n", skb->data, asmptr);

		*asmptr = AX25_UI;

		/* Datagram frames go straight out of the door as UI */
		ax25_queue_xmit(skb, sk->protinfo.ax25->device, SOPRI_NORMAL);

		return len;
	}
}

static int ax25_recvmsg(struct socket *sock, struct msghdr *msg, int size, int noblock, int flags, int *addr_len)
{
	struct sock *sk = (struct sock *)sock->data;
	struct sockaddr_ax25 *sax = (struct sockaddr_ax25 *)msg->msg_name;
	int copied;
	struct sk_buff *skb;
	int er;

	if (sk->err)
		return sock_error(sk);

	if (addr_len != NULL)
		*addr_len = sizeof(*sax);

	/*
	 * 	This works for seqpacket too. The receiver has ordered the
	 *	queue for us! We do one quick check first though
	 */
	if (sk->type == SOCK_SEQPACKET && sk->state != TCP_ESTABLISHED)
		return -ENOTCONN;

	/* Now we can treat all alike */
	if ((skb = skb_recv_datagram(sk, flags, noblock, &er)) == NULL)
		return er;

	if (!sk->protinfo.ax25->pidincl)
		skb_pull(skb, 1);		/* Remove PID */

	skb->h.raw = skb->data;

	copied = (size < skb->len) ? size : skb->len;
	skb_copy_datagram_iovec(skb, 0, msg->msg_iov, copied);
	
	if (sax != NULL) {
		ax25_digi digi;
		ax25_address dest;
		int dama;

		if (addr_len == NULL)
			return -EINVAL;
		if (*addr_len != sizeof(struct sockaddr_ax25) && *addr_len != sizeof(struct full_sockaddr_ax25))
			return -EINVAL;

		ax25_parse_addr(skb->data, skb->len, NULL, &dest, &digi, NULL, &dama);

		sax->sax25_family = AF_AX25;
		/* We set this correctly, even though we may not let the
		   application know the digi calls further down (because it
		   did NOT ask to know them).  This could get political... **/
		sax->sax25_ndigis = digi.ndigi;
		sax->sax25_call   = dest;

		*addr_len = sizeof(struct sockaddr_ax25);

		if (*addr_len == sizeof(struct full_sockaddr_ax25) && sax->sax25_ndigis != 0) {
			int ct           = 0;
			struct full_sockaddr_ax25 *fsa = (struct full_sockaddr_ax25 *)sax;

			while (ct < digi.ndigi) {
				fsa->fsa_digipeater[ct] = digi.calls[ct];
				ct++;
			}

			*addr_len = sizeof(struct full_sockaddr_ax25);
		}
	}

	skb_free_datagram(sk, skb);

	return copied;
}

static int ax25_shutdown(struct socket *sk, int how)
{
	/* FIXME - generate DM and RNR states */
	return -EOPNOTSUPP;
}

static int ax25_select(struct socket *sock , int sel_type, select_table *wait)
{
	struct sock *sk = (struct sock *)sock->data;

	return datagram_select(sk, sel_type, wait);
}

static int ax25_ioctl(struct socket *sock, unsigned int cmd, unsigned long arg)
{
	struct sock *sk = (struct sock *)sock->data;
	int err;

	switch (cmd) {
		case TIOCOUTQ: {
			long amount;
			if ((err = verify_area(VERIFY_WRITE, (void *)arg, sizeof(int))) != 0)
				return err;
			amount = sk->sndbuf - sk->wmem_alloc;
			if (amount < 0)
				amount = 0;
			put_fs_long(amount, (int *)arg);
			return 0;
		}

		case TIOCINQ: {
			struct sk_buff *skb;
			long amount = 0L;
			/* These two are safe on a single CPU system as only user tasks fiddle here */
			if ((skb = skb_peek(&sk->receive_queue)) != NULL)
				amount = skb->len;
			if ((err = verify_area(VERIFY_WRITE, (void *)arg, sizeof(int))) != 0)
				return err;
			put_fs_long(amount, (int *)arg);
			return 0;
		}

		case SIOCGSTAMP:
			if (sk != NULL) {
				if (sk->stamp.tv_sec == 0)
					return -ENOENT;
				if ((err = verify_area(VERIFY_WRITE, (void *)arg, sizeof(struct timeval))) != 0)
					return err;
				memcpy_tofs((void *)arg, &sk->stamp, sizeof(struct timeval));
				return 0;
			}
			return -EINVAL;

		case SIOCAX25ADDUID:	/* Add a uid to the uid/call map table */
		case SIOCAX25DELUID:	/* Delete a uid from the uid/call map table */
		case SIOCAX25GETUID: {
			struct sockaddr_ax25 sax25;
			if ((err = verify_area(VERIFY_READ, (void *)arg, sizeof(struct sockaddr_ax25))) != 0)
				return err;
			memcpy_fromfs(&sax25, (void *)arg, sizeof(sax25));
			return ax25_uid_ioctl(cmd, &sax25);
		}

		case SIOCAX25NOUID: {	/* Set the default policy (default/bar) */
			long amount;
			if ((err = verify_area(VERIFY_READ, (void *)arg, sizeof(unsigned long))) != 0)
				return err;
			if (!suser())
				return -EPERM;
			amount = get_fs_long((void *)arg);
			if (amount > AX25_NOUID_BLOCK)
				return -EINVAL;
			ax25_uid_policy = amount;
			return 0;
		}

		case SIOCADDRT:
		case SIOCDELRT:
		case SIOCAX25OPTRT:
			if (!suser())
				return -EPERM;
			return ax25_rt_ioctl(cmd, (void *)arg);

		case SIOCAX25CTLCON:
			if (!suser())
				return -EPERM;
			return ax25_ctl_ioctl(cmd, (void *)arg);

		case SIOCAX25GETINFO: {
			struct ax25_info_struct ax25_info;
			if ((err = verify_area(VERIFY_WRITE, (void *)arg, sizeof(ax25_info))) != 0)
				return err;
			ax25_info.t1        = sk->protinfo.ax25->t1   / AX25_SLOWHZ;
			ax25_info.t2        = sk->protinfo.ax25->t2   / AX25_SLOWHZ;
			ax25_info.t3        = sk->protinfo.ax25->t3   / AX25_SLOWHZ;
			ax25_info.idle      = sk->protinfo.ax25->idle / (60 * AX25_SLOWHZ);
			ax25_info.n2        = sk->protinfo.ax25->n2;
			ax25_info.t1timer   = sk->protinfo.ax25->t1timer   / AX25_SLOWHZ;
			ax25_info.t2timer   = sk->protinfo.ax25->t2timer   / AX25_SLOWHZ;
			ax25_info.t3timer   = sk->protinfo.ax25->t3timer   / AX25_SLOWHZ;
			ax25_info.idletimer = sk->protinfo.ax25->idletimer / (60 * AX25_SLOWHZ);
			ax25_info.n2count   = sk->protinfo.ax25->n2count;
			ax25_info.state     = sk->protinfo.ax25->state;
			ax25_info.rcv_q     = sk->rmem_alloc;
			ax25_info.snd_q     = sk->wmem_alloc;
			memcpy_tofs((void *)arg, &ax25_info, sizeof(ax25_info));
			return 0;
		}

		case SIOCAX25ADDFWD:
		case SIOCAX25DELFWD: {
			struct ax25_fwd_struct ax25_fwd;
			if (!suser())
				return -EPERM;
			if ((err = verify_area(VERIFY_READ, (void *)arg, sizeof(ax25_fwd))) != 0)
				return err;
			memcpy_fromfs(&ax25_fwd, (void *)arg, sizeof(ax25_fwd));
			return ax25_fwd_ioctl(cmd, &ax25_fwd);
		}

		case SIOCGIFADDR:
		case SIOCSIFADDR:
		case SIOCGIFDSTADDR:
		case SIOCSIFDSTADDR:
		case SIOCGIFBRDADDR:
		case SIOCSIFBRDADDR:
		case SIOCGIFNETMASK:
		case SIOCSIFNETMASK:
		case SIOCGIFMETRIC:
		case SIOCSIFMETRIC:
			return -EINVAL;

		default:
			return dev_ioctl(cmd, (void *)arg);
	}

	/*NOTREACHED*/
	return 0;
}


static int ax25_get_info(char *buffer, char **start, off_t offset, int length, int dummy)
{
	ax25_cb *ax25;
	struct device *dev;
	const char *devname;
	char callbuf[15];
	int len = 0;
	off_t pos = 0;
	off_t begin = 0;

	cli();

	len += sprintf(buffer, "dest_addr src_addr   dev  st  vs  vr  va    t1     t2     t3      idle   n2  rtt wnd paclen Snd-Q Rcv-Q Inode\n");

	for (ax25 = ax25_list; ax25 != NULL; ax25 = ax25->next) {
		if ((dev = ax25->device) == NULL)
			devname = "???";
		else
			devname = dev->name;

		len += sprintf(buffer + len, "%-9s ",
			ax2asc(&ax25->dest_addr));

		sprintf(callbuf, "%s%c", ax2asc(&ax25->source_addr),
					 (ax25->iamdigi) ? '*' : ' ');

		len += sprintf(buffer + len, "%-10s %-4s %2d %3d %3d %3d %3d/%03d %2d/%02d %3d/%03d %3d/%03d %2d/%02d %3d %3d  %5d",
			callbuf, devname,
			ax25->state,
			ax25->vs, ax25->vr, ax25->va,
			ax25->t1timer / AX25_SLOWHZ,
			ax25->t1      / AX25_SLOWHZ,
			ax25->t2timer / AX25_SLOWHZ,
			ax25->t2      / AX25_SLOWHZ,
			ax25->t3timer / AX25_SLOWHZ,
			ax25->t3      / AX25_SLOWHZ,
			ax25->idletimer / (AX25_SLOWHZ * 60),
			ax25->idle      / (AX25_SLOWHZ * 60),
			ax25->n2count, ax25->n2,
			ax25->rtt     / AX25_SLOWHZ,
			ax25->window,
			ax25->paclen);

		if (ax25->sk != NULL) {
			struct sock *s = ax25->sk;

			len += sprintf(buffer + len, " %5d %5d %ld\n",
				s->wmem_alloc,
				s->rmem_alloc,
				s->socket && SOCK_INODE(s->socket) ?
				SOCK_INODE(s->socket)->i_ino : 0);
		} else {
			len += sprintf(buffer + len, "\n");
		}

		pos = begin + len;

		if (pos < offset) {
			len   = 0;
			begin = pos;
		}

		if (pos > offset + length)
			break;
	}

	sti();

	*start = buffer + (offset - begin);
	len   -= (offset - begin);

	if (len > length) len = length;

	return(len);
} 

static struct proto_ops ax25_proto_ops = {
	AF_AX25,

	ax25_create,
	ax25_dup,
	ax25_release,
	ax25_bind,
	ax25_connect,
	ax25_socketpair,
	ax25_accept,
	ax25_getname,
	ax25_select,
	ax25_ioctl,
	ax25_listen,
	ax25_shutdown,
	ax25_setsockopt,
	ax25_getsockopt,
	ax25_fcntl,
	ax25_sendmsg,
	ax25_recvmsg
};

/*
 *	Called by socket.c on kernel start up
 */
static struct packet_type ax25_packet_type =
{
	0,	/* MUTTER ntohs(ETH_P_AX25),*/
	0,		/* copy */
	kiss_rcv,
	NULL,
	NULL,
};

static struct notifier_block ax25_dev_notifier = {
	ax25_device_event,
	0
};

#ifdef CONFIG_PROC_FS
static struct proc_dir_entry proc_ax25_route = {
	PROC_NET_AX25_ROUTE, 10, "ax25_route",
	S_IFREG | S_IRUGO, 1, 0, 0,
	0, &proc_net_inode_operations,
	ax25_rt_get_info
};
static struct proc_dir_entry proc_ax25 = {
	PROC_NET_AX25, 4, "ax25",
	S_IFREG | S_IRUGO, 1, 0, 0,
	0, &proc_net_inode_operations,
	ax25_get_info
};
static struct proc_dir_entry proc_ax25_calls = {
	PROC_NET_AX25_CALLS, 10, "ax25_calls",
	S_IFREG | S_IRUGO, 1, 0, 0,
	0, &proc_net_inode_operations,
	ax25_cs_get_info
};
#endif

static struct symbol_table ax25_syms = {
#include <linux/symtab_begin.h>
	X(ax25_encapsulate),
	X(ax25_rebuild_header),
	X(ax25_findbyuid),
	X(ax25_find_cb),
	X(ax25_linkfail_register),
	X(ax25_linkfail_release),
	X(ax25_listen_register),
	X(ax25_listen_release),
	X(ax25_protocol_register),
	X(ax25_protocol_release),
	X(ax25_send_frame),
	X(ax25_uid_policy),
	X(ax25cmp),
	X(ax2asc),
	X(asc2ax),
	X(null_ax25_address),
#include <linux/symtab_end.h>
};

void ax25_proto_init(struct net_proto *pro)
{
	sock_register(ax25_proto_ops.family, &ax25_proto_ops);
	ax25_packet_type.type = htons(ETH_P_AX25);
	dev_add_pack(&ax25_packet_type);
	register_netdevice_notifier(&ax25_dev_notifier);
	ax25_register_sysctl();
	register_symtab(&ax25_syms);

#ifdef CONFIG_PROC_FS
	proc_net_register(&proc_ax25_route);
	proc_net_register(&proc_ax25);
	proc_net_register(&proc_ax25_calls);
#endif

	printk(KERN_INFO "G4KLX/GW4PTS AX.25 for Linux. Version 0.35 for Linux NET3.035 (Linux 2.0)\n");
}

/*
 *	A small shim to dev_queue_xmit to add the KISS control byte, and do
 *	any packet forwarding in operation.
 */
void ax25_queue_xmit(struct sk_buff *skb, struct device *dev, int pri)
{
	unsigned char *ptr;

#ifdef CONFIG_FIREWALL
	if (call_out_firewall(PF_AX25, skb->dev, skb->data, NULL) != FW_ACCEPT) {
		dev_kfree_skb(skb, FREE_WRITE);
		return;
	}
#endif

	skb->protocol = htons(ETH_P_AX25);
	skb->dev      = ax25_fwd_dev(dev);
	skb->arp      = 1;

	ptr  = skb_push(skb, 1);
	*ptr = 0x00;			/* KISS */

	dev_queue_xmit(skb, skb->dev, pri);
}

/*
 *	IP over AX.25 encapsulation.
 */

/*
 *	Shove an AX.25 UI header on an IP packet and handle ARP
 */

#ifdef CONFIG_INET

int ax25_encapsulate(struct sk_buff *skb, struct device *dev, unsigned short type, void *daddr,
		void *saddr, unsigned len)
{
  	/* header is an AX.25 UI frame from us to them */
 	unsigned char *buff = skb_push(skb, AX25_HEADER_LEN);

  	*buff++ = 0;	/* KISS DATA */

	if (daddr != NULL)
		memcpy(buff, daddr, dev->addr_len);	/* Address specified */

  	buff[6] &= ~AX25_CBIT;
  	buff[6] &= ~AX25_EBIT;
  	buff[6] |= AX25_SSSID_SPARE;
  	buff += AX25_ADDR_LEN;

  	if (saddr != NULL)
  		memcpy(buff, saddr, dev->addr_len);
  	else
  		memcpy(buff, dev->dev_addr, dev->addr_len);

  	buff[6] &= ~AX25_CBIT;
  	buff[6] |= AX25_EBIT;
  	buff[6] |= AX25_SSSID_SPARE;
  	buff   += AX25_ADDR_LEN;

  	*buff++ = AX25_UI;	/* UI */

  	/* Append a suitable AX.25 PID */
  	switch (type) {
  		case ETH_P_IP:
  			*buff++ = AX25_P_IP;
 			break;
  		case ETH_P_ARP:
  			*buff++ = AX25_P_ARP;
  			break;
  		default:
  			printk(KERN_ERR "AX.25 wrong protocol type 0x%x2.2\n", type);
  			*buff++ = 0;
  			break;
 	}

	if (daddr != NULL)
	  	return AX25_HEADER_LEN;

	return -AX25_HEADER_LEN;	/* Unfinished header */
}

int ax25_rebuild_header(void *buf, struct device *dev, unsigned long dest, struct sk_buff *skb)
{
	struct sk_buff *ourskb;
	unsigned char *bp = (unsigned char *)buf;
	ax25_address *src, *dst;
	ax25_digi *digi;
	int mode;

	dst = (ax25_address *)(bp + 1);
	src = (ax25_address *)(bp + 8);

  	if (arp_find(bp + 1, dest, dev, dev->pa_addr, skb))
  		return 1;

	digi = ax25_rt_find_path(dst, dev);

	if (bp[16] == AX25_P_IP) {
		mode = ax25_rt_mode_get(dst, dev);

		if (mode == 'V' || (mode == ' ' && ax25_dev_get_value(dev, AX25_VALUES_IPDEFMODE))) {
			/*
			 *	We clone the buffer and release the original thereby
			 *	keeping it straight
			 *
			 *	Note: we report 1 back so the caller will
			 *	not feed the frame direct to the physical device
			 *	We don't want that to happen. (It won't be upset
			 *	as we have pulled the frame from the queue by
			 *	freeing it).
			 */
			if ((ourskb = skb_copy(skb, GFP_ATOMIC)) == NULL) {
				dev_kfree_skb(skb, FREE_WRITE);
				return 1;
			}

			ourskb->sk = skb->sk;

			if (ourskb->sk != NULL)
				atomic_add(ourskb->truesize, &ourskb->sk->wmem_alloc);

			dev_kfree_skb(skb, FREE_WRITE);

			skb_pull(ourskb, AX25_HEADER_LEN - 1);	/* Keep PID */

			ax25_send_frame(ourskb, ax25_dev_get_value(dev, AX25_VALUES_PACLEN), src, dst, digi, dev);

			return 1;
		}
	}

  	bp[7]  &= ~AX25_CBIT;
  	bp[7]  &= ~AX25_EBIT;
  	bp[7]  |= AX25_SSSID_SPARE;

  	bp[14] &= ~AX25_CBIT;
  	bp[14] |= AX25_EBIT;
  	bp[14] |= AX25_SSSID_SPARE;

	skb_pull(skb, AX25_KISS_HEADER_LEN);

	if (digi != NULL)
		ax25_rt_build_path(skb, src, dst, digi);

	ax25_queue_xmit(skb, dev, SOPRI_NORMAL);

  	return 1;
}

#endif

#ifdef MODULE
int init_module(void)
{
	ax25_proto_init(NULL);

	return 0;
}

void cleanup_module(void)
{
#ifdef CONFIG_PROC_FS
	proc_net_unregister(PROC_NET_AX25_ROUTE);
	proc_net_unregister(PROC_NET_AX25);
	proc_net_unregister(PROC_NET_AX25_CALLS);
	proc_net_unregister(PROC_NET_AX25_ROUTE);
#endif
	ax25_rt_free();

	ax25_unregister_sysctl();

	unregister_netdevice_notifier(&ax25_dev_notifier);

	ax25_packet_type.type = htons(ETH_P_AX25);
	dev_remove_pack(&ax25_packet_type);

	sock_unregister(AF_AX25);
}
#endif

#endif
