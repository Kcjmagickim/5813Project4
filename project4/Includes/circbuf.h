/**********************************
@file: circbuf.h
@brief: circular buffer functions
To be used to send and receive uart data
@author: John Kim
@date: Feb 3rd, 2018

Note: All function descriptions
resides in the header file.
***********************************/
#ifndef CIRCBUF_H
#define CIRCBUF_H

#include "core_cmFunc.h"
#include <stdio.h>
#include <stdint.h>

typedef struct {
	uint8_t * begin;
	uint8_t * end;
	uint8_t * head;
	uint8_t * tail;
	size_t length;
	size_t count;
} CB_t;
/*******************************************************
@brief: Circular buffer type. LIFO buffer for byte data
*******************************************************/

typedef enum {
	SUCCESS,
	NULL_PTR,
	NO_LENGTH,
	FULL,
	EMPTY,
} CB_e;
/*************************************************
@brief: CB return type enumeration.
		Error type or success
**************************************************/

CB_e CB_init(CB_t *buf, size_t length);
/***************************************************************
@brief: initializes circular buffer on heap
@param: buf - base pointer to the CB_t * type where
		all circular buffer parameters will be initialized
		length - number of elements buffer should store
@return: SUCCESS or error type
****************************************************************/

CB_e CB_destroy(CB_t *buf);
/***************************************************************
@brief: destroys circular buffer on heap
@param: buf - base pointer to the CB_t * type where
		all circular buffer memory will be deallocated/nullified
@return: SUCCESS or error type
****************************************************************/

CB_e CB_buffer_add_item(CB_t *buf, uint8_t in);
/***************************************************************
@brief: adds a byte to circular buffer tail
@param: buf - base pointer to the CB_t * type where
		a byte will be added
		in - input data to be added
@return: SUCCESS or error type
****************************************************************/

CB_e CB_buffer_remove_item(CB_t *buf, uint8_t * out);
/***************************************************************
@brief: removes a byte to circular buffer tail
@param: buf - base pointer to the CB_t * type where
		a byte will be added
		out - dereferenced to store the removed data
@return: SUCCESS or error type
****************************************************************/

__attribute__((always_inline)) static inline CB_e CB_is_full(CB_t *buf){
	if (!buf) return NULL_PTR;
	return (buf->count == buf->length) ? 1 : 0;
}
/***************************************************************
@brief: checks if the buffer is full
@param: buf - buffer to check
@return: 1 if full, 0 if not
****************************************************************/

__attribute__((always_inline)) static inline CB_e CB_is_empty(CB_t *buf){
	if (!buf) return NULL_PTR;
	return (buf->count == 0) ? 1 : 0;
}
/***************************************************************
@brief: checks if the buffer is empty
@param: buf - buffer to check
@return: 1 if empty, 0 if not
****************************************************************/

CB_e CB_peek(CB_t *buf, size_t position,  uint8_t * peek);
/***************************************************************
@brief: checks a data value of buffer without interfering with it.
@param: buf - buffer to peek
		position - position of the buffer to peek, counting from head
		peek - stores the peeked value
@return: 1 if full, 0 if not
****************************************************************/

#define START_CRITICAL	  __disable_irq()
#define END_CRITICAL	__enable_irq()
/***************************************************************
@brief: Important Macro that can protect buffer operations from
		interrupts. Either disable or enables interrups globally
****************************************************************/

#endif /*circbuf*/
