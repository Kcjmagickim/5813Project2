/**********************************
@file: circbuf.h
@brief: header file for .c file
@author: John Kim
@date: Feb 23rd, 2018
***********************************/
#ifndef CIRCBUF_H
#define CIRCBUF_H

typedef struct {
	uint8_t * begin;
	uint8_t * end;
	uint8_t * head;
	uint8_t * tail;
	size_t length;
	size_t count;
} CB_t;

typedef enum {
	SUCCESS;
	NULL_PTR;
	NO_LENGTH;
	FULL;
	EMPTY;
} CB_e;


CB_e CB_init(CB_t *buf, size_t length);

//returns the status of the circular buffer or an error codes
//The circular buffer structure needs to be allocated in heap memory
//The circular buffer memory array pointed to by the base pointer 
//needs to be allocated in heap memory
//allocate length number of items for the buffer memory section
//Two independent dynamic memory allocations should be called
//must check for success/failure from the return of malloc
//After allocating memory, the buffer members should properly initialize the buffer pointer
//head, tail, the length, and the count.

CB_e CB_destroy(CB_t *buf);
//The functions takes in a pointer to the circular buffer to be destroyed
//should deallocate both the structure and buffer memory region of heap memory using free
//returns the status of the circular buffer
//circular buffer pointer should be reset to NULL after all memory is returned to the heap

CB_e CB_buffer_add_item(CB_t *buf, uint8_t in);
//2 arguments: Pointer to the circular buffer to add items	data to be added
//returns an enumeration that specifies the success, failure etc. of the function call
//consider the corner cases possible

CB_e CB_buffer_remove_item(CB_t *buf, uint8_t out);
//2 arguments: Pointer to the circular buffer  Variable to store/return the removed item
//returns an enumeration that specifies the success, failure etc. of the function call
//Must take into consideration the corner cases possible

CB_e CB_is_full(CB_t *buf)_attribute__((always_inline)) inline __INLINE;
//check if it is full
//0 = Buffer is not full 	1 = Buffer is full
//should be implemented as an inline function with a few as operations as possible.

CB_e CB_is_empty(CB_t *buf) _attribute__((always_inline)) inline __INLINE;
The function will take in the circular buffer pointer to check if it is empty
//0 = Buffer is not empty 	1 = Buffer is empty
//should be implemented as an inline function with a few as operations as possible.

CB_e CB_peek(CB_t *buf, size_t position,  uint8_t peek);
//3 args: Pointer to the circular buffer 	position from the head of the buffer to peek into
//A pointer to hold the data you peeked at
//returns the status of the circular buffer or an error codes
//Must take into consideration the corner cases possible

//Define a two new macro function called that correctly enable/disable interrupts:
#define START_CRITICAL
#define END_CRITICAL

#endif /*circbuf*/