/**********************************
@file: arch_arm32.h
@brief: header file for .c file
@author: John Kim
@date: Feb 17th, 2018
***********************************/

#ifndef ARCH_ARM32_H
#define ARCH_ARM32_H

#include <stdint.h>

#define __SCB_ADDRESS (volatile int32_t) 0xE000ED00
#define __SCB_ADDRESS (???)
#define __CPUID_ADDRESS_OFFSET (???)
#define __CPUID (???)
#define __CPUID_PART_NO_OFFSET (???)
#define __CPUID_PART_NO_MASK   (???)
#define __CCR_ADDRESS_OFFSET (???)
#define __CCR (???)
#define __CCR_STK_ALIGNMENT_OFFSET (???)
#define __CCR_STK_ALIGNMENT_MASK   (???)
#define __CCR_UNALIGNED_ACCESS_TRAP_OFFSET (???)
#define __CCR_UNALIGNED_ACCESS_TRAP_MASK   (???)
#define __CCR_DIVIDE_BY_ZERO_TRAP_OFFSET (???)
#define __CCR_DIVIDE_BY_ZERO_TRAP_MASK   (???)

uint32_t ARM32_CCR_get_stack_alignment();
//read the ARM Configuration and Control Register (CCR) and
//return the stack alignment value of the current configured ARM processor.
//use a direct memory dereference of the CCR register to access the contents.
//should directly return the value of the alignment.
//0 = 4-byte aligned 	1 = 8-Byte aligned
//needs to be defined as a inline function. also ensure the compiler makes this
//an inline function using __attribute__((always_inline)) gcc attribute.

uint32_t ARM32_CPUID_get_part_number();
//needs to read the ARM CPU ID Register (CPUID) and return the value of
//the Part Number for the current ARM processor.
//direct memory dereference of the CPUID register in order to access the contents.
//directly return the value of the part number. Cortex-M4 should return the value 0xC24.
//needs to be defined as a inline function. also ensure the compiler makes 
//inline function by using the __attribute__((always_inline)) gcc attribute.

uint32_t ARM32_CCR_enable_divide_by_zero_trap();
//needs to write to the ARM Configuration and Control Register (CCR) to set
//a divide by zero trap by writing a 1 to the correct bit location of DIV_0_TRP.
//direct memory dereference of the CCR register in order to access the contents.
//needs to be defined as a inline function. also ensure the compiler makes 
//this an inline function by using the __attribute__((always_inline)) gcc attribute

uint32_t ARM32_CCR_enable_unaligned_access_trap();
//needs to write to the ARM Configuration and Control Register (CCR) to set
//unaligned memory access trap by writing 1 to the correct bit location of UNALIGN_TRP.
//needs to use a direct memory dereference of the CCR register to access the contents.
//needs to be defined as a inline function. ensure the compiler makes this an 
//inline function by using the __attribute__((always_inline)) gcc attribute.

void ARM32_create_unaligned_access_trap();
//perform an unaligned access in order to trigger a trap or exception on the microcontroller.
//This function should not return and a UsageFault Exception should be called
//automatically upon execution of the error causing line of code.

void ARM32_create_divide_by_zero_trap();
//should perform a divide by zero in order to trigger a trap or exception on
//the microcontroller.
//should not return and a UsageFault Exception should be called
//automatically upon execution of the error causing line of c

#endif /*arch_arm32*/
