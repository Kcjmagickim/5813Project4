/**********************************
@file: project2.c
@brief: main execution of program happens here
@author: John Kim
@date: Mar 5th, 2018
Note: all function descriptions in the header file
***********************************/

#include <stddef.h>
#include <stdlib.h>
#include "project2.h"
#include "circbuf.h"
#include "uart.h"
#include "port.h"
#include "conversion.h"

uint32_t alph = 0;
uint32_t numb = 0;
uint32_t punc = 0;
uint32_t misc = 0;
char number1[10] = "";
char number2[10] = "";
char number3[10] = "";
char number4[10] = "";

char number5[10] = "";
char number6[10] = "";
char number7[10] = "";

/*These numbers are used to keep track of statistics*/
char a[50] = "Number of alphabets in the string: ";
char b[50] = "Number of punctuations in the string: ";
char c[50] = "Number of numbers in the string: ";
char d[50] = "Number of misc characters in the string: ";

char nline[3] = "\n";
char in[30] = "-----Starting Project 2-----\n";
char dump[30] = "-----Input String-----\n";
char stats[30] = "-----Analysis of Input-----\n";

void project2(){
	GPIO_Configure();
	RGB_BLUE_ON();

	uint8_t stat = 0;
	uint8_t out;
	uint8_t end;

	#ifdef ESC
		end=0x1b;
	#elif ENTER
		end=0x0d;
	#else
		end=0x1b;
	#endif

	UART_configure(9600);
	//check = readFile("C:\in.txt", CB_tx);
	//if(check != SUCCESS) return;
	UART_send_string(in);
	uint8_t count=0;
	uint8_t * check;
	while(stat != 1){
		check  = ((CB_rx)->tail);
		check--;
    	if(*check == end){
    		if(count<2){
    			count++;
    			CB_buffer_add_item(CB_rx, 'x');
    		}else if (count==2){
    			stat = 1;
    		}
    	}
	}


	UART_send_string(dump);
	uint8_t CRC1;
	uint8_t CRC2;
	uint8_t CRC3;

	while(*(CB_rx->head) != 0x0d){
		UART_receive(&out);
		stat_update(out);
		UART_send(&out);
		CRC1 ^= out;
	}
	UART_receive(&out);
	UART_receive(&out);
	UART_send(nline);
	while(*(CB_rx->head) != 0x0d){
		UART_receive(&out);
		stat_update(out);
		UART_send(&out);
		CRC2 ^= out;
	}
	UART_receive(&out);
	UART_receive(&out);
	UART_send(nline);
	while(*(CB_rx->head) != 0x0d){
		UART_receive(&out);
		stat_update(out);
		UART_send(&out);
		CRC3 ^= out;
	}
	UART_send(nline);

	uint8_t digits;
	DUMP_STAT();
	digits=my_itoa(CRC1, number5, 10);
	UART_send_n(number5, digits-1);
	UART_send(nline);
	digits=my_itoa(CRC2, number6, 10);
	UART_send_n(number6, digits-1);
	UART_send(nline);
	digits=my_itoa(CRC3, number7, 10);
	UART_send_n(number7, digits-1);
	UART_send(nline);

	return;
}

void DUMP_STAT(){
	uint8_t digits;

	UART_send_string(stats);
	UART_send_string(a);
	digits=my_itoa(alph, number1, 10);
	UART_send_n(number1, digits-1);
	UART_send(nline);
	UART_send_string(b);
	digits=my_itoa(punc, number2, 10);
	UART_send_n(number2, digits-1);
	UART_send(nline);
	UART_send_string(c);
	digits=my_itoa(numb, number3, 10);
	UART_send_n(number3, digits-1);
	UART_send(nline);
	UART_send_string(d);
	digits=my_itoa(misc, number4, 10);
	UART_send_n(number4, digits-1);
	UART_send(nline);
	return;
}

void stat_update(uint8_t data){
	if (0x30<=data && data<=0x39)
		numb++;
	else if ((0x41<=data && data<=0x5A) || (0x61<=data && data<=0x7A))
		alph++;
	else if (ispunc(data) == 1)
		punc++;
	else
		misc++;
}

uint8_t ispunc(uint8_t data){
	if (data==0x21||data==0x22||data==0x27||data==0x28||data==0x29||data==0x2c||data==0x3a||data==0x3b||data==0x3f||data==0x5b||data==0x5d||data==0x7b||data==0x7d)
		return 1;
	else
		return 0;
}
