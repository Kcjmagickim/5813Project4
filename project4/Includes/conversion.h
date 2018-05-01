/**********************************
@file: conversion.h
@brief: header file for .c file
@author: John Kim
@date: Feb 1st, 2018
@revised: Feb 18th, 2018
***********************************/

#ifndef CONVERSION_H_
#define CONVERSION_H_

#include <stdint.h>

#define BASE_16 16
#define BASE_10 10
/*Header file for basic data manipulation*/

uint8_t my_itoa(int32_t data, uint8_t * ptr, uint32_t base);
/***************************************
@brief: converts interger value to its corresponding ASCII string
@param: data-integer ptr-beginning of the string base-numerical base such as decimal or hex
@return: length of the string including '-' and '\0'
****************************************/

int32_t my_atoi(uint8_t * ptr, uint8_t digits, uint32_t base);
/***************************************
@brief: converts an ASCII string to its corresponding numercal value
@param: ptr-locatin of the string digits-number of digits including '-' and '\0'
		base-numerical base
@return: converted integer value
****************************************/

#endif
