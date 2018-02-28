/**********************************
@file: port.c
@brief: 
@author: John Kim
@date: Feb 21st, 2018
***********************************/
#include "MKL25Z4.h"
#include "port.h"

void GPIO_Configure(){
	if(!(PTD_BASE_PTR->PDDR & RGB_BLUE_PIN) || !(PTB_BASE_PTR->PDDR & RGB_GREEN_PIN)
	 || !(PTB_BASE_PTR->PDDR & RGB_RED_PIN)){
		PTB_BASE_PTR->PDDR |= (RGB_RED_PIN + RGB_GREEN_PIN);
		PTD_BASE_PTR->PDDR |= RGB_BLUE_PIN;
	}
}

void Toggle_Red_LED(){
	PTB_BASE_PTR->PTOR |= RGB_RED_PIN;
}//Toggle the Red LED state. On to Off, or Off to on.

void PORTB_Set(uint8_t bit_num){
	uint32_t set = 0x1 << bit_num;
	PTB_BASE_PTR->PSOR |= set;
}

void PORTD_Set(uint8_t bit_num){
	uint32_t set = 0x1 << bit_num;
	PTD_BASE_PTR->PSOR |= set;
}//These two functions should use the appropriate GPIO function to toggle the output (PSOR)

void PORTB_Clear(uint8_t bit_num){
	uint32_t clear = 0x1 << bit_num;
	PTB_BASE_PTR->PCOR |= clear;
}

void PORTD_Clear(uint8_t bit_num){
	uint32_t clear = 0x1 << bit_num;
	PTD_BASE_PTR->PCOR |= clear;
}//These two functions should use the appropriate GPIO function to toggle the output (PCOR)

void PORTB_Toggle(uint8_t bit_num){
	uint32_t clear = 0x1 << bit_num;
	PTB_BASE_PTR->PTOR |= clear;
}

void PORTD_Toggle(uint8_t bit_num){
	uint32_t clear = 0x1 << bit_num;
	PTD_BASE_PTR->PTOR |= clear;
}
//These two functions should use the appropriate GPIO function to toggle the output (PTOR)


#define RGB_RED_ON()     (PORTB_Set( RGB_RED_PIN ))
#define RGB_RED_OFF()    (PORTB_Clear( RGB_RED_PIN ))
#define RGB_RED_TOGGLE() (PORTB_Toggle( RGB_RED_PIN ))

#define RGB_GREEN_ON()     (PORTB_Set( RGB_GREEN_PIN ))
#define RGB_GREEN_OFF()    (PORTB_Clear( RGB_GREEN_PIN ))
#define RGB_GREEN_TOGGLE() (PORTB_Toggle( RGB_GREEN_PIN ))

#define RGB_BLUE_ON()     (PORTB_Set( RGB_BLUE_PIN ))
#define RGB_BLUE_OFF()    (PORTB_Clear( RGB_BLUE_PIN ))
#define RGB_BLUE_TOGGLE() (PORTB_Toggle( RGB_BLUE_PIN ))