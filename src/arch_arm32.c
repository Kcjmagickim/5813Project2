/**********************************
@file: arch_arm32.c
@brief: 
@author: John Kim
@date: Feb 17th, 2018

Note: All function descriptions 
resides in the header file.
***********************************/

#include "arch_arm32.h"
#include <stdint.h>

uint32_t ARM32_CCR_get_stack_alignment(){
	return ((__CCR & __CCR_STK_ALIGNMENT_MASK) >> __CCR_STK_ALIGNMENT_OFFSET);
}
//read the ARM Configuration and Control Register (CCR) and
//return the stack alignment value of the current configured ARM processor.
//use a direct memory dereference of the CCR register to access the contents.
//should directly return the value of the alignment.
//0 = 4-byte aligned 	1 = 8-Byte aligned

uint32_t ARM32_CPUID_get_part_number(){
	return ((__CPUID & __CPUID_PART_NO_MASK) >> __CPUID_PART_NO_OFFSET);
}
//needs to read the ARM CPU ID Register (CPUID) and return the value of
//the Part Number for the current ARM processor.
//direct memory dereference of the CPUID register in order to access the contents.
//directly return the value of the part number. Cortex-M4 should return the value 0xC24.

uint32_t ARM32_CCR_enable_divide_by_zero_trap(){
	* (int32_t *) (__SCB_ADDRESS+__CCR_ADDRESS_OFFSET) = __CCR | __CCR_DIVIDE_BY_ZERO_TRAP_MASK;
	return 0;
}
//needs to write to the ARM Configuration and Control Register (CCR) to set
//a divide by zero trap by writing a 1 to the correct bit location of DIV_0_TRP.
//direct memory dereference of the CCR register in order to access the contents.

uint32_t ARM32_CCR_enable_unaligned_access_trap(){
	* (int32_t *) (__SCB_ADDRESS+__CCR_ADDRESS_OFFSET) = __CCR | __CCR_UNALIGNED_ACCESS_TRAP_MASK;
	return 0;
}
//needs to write to the ARM Configuration and Control Register (CCR) to set
//unaligned memory access trap by writing 1 to the correct bit location of UNALIGN_TRP.
//needs to use a direct memory dereference of the CCR register to access the contents.

void ARM32_create_unaligned_access_trap(){
	int8_t TRAP= * (int8_t *) 0xE000ED15;
	UNUSED(TRAP);
}

void ARM32_create_divide_by_zero_trap(){
	int8_t TRAP= 0;
	int8_t TRAP1= 1/TRAP;
	UNUSED(TRAP1);
}
//should perform a divide by zero in order to trigger a trap or exception on
//the microcontroller.
//should not return and a UsageFault Exception should be called
//automatically upon execution of the error causing line of c