/**********************************
@file: data.c
@brief: Used to determine the size of various types.
#Also capable of determining endianness setting and performing
#swaps to accomodate different endianness
@author: John Kim
@date: Feb 3rd, 2018

Note: All function descriptions
resides in the header file.
***********************************/

#include "data.h"
#include <stdint.h>
#include <stddef.h>
#include "platform.h"

void print_cstd_type_sizes(){
	size_t temp;
	temp = sizeof(char);
	PRINTF("size of char = %zd", temp);
	temp = sizeof(short);
	PRINTF("size of short = %zd", temp);
	temp = sizeof(int);
	PRINTF("size of int = %zd", temp);
	temp = sizeof(long);
	PRINTF("size of long = %zd", temp);
	temp = sizeof(double);
	PRINTF("size of double = %zd", temp);
	temp = sizeof(float);
	PRINTF("size of float = %zd", temp);
	temp = sizeof(unsigned char);
	PRINTF("size of unsigned char = %zd", temp);
	temp = sizeof(unsigned int);
	PRINTF("size of unsigned int = %zd", temp);
	temp = sizeof(unsigned long);
	PRINTF("size of unsigned long = %zd", temp);
	temp = sizeof(signed char);
	PRINTF("size of signed char = %zd", temp);
	temp = sizeof(signed int);
	PRINTF("size of signed int = %zd", temp);
	temp = sizeof(signed long);
	PRINTF("size of signed long = %zd", temp);
}

void print_stdint_type_sizes(){
	size_t temp;
	temp = sizeof(int8_t);
	PRINTF("size of int8_t = %zd", temp);
	temp = sizeof(uint8_t);
	PRINTF("size of uint8_t = %zd", temp);
	temp = sizeof(int16_t);
	PRINTF("size of int16_t = %zd", temp);
	temp = sizeof(uint16_t);
	PRINTF("size of uint16_t = %zd", temp);
	temp = sizeof(int32_t);
	PRINTF("size of int32_t = %zd", temp);
	temp = sizeof(uint32_t);
	PRINTF("size of uint32_t = %zd", temp);
	temp = sizeof(uint_fast8_t);
	PRINTF("size of uint_fast8_t = %zd", temp);
	temp = sizeof(int_fast16_t);
	PRINTF("size of uint_fast16_t = %zd", temp);
	temp = sizeof(uint_fast32_t);
	PRINTF("size of uint_fast32_t = %zd", temp);
	temp = sizeof(uint_least8_t);
	PRINTF("size of uint_least8_t = %zd", temp);
	temp = sizeof(int_least16_t);
	PRINTF("size of uint_least16_t = %zd", temp);
	temp = sizeof(uint_least32_t);
	PRINTF("size of uint_least32_t = %zd", temp);
	temp = sizeof(size_t);
	PRINTF("size of size_t = %zd", temp);
	temp = sizeof(ptrdiff_t);
	PRINTF("size of ptrdiff_t = %zd", temp);
}

void print_pointer_sizes(){
	size_t temp;
	temp = sizeof(char *);
	PRINTF("size of char * = %zd", temp);
	temp = sizeof(short *);
	PRINTF("size of short * = %zd", temp);
	temp = sizeof(int *);
	PRINTF("size of int * = %zd", temp);
	temp = sizeof(long *);
	PRINTF("size of long * = %zd", temp);
	temp = sizeof(double *);
	PRINTF("size of double * = %zd", temp);
	temp = sizeof(float *);
	PRINTF("size of float * = %zd", temp);
	temp = sizeof(void *);
	PRINTF("size of void * = %zd", temp);
	temp = sizeof(int8_t *);
	PRINTF("size of int8_t * = %zd", temp);
	temp = sizeof(int16_t *);
	PRINTF("size of int16_t * = %zd", temp);
	temp = sizeof(int32_t *);
	PRINTF("size of int32_t * = %zd", temp);
	temp = sizeof(char **);
	PRINTF("size of char ** = %zd", temp);
	temp = sizeof(int **);
	PRINTF("size of int ** = %zd", temp);
	temp = sizeof(void **);
	PRINTF("size of void ** = %zd", temp);
}

int32_t swap_data_endianness(uint8_t * data, size_t type_length){
	if (!data) return SWAP_ERROR;
	int8_t bits = type_length/sizeof(*data);
	uint8_t i;
	uint8_t * end = data+bits-1;
	if (!end) return SWAP_ERROR;
	for (i=0; i<bits/2; i++){
		*data ^= *end;
		*end ^= *data;
		*data ^= *end;
		data++; end--;
	}
	return SWAP_NO_ERROR;
}

uint32_t determine_endianness(){
	uint32_t helper = 1;
	uint8_t * endian = (uint8_t *) &helper;
	if (*endian==1){return LITTLE_ENDIAN;}
	else if (*endian==0){return BIG_ENDIAN;}
	else return -1;
}
