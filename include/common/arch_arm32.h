/**********************************
@file: arch_arm32.h
@brief: header file for .c file
@author: John Kim
@date: Feb 17th, 2018
***********************************/

#ifndef ARCH_ARM32_H
#define ARCH_ARM32_H

#include <stdint.h>

#define __SCB_ADDRESS (volatile int32_t) 0xE000E008
#define __CPUID_ADDRESS_OFFSET (volatile int16_t) 0xCF8
#define __CPUID (int32_t) * (int32_t *) 0xE000ED00
#define __CPUID_PART_NO_OFFSET (volatile int8_t) 0x4
#define __CPUID_PART_NO_MASK (volatile int16_t)  0xFFF0
#define __CCR_ADDRESS_OFFSET (volatile int16_t) 0xD0C
#define __CCR (int32_t) * (int32_t *) 0xE000ED14
#define __CCR_STK_ALIGNMENT_OFFSET (volatile int8_t) 0x9
#define __CCR_STK_ALIGNMENT_MASK (volatile int16_t)   0x200
#define __CCR_UNALIGNED_ACCESS_TRAP_OFFSET  (volatile int8_t) 0x3
#define __CCR_UNALIGNED_ACCESS_TRAP_MASK   (volatile int8_t)  0x8
#define __CCR_DIVIDE_BY_ZERO_TRAP_OFFSET (volatile int8_t) 0x4
#define __CCR_DIVIDE_BY_ZERO_TRAP_MASK (volatile int8_t)   0x10

#define UNUSED(expr) do {(void)(expr);} while(0)

inline uint32_t ARM32_CCR_get_stack_alignment() __attribute__((always_inline));
//read the ARM Configuration and Control Register (CCR) and
//return the stack alignment value of the current configured ARM processor.
//use a direct memory dereference of the CCR register to access the contents.
//should directly return the value of the alignment.
//0 = 4-byte aligned 	1 = 8-Byte aligned

inline uint32_t ARM32_CPUID_get_part_number() __attribute__((always_inline));
//needs to read the ARM CPU ID Register (CPUID) and return the value of
//the Part Number for the current ARM processor.
//direct memory dereference of the CPUID register in order to access the contents.
//directly return the value of the part number. Cortex-M4 should return the value 0xC24.

inline uint32_t ARM32_CCR_enable_divide_by_zero_trap() __attribute__((always_inline));
//needs to write to the ARM Configuration and Control Register (CCR) to set
//a divide by zero trap by writing a 1 to the correct bit location of DIV_0_TRP.
//direct memory dereference of the CCR register in order to access the contents.

inline uint32_t ARM32_CCR_enable_unaligned_access_trap() __attribute__((always_inline));
//needs to write to the ARM Configuration and Control Register (CCR) to set
//unaligned memory access trap by writing 1 to the correct bit location of UNALIGN_TRP.
//needs to use a direct memory dereference of the CCR register to access the contents.

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
