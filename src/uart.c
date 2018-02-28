#include "uart.h"
#include "MLK25Z.h"

void UART_configure (){
	SIM_SCGC4_REG(SIM) &= ~(0x400);
	SIM_SOPT_REG(SIM) &= 0xC000000;	//turn off UART0

	UART0->BDH |= ;	//baud rate
	
	SIM_SCGC4_REG(SIM) |= 0x400;	//turn on UART0
	SIM_SOPT_REG(SIM) = (SIM_SOPT_REG(SIM) | 0x4000000) & !(0x8000000);
	
}
//Configures UART to the given settings.
//No hardcoded configurations.need to use predefined Bit Masks
//and macro functions to help determine calculated values

void UART_send (unsigned char * src){
	UART0_C2 |= 0x8;	//transmitter enabled
	while((UART0_S1 & 0xC0) != 0xC0);
	UART0_D = *src;
}
//send a single byte down a specific UART device
//1 argument: Pointer to the data item to send
//This function should block on transmitting data

void UART_send_n (unsigned char * src, int32_t length){
	UART0_C2 |= 0x8;	//transmitter enabled
	uint32_t cnt = 0;
	while(cnt<length){
		while((UART0_S1 & 0xC0) != 0xC0){}
		UART0_D = *src;
		cnt++; src++;
	}
}
//2 arguments: 
//Pointer to a contiguous block of data that needs to be transmitted
//Number of items to transmit
//This function should block on transmitting data

void UART_receive(unsigned char * dst){
	UART0_C2 |= 0x4;	//receiver enabled
	while((UART0_S1 & 0x20) == 0){}
	*dst = UART0_D;
	UART0_C2 &= !(0x4);	//receiver disabled
}
//return a received byte on the UART using an input parameter pointer.
//should block until a character has been received.

void UART_receive_n ( * dst, int32_t length ){
	UART0_C2 |= 0x4;	//receiver enabled
	uint32_t cnt = 0;
	while(cnt<length){
		while((UART0_S1 & 0x20) == 0){}
		*dst = UART0_D;
		cnt++; data++;
	}
	UART0_C2 &= !(0x4);	//receiver disabled
}

//should receive a number of bytes on the UART.
//2 arguments 
//Pointer to a memory location to place data that is being received
//Number of items to receive
//should block until a number of characters have been received.

void UART0_IRQHandler();
//This function is the IRQ handler for the UART.
//need to handle two types of interrupts in this function
//Receive Interrupts
//Transmit interrupt
//Each interrupt should clear their associated flag when completed but only if they were set
//This routine should be as short as possible
