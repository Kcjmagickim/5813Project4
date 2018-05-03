/**********************************
@file: logger_queue.h
@brief: Implementation of the non blocking logger
@author: John Kim
@date: Apr 28th, 2018
***********************************/

#ifndef LOGGER_QUEUE_H
#define LOGGER_QUEUE_H

#include "logger.h"
#include <stdint.h>
#include <stdlib.h>

void LOG_ITEM(LogItem_t * log);
/**********************************
@param log - struct type containing the logging information
@brief: blocking logger
***********************************/

void log_item_nonblock(LogItem_t * log);
/**********************************
@param log - struct type containing the logging information
@brief: non blocking logger
***********************************/

#endif
