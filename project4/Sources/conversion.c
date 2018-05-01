/**********************************
@file: conversion.c
@brief: converts between integer and hex value
@author: John Kim
@date: Feb 3rd, 2018
@revised: Feb 18th, 2018
Note: All function descriptions
resides in the header file.
***********************************/

#include "conversion.h"
#include <stdint.h>
#include <stdio.h>

uint8_t my_itoa(int32_t data, uint8_t * ptr, uint32_t base){
	if(!ptr) return -1;
	int8_t exp = 0;
	int8_t rem, i;
	int8_t neg = 0;
	int32_t val = data;
	if (base>16 || base<2) return -1;
	if(val>0){
		while(val>0){
			val/=base;
			exp++;
		}
	}else if(val==0){
		exp++;
	}else{
		val*=-1;
		while(val>0){
			val/=base;
			exp++;
		}
		exp++;
		data*=-1;
		neg=1;
	}

	ptr += exp;
	*ptr = '\0';
	ptr--;
	for (i=0;i<exp-1;i++){
		rem=data%base;
		data/=base;
		*ptr= (char) (rem+'0');
		ptr--;
	}
	if(neg){
		*ptr='-';
	}
	else{
		*ptr= (char) (data+'0');
	}
	return exp+1;
}

int32_t my_atoi(uint8_t * ptr, uint8_t digits, uint32_t base){
	int8_t i;
	int32_t val = 0;
	int8_t neg = 0;
	if(!ptr) return -1;
	if (base>16 || base<2) return -1;
	if (*ptr == '-'){
		neg=1;
		digits--;
		ptr++;
	}
	for(i=0; i<digits-1; i++){
		val= base*val+((uint8_t) (*ptr-'0'));
		ptr++;
	}

	if (neg){
		val*=-1;
	}
	return val;
}
