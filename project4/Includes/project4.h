/**********************************
@file: project4.h
@brief:
@author: John Kim
@date:
***********************************/
#ifndef PROJECT4_H
#define PROJECT4_H

#include "logger.h"

void DUMP_STAT2();

void project4();
/***************************************************************
@brief:
****************************************************************/

void stat_update1(uint8_t data);

void logging(LogID_e id, uint32_t modID, uint32_t TS, uint32_t LL, char * PL, uint32_t cs);

void logging2(LogID_e id, uint32_t modID, uint32_t TS, uint32_t LL, char * ns, uint32_t cs);

void logging3(LogID_e id, uint32_t modID, uint32_t TS, uint32_t LL, char * pc, char * sp, uint32_t cs);

#endif /*project4*/
