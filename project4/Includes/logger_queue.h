#ifndef LOGGER_QUEUE_H
#define LOGGER_QUEUE_H

#include "logger.h"
#include <stdint.h>
#include <stdlib.h>

void LOG_ITEM(LogItem_t * log);

void log_item_nonblock(LogItem_t * log);

#endif
