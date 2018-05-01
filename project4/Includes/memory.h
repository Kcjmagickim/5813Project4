/**********************************
@file: memory.h
@brief: header file for .c file
@author: John Kim
@date: Feb 1st, 2018
***********************************/

#ifndef MEMORY_H_
#define MEMORY_H_
#include <stdint.h>
#include <stddef.h>

/*Header file for memeory manipulation functions*/

uint8_t * my_memmove(uint8_t *src, uint8_t *dst, size_t length);
/***************************************
@brief: moves from the source to destination. Coded to
		protect from corruption due to overlapping memory address
@param: src-place to get the copy 	dst-place to paste 	length-number of elements to copy
@return: destination pointer(dst)
****************************************/

uint8_t * my_memcpy(uint8_t *src, uint8_t *dst, size_t length);
/***************************************
@brief: same as my_memmove but does not provide protection from
		overlapping memory address
****************************************/

uint8_t * my_memset(uint8_t *src, size_t length, uint8_t value);
/***************************************
@brief: sets length bytes to given value
@param: src-location at which value setting starts		length-number of bytes to set
		value-value to set
@return: src
****************************************/

uint8_t * my_memzero(uint8_t *src, size_t length);
/***************************************
@brief: equivalent to my_memset with value=0
****************************************/

uint8_t * my_reverse(uint8_t *src, size_t length);
/***************************************
@brief: reverses the order of length bytes of memory value
@param: src-location at which reversing should start 	length-number of bytes to reverse
@return: src
****************************************/

void * reserve_words(size_t length);
/***************************************
@brief: reserves length number of size_t, determined by variable type of input
@param: length-number of word that needs to be allocated
@return: pointer to the beginning of the allocated memory
****************************************/

void free_words(uint32_t *src);
/***************************************
@brief: frees the dynamically allocated memory
@param: src-location of the allocated memory
@return: void
****************************************/

#endif
