/**********************************
@file: dma.c
@brief: Provdies control over DMA
@author: John Kim
@date: Apr 17th, 2018 (??)
***********************************/

#include <stdint.h>
#include <stddef.h>
#include "dma.h"
#include "systick.h"
#include <MKL25Z4.h>

uint8_t quart;

void dma_setup(uint8_t mode){

	//DMA clock
	SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;
	SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;

	uint8_t i;

	DMAMUX0_CHCFG0 = 0x00;

	// Clear pending errors and/or the done bit
	if (((DMA_DSR_BCR0 & DMA_DSR_BCR_DONE_MASK) == DMA_DSR_BCR_DONE_MASK)
			| ((DMA_DSR_BCR0 & DMA_DSR_BCR_BES_MASK) == DMA_DSR_BCR_BES_MASK)
			| ((DMA_DSR_BCR0 & DMA_DSR_BCR_BED_MASK) == DMA_DSR_BCR_BED_MASK)
			| ((DMA_DSR_BCR0 & DMA_DSR_BCR_CE_MASK) == DMA_DSR_BCR_CE_MASK))
		DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE_MASK;


	DMA_DCR0 &= ~(DMA_DCR_DSIZE_MASK | DMA_DCR_SSIZE_MASK);

	if (mode == 1){
		DMA_DCR0 |= DMA_DCR_DSIZE(1) | DMA_DCR_SSIZE(1);
	}
	else if (mode == 2){
		DMA_DCR0 |= DMA_DCR_DSIZE(2) | DMA_DCR_SSIZE(2);
	}
	else if (mode == 4){
		DMA_DCR0 |= DMA_DCR_DSIZE(0) | DMA_DCR_SSIZE(0);
	}
	else{
		DMA_DCR0 |= DMA_DCR_DSIZE(1) | DMA_DCR_SSIZE(1);
	}

	// Set DMA
	DMA_DCR0 |= (DMA_DCR_EINT_MASK		// Int. enable... used if FREEDOM macro is set
			| DMA_DCR_ERQ_MASK			//Enable Peripheral request
			//	| DMA_DCR_CS_MASK			//Single read/write per request
			//	| DMA_DCR_EADREQ_MASK		//Enable Async. DMA Requests
			| DMA_DCR_DINC_MASK			//Destination address increments
			| DMA_DCR_DMOD(10)			//32-bytes circular buffer enabled
			| DMA_DCR_D_REQ_MASK		//DMA request is cleared
			);

	DMAMUX0_CHCFG0 |= DMAMUX_CHCFG_ENBL_MASK;
}

uint8_t * memmove_dma(uint8_t *src, uint8_t *dst, size_t length){
	done = 0;
	DMA_SAR0 = (uint32_t) src;
	DMA_DAR0 = (uint32_t) dst;
	uint32_t i;
	if (DMA_DSR_BCR0 & DMA_DSR_BCR_CE_MASK) return NULL;
	DMA_DSR_BCR0 &= ~DMA_DSR_BCR_BCR_MASK;
	DMA_DSR_BCR0 |= DMA_DSR_BCR_BCR(length);

	tick1 = SYST_CVR&SysTick_CVR_CURRENT_MASK;

	if((dst-src)>0 && (dst-src)<length){
		src+=(length-1); dst+=(length-1);
		for(i=0; i<length; i++){
			DMA_SAR0 = (uint32_t) src;
			DMA_DAR0 = (uint32_t) dst;
			DMA_DSR_BCR0 &= ~DMA_DSR_BCR_BCR_MASK;
			DMA_DSR_BCR0 |= DMA_DSR_BCR_BCR(1);
			if(i==0){tick1 = SYST_CVR&SysTick_CVR_CURRENT_MASK;}
			else if(i==length-1)		done=1;
			DMA_DCR0 |= DMA_DCR_START_MASK;
			src--; dst--;
		}
	}
	else{
		tick1 = SYST_CVR&SysTick_CVR_CURRENT_MASK;
		done=1;
		DMA_DCR0 |= (DMA_DCR_START_MASK
				| DMA_DCR_SINC_MASK);			//Source address increments
	}
}

uint8_t * memset_dma(uint8_t *src, size_t length, uint8_t value){
	done=0;
	DMA_SAR0 = (uint32_t) &value;
	DMA_DAR0 = (uint32_t) src;
	if (DMA_DSR_BCR0 & DMA_DSR_BCR_CE_MASK) return NULL;
	DMA_DSR_BCR0 &= ~DMA_DSR_BCR_BCR_MASK;
	DMA_DSR_BCR0 |= DMA_DSR_BCR_BCR(length);

	DMA_DCR0 &= ~(DMA_DCR_SINC_MASK);			//Source address shouldn't increments
	tick1 = SYST_CVR&SysTick_CVR_CURRENT_MASK;

	DMA_DCR0 |= DMA_DCR_START_MASK;
}

void DMA0_IRQHandler(void){
	tick2 = SYST_CVR&SysTick_CVR_CURRENT_MASK;	//Get time done
	DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE_MASK; // Clear interrupt
	done=1;
}
