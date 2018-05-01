/**********************************
@file: platform.h
@brief: header file for .c file
@author: John Kim
@date: Feb 4th, 2018
***********************************/

#ifndef PLATFORM_H_
#define PLATFORM_H_
#include <stdarg.h>
#include <stdio.h>

/***************************************
@brief: PRINTF macro
****************************************/

#ifdef KL25Z
	#define PRINTF(...) NULL
#else
	#define PRINTF(...) printf(__VA_ARGS__)
#endif/*KL25z*/

#endif/*PLATFORM_H*/
