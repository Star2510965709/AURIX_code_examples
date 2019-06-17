/**
 * \file IfxCpu_IntrinsicsDcc.h
 * \version iLLD_1_0_1_9_0
 * \copyright Copyright (c) 2018 Infineon Technologies AG. All rights reserved.
 *
 *
 *
 *                                 IMPORTANT NOTICE
 *
 *
 * Infineon Technologies AG (Infineon) is supplying this file for use
 * exclusively with Infineon's microcontroller products. This file can be freely
 * distributed within development tools that are supporting such microcontroller
 * products.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 * \defgroup IfxLld_Cpu_Intrinsics_Dcc intrinsics for DCC compiler
 * \ingroup IfxLld_Cpu_Intrinsics
 *
 */
#ifndef IFXCPU_INTRINSICSDCC_H
#define IFXCPU_INTRINSICSDCC_H
/******************************************************************************/
#include "Ifx_Types.h"

/******************************************************************************/
/* *INDENT-OFF* */
/** \defgroup IfxLld_Cpu_Intrinsics_Dcc_min_smax Minimum and Maximum of (Short) Integers
 These intrinsic functions return the minimum or maximum of a signed integer, unsigned integer or short integer.
 * \ingroup IfxLld_Cpu_Intrinsics_Dcc
 * \{
 */

/** Function call without return
 */
asm volatile void Ifx__non_return_call(void (*fun)(void))
{
% reg fun
    ji fun
}

/** Jump and link
 */
asm volatile void Ifx__jump_and_link(void (*fun)(void))
{
% reg fun
    jli fun
}

/** \} */

asm volatile void Ifx__moveToDataParam0(unsigned int var)
{
% reg var
! "%d4"
	mov %d4, var
}

asm volatile void Ifx__moveToDataParamRet(unsigned int var)
{
% reg var
! "%d2"
	mov %d2, var
}

asm volatile unsigned int Ifx__getDataParamRet(void)
{
! "%d2"
	mov %d2, %d2
}

asm volatile void Ifx__moveToAddrParam0(const void *var)
{
% reg var
! "%a4"
	mov.aa %a4, var
}

IFX_INLINE void Ifx__jumpToFunction(const void *fun)
{
	Ifx__non_return_call((void (*)(void))fun);
}

IFX_INLINE void Ifx__jumpToFunctionWithLink(const void *fun)
{
	Ifx__jump_and_link((void (*)(void))fun);
}

asm volatile void Ifx__jumpBackToLink(void)
{
! "%a11"
	ji %a11
}

/** \defgroup IfxLld_Cpu_Intrinsics_Dcc_any_type Cross type arithmetic operation
 *
 * Macro compatible with float, fix point, signed integer and unsigned integer
 *
 * \ingroup IfxLld_Cpu_Intrinsics_Dcc
 * \{
 */
#define Ifx__minX(X,Y)                     ( ((X) < (Y)) ? (X) : (Y) )
#define Ifx__maxX(X,Y)                     ( ((X) > (Y)) ? (X) : (Y) )
#define Ifx__saturateX(X,Min,Max)          ( Ifx__minX(Ifx__maxX(X, Min), Max) )
#define Ifx__checkrangeX(X,Min,Max)        (((X) >= (Min)) && ((X) <= (Max)))

/** Return minimum of two integers
 */
extern sint32 __min( sint32,  sint32) __attribute__((intrinsic_pseudo(3, "min") ));

#define Ifx__min  __min

/** Return minimum of two short integers
 */
extern sint32 __mins( sint32,  sint32) __attribute__((intrinsic_function(0x10b, 0, "min.h") ));

#define Ifx__mins __mins

/** Return minimum of two unsigned integers
 */
extern uint32 __minu( uint32,  uint32) __attribute__((intrinsic_pseudo(3, "min.u") ));

#define Ifx__minu __minu

/** Return maximum of two integers
 */
extern sint32 __max( sint32,  sint32) __attribute__((intrinsic_pseudo(3, "max") ));

#define Ifx__max __max

/** Return maximum of two short integers
 */
extern uint32 __maxs( uint32,  uint32) __attribute__((intrinsic_function(0x10b, 0, "max.h") ));

#define Ifx__maxs __maxs

/** Return maximum of two unsigned integers
 */
extern uint32 __maxu( uint32,  uint32) __attribute__((intrinsic_pseudo(3, "max.u") ));

#define Ifx__maxu __maxu

/** \} */

/** \defgroup intrinsicstasking_float Floating point operation
 * \ingroup IfxLld_Cpu_Intrinsics_Dcc
 * \{
 */
#define Ifx__saturate(X,Min,Max)           ( __minf(__maxf(X, Min), Max) )

#define Ifx__sqrf(X)                       ((X) * (X))
#define Ifx__sqrtf(X)                      sqrtf(X)
#define Ifx__checkrange(X,Min,Max)         (((X) >= (Min)) && ((X) <= (Max)))

#define Ifx__roundf(X)                     ((((X) - (sint32)(X)) > 0.5) ? (1 + (sint32)(X)) : ((sint32)(X)))
#define Ifx__absf(X)                       ( ((X) < 0.0) ? -(X) : (X) )
#define Ifx__minf(X,Y)                     ( ((X) < (Y)) ? (X) : (Y) )
#define Ifx__maxf(X,Y)                     ( ((X) > (Y)) ? (X) : (Y) )
#define Ifx__saturatef(X,Min,Max)          ( __minf(__maxf(X, Min), Max) )
#define Ifx__checkrangef(X,Min,Max)        (((X) >= (Min)) && ((X) <= (Max)))

#define Ifx__abs_stdreal(X)                ( ((X) > 0.0) ? (X) : -(X) )
#define Ifx__min_stdreal(X,Y)              ( ((X) < (Y)) ? (X) : (Y) )
#define Ifx__max_stdreal(X,Y)              ( ((X) > (Y)) ? (X) : (Y) )
#define Ifx__saturate_stdreal(X,Min,Max)    ( Ifx__min_stdreal(Ifx__max_stdreal(X, Min), Max) )

#define Ifx__neqf(X,Y)                     ( ((X) > (Y)) ||  ((X) < (Y)) )     /**< X != Y */
#define Ifx__leqf(X,Y)                     ( !((X) > (Y)) )     /**< X <= Y */
#define Ifx__geqf(X,Y)                     ( !((X) < (Y)) )     /**< X >= Y */
/** \} */

/** \defgroup IfxLld_Cpu_Intrinsics_Dcc_fractional Fractional Arithmetic Support
 The next table provides an overview of intrinsic functions to convert fractional values. Note that the
 TASKING VX-toolset C compiler for TriCore fully supports the fractional type so normally you should not
 need these intrinsic functions (except for __mulfractlong). For compatibility reasons the TASKING C
 compiler does support these functions.
 * \ingroup IfxLld_Cpu_Intrinsics_Dcc
 * \{
 */

