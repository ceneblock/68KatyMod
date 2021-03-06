/*
 * Machine dependent access functions for RTC registers.
 */
#ifndef _ASM_MC146818RTC_H
#define _ASM_MC146818RTC_H

#include <asm/arch/irqs.h>
#include <asm/io.h>

#ifndef RTC_PORT
#define RTC_PORT(x)	(0x70 + (x))
#define RTC_ALWAYS_BCD	1	/* RTC operates in binary mode */
#endif

/*
 * The yet supported machines all access the RTC index register via
 * an ISA port access but the way to access the date register differs ...
 */


#define CMOS_READ(addr) ({ \
outb_p((addr),RTC_PORT(0)); \
inb_p(RTC_PORT(1)); \
})
#define CMOS_WRITE(val, addr) ({ \
outb_p((addr),RTC_PORT(0)); \
outb_p((val),RTC_PORT(1)); \
})

#ifdef CONFIG_ARCH_RISCSTATION

/* RiscStation hardware has a lock to ensure random read/writes can't
 * do anything nasty to it
*/

#undef CMOS_READ
#undef CMOS_WRITE

#define CMOS_READ(addr) ({ \
outb_p((addr),RTC_PORT(0)); \
outb_p((addr),RTC_PORT(3)); \
inb_p(RTC_PORT(1)); \
})
#define CMOS_WRITE(val, addr) ({ \
outb_p((addr),RTC_PORT(0)); \
outb_p((addr),RTC_PORT(3)); \
outb_p((val),RTC_PORT(1)); \
})
#endif /* CONFIG_ARCH_RISCSTATION */

#endif /* _ASM_MC146818RTC_H */
