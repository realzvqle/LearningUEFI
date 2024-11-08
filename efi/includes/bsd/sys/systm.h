/*-
 * Copyright (c) 1982, 1988, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
 *
 * Portions copyright (c) 1999, 2000
 * Intel Corporation.
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 * 
 *    This product includes software developed by the University of
 *    California, Berkeley, Intel Corporation, and its contributors.
 * 
 * 4. Neither the name of University, Intel Corporation, or their respective
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS, INTEL CORPORATION AND
 * CONTRIBUTORS ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
 * BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS,
 * INTEL CORPORATION OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *	@(#)systm.h	8.7 (Berkeley) 3/29/95
 * $Id: systm.h,v 1.1.1.1 2006/05/30 06:13:01 hhzhou Exp $
 */

#ifndef _SYS_SYSTM_H_
#define	_SYS_SYSTM_H_

#include <machine/cpufunc.h>
#include <sys/callout.h>

extern int securelevel;		/* system security level (see init(8)) */

extern int cold;		/* nonzero if we are doing a cold boot */
extern const char *panicstr;	/* panic message */
extern int safepri;		/* safe ipl when cold or panicing */
extern char version[];		/* system version */
extern char copyright[];	/* system copyright */

extern int nblkdev;		/* number of entries in bdevsw */
extern int nchrdev;		/* number of entries in cdevsw */
extern int nswap;		/* size of swap space */

extern int selwait;		/* select timeout address */

extern u_char curpriority;	/* priority of current process */

extern int physmem;		/* physical memory */

extern dev_t dumpdev;		/* dump device */
extern long dumplo;		/* offset into dumpdev */

extern dev_t rootdev;		/* root device */
extern dev_t rootdevs[2];	/* possible root devices */
extern char *rootdevnames[2];	/* names of possible root devices */
extern struct vnode *rootvp;	/* vnode equivalent to above */

extern struct vnode *swapdev_vp;/* vnode for swap device */

extern int boothowto;		/* reboot flags, from console subsystem */
extern int bootverbose;		/* nonzero to print verbose messages */

#ifdef	INVARIANTS		/* The option is always available */
#define	KASSERT(exp,msg)	do { if (!(exp)) panic msg; } while (0)
#else
#define	KASSERT(exp,msg)
#endif

/*
 * General function declarations.
 */

struct clockframe;
struct malloc_type;
struct proc;
struct timeval;
struct tty;
struct uio;

void	Debugger __P((const char *msg));
int	nullop __P((void));
int	eopnotsupp __P((void));
int	einval __P((void));
int	seltrue __P((dev_t dev, int which, struct proc *p));
int	ureadc __P((int, struct uio *));
void	*hashinit __P((int count, struct malloc_type *type, u_long *hashmask));
void	*phashinit __P((int count, struct malloc_type *type, u_long *nentries));

void	panic __P((const char *, ...)) __dead2 __printflike(1, 2);
void	cpu_boot __P((int));
void	cpu_rootconf __P((void));
void	cpu_dumpconf __P((void));
void	tablefull __P((const char *));
int	addlog __P((const char *, ...)) __printflike(1, 2);
int	kvprintf __P((char const *, void (*)(int, void*), void *, int,
		      _BSD_VA_LIST_)) __printflike(1, 0);
#define log log_
void	log_ __P((int, const char *, ...)) __printflike(2, 3);
void	logwakeup __P((void));
int	printf __P((const char *, ...)) __printflike(1, 2);
int	snprintf __P((char *, size_t, const char *, ...)) __printflike(3, 4);
int	sprintf __P((char *buf, const char *, ...)) __printflike(2, 3);
void uprintf __P((const char *, ...)) __printflike(1, 2);
int	vprintf __P((const char *, _BSD_VA_LIST_)) __printflike(1, 0);
int	vsnprintf __P((char *, size_t, const char *, _BSD_VA_LIST_)) __printflike(3, 0);
int     vsprintf __P((char *buf, const char *, _BSD_VA_LIST_)) __printflike(2, 0);
void	ttyprintf __P((struct tty *, const char *, ...)) __printflike(2, 3);
int	sscanf __P((const char *, char const *, ...));
int	vsscanf __P((const char *, char const *, _BSD_VA_LIST_));
u_quad_t strtouq __P((const char *, char **, int));
quad_t	strtoq __P((const char *, char **, int base));

void	bcopy __P((const void *from, void *to, size_t len));
void	ovbcopy __P((const void *from, void *to, size_t len));
#ifdef __i386__
extern void	(*bzero) __P((void *buf, size_t len));
#else
void	bzero __P((void *buf, size_t len));
#endif

void	*memcpy __P((void *to, const void *from, size_t len));

int	copystr __P((const void *kfaddr, void *kdaddr, size_t len,
		size_t *lencopied));
int	copyinstr __P((const void *udaddr, void *kaddr, size_t len,
		size_t *lencopied));
int	copyin __P((const void *udaddr, void *kaddr, size_t len));
int	copyout __P((const void *kaddr, void *udaddr, size_t len));

int	fubyte __P((const void *base));
int	subyte __P((void *base, int byte));
int	suibyte __P((void *base, int byte));
long	fuword __P((const void *base));
int	suword __P((void *base, long word));
long	fusword __P((void *base));
int	susword __P((void *base, long word));

void	realitexpire __P((void *));

void	hardclock __P((struct clockframe *frame));
void	softclock __P((void));
void	statclock __P((struct clockframe *frame));

void	startprofclock __P((struct proc *));
void	stopprofclock __P((struct proc *));
void	setstatclockrate __P((int hzrate));