/** Count the consecutive number of bits that have the same value as bit 15 of an sfract
 */
asm short Ifx__clssf(sfract a)
{
% reg a
! "%d2"
    sh a,a,16
    cls  %d2, a
}

/** Convert float to fract
 */
asm fract Ifx__float_to_fract(float a)
{
% reg a
! "%d2", "%d3"
	mov    %d3, 0
	ftoq31 %d2, a, %d3
}

/** \brief Convert fract to float
 */
asm float Ifx__fract_to_float(fract a)
{
% reg a
! "%d2", "%d3"
    mov    %d3, 0
    q31tof %d2, a, %d3
}

/** Convert __laccum to fract
 */
asm fract Ifx__getfract(laccum a)
{
% reg a
! "%d2"
    dextr  %d2, a!H, a!L, 17
}

/** Multiply-add with rounding. Returns the rounded result of ( a + b * c )
 */
#ifdef INTRINSIC_WORKAROUND
extern sfract __mac_r_sf(sfract a, sfract b, sfract c);
#else
asm sfract Ifx__mac_r_sf(sfract a, sfract b, sfract c)
{
% reg a, b, c
! "%d2"
    maddrs.q %d2, a, bU, cU, 1
}
#endif

/** Multiply-add sfract. Returns ( a + b * c )
 */
#ifdef INTRINSIC_WORKAROUND
extern sfract __mac_sf(sfract a, sfract b, sfract c);
#else
asm sfract Ifx__mac_sf(sfract a, sfract b, sfract c)
{
% reg a, b, c
! "%d2"
    madds.q  %d2, a, bU, cU, 1
}
#endif

/** Integer part of the multiplication of a fract and a fract
 */
asm long Ifx__mulfractfract(fract a, fract b)
{
% reg a, b
! "%d2"
    mul.q %d2, a, b, 1
}

/** Integer part of the multiplication of a fract and a long
 */
asm long Ifx__mulfractlong(fract a, long b)
{
% reg a, b
! "%d2"
    mul.q %d2, a, b, 1
}

/** Convert fract to sfract
 */
asm sfract Ifx__round16(fract a)
{
% reg a
! "%d2"
    mov.u  %d2, 0x8000
    adds  %d2, a
	extr  %d2,%d2,0x10,0x10
}

#define Ifx__fract_to_sfract Ifx__round16

/** Convert float to sfract
 */
IFX_INLINE sfract __float_to_sfract(float a)
{
    fract tmp = Ifx__float_to_fract(a);
    return Ifx__fract_to_sfract(tmp);
}

/** Convert signed short to sfract
 */
asm sfract Ifx__s16_to_sfract(short a)
{
% reg a
! "%d2"
    sh  %d2, a, 16
	sh  %d2, %d2, -16
}

/** Convert sfract to signed short
 */
asm short Ifx__sfract_to_s16(sfract a)
{
% reg a
    sh  a, a, 16
    sh  %d2, a, -16
}

/** Convert sfract to uint16
 */
asm volatile uint16 Ifx__sfract_to_u16(sfract a)
{
% reg a
! "%d2"
    sh  a, a, 16
    sh  %d2, a, -16
}

/** Left/right shift of an __laccum
 */
asm laccum Ifx__shaaccum(laccum a, sint32 b)
{
% lab L0, L1; reg a, b
! "%d2", "%d3"
    jge   b, 0, L0
    sha   %d3, a!L, b
    rsub  b, b, 0
    dextr %d2, a!H, a!L, b
    j L1
L0:
    dextr %d2, a!H, a!L, b
    sha   %d2, a!L, b
L1:
}

/** Left/right shift of an fract
 */
#ifdef INTRINSIC_WORKAROUND
extern fract __shafracts(fract a, sint32 b);
#else
asm fract Ifx__shafracts(fract a, sint32 b)
{
% reg a, b
! "%d2"
    shas  %d2, a, b
}
#endif

/** Left/right shift of an sfract
 */
#ifdef INTRINSIC_WORKAROUND
extern sfract __shasfracts(sfract a, sint32 b);
#else
asm sfract Ifx__shasfracts(sfract a, sint32 b)
{
% reg a, b
! "%d2"
    shas %d2, a, b
}
#endif

/** Convert uint16 to sfract
 */
asm sfract Ifx__u16_to_sfract(uint16 a)
{
% reg a
! "%d2"
    sh  %d2, a, 16
    sh  %d2, %d2, -16
}

/** \} */

/** \defgroup IfxLld_Cpu_Intrinsics_Dcc_insert Insert / Extract Bit-fields and Bits
 * \ingroup IfxLld_Cpu_Intrinsics_Dcc
 * \{
 */

/** Extract a bit-field (bit pos to bit pos+width) from value
 */
extern sint32 __extr( sint32,  uint32,  const uint32) __attribute__((intrinsic_function(0x108, 0, "extr") ));

#define Ifx__extr __extr

/** Same as __extr() but return bit-field as unsigned integer
 */
extern uint32 __extru( uint32,  uint32,  const uint32) __attribute__((intrinsic_function(0x108, 0, "extr.u") ));

#define Ifx__extru __extru

/** Load a single bit.
 */
#define Ifx__getbit( address, bitoffset ) __extru( *(address), bitoffset, 1 )

/** Return trg but replace trgbit by srcbit in src.
 */
extern uint32 __ins( uint32,  const uint32,  uint32,  const uint32) __attribute__((intrinsic_function(0x121, 0, "ins.t") ));

#define Ifx__ins __ins

/** Extract bit-field (width w bits starting at bit 0) from a and insert it in
 * b at position p.
 */
extern uint32 __insert( uint32,  uint32,  uint32,  const uint32) __attribute__((intrinsic_function(0x109, 0, "insert") ));

#define Ifx__insert __insert

/** Return trg but replace trgbit by inverse of srcbit in src.
 */
extern uint32 __insn( uint32,  const uint32,  uint32,  const uint32) __attribute__((intrinsic_function(0x121, 0, "insn.t") ));

#define Ifx__insn __insn

/** Atomic load-modify-store.
 */
#ifdef INTRINSIC_WORKAROUND
extern void __imaskldmst(void* a, sint32 b, sint32 p, const sint32 w);
#else
asm volatile void Ifx__imaskldmst(void* a, sint32 b, sint32 p, const sint32 w)
{
% reg a, b, p; con w
! "%d2", "%d3"
    imask %e2, b, p, w
    ldmst  [a]0, %e2
}
#endif

/** Store a single bit.
 */
#define Ifx__putbit(value,address,bitoffset) Ifx__imaskldmst(address,value,bitoffset,1)

/** \} */

/** \defgroup IfxLld_Cpu_Intrinsics_Dcc_interrupt_handling Interrupt Handling
 The next table provides an overview of the intrinsic functions to read or set interrupt handling.
 * \ingroup IfxLld_Cpu_Intrinsics_Dcc
 * \{
 */

