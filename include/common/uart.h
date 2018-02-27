#ifndef UART_H
#define UART_H


#define 
<type> UART_configure ();
//Configures UART to the given settings.
//No hardcoded configurations need to use predefined Bit Masks
//and macro functions to help determine calculated values

<type> UART_send ( <data-to-send> );
//send a single byte down a specific UART device
//1 argument: Pointer to the data item to send
//This function should block on transmitting data

<type> UART_send_n ( <data-to-send>, <length-of-data> );
//2 arguments: 
//Pointer to a contiguous block of data that needs to be transmitted
//Number of items to transmit
//This function should block on transmitting data

<type> UART_receive( data );
//return a received byte on the UART using an input parameter pointer.
//should block until a character has been received.

<type> UART_receive_n ( <received-data>, <length-of-data-to-receive> );
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

#endif /*uart*/