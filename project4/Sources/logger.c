/**********************************
@file: logger_queue.c
@brief: Implementation of the partial logging and blocking logger
@author: John Kim
@date: Apr 28th, 2018
***********************************/

#include <stdint.h>
#include "uart.h"
#include "logger.h"
#include "conversion.h"
#include <stdio.h>

char number[10] = "";
char newline[3] = "\n";
char space[3] = " ";


void LOG_RAW_DATA(uint8_t * src, uint32_t length){
	#ifdef BBB
	printf_data(src, length);
	#elif KL25Z
	log_data(src, length);
	#endif
}

//blocking log: just output binary
void log_data(uint8_t * src, uint32_t length){
	uint8_t digits;
	while(length>0){
		number[0] = '\0';
		digits=my_itoa((uint32_t) * src, number, 2);
		UART_send_n(number, digits-1);
	}
}

//BBB logging
void printf_data(uint8_t * src, uint32_t length){
	while(length>0){
		printf("%c", *(char*)src);
		src++; length--;
	}
}

void LOG_RAW_STRING(char * str){
	#ifdef BBB
	printf("%s", str);
	#elif KL25Z
	log_string(str);
	#endif
}

void log_string(char * str){
	UART_send_string(str);
}

void LOG_RAW_INTEGER(uint32_t integer){
	#ifdef BBB
	printf("%z", integer);
	#elif KL25Z
	log_integer(integer);
	#endif
}

void log_integer(uint32_t integer){
	uint8_t digits;
	number[0] = '\0';
	digits=my_itoa(integer, number, 10);
	UART_send_n(number, digits-1);
}

void LOG_RAW_ITEM(LogItem_t * log){
	#ifdef BBB
	log_item_printf(log);
	#elif KL25Z
	log_item(log);
	#endif
}

void log_item(LogItem_t * log){
	log_integer((uint32_t) log->ID);
	UART_send(space);
	log_integer((uint32_t) log->moduleID);
	UART_send(space);
	log_integer(log->LogL);
	UART_send(space);
	log_string(log->payload);
	UART_send(space);
	log_integer(log->checksum);
	UART_send(space);
	if((log->ID == GPIO_INITIALIZED) || (log->ID == LOGGER_INITIALIZED)){
		UART_send("1");UART_send("0");
	}
	log_integer(log->timestamp);
	UART_send(newline);
}

void log_item_printf(LogItem_t * log){
	printf("%z ", (uint32_t) log->ID);
	printf("%z ", log->moduleID);
	printf("%z ", log->timestamp);
	printf("%z ", log->LogL);
	printf("%s ", log->payload);
	printf("%z\n", log->checksum);
}

void log_flush(){
	while(!CB_is_empty(CB_tx));
}


void logging(LogID_e id, uint32_t modID, uint32_t TS, uint32_t LL, char * PL, uint32_t cs){
	LogItem_t * check = malloc(sizeof(LogItem_t));
	check -> ID = id;
	check -> moduleID = modID;
	check -> timestamp = TS;
	check -> LogL = LL;
	check -> payload = PL;
	check -> checksum = cs;
	#ifdef DEBUG
	log_item(check);
	log_flush();
	free(check);
	#endif
}


void logging2(LogID_e id, uint32_t modID, uint32_t TS, uint32_t LL, char * ns, uint32_t cs){
	log_integer(id);
	UART_send(space);
	log_integer((uint32_t) modID);
	UART_send(space);
	log_integer(LL);
	UART_send(space);
//	log_string("Execution took");
//	UART_send(space);
	log_string(ns);
	UART_send(space);
	log_integer(cs);
	UART_send(space);
//	log_string("clock cycles");
//	UART_send(space);
	log_integer(TS);
	UART_send(newline);
	log_flush();
}

void logging3(LogID_e id, uint32_t modID, uint32_t TS, uint32_t LL, char * pc, char * sp, uint32_t cs){
	log_integer(id);
	UART_send(space);
	log_integer((uint32_t) modID);
	UART_send(space);
	log_integer(LL);
	UART_send(space);
	log_string("Current PC is:");
	UART_send(space);
	log_string(pc);
	UART_send(space);
	log_string("Current Stack Pointer is:");
	UART_send(space);
	log_string(sp);
	UART_send(space);
	log_integer(cs);
	UART_send(space);
	log_integer(TS);
	UART_send(newline);
	log_flush();
}