/** Set CPU priority number [0..255] (or [0..1023] for TriCore 1.6.x) and enable interrupts immediately at function entry
 */
extern void __bisr( const uint32) __attribute__((intrinsic_function(0x100, 0, "bisr") ));

#define Ifx__bisr __bisr

/** Disable interrupts. Only supported for TriCore1
 */
extern void __disable( void) __attribute__((intrinsic_function(0x103, 0, "disable") ));

#define Ifx__disable __disable

/** Disable interrupts and return previous interrupt state (enabled or disabled). Direct supported for TriCore1.6. Emulated on TC1.3.1
 */
#if defined INTRINSIC_WORKAROUND
extern sint32 __disable_and_save(void);
#endif

/** Enable interrupts immediately at function entry
 */
extern void __enable( void) __attribute__((intrinsic_function(0x103, 0, "enable") ));

#define Ifx__enable __enable

/** Restore interrupt state. Direct supported for TriCore1.6. Emulated on TC1.3.1
 */
extern void __restore( sint32) __attribute__((intrinsic_function(0x104, 0, "restore") ));

#define Ifx__restore __restore

/** Call a system call function number
 */
extern void __syscall( const uint32) __attribute__((intrinsic_function(0x100, 0, "syscall") ));

#define Ifx__syscall __syscall

/** \} */

/** \defgroup IfxLld_Cpu_Intrinsics_Dcc_miscellaneous Miscellaneous Intrinsic Functions
 * \ingroup IfxLld_Cpu_Intrinsics_Dcc
 * \{
 */

/**  Write back and invalidate cache address "p". Generates CACHEA.WI [Ab].
 */
extern void __cacheawi( void*) __attribute__((intrinsic_function(0x110, 0, "cachea.wi") ));

#define Ifx__cacheawi __cacheawi

/**  Write back and invalidate cache address \"p\" and return post incremented
 * value of \"p\". Generates CACHEA.WI [Ab+].
 */
asm volatile uint8* Ifx__cacheawi_bo_post_inc(uint8* p)
{
% reg p
!
    cachea.wi [p + ]0
    mov.aa %a2, p
}

/**  Write back and invalidate cache index "p". Generates CACHEI.WI [Ab].
 */
asm volatile void Ifx__cacheiwi(uint8* p)
{
% reg p
!
    cachei.wi [p]
}

/** Initialize a circular pointer with a dynamically allocated buffer at run-time.
 */
asm circ_t __initcirc(void* buf, uint16 bufsize, uint16 byteindex)
{
% reg buf, bufsize, byteindex
! "%a2", "%a3"
    lea    %a2, [buf]0
    extr.u bufsize, bufsize, 0, 16
    insert bufsize, byteindex, bufsize, 16, 16
    mov.a  %a3, bufsize
}

/** Multiply two 32-bit numbers to an intermediate 64-bit result, and scale
 * back the result to 32 bits. To scale back the result, 32 bits are extracted
 * from the intermediate 64-bit result: bit 63-offset to bit 31-offset.
 */
asm volatile sint32 Ifx__mulsc(sint32 a, sint32 b, sint32 offset)
{
% reg a, b, offset
! "%d2", "%d3"
    mul  %e2, a, b
    dextr %d2, %d3, %d2, offset
}

/**  Rotate operand left count times. The bits that are shifted out are inserted at the right side (bit 31 is shifted to bit 0).
 */
asm volatile uint32 Ifx__rol(uint32 operand, uint32 count)
{
% reg operand, count
! "%d2"
    dextr %d2, operand, operand, count
}

/**  Rotate operand right count times. The bits that are shifted out are inserted at the left side (bit 0 is shifted to bit 31).
 */
asm volatile uint32 Ifx__ror(uint32 operand, uint32 count)
{
% reg operand, count
! "%d2"
    rsub count, count, 0
    dextr %d2, operand, operand, count
}

/** \} */

/** \defgroup IfxLld_Cpu_Intrinsics_Dcc_packed Packed Data Type Support
 The next table provides an overview of the intrinsic functions for initialization of packed data type.
 * \ingroup IfxLld_Cpu_Intrinsics_Dcc
 * \{
 */

/**  Absolute value of __packb
*/
asm __packb Ifx__absb(__packb a)
{
% reg a
! "%d2"
    abs.b %d2, a
}

/**  Absolute value of __packhw
 */
asm __packhw Ifx__absh(__packhw a)
{
% reg a
! "%d2"
    abs.h %d2, a
}

/**  Absolute value of __packhw using saturation
 */
asm __packhw Ifx__abssh(__packhw a)
{
% reg a
! "%d2"
    abss.h %d2, a
}

/** \brief  Extract first byte from a __packb
 */
asm sint8 Ifx__extractbyte1(__packb a)
{
% reg a
! "%d2"
    extr  %d2, a, 0, 8
}

/** \brief  Extract second byte from a __packb
 */
asm sint8 Ifx__extractbyte2(__packb a)
{
% reg a
! "%d2"
    extr  %d2, a, 8, 8
}

/** \brief  Extract third byte from a __packb
 */
asm sint8 Ifx__extractbyte3(__packb a)
{
% reg a
! "%d2"
    extr  %d2, a, 16, 8
}

/** \brief  Extract fourth byte from a __packb
 */
asm sint8 Ifx__extractbyte4(__packb a)
{
% reg a
! "%d2"
    extr  %d2, a, 24, 8
}

/** \brief Extract first short from a __packhw
 */
asm short Ifx__extracthw1(__packhw a)
{
% reg a
! "%d2"
    extr  %d2, a, 0, 16
}

/** \brief Extract second short from a __packhw
 */
asm short Ifx__extracthw2(__packhw a)
{
% reg a
! "%d2"
    extr  %d2, a, 16, 16
}

/** Extract first unsigned byte from a __packb
 */
asm volatile uint8 Ifx__extractubyte1(__upackb a)
{
% reg a
! "%d2"
    extr  %d2, a, 0, 8
}

/** Extract second unsigned byte from a __packb
 */
asm volatile uint8 Ifx__extractubyte2(__upackb a)
{
% reg a
! "%d2"
    extr  %d2, a, 8, 8
}

/** Extract third unsigned byte from a __packb
 */
asm volatile uint8 Ifx__extractubyte3(__upackb a)
{
% reg a
! "%d2"
    extr  %d2, a, 16, 8
}

/** Extract fourth unsigned byte from a __packb
 */
asm volatile uint8 Ifx__extractubyte4(__upackb a)
{
% reg a
! "%d2"
    extr  %d2, a, 24, 8
}

/** Extract first uint16 from a __packhw
 */
asm volatile uint16 Ifx__extractuhw1(__upackhw a)
{
% reg a
! "%d2"
    extr  %d2, a, 0, 16
}

/** Extract second uint16 from a __packhw
 */
asm volatile uint16 Ifx__extractuhw2(__upackhw a)
{
% reg a
! "%d2"
    extr  %d2, a, 16, 16
}

