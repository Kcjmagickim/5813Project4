/**********************************
@file: circbuf.c
@brief: circular buffer functions
To be used to send and receive uart data
@author: John Kim
@date: Feb 23rd, 2018

Note: All function descriptions
resides in the header file.
***********************************/

#include <stdlib.h>
#include <stdint.h>
#include "circbuf.h"
#include "systick.h"
#include "uart.h"

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
	START_CRITICAL;
	if (!buf) return NULL_PTR;
	if (buf->count == buf->length) return FULL;
	*(buf->tail) = in;
	buf->count++;
	if(buf->tail == buf->end){
		buf->tail=buf->begin;
	}else{
		(buf -> tail) ++;
	}
	END_CRITICAL;
	return SUCCESS;
}

CB_e CB_buffer_remove_item(CB_t *buf, uint8_t * out){
	START_CRITICAL;
	if (!buf | !out) return NULL_PTR;
	if (buf->count == 0) return EMPTY;
	*out = *(buf->head);
	buf->count--;
	if(buf->head == buf->end){
		buf->head=buf->begin;
	}else{
		(buf -> head) ++;
	}
	END_CRITICAL;
	return SUCCESS;
}

CB_e CB_peek(CB_t *buf, size_t position, uint8_t * peek){
	if (!buf) return NULL_PTR;
	if (position<=0) return NULL_PTR;
	uint8_t *ptr = (uint8_t *) buf->begin + position*sizeof(uint8_t);
	*peek = *(ptr);
	return SUCCESS;
}
