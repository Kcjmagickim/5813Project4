/**********************************
@file: project4.h
@brief: main function to get called
@author: John Kim
@date: Apr 29th, 2018
***********************************/
#ifndef PROJECT4_H
#define PROJECT4_H

#include "logger.h"

void DUMP_STAT2();

void project4();
/***************************************************************
@brief: Combines logging and project 2
****************************************************************/

void stat_update1(uint8_t data);
void logging(LogID_e id, uint32_t modID, uint32_t TS, uint32_t LL, char * PL, uint32_t cs);
void logging2(LogID_e id, uint32_t modID, uint32_t TS, uint32_t LL, char * ns, uint32_t cs);
void logging3(LogID_e id, uint32_t modID, uint32_t TS, uint32_t LL, char * pc, char * sp, uint32_t cs);
/***************************************************************
@brief: Logger.h for more information
****************************************************************/

#endif /*project4*/