/**  Extract first byte from a __packb
 */
asm sint8 Ifx__getbyte1(__packb* a)
{
% reg a
! "%d2"
    ld.w  %d2, [a]
    extr  %d2, %d2, 0, 8
}

/**  Extract second byte from a __packb
 */
asm sint8 Ifx__getbyte2(__packb* a)
{
% reg a
! "%d2"
    ld.w  %d2, [a]
    extr  %d2, %d2, 8, 8
}

/**  Extract third byte from a __packb
 */
asm sint8 Ifx__getbyte3(__packb* a)
{
% reg a
! "%d2"
    ld.w  %d2, [a]
    extr  %d2, %d2, 16, 8
}

/**  Extract fourth byte from a __packb
 */
asm sint8 Ifx__getbyte4(__packb* a)
{
% reg a
! "%d2"
    ld.w  %d2, [a]
    extr  %d2, %d2, 24, 8
}

/**  Extract first short from a __packhw
 */
asm short Ifx__gethw1(__packhw* a)
{
% reg a
! "%d2"
    ld.w  %d2, [a]
    extr  %d2, %d2, 0, 16
}

/**  Extract second short from a __packhw
 */
asm short Ifx__gethw2(__packhw* a)
{
% reg a
! "%d2"
    ld.w  %d2, [a]
    extr  %d2, %d2, 16, 16
}

/**  Extract first unsigned byte from a __packb
 */
asm volatile uint8 Ifx__getubyte1(__upackb* a)
{
% reg a
! "%d2"
    ld.w  %d2, [a]
    extr  %d2, %d2, 0, 8
}

/**  Extract second unsigned byte from a __packb
 */
asm volatile uint8 Ifx__getubyte2(__upackb* a)
{
% reg a
! "%d2"
    ld.w  %d2, [a]
    extr  %d2, %d2, 8, 8
}

/**  Extract third unsigned byte from a __packb
 */
asm volatile uint8 Ifx__getubyte3(__upackb* a)
{
% reg a
! "%d2"
    ld.w  %d2, [a]
    extr  %d2, %d2, 16, 8
}

/**  Extract fourth unsigned byte from a __packb
 */
asm volatile uint8 Ifx__getubyte4(__upackb* a)
{
% reg a
! "%d2"
    ld.w  %d2, [a]
    extr  %d2, %d2, 24, 8
}

/**  Extract first uint16 from a __packhw
 */
asm volatile uint16 Ifx__getuhw1(__upackhw* a)
{
% reg a
! "%d2"
    ld.w  %d2, [a]
    extr  %d2, %d2, 0, 16
}

/**  Extract second uint16 from a __packhw
 */
asm volatile uint16 Ifx__getuhw2(__upackhw* a)
{
% reg a
! "%d2"
    ld.w  %d2, [a]
    extr  %d2, %d2, 16, 16
}

/**  Initialize  __packb with four integers
 */
asm __packb Ifx__initpackb(sint32 a, sint32 b, sint32 c, sint32 d)
{
% reg a, b, c, d
! "%d2"
    insert  c, c, d, 8, 8
    insert  d, a, b, 8, 8
    insert  %d2, d, c, 16, 16
}

/** Initialize  __packb with a long integer
 */
asm __packb Ifx__initpackbl(long a)
{
% reg a
! "%d2"
    mov %d2, a
}

/** \brief  Initialize  __packhw with two integers
 */
asm __packhw Ifx__initpackhw(short a, short b)
{
% reg a, b
! "%d2"
    insert  %d2, a, b, 16, 16
}

/**  Initialize  __packhw with a long integer
 */
asm __packhw Ifx__initpackhwl(long a)
{
% reg a
! "%d2"
    mov %d2, a
}

/** Initialize  __packb with four unsigned integers
 */
asm __upackb    Ifx__initupackb( uint32 a, uint32 b, uint32 c, uint32 d)
{
% reg a, b, c, d
! "%d2"
    insert  c, c, d, 8, 8
    insert  a, a, b, 8, 8
    insert  %d2, a, c, 16, 16
}

/**  Initialize  __packhw with two unsigned integers
 */
asm __upackhw    Ifx__initupackhw( uint16 a, uint16 b)
{
% reg a, b
! "%d2"
    insert  %d2, a, b, 16, 16
}

/** \brief  Insert sint8 into first byte of a __packb
 */
asm __packb Ifx__insertbyte1(__packb a, sint8 b)
{
% reg a, b
! "%d2"
    insert  %d2, a, b, 0, 8
}

/** \brief  Insert sint8 into second byte of a __packb
 */
asm __packb Ifx__insertbyte2(__packb a, sint8 b)
{
% reg a, b
! "%d2"
    insert  %d2, a, b, 8, 8
}

/** \brief  Insert sint8 into third byte of a __packb
 */
asm __packb Ifx__insertbyte3(__packb a, sint8 b)
{
% reg a, b
! "%d2"
    insert  %d2, a, b, 16, 8
}

/** \brief  Insert sint8 into fourth byte of a __packb
 */
asm __packb Ifx__insertbyte4(__packb a, sint8 b)
{
% reg a, b
! "%d2"
    insert  %d2, a, b, 24, 8
}

/**  Insert short into first halfword of a __packhw
 */
asm __packhw Ifx__inserthw1(__packhw a, short b)
{
% reg a, b
! "%d2"
    insert  %d2, a, b, 0, 16
}

/**  Insert short into second halfword of a __packhw
 */
asm __packhw Ifx__inserthw2(__packhw a, short b)
{
% reg a, b
! "%d2"
    insert  %d2, a, b, 16, 16
}

/** \brief  Insert uint8 into first unsigned byte of a __packb
 */
asm __upackb    Ifx__insertubyte1( __upackb a, uint8 b)
{
% reg a, b
! "%d2"
    insert  %d2, a, b, 0, 8
}

/** \brief  Insert uint8 into second unsigned byte of a __packb
 */
asm __upackb    Ifx__insertubyte2( __upackb a, uint8 b)
{
% reg a, b
! "%d2"
    insert  %d2, a, b, 8, 8
}

/** \brief  Insert uint8 into third unsigned byte of a __packb
 */
asm __upackb     Ifx__insertubyte3( __upackb a, uint8 b)
{
% reg a, b
! "%d2"
    insert  %d2, a, b, 16, 8
}

/** \brief  Insert uint8 into fourth unsigned byte of a __packb
 */
asm __upackb     Ifx__insertubyte4( __upackb a, uint8 b)
{
% reg a, b
! "%d2"
    insert  %d2, a, b, 24, 8
}

/**  Insert uint16 into first halfword of a __upackhw
 */
asm __upackhw    Ifx__insertuhw1( __upackhw a, uint16 b)
{
% reg a, b
! "%d2"
    insert  %d2, a, b, 0, 16
}

/**  Insert uint16 into second halfword of a __upackhw
 */
