#include <stdlib.h>
#include <stdint.h>
#include "circbuf.h"

CB_e CB_init(CB_t *buf, size_t length){
	if (!buf) return NULL_PTR;
	if (length <= 0) return NO_LENGTH;
	buf -> begin = malloc(length * sizeof(uint8_t));
	if (!(buf -> begin)) return NULL_PTR;
	buf -> end = buf -> begin + (length-1) * sizeof(uint8_t);
	buf ->length = length;
	buf -> head = buf -> begin;
	buf -> tail = buf -> begin;
	buf -> count = 0;
	return SUCCESS;
}

CB_e CB_destroy(CB_t *buf){
	if (!buf) return NULL_PTR;
	free(buf->begin);
	buf -> tail = NULL;
	buf -> head = NULL;
	buf -> tail = NULL;
	buf -> length = 0;
	return SUCCESS;
}

CB_e CB_buffer_add_item(CB_t *buf, uint8_t in){
	if (!buf) return NULL_PTR;
	if (buf->count == buf->length) return FULL;
	*(buf->tail) = in;
	buf->count++;
	if(buf->tail == buf->end){
		buf->tail=buf->begin;
	}else{
		(buf -> tail) ++;
	}
	return SUCCESS;
}
//2 arguments: Pointer to the circular buffer to add items	data to be added
//returns an enumeration that specifies the success, failure etc. of the function call
//consider the corner cases possible

CB_e CB_buffer_remove_item(CB_t *buf, uint8_t * out){
	if (!buf | !out) return NULL_PTR;
	if (buf->count == 0) return EMPTY;
	*out = *(buf->head);
	buf->count--;
	if(buf->head == buf->end){
		buf->head=buf->begin;
	}else{
		(buf -> head) ++;
	}
	return SUCCESS;
}

//2 arguments: Pointer to the circular buffer  Variable to store/return the removed item
//returns an enumeration that specifies the success, failure etc. of the function call
//Must take into consideration the corner cases possible

/*CB_e CB_is_full(CB_t *buf){
	if (!buf) return NULL_PTR;
	return (buf->count == buf->length) ? FULL : 0;
}
//check if it is full
//0 = Buffer is not full 	1 = Buffer is full
//should be implemented as an inline function with a few as operations as possible.

CB_e CB_is_empty(CB_t *buf){
	if (!buf) return NULL_PTR;
	return (buf->count == 0) ? EMPTY : 0;
}
//The function will take in the circular buffer pointer to check if it is empty
//0 = Buffer is not empty 	1 = Buffer is empty
//should be implemented as an inline function with a few as operations as possible.
*/

CB_e CB_peek(CB_t *buf, size_t position, uint8_t peek){
	if (!buf) return NULL_PTR;
	if (position<=0) return NULL_PTR;
	uint8_t *ptr = (uint8_t *) buf->begin + position*sizeof(uint8_t);
	peek = *(ptr);
	return SUCCESS;
}
//3 args: Pointer to the circular buffer 	position from the head of the buffer to peek into
//A pointer to hold the data you peeked at
//returns the status of the circular buffer or an error codes
//Must take into consideration the corner cases possible