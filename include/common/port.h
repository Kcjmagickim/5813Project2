/**********************************

@file: port.h

@brief: header file for .c file

@author: John Kim

@date: Feb 17th, 2018

***********************************/

#include "MKL25Z4.h"

#ifndef PORT_H

#define PORT_H



//You will also create 4 specific definitions that map to the correct Red RGB LED, Green RGB LED

//and Blue RGB LED pin values. Those should look some like:

#define RGB_RED_PIN       18

#define RGB_GREEN_PIN     19

#define RGB_BLUE_PIN      1



void GPIO_Configure();

//Configures the RGB LEDs to be output with their initial values.



void Toggle_Red_LED();

//Toggle the Red LED state. On to Off, or Off to on.



void PORTB_Set(uint8_t bit_num);

void PORTD_Set(uint8_t bit_num);

//These two functions should use the appropriate GPIO function to toggle the output (PSOR)



void PORTB_Clear(uint8_t bit_num);

void PORTD_Clear(uint8_t bit_num);

//These two functions should use the appropriate GPIO function to toggle the output (PCOR)



void PORTB_Toggle(uint8_t bit_num);

void PORTD_Toggle(uint8_t bit_num);

//These two functions should use the appropriate GPIO function to toggle the output (PTOR)







//Both register and platform constants or registers that can be defined in a register

//definition file. Can also have Board Support Package (BSP) which contains

//definitions specific for your specific PCB. These functions Port 1 and Port 2

//functions can be used in a BSP file so you can create even more readable and specialized

// RGB access macros using a #define specific to your board. These would look like this:

#define RGB_RED_ON()     (PORTB_Clear( RGB_RED_PIN ))

#define RGB_RED_OFF()    (PORTB_Set( RGB_RED_PIN ))

#define RGB_RED_TOGGLE() (PORTB_Toggle( RGB_RED_PIN ))


#define RGB_GREEN_ON()     (PORTB_Clear( RGB_GREEN_PIN ))

#define RGB_GREEN_OFF()    (PORTB_Set( RGB_GREEN_PIN ))

#define RGB_GREEN_TOGGLE() (PORTB_Toggle( RGB_GREEN_PIN ))


#define RGB_BLUE_ON()     (PORTD_Clear( RGB_BLUE_PIN ))

#define RGB_BLUE_OFF()    (PORTD_Set( RGB_BLUE_PIN ))

#define RGB_BLUE_TOGGLE() (PORTD_Toggle( RGB_BLUE_PIN ))



#endif /*port*/
