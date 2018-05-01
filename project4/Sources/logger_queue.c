#include "logger_queue.h"
#include <stdint.h>
#include "uart.h"
#include "logger.h"
#include "conversion.h"
#include <stdio.h>

char newline1[3] = "\n";
char space1[3] = " ";

void LOG_ITEM(LogItem_t * log){
	#ifdef KL25Z
		log_item_nonblock(log);
	#endif
}

void log_item_nonblock(LogItem_t * log){
	log_integer((uint32_t) log->ID);
	UART_send(space1);
	log_integer((uint32_t) log->moduleID);
	UART_send(space1);
	log_integer(log->timestamp);
	log_integer(log->LogL);
	UART_send(space1);
	log_string(log->payload);
	UART_send(space1);
	log_integer(log->checksum);
	UART_send(newline1);
}
