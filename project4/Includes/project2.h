/**********************************
@file: project2.h
@brief: main execution of program happens here
@author: John Kim
@date: Mar 5th, 2018
***********************************/
#ifndef PROJECT2_H
#define PROJECT2_H

#include <stdint.h>

void project2();
/***************************************************************
@brief: call various function to initialize uart, gpio, and
        perform a serial transmission and reception
****************************************************************/

void stat_update(uint8_t data);
/***************************************************************
@brief: responsible for updating number of chracters after
        classifying them into appropriate category
@param: data - categorize to right type (alphabet, punctuation, etc)
****************************************************************/

uint8_t ispunc(uint8_t data);
/***************************************************************
@brief: helper function for stat_update. Determines if punctuation or not
@param: data - compared with thirteen ascii punctuations
@return: 1 if punctuation, 0 else
****************************************************************/

void DUMP_STAT();
/***************************************************************
@brief: equivalent to printf. Displays analysis result
****************************************************************/

#endif /*project2*/
