/****************************************************
@file:
@brief:
@author: John Kim
@date:
Note: function description resides in the header file
****************************************************/

#include <stdint.h>
#include <stdlib.h>
#include "spi.h"
#include "MKL25Z4.h"

void SPI_init(){
	SPI0_C1 |= SPI_C1_MSTR_MASK | SPI_C1_CPHA_MASK; // | SPI_C1_SSOE_MASK; //0x52
	//PI0_C2 |= SPI_C2_MODFEN_MASK; //0x10 DMA?
	SPI0_BR = (SPI_BR_SPPR(0x02) | SPI_BR_SPR(0x08));
	//prescale divisor 3 & baud rate divisor 64 baud rate 15625 hz
	SPI0_C1 |= SPI_C1_SPE_MASK;
}

void SPI_read_byte(uint8_t * byte){
	while ((SPI0_S & SPI_S_SPRF_MASK) != SPI_S_SPRF_MASK); //wait
	*byte = SPI0->D;
}

void SPI_write_byte(uint8_t byte){
	//SPI0->C2 |= 0x04;
	SPI_flush();
	SPI0->D = byte;
	SPI_flush();
}

void SPI_send_packet(uint8_t * p, size_t length){
	uint8_t i;
	//SPI0->C2 |= 0x04;
	for (i = 0; i < length; i++){
		SPI_write_byte(*p);
		p++;
	}
}

void SPI_flush(){
	while ((SPI0_S & SPI_S_SPTEF_MASK)!=SPI_S_SPTEF_MASK); //wait
}