asm __upackhw    Ifx__insertuhw2( __upackhw a, uint16 b)
{
% reg a, b
! "%d2"
    insert  %d2, a, b, 16, 16
}

/**  Minimum of two  __packb values
 */
#ifdef INTRINSIC_WORKAROUND
extern __packb __minb(__packb a, __packb b);
#else
asm __packb Ifx__minb(__packb a, __packb b)
{
% reg a, b
! "%d2"
    min.b %d2, a, b
}
#endif

/**  Minimum of two __upackb  values
 */
asm __upackb     Ifx__minbu( __upackb  a, __upackb  b)
{
% reg a, b
! "%d2"
    min.bu %d2, a, b
}

/**  Minimum of two  __packhw values
 */
asm __packhw Ifx__minh(__packhw a, __packhw b)
{
% reg a, b
! "%d2"
    min.h %d2, a, b
}

/**  Minimum of two __upackhw values
 */
asm __upackhw    Ifx__minhu( __upackhw a, __upackhw b)
{
% reg a, b
! "%d2"
    min.hu %d2, a, b
}

/**  Insert sint8 into first byte of a __packb
 */
asm volatile void Ifx__setbyte1(__packb* a, sint8 b)
{
% reg a, b
! "%d2"
    ld.w   %d2, [a]
    insert %d2, %d2, b, 0, 8
    st.w   [a], %d2
}

/**  Insert sint8 into second byte of a __packb
 */
asm volatile void Ifx__setbyte2(__packb* a, sint8 b)
{
% reg a, b
! "%d2"
    ld.w   %d2, [a]
    insert %d2, %d2, b, 8, 8
    st.w   [a], %d2
}

/**  Insert sint8 into third byte of a __packb
 */
asm volatile void Ifx__setbyte3(__packb* a, sint8 b)
{
% reg a, b
! "%d2"
    ld.w   %d2, [a]
    insert %d2, %d2, b, 16, 8
    st.w   [a], %d2
}

/**  Insert sint8 into fourth byte of a __packb
 */
asm volatile void Ifx__setbyte4(__packb* a, sint8 b)
{
% reg a, b
! "%d2"
    ld.w   %d2, [a]
    insert %d2, %d2, b, 24, 8
    st.w   [a], %d2
}

/**  Insert short into first halfword of a __packhw
 */
asm volatile void Ifx__sethw1(__packhw* a, short b)
{
% reg a, b
! "%d2"
    ld.w   %d2, [a]
    insert %d2, %d2, b, 0, 16
    st.w   [a], %d2
}

/**  Insert short into second halfword of a __packhw
 */
asm volatile void Ifx__sethw2(__packhw* a, short b)
{
% reg a, b
! "%d2"
    ld.w   %d2, [a]
    insert %d2, %d2, b, 16, 16
    st.w   [a], %d2
}

/**  Insert uint8 into first byte of a __upackb
 */
asm volatile void Ifx__setubyte1(__upackb* a, uint8 b)
{
% reg a, b
! "%d2"
    ld.w   %d2, [a]
    insert %d2, %d2, b, 0, 8
    st.w   [a], %d2
}

/**  Insert uint8 into second byte of a __upackb
 */
asm volatile void Ifx__setubyte2(__upackb* a, uint8 b)
{
% reg a, b
! "%d2"
    ld.w   %d2, [a]
    insert %d2, %d2, b, 8, 8
    st.w   [a], %d2
}

/**  Insert uint8 into third byte of a __upackb
 */
asm volatile void Ifx__setubyte3(__upackb* a, uint8 b)
{
% reg a, b
! "%d2"
    ld.w   %d2, [a]
    insert %d2, %d2, b, 16, 8
    st.w   [a], %d2
}

/**  Insert uint8 into fourth byte of a __upackb
 */
asm volatile void Ifx__setubyte4(__upackb* a, uint8 b)
{
% reg a, b
! "%d2"
    ld.w   %d2, [a]
    insert %d2, %d2, b, 24, 8
    st.w   [a], %d2
}

/**  Insert uint16 into first halfword of a __upackhw
 */
asm volatile void Ifx__setuhw1(__upackhw* a, uint16 b)
{
% reg a, b
! "%d2"
    ld.w   %d2, [a]
    insert %d2, %d2, b, 0, 16
    st.w   [a], %d2
}

/**  Insert uint16 into second halfword of a __upackhw
 */
asm volatile void Ifx__setuhw2(__upackhw* a, uint16 b)
{
% reg a, b
! "%d2"
    ld.w   %d2, [a]
    insert %d2, %d2, b, 16, 16
    st.w   [a], %d2
}

/** \} */

/** \defgroup IfxLld_Cpu_Intrinsics_Dcc_register Register Handling
 The next table provides an overview of the intrinsic functions that you can use to access control registers.
 * \ingroup IfxLld_Cpu_Intrinsics_Dcc
 * \{
 */

/**  Return absolute value
 */
extern sint32 __abs( sint32) __attribute__((intrinsic_pseudo(1, "abs") ));

#define Ifx__abs __abs

/** Return absolue difference of two integers
 */
extern sint32 __absdif( sint32,  sint32) __attribute__((intrinsic_pseudo(1, "absdif") ));

#define Ifx__absdif __absdif

/**  Return absolute value with saturation
 */
extern sint32 __abss( sint32) __attribute__((intrinsic_pseudo(1, "abss") ));

#define Ifx__abss __abss

/**  Count leading ones in int
 */
extern sint32 __clo( sint32) __attribute__((intrinsic_pseudo(1, "clo") ));

#define Ifx__clo __clo

/**  Count number of redundant sign bits (all consecutive bits with the same value as bit 31
 */
extern sint32 __cls( sint32) __attribute__((intrinsic_pseudo(1, "cls") ));

#define Ifx__cls __cls

/**  Count leading zeros in int
 */
extern sint32 __clz( sint32) __attribute__((intrinsic_pseudo(1, "clz") ));

#define Ifx__clz __clz

/**  Return absolute double precision floating-point value
 */
asm double Ifx__fabs(double d)
{
% reg d
! "%d2"
    insert  %d2, d, 0, 31, 1
}

/**  Return absolute floating-point value
 */
asm float Ifx__fabsf(float f)
{
% reg f
! "%d2"
    insert %d2, f, 0, 31, 1
}

/**  Move contents of the addressed core SFR into a data register
 */
extern sint32 __mfcr( const uint32) __attribute__((intrinsic_function(0x101, 0, "mfcr") ));

#define Ifx__mfcr __mfcr

/**  Move contents of a data register (second sint32) to the addressed core SFR (first sint32)
 */
extern void __mtcr( const uint32,  sint32) __attribute__((intrinsic_function(0x102, 0, "mtcr") ));

#define Ifx__mtcr __mtcr

/**  Return parity
 */
asm volatile sint32 Ifx__parity(sint32 a)
{
% reg a
! "%d2"
    parity %d2, a
}

/**  Return saturated byte
 */
