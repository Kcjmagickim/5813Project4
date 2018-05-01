#ifndef DMA_H_
#define DMA_H_

#include <MKL25Z4.h>
#include <stdint.h>
#include <stddef.h>

#define ONEBYTE 0x120000u
#define TWOBYTE 0x240000u
#define FOURBYTE 0x000000u
#define BUFF_SIZE 4
#define DESTINATION_ADDRESS 0x20000000

uint8_t done;

void dma_setup(uint8_t mode);

uint8_t * memmove_dma(uint8_t *src, uint8_t *dst, size_t length);

uint8_t * memset_dma(uint8_t *src, size_t length, uint8_t value);

void DMA0_IRQHandler(void);

#endif /*DMA*/
