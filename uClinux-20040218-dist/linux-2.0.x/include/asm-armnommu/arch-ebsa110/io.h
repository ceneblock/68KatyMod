/*
 * linux/include/asm-arm/arch-ebsa/io.h
 *
 * Copyright (C) 1997 Russell King
 *
 * Modifications:
 *  06-Dec-1997	RMK	Created.
 */
#ifndef __ASM_ARM_ARCH_IO_H
#define __ASM_ARM_ARCH_IO_H

/*
 * This architecture does not require any delayed IO, and
 * has the constant-optimised IO
 */
#undef	ARCH_IO_DELAY

/*
 * We use two different types of addressing - PC style addresses, and ARM
 * addresses.  PC style accesses the PC hardware with the normal PC IO
 * addresses, eg 0x3f8 for serial#1.  ARM addresses are 0x80000000+
 * and are translated to the start of IO.  Note that all addresses are
 * shifted left!
 */
#define __PORT_PCIO(x)	(!((x) & 0x80000000))

/*
 * Dynamic IO functions - let the compiler
 * optimize the expressions
 */
#define DECLARE_DYN_OUT(fnsuffix,instr)						\
extern __inline__ void __out##fnsuffix (unsigned int value, unsigned int port)	\
{										\
	unsigned long temp;							\
	__asm__ __volatile__(							\
	"tst	%2, #0x80000000\n\t"						\
	"mov	%0, %4\n\t"							\
	"addeq	%0, %0, %3\n\t"							\
	"str" ##instr## "	%1, [%0, %2, lsl #2]"				\
	: "=&r" (temp)								\
	: "r" (value), "r" (port), "Ir" (PCIO_BASE - IO_BASE), "Ir" (IO_BASE)	\
	: "cc");								\
}

#define DECLARE_DYN_IN(sz,fnsuffix,instr)					\
extern __inline__ unsigned sz __in##fnsuffix (unsigned int port)		\
{										\
	unsigned long temp, value;						\
	__asm__ __volatile__(							\
	"tst	%2, #0x80000000\n\t"						\
	"mov	%0, %4\n\t"							\
	"addeq	%0, %0, %3\n\t"							\
	"ldr" ##instr## "	%1, [%0, %2, lsl #2]"				\
	: "=&r" (temp), "=r" (value)						\
	: "r" (port), "Ir" (PCIO_BASE - IO_BASE), "Ir" (IO_BASE)		\
	: "cc");								\
	return (unsigned sz)value;						\
}

extern __inline__ unsigned int __ioaddr (unsigned int port)			\
{										\
	if (__PORT_PCIO(port))							\
		return (unsigned int)(PCIO_BASE + (port << 2));			\
	else									\
		return (unsigned int)(IO_BASE + (port << 2));			\
}

#define DECLARE_IO(sz,fnsuffix,instr)	\
	DECLARE_DYN_OUT(fnsuffix,instr)	\
	DECLARE_DYN_IN(sz,fnsuffix,instr)

DECLARE_IO(char,b,"b")
DECLARE_IO(short,w,"")
DECLARE_IO(long,l,"")

#undef DECLARE_IO
#undef DECLARE_DYN_OUT
#undef DECLARE_DYN_IN

/*
 * Constant address IO functions
 *
 * These have to be macros for the 'J' constraint to work -
 * +/-4096 immediate operand.
 */
#define __outbc(value,port)							\
({										\
	if (__PORT_PCIO((port)))						\
		__asm__ __volatile__(						\
		"strb	%0, [%1, %2]"						\
		: : "r" (value), "r" (PCIO_BASE), "Jr" ((port) << 2));		\
	else									\
		__asm__ __volatile__(						\
		"strb	%0, [%1, %2]"						\
		: : "r" (value), "r" (IO_BASE), "r" ((port) << 2));		\
})

#define __inbc(port)								\
({										\
	unsigned char result;							\
	if (__PORT_PCIO((port)))						\
		__asm__ __volatile__(						\
		"ldrb	%0, [%1, %2]"						\
		: "=r" (result) : "r" (PCIO_BASE), "Jr" ((port) << 2));		\
	else									\
		__asm__ __volatile__(						\
		"ldrb	%0, [%1, %2]"						\
		: "=r" (result) : "r" (IO_BASE), "r" ((port) << 2));		\
	result;									\
})

#define __outwc(value,port)							\
({										\
	unsigned long v = value;						\
	if (__PORT_PCIO((port)))						\
		__asm__ __volatile__(						\
		"str	%0, [%1, %2]"						\
		: : "r" (v|v<<16), "r" (PCIO_BASE), "Jr" ((port) << 2));	\
	else									\
		__asm__ __volatile__(						\
		"str	%0, [%1, %2]"						\
		: : "r" (v|v<<16), "r" (IO_BASE), "r" ((port) << 2));		\
})

#define __inwc(port)								\
({										\
	unsigned short result;							\
	if (__PORT_PCIO((port)))						\
		__asm__ __volatile__(						\
		"ldr	%0, [%1, %2]"						\
		: "=r" (result) : "r" (PCIO_BASE), "Jr" ((port) << 2));		\
	else									\
		__asm__ __volatile__(						\
		"ldr	%0, [%1, %2]"						\
		: "=r" (result) : "r" (IO_BASE), "r" ((port) << 2));		\
	result & 0xffff;							\
})

#define __outlc(v,p) __outwc((v),(p))

#define __inlc(port)								\
({										\
	unsigned long result;							\
	if (__PORT_PCIO((port)))						\
		__asm__ __volatile__(						\
		"ldr	%0, [%1, %2]"						\
		: "=r" (result) : "r" (PCIO_BASE), "Jr" ((port) << 2));		\
	else									\
		__asm__ __volatile__(						\
		"ldr	%0, [%1, %2]"						\
		: "=r" (result) : "r" (IO_BASE), "r" ((port) << 2));		\
	result;									\
})

#define __ioaddrc(port)								\
({										\
	unsigned long addr;							\
	if (__PORT_PCIO((port)))						\
		addr = PCIO_BASE + ((port) << 2);				\
	else									\
		addr = IO_BASE + ((port) << 2);					\
	addr;									\
})

/*
 * Translated address IO functions
 *
 * IO address has already been translated to a virtual address
 */
#define outb_t(v,p)								\
	(*(volatile unsigned char *)(p) = (v))

#define inb_t(p)								\
	(*(volatile unsigned char *)(p))

#define outl_t(v,p)								\
	(*(volatile unsigned long *)(p) = (v))

#define inl_t(p)								\
	(*(volatile unsigned long *)(p))

#endif
