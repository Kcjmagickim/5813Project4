/**********************************
@file: memory.c
@brief: Performs various memory manipulation including
dynamic allocation, moves, and swaps
@author: John Kim
@date: Feb 1st, 2018

Note: All function descriptions
resides in the header file.
***********************************/

#include "memory.h"
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

uint8_t * my_memmove(uint8_t *src, uint8_t *dst, size_t length){
	/*Given pointer and length, move from src to dst*/
	int i;
	uint8_t *ret=dst;
	if((dst-src)>0 && (dst-src)<length){
		src+=(length-1); dst+=(length-1);
		for(i=0; i<length; i++){
			*dst=*src;
			src--; dst--;
		}
	}
	else{
		for(i=0; i<length; i++){
			*dst=*src;
			src++; dst++;
		}
	}
	return ret;
}

uint8_t * my_memcpy(uint8_t * src, uint8_t * dst, size_t length){
	/*Given pointer and length, move from src to dst*/
	/*unlike memmove, no protection from overlapping memory*/
	int i;
	for(i=0; i<length; i++){
		*dst=*src;
		src++; dst++;
	}
	return dst;
}

uint8_t * my_memset(uint8_t *src, size_t length, uint8_t value){
	/*Given pointer and length, set values to value*/
	int i;
	for(i=0; i<length; i++){
		*src=value;
		src++;
	}
	return src;
}

uint8_t * my_memzero(uint8_t * src, size_t length){
	/*Given pointer and length, set values to zero*/
	int i;
	for(i=0; i<length; i++){
		*src=0;
		src++;
	}
	return src;
}

uint8_t * my_reverse(uint8_t *src, size_t length){
	/*Given pointer and length, reverse the bits*/
	int i;
	uint8_t *begin = src;
	uint8_t *end = src+(length-1);
	for(i=0; i<(length/2); i++){
		(*begin)^=(*end);
		(*end)^=(*begin);
		(*begin)^=(*end);
		begin++; end--;
	}
	return src;
}

void * reserve_words(size_t length){
	/*Given length, reserve dynamic word bits*/
	size_t * reserve;
	reserve = (size_t *)malloc (sizeof(size_t)*length);
	if(!reserve){return NULL;}
	else{return reserve;}
}

void free_words(uint32_t *src){
	/*Given pointer, free dynamic word bits*/
	if(!src){return;}
	free(src);
	src=NULL;
	return;
}
