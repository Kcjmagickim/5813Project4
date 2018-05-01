/**********************************
@file:
@brief:
@author: John Kim
@date:
***********************************/

#include <stdint.h>
#include <stdlib.h>
#ifndef SPI_H
#define SPI_H

void SPI_init();

void SPI_read_byte(uint8_t * byte);

void SPI_write_byte(uint8_t byte);

void SPI_send_packet(uint8_t * p, size_t length);

void SPI_flush();

#endif /*spi*/
