/**********************************
@file: logger_queue.h
@brief: Implementation of the partial logging and blocking logger
@author: John Kim
@date: Apr 28th, 2018
***********************************/

#ifndef LOGGER_H
#define LOGGER_H

#include <stdint.h>
#include <stdlib.h>

typedef enum {
	SYSTEM_ID = 10,
	SYSTEM_VERSION,
	LOGGER_INITIALIZED,
	GPIO_INITIALIZED,
	SYSTEM_INITIALIZED,
	SYSTEM_HALTED,
	INFO,
	WARNING,
	ERROR,
	PROFILING_STARTED,
	PROFILING_RESULT,
	PROFILING_COMPLETED,
	DATA_RECEIVED,
	DATA_ANALYSIS_STARTED,
	DATA_ALPHA_COUNT,
	DATA_NUMERIC_COUNT,
	DATA_PUNCTUATION_COUNT,
	DATA_MISC_COUNT,
	DATA_ANALYSIS_COMPLETED,
	HEARTBEAT,
	CORE_DUMP,
} LogID_e;

typedef struct {
	LogID_e ID;
	uint32_t moduleID;
	uint32_t timestamp;
	uint32_t LogL;
	char * payload;
	uint32_t checksum;
} LogItem_t;

void LOG_RAW_DATA(uint8_t * src, uint32_t length);
void log_data(uint8_t * src, uint32_t length);
void printf_data(uint8_t * src, uint32_t length);
/**********************************
@param src - string to log length - of the string
@brief: log the payload (KL25z or BBB)
***********************************/

void LOG_RAW_STRING(char * str);
void log_string(char * str);
void LOG_RAW_INTEGER(uint32_t integer);
/**********************************
@param src - string to log length - of the string
@brief: log the string (KL25z or BBB)
***********************************/

void log_integer(uint32_t integer);
void log_flush();
void LOG_RAW_ITEM(LogItem_t * log);
/**********************************
@param integer - integer to log
@brief: log the integer (KL25z or BBB)
***********************************/

void log_item(LogItem_t * log);
void log_item_printf(LogItem_t * log);
/**********************************
@param log - logging block
@brief: call series of loggers
***********************************/


void logging(LogID_e id, uint32_t modID, uint32_t TS, uint32_t LL, char * PL, uint32_t cs);
void logging2(LogID_e id, uint32_t modID, uint32_t TS, uint32_t LL, char * ns, uint32_t cs);
void logging3(LogID_e id, uint32_t modID, uint32_t TS, uint32_t LL, char * pc, char * sp, uint32_t cs);
/**********************************
@param id - logid modid - module id ts - time ll - log length pl - payload cs - checksum
@brief: log the integer (KL25z or BBB)
***********************************/

#endif
