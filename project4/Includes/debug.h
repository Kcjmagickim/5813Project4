/**********************************
@file: debug.h
@brief: header file for .c file
@author: John Kim
@date: Feb 1st, 2018
***********************************/

#ifndef DEBUG_H_
#define DEBUG_H_
#include <stdint.h>
/*Header file for debugging tools*/

void print_array(uint8_t *start, uint32_t length);
/***************************************
@brief: prints array of integer if VERBOSE flag is on. Depends on PRINTF macro
@param: start-beginning of the array 	length-number of elements wished to print out
@return: command line print out
****************************************/

#endif
