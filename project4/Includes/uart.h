/**********************************
@file: uart.h
@brief: Provdies control over UART
@author: John Kim
@date: Mar 2nd, 2018
***********************************/

#ifndef UART_H
#define UART_H

#define OVER_SAMPLE 16
#define BUFLEN 500

#include "project4.h"
#include <stdint.h>
#include "circbuf.h"

CB_t * CB_tx;
CB_t * CB_rx;


void UART_configure (int baud_rate);
/***************************************************************
@brief: initializes uart to meet our need
		set up includes clock, NVIC, and buffers
@param: baud rate - rate of data transfer
****************************************************************/

void UART_send (uint8_t * src);
/***************************************************************
@brief: sends a byte to uart. Blocks on transmission
@param: src - address of the byte to be sent
****************************************************************/

void UART_send_n (uint8_t * src, int32_t length);
/***************************************************************
@brief: sends n bytes to uart. Blocks on transmission
@param: src - base address of the bytes to be sent
		length - number of bytes to send
****************************************************************/

void UART_receive(uint8_t * dst);
/***************************************************************
@brief: receives a byte from uart. Blocks on reception
@param: dst - address where byte is to be stored
****************************************************************/

void UART_receive_n (uint8_t * dst, int32_t length );
/***************************************************************
@brief: receives n bytes from uart. Blocks on reception
@param: dst - address where byte is to be received
		length - number of bytes to receive
****************************************************************/

void UART0_IRQHandler();
/***************************************************************
@brief: Handles the interrupt. Triggered when data is sent
		or received to uart. Disabled when rx buffer is full or
		tx buffer is empty to avoid data hazard
****************************************************************/

void UART_send_string(char * output);
/***************************************************************
@brief: My short cut to send a string to uart
@param: base address to the string to be sent.
		Expects a null terminator for the string
****************************************************************/

#endif /*uart*/