char	*getenv __P((char *name));
int	getenv_int __P((char *name, int *data));
extern char *kern_envp;

#ifdef APM_FIXUP_CALLTODO 
void	adjust_timeout_calltodo __P((struct timeval *time_change)); 
#endif /* APM_FIXUP_CALLTODO */ 

#include <sys/libkern.h>

/* Initialize the world */
void	consinit __P((void));
void	cpu_initclocks __P((void));
void	nchinit __P((void));
void	usrinfoinit __P((void));
void	vntblinit __P((void));

/* Finalize the world. */
void	shutdown_nice __P((void));

/*
 * Kernel to clock driver interface.
 */
void	inittodr __P((time_t base));
void	resettodr __P((void));
void	startrtclock __P((void));

/* Timeouts */
typedef void timeout_t __P((void *));	/* timeout function type */
#define CALLOUT_HANDLE_INITIALIZER(handle)	\
	{ NULL }

void	callout_handle_init __P((struct callout_handle *));
#ifdef _ORG_FREEBSD_
struct	callout_handle timeout __P((timeout_t *, void *, int));
#else
void	timeout __P((timeout_t *, void *, int));
#endif
void	untimeout __P((timeout_t *, void *, struct callout_handle));

/* Interrupt management */

#if defined(__i386__) || !defined(_ORG_FREEBSD_)
void		setdelayed __P((void));
void		setsoftast __P((void));
void		setsoftcambio __P((void));
void		setsoftcamnet __P((void));
void		setsoftclock __P((void));
void		setsoftnet __P((void));
void		setsofttty __P((void));
void		setsoftvm __P((void));
void		schedsoftcamnet __P((void));
void		schedsoftcambio __P((void));
void		schedsoftnet __P((void));
void		schedsofttty __P((void));
void		schedsoftvm __P((void));
intrmask_t	softclockpending __P((void));
void		spl0 __P((void));
intrmask_t	splbio __P((void));
intrmask_t	splcam __P((void));
intrmask_t	splclock __P((void));
intrmask_t	splhigh __P((void));
intrmask_t	splimp __P((void));
intrmask_t	splnet __P((void));
#ifdef SMP
intrmask_t	splq __P((intrmask_t mask));
#endif
intrmask_t	splsoftcam __P((void));
intrmask_t	splsoftcambio __P((void));
intrmask_t	splsoftcamnet __P((void));
intrmask_t	splsoftclock __P((void));
intrmask_t	splsofttty __P((void));
intrmask_t	splsoftvm __P((void));
intrmask_t	splstatclock __P((void));
intrmask_t	spltty __P((void));
intrmask_t	splvm __P((void));
void		splx __P((intrmask_t ipl));
void		splz __P((void));
#endif /* __i386__ */

#ifdef __alpha__
#include <machine/ipl.h>
#endif

/*
 * XXX It's not clear how "machine independent" these will be yet, but
 * they are used all over the place especially in pci drivers.  We would
 * have to modify lots of drivers since <machine/cpufunc.h> no longer
 * implicitly causes these to be defined when it #included <machine/spl.h>
 */
extern intrmask_t bio_imask;	/* group of interrupts masked with splbio() */
extern intrmask_t cam_imask;	/* group of interrupts masked with splcam() */
extern intrmask_t net_imask;	/* group of interrupts masked with splimp() */
extern intrmask_t stat_imask;	/* interrupts masked with splstatclock() */
extern intrmask_t tty_imask;	/* group of interrupts masked with spltty() */

/* Read only */
extern const intrmask_t soft_imask;    /* interrupts masked with splsoft*() */
extern const intrmask_t softnet_imask; /* interrupt masked with splnet() */
extern const intrmask_t softtty_imask; /* interrupt masked with splsofttty() */

/*
 * Various callout lists.
 */

/* Exit callout list declarations. */
typedef void (*exitlist_fn) __P((struct proc *procp));

int	at_exit __P((exitlist_fn function));
int	rm_at_exit __P((exitlist_fn function));

/* Fork callout list declarations. */
typedef void (*forklist_fn) __P((struct proc *parent, struct proc *child,
				 int flags));

int	at_fork __P((forklist_fn function));
int	rm_at_fork __P((forklist_fn function));

/* Shutdown callout list definitions and declarations. */
#define	SHUTDOWN_PRE_SYNC	0
#define	SHUTDOWN_POST_SYNC	1
#define	SHUTDOWN_FINAL		2
#define	SHUTDOWN_PRI_FIRST	0
#define	SHUTDOWN_PRI_DEFAULT	10000
#define	SHUTDOWN_PRI_LAST	20000

typedef void (*bootlist_fn) __P((int, void *));

int	at_shutdown __P((bootlist_fn function, void *arg, int position));
int	at_shutdown_pri __P((bootlist_fn function, void *arg, int position, int pri));
int	rm_at_shutdown __P((bootlist_fn function, void *arg));

/*
 * Not exactly a callout LIST, but a callout entry.
 * Allow an external module to define a hardware watchdog tickler.
 * Normally a process would do this, but there are times when the
 * kernel needs to be able to hold off the watchdog, when the process
 * is not active, e.g., when dumping core.
 */
typedef void (*watchdog_tickle_fn) __P((void));

extern watchdog_tickle_fn	wdog_tickler;

/* 
 * Common `proc' functions are declared here so that proc.h can be included
 * less often.
 */
int	tsleep __P((void *chan, int pri, const char *wmesg, int timo));
int	asleep __P((void *chan, int pri, const char *wmesg, int timo));
int	await  __P((int pri, int timo));
void	wakeup __P((void *chan));

#endif /* !_SYS_SYSTM_H_ */