asm sint8 Ifx__satb(sint32 a)
{
% reg a
! "%d2"
    sat.b %d2, a
}

/**  Return saturated unsigned byte
 */
asm volatile uint8 Ifx__satbu(sint32 a)
{
% reg a
! "%d2"
    sat.bu %d2, a
}

/**  Return saturated halfword
 */
asm short Ifx__sath(sint32 a)
{
% reg a
! "%d2"
    sat.h %d2, a
}

/**  Return saturated unsignedhalfword
 */
asm volatile uint16 Ifx__sathu(sint32 a)
{
% reg a
! "%d2"
    sat.hu %d2, a
}

/** \} */

/** \defgroup IfxLld_Cpu_Intrinsics_Dcc_saturation Saturation Arithmetic Support
 These intrinsics support saturation arithmetic
 * \ingroup IfxLld_Cpu_Intrinsics_Dcc
 * \{
 */
/** add signed with saturation
 */
extern sint32 __adds( sint32,  sint32) __attribute__((intrinsic_pseudo(1, "adds") ));

#define Ifx__adds __adds

/** add unsigned with saturation
 */
asm volatile uint32 Ifx__addsu(uint32 a, uint32 b)
{
% reg a, b
! "%d2"
    adds.u %d2, a, b
}

/** substract signed with saturation
 */
asm volatile sint32 Ifx__subs(sint32 a, sint32 b)
{
% reg a, b
! "%d2"
    subs %d2, a, b
}

/** substract unsigned with saturation
 */
asm volatile uint32 Ifx__subsu(uint32 a, uint32 b)
{
% reg a, b
! "%d2"
    subs.u %d2, a, b
}

/** \} */

/** \defgroup IfxLld_Cpu_Intrinsics_Dcc_single_assembly Insert Single Assembly Instruction
 The next table provides an overview of the intrinsic functions that you can use to insert a single assembly
 instruction.You can also use inline assembly but these intrinsics provide a shorthand for frequently used
 assembly instructions.
 * \ingroup IfxLld_Cpu_Intrinsics_Dcc
 * \{
 */

/** Insert DEBUG instruction
 */
extern void __debug( void) __attribute__((intrinsic_function(0x103, 0, "debug") ));

#define Ifx__debug __debug

/** Insert DSYNC instruction
 */
extern void __dsync( void) __attribute__((intrinsic_function(0x103, 0, "dsync") ));

#define Ifx__dsync __dsync

/** Insert ISYNC instruction
 */
extern void __isync( void) __attribute__((intrinsic_function(0x103, 0, "isync") ));

#define Ifx__isync __isync

/** Insert LDMST instruction. Note that all operands must be word-aligned.
 */
#ifdef INTRINSIC_WORKAROUND
#define __ldmst __ldmst_c
#else
asm volatile void Ifx__ldmst(volatile void *address, uint32 mask, uint32 value)
{
%reg address, mask, value;
!"%d2", "%d3"
 mov     %d3, mask
 mov     %d2, value
 ldmst	[address],%e2
}

#endif

extern void __scheduling_barrier( void) __attribute__((intrinsic_function(9, 4, "$$sb") ));
#define Ifx__mem_barrier __scheduling_barrier

/** Insert NOP instruction
 */
extern void __nop( void) __attribute__((intrinsic_function(0x103, 0, "nop") ));

#define Ifx__nop __nop

#define Ifx__NOP __nops

/** Insert a loop over n NOP instruction
 */
asm volatile void Ifx__nops(uint32 cnt)
{
% reg cnt;lab L0;
! "%a2"
    mov %a2,cnt
    add.a %a2, -1
L0:
    nop
    loop %a2, L0
}

/** Insert a loop over n times 1000 NOP instruction
 */
asm volatile void Ifx__nops1000(uint32 x)
{
% reg x;
    lab L0, L1
! "%a2", "%a3"
    mov.a %a2, x
L1:
    lea   %a3, 999
L0:
    nop
    nop
    loop  %a3, L0
    loop  %a2, L1
}

/** Insert RSLCX instruction
 */
extern void __rslcx( void) __attribute__((intrinsic_function(0x103, 0, "rslcx") ));

#define Ifx__rslcx

/** Insert SVLCX instruction
 */
extern void __svlcx( void) __attribute__((intrinsic_function(0x103, 0, "svlcx") ));

#define Ifx__svlcx

/** Insert SWAP instruction. Note that all operands must be word-aligned.
 */
#ifdef INTRINSIC_WORKAROUND
extern uint32 __swap(void* place, uint32 value);
#else
asm volatile uint32 Ifx__swap(void* place, uint32 value)
{
% reg place, value
! "%d2"
    mov %d2, value
    swap.w [place], %d2
}
#endif

// FIXME
asm volatile unsigned int Ifx__cmpAndSwap(unsigned int *address, unsigned long value, unsigned long CmpVal)
{
%reg value, address, CmpVal
! "%d2", "%d3"
  mov %d2,value
  mov %d3,CmpVal
  cmpswap.w [address], %e2
}
/** \} */

/** Insert n NOP instruction
 */
//#info "NOP: Feature not yet implemented."

