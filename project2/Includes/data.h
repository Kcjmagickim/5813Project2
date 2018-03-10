/**********************************
@file: data.h
@brief: header file for .c file
@author: John Kim
@date: Feb 1st, 2018
***********************************/

#ifndef DATA_H_
#define DATA_H_
#include <stddef.h>
#include <stdint.h>

#define LITTLE_ENDIAN  0
#define BIG_ENDIAN 1
#define SWAP_NO_ERROR  0
#define SWAP_ERROR  -1

void print_cstd_type_sizes();
/***************************************
@brief: help determine the byte size of various types
@return: prints out size of char, int, long, double, float, etc.
****************************************/

void print_stdint_type_sizes();
/***************************************
@brief: help determine the byte size of various standart integers
@return: prints out size of int8_t, uint16_t, size_t, etc.
****************************************/

void print_pointer_sizes();
/***************************************
@brief: help determine the byte size of various types of pointers
@return: prints out size of int*, void*, char**, etc
****************************************/

int32_t swap_data_endianness(uint8_t * data, size_t type_length);
/***************************************
@brief: convert data from one endianness to another
@param: data-location of the first byte 	type_length-length of the type that needs swap
@return: SWAP_ERROR or SWAP_NO_ERROR
****************************************/

uint32_t determine_endianness();
/***************************************
@brief: determines the current endianness
@return: BIG_ENDIAN or LIttlE_ENDIAN
****************************************/

#endif /*Data.h*/