#define Ifx__setareg(areg,val) ___setareg(areg,val)
/* we need to use a15 for the address register and not direct that the compiler this will not remove */
#define ___setareg(areg,val) \
    { __asm ("#$$bp"); \
      __asm ("  movh.a\t %a15,"#val"@ha\n"); \
      __asm ("  lea\t %a15,[%a15]"#val"@l\n"); \
      __asm ("  mov.aa %"#areg", %a15\n"); \
      __asm ("#$$ep"); }

/* FIXME check that the compiler take in account that d0 is used by the inline function */
asm volatile void Ifx__stopPerfCounters(void)
{
! "%d0"
	mov %d0,0
    mtcr 0xFC00,%d0
    isync
}

/** \brief Convert a fixpoint value to float32
 *
 * This function converts a value from a fixpoint format to a float32 format.
 *
 *
 * \param value value to be converted.
 * \param shift position of the fix point. Range = [-256, 255] => (Qx.y format where x = shift+1).
 *
 * \return Returns the converted value in the float32 format.
 *
 */
asm float Ifx__fixpoint_to_float32(fract value, sint32 shift)
{
% reg value, shift
! "%d2"
    q31tof %d2, value, shift
}

asm volatile void* Ifx__getA11(void)
{
! "%a11", "%a4"
	mov.aa %a4, %a11
}

asm void Ifx__setStackPointer(void *stackAddr)
{
% reg stackAddr
! "%a10"
	mov.aa %a10, stackAddr
}

asm volatile unsigned int Ifx__crc32(uint32 b,uint32 a)
{
% reg b, a
! "%d2"
	CRC32 %d2, b, a
}

IFX_INLINE unsigned int IfxCpu_calculateCrc32(uint32 *startaddress, uint8 length)
{
    uint32 returnvalue = 0; /* set seed value to 0 */
    for (;length > 0; length--)
    {
          /* calculate the CRC over all data */
        returnvalue = Ifx__crc32(returnvalue,*startaddress);
        startaddress++;
    }
    return returnvalue;
}

/** \brief Generate the Random value
 *
 * This function generates the random value by taking a valid seed and limits.
 *
 * \param a lower limit.
 * \param x valid seed value.
 * \param m upper limit.
 *
 * \return Returns the random value.
 *
 */
asm volatile uint32 IfxCpu_getRandomVal(uint32 a, uint32 x, uint32 m)
{
% reg a,x,m; lab cmp_m, sub_m, done;
! "%d4","%d5","%d6","%d0","%d1","%d2"
    mul.u     %e4,a,x       /* d5 = Eh; d4 = El */
    mov       %d0,%d4       /* e0 = El  */
    mov       %d1, 0
    madd.u    %e4,%e0,%d5,5 /* e4 = El + 5 * d5 */
cmp_m:
    jge.u     %d4,m,sub_m
    jz        %d5,done
sub_m:
    subx      %d4,%d4,m     /* e4=e4-m */
    subc      %d5,%d5,%d1   /* d5=d5-0 */
    loopu     cmp_m
done:
    mov       %d2,%d4
}

/* Macros for backward compatibility of the intrinsics*/
/******************************************************************************/
#ifndef __non_return_call
#define __non_return_call Ifx__non_return_call
#endif

#ifndef __jump_and_link
#define __jump_and_link Ifx__jump_and_link
#endif

#ifndef __moveToDataParam0
#define __moveToDataParam0 Ifx__moveToDataParam0
#endif

#ifndef __moveToDataParamRet
#define __moveToDataParamRet Ifx__moveToDataParamRet
#endif

#ifndef __getDataParamRet
#define __getDataParamRet Ifx__getDataParamRet
#endif

#ifndef __moveToAddrParam0
#define __moveToAddrParam0 Ifx__moveToAddrParam0
#endif

#ifndef __jumpToFunction
#define __jumpToFunction Ifx__jumpToFunction
#endif

#ifndef __jumpToFunctionWithLink
#define __jumpToFunctionWithLink Ifx__jumpToFunctionWithLink
#endif

#ifndef __jumpBackToLink
#define __jumpBackToLink Ifx__jumpBackToLink
#endif

#ifndef __minX
#define __minX Ifx__minX
#endif

#ifndef __maxX
#define __maxX Ifx__maxX
#endif

#ifndef __saturateX
#define __saturateX Ifx__saturateX
#endif

#ifndef __checkrangeX
#define __checkrangeX Ifx__checkrangeX
#endif

#ifndef __saturate
#define __saturate Ifx__saturate
#endif

#ifndef __sqrf
#define __sqrf Ifx__sqrf
#endif

#ifndef __sqrtf
#define __sqrtf Ifx__sqrtf
#endif

#ifndef __checkrange
#define __checkrange Ifx__checkrange
#endif

#ifndef __roundf
#define __roundf Ifx__roundf
#endif

#ifndef __absf
#define __absf Ifx__absf
#endif

#ifndef __minf
#define __minf Ifx__minf
#endif

#ifndef __maxf
#define __maxf Ifx__maxf
#endif

#ifndef __saturatef
#define __saturatef Ifx__saturatef
#endif

#ifndef __checkrangef
#define __checkrangef Ifx__checkrangef
#endif

#ifndef __abs_stdreal
#define __abs_stdreal Ifx__abs_stdreal
#endif

#ifndef __min_stdreal
#define __min_stdreal Ifx__min_stdreal
#endif

#ifndef __max_stdreal
#define __max_stdreal Ifx__max_stdreal
#endif

#ifndef __saturate_stdreal
#define __saturate_stdreal Ifx__saturate_stdreal
#endif

#ifndef __neqf
#define __neqf Ifx__neqf
#endif

#ifndef __leqf
#define __leqf Ifx__leqf
#endif

#ifndef __geqf
#define __geqf Ifx__geqf
#endif

#ifndef __clssf
#define __clssf Ifx__clssf
#endif

#ifndef __float_to_fract
#define __float_to_fract Ifx__float_to_fract
#endif

#ifndef __fract_to_float
#define __fract_to_float Ifx__fract_to_float
#endif

#ifndef __getfract
#define __getfract Ifx__getfract
#endif

#ifndef __mac_r_sf
#define __mac_r_sf Ifx__mac_r_sf
#endif

#ifndef __mac_sf
#define __mac_sf Ifx__mac_sf
#endif

#ifndef __mulfractfract
#define __mulfractfract Ifx__mulfractfract
#endif

#ifndef __mulfractlong
#define __mulfractlong Ifx__mulfractlong
#endif

#ifndef __round16
#define __round16 Ifx__round16
#endif

#ifndef __fract_to_sfract
#define __fract_to_sfract Ifx__fract_to_sfract
#endif

#ifndef __round16
#define __round16 Ifx__round16
#endif

#ifndef __s16_to_sfract
#define __s16_to_sfract Ifx__s16_to_sfract
#endif

#ifndef __sfract_to_s16
#define __sfract_to_s16 Ifx__sfract_to_s16
#endif

#ifndef __sfract_to_u16
#define __sfract_to_u16 Ifx__sfract_to_u16
#endif

#ifndef __shaaccum
#define __shaaccum Ifx__shaaccum
#endif

#ifndef __shafracts
#define __shafracts Ifx__shafracts
#endif

#ifndef __shasfracts
#define __shasfracts Ifx__shasfracts
#endif

#ifndef __u16_to_sfract
#define __u16_to_sfract Ifx__u16_to_sfract
#endif

#ifndef __getbit
#define __getbit Ifx__getbit
#endif

#ifndef __imaskldmst
#define __imaskldmst Ifx__imaskldmst
#endif

#ifndef __putbit
#define __putbit Ifx__putbit
#endif

#ifndef __cacheawi_bo_post_inc
#define __cacheawi_bo_post_inc Ifx__cacheawi_bo_post_inc
#endif

#ifndef __cacheiwi
#define __cacheiwi Ifx__cacheiwi
#endif

#ifndef __mulsc
#define __mulsc Ifx__mulsc
#endif

#ifndef __rol
#define __rol Ifx__rol
#endif

#ifndef __ror
#define __ror Ifx__ror
#endif

#ifndef __absb
#define __absb Ifx__absb
#endif

#ifndef __absh
#define __absh Ifx__absh
#endif

#ifndef __abssh
#define __abssh Ifx__abssh
#endif

#ifndef __extractbyte1
#define __extractbyte1 Ifx__extractbyte1
#endif

#ifndef __extractbyte2
#define __extractbyte2 Ifx__extractbyte2
#endif

#ifndef __extractbyte3
#define __extractbyte3 Ifx__extractbyte3
#endif

#ifndef __extractbyte4
#define __extractbyte4 Ifx__extractbyte4
#endif

#ifndef __extracthw1
#define __extracthw1 Ifx__extracthw1
#endif

#ifndef __extracthw2
#define __extracthw2 Ifx__extracthw2
#endif

#ifndef __extractubyte1
#define __extractubyte1 Ifx__extractubyte1
#endif

#ifndef __extractubyte2
#define __extractubyte2 Ifx__extractubyte2
#endif

#ifndef __extractubyte3
#define __extractubyte3 Ifx__extractubyte3
#endif

#ifndef __extractubyte4
#define __extractubyte4 Ifx__extractubyte4
#endif

#ifndef __extractuhw1
#define __extractuhw1 Ifx__extractuhw1
#endif

#ifndef __extractuhw2
#define __extractuhw2 Ifx__extractuhw2
#endif

#ifndef __getbyte1
#define __getbyte1 Ifx__getbyte1
#endif

#ifndef __getbyte2
#define __getbyte2 Ifx__getbyte2
#endif

#ifndef __getbyte3
#define __getbyte3 Ifx__getbyte3
#endif

#ifndef __getbyte4
#define __getbyte4 Ifx__getbyte4
#endif

#ifndef __gethw1
#define __gethw1 Ifx__gethw1
#endif

#ifndef __gethw2
#define __gethw2 Ifx__gethw2
#endif

#ifndef __getubyte1
#define __getubyte1 Ifx__getubyte1
#endif

#ifndef __getubyte2
#define __getubyte2 Ifx__getubyte2
#endif

#ifndef __getubyte3
#define __getubyte3 Ifx__getubyte3
#endif

#ifndef __getubyte4
#define __getubyte4 Ifx__getubyte4
#endif

#ifndef __getuhw1
#define __getuhw1 Ifx__getuhw1
#endif

#ifndef __getuhw2
#define __getuhw2 Ifx__getuhw2
#endif

#ifndef __initpackb
#define __initpackb Ifx__initpackb
#endif

#ifndef __initpackbl
#define __initpackbl Ifx__initpackbl
#endif

#ifndef __initpackhw
#define __initpackhw Ifx__initpackhw
#endif

#ifndef __initpackhwl
#define __initpackhwl Ifx__initpackhwl
#endif

#ifndef __initupackb
#define __initupackb Ifx__initupackb
#endif

#ifndef __initupackhw
#define __initupackhw Ifx__initupackhw
#endif

#ifndef __insertbyte1
#define __insertbyte1 Ifx__insertbyte1
#endif

#ifndef __insertbyte2
#define __insertbyte2 Ifx__insertbyte2
#endif

#ifndef __insertbyte3
#define __insertbyte3 Ifx__insertbyte3
#endif

#ifndef __insertbyte4
#define __insertbyte4 Ifx__insertbyte4
#endif

#ifndef __inserthw1
#define __inserthw1 Ifx__inserthw1
#endif

#ifndef __inserthw2
#define __inserthw2 Ifx__inserthw2
#endif

#ifndef __insertubyte1
#define __insertubyte1 Ifx__insertubyte1
#endif

#ifndef __insertubyte2
#define __insertubyte2 Ifx__insertubyte2
#endif

#ifndef __insertubyte3
#define __insertubyte3 Ifx__insertubyte3
#endif

#ifndef __insertubyte4
#define __insertubyte4 Ifx__insertubyte4
#endif

#ifndef __insertuhw1
#define __insertuhw1 Ifx__insertuhw1
#endif

#ifndef __insertuhw2
#define __insertuhw2 Ifx__insertuhw2
#endif

#ifndef __minb
#define __minb Ifx__minb
#endif

#ifndef __minbu
#define __minbu Ifx__minbu
#endif

#ifndef __minh
#define __minh Ifx__minh
#endif

#ifndef __minhu
#define __minhu Ifx__minhu
#endif

#ifndef __setbyte1
#define __setbyte1 Ifx__setbyte1
#endif

#ifndef __setbyte2
#define __setbyte2 Ifx__setbyte2
#endif

#ifndef __setbyte3
#define __setbyte3 Ifx__setbyte3
#endif

#ifndef __setbyte4
#define __setbyte4 Ifx__setbyte4
#endif

#ifndef __sethw1
#define __sethw1 Ifx__sethw1
#endif

#ifndef __sethw2
#define __sethw2 Ifx__sethw2
#endif

#ifndef __setubyte1
#define __setubyte1 Ifx__setubyte1
#endif

#ifndef __setubyte2
#define __setubyte2 Ifx__setubyte2
#endif

#ifndef __setubyte3
#define __setubyte3 Ifx__setubyte3
#endif

#ifndef __setubyte4
#define __setubyte4 Ifx__setubyte4
#endif

#ifndef __setuhw1
#define __setuhw1 Ifx__setuhw1
#endif

#ifndef __setuhw2
#define __setuhw2 Ifx__setuhw2
#endif

#ifndef __fabs
#define __fabs Ifx__fabs
#endif

#ifndef __fabsf
#define __fabsf Ifx__fabsf
#endif

#ifndef __parity
#define __parity Ifx__parity
#endif

#ifndef __satb
#define __satb Ifx__satb
#endif

#ifndef __satbu
#define __satbu Ifx__satbu
#endif

#ifndef __sath
#define __sath Ifx__sath
#endif

#ifndef __sathu
#define __sathu Ifx__sathu
#endif

#ifndef __addsu
#define __addsu Ifx__addsu
#endif

#ifndef __subs
#define __subs Ifx__subs
#endif

#ifndef __subsu
#define __subsu Ifx__subsu
#endif

#ifndef __ldmst
#define __ldmst Ifx__ldmst
#endif

#ifndef __mem_barrier
#define __mem_barrier Ifx__mem_barrier
#endif

#if ((!defined(NOP)) && (!defined(MCAL_COMPILER_H)))
#define NOP Ifx__NOP
#endif

#ifndef __nops
#define __nops Ifx__nops
#endif

#ifndef __nops1000
#define __nops1000 Ifx__nops1000
#endif

#ifndef __swap
#define __swap Ifx__swap
#endif

#ifndef __cmpAndSwap
#define __cmpAndSwap Ifx__cmpAndSwap
#endif

#ifndef __setareg
#define __setareg Ifx__setareg
#endif

#ifndef __stopPerfCounters
#define __stopPerfCounters Ifx__stopPerfCounters
#endif

#ifndef __fixpoint_to_float32
#define __fixpoint_to_float32 Ifx__fixpoint_to_float32
#endif

#ifndef __getA11
#define __getA11 Ifx__getA11
#endif

#ifndef __setStackPointer
#define __setStackPointer Ifx__setStackPointer
#endif

#if ((!defined(__crc32)) && (!defined(MCAL_COMPILER_H)))
#define __crc32 Ifx__crc32
#endif

/******************************************************************************/
/* *INDENT-ON* */
/******************************************************************************/
#endif /* IFXCPU_INTRINSICSDCC_H */
