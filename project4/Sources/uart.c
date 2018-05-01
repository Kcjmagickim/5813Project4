/**********************************
@file: uart.c
@brief: Provdies control over UART
@author: John Kim
@date: Mar 2nd, 2018
***********************************/

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include "uart.h"
#include "MKL25Z4.h"
#include "circbuf.h"
#include "core_cm0plus.h"
#include "systick.h"
#include "project4.h"


void UART_configure (int baud_rate){
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;

	// Select "Alt 2" usage to enable UART0 on pins
    PORTA_PCR1 = PORT_PCR_MUX(2)|PORT_PCR_IRQC(0xA);
    PORTA_PCR2 = PORT_PCR_MUX(2)|PORT_PCR_IRQC(0xA);


    // Turn on clock to UART0
    SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;
    SIM_SOPT2 &= ~SIM_SOPT2_UART0SRC_MASK;
    SIM_SOPT2 |= SIM_SOPT2_UART0SRC(1);       // FLL/PLL/2 clock

    // Set the baud rate divisor
    uint16_t divisor = (DEFAULT_SYSTEM_CLOCK / OVER_SAMPLE) / baud_rate;
    UART0_C4 = UARTLP_C4_OSR(OVER_SAMPLE - 1);
    UART0_BDH = (divisor >> 8) & UARTLP_BDH_SBR_MASK;
    UART0_BDL = (divisor & UARTLP_BDL_SBR_MASK);

    UART0_C1 = 0;
    UART0_C3 = 0;
    UART0_S2 = 0;

    // Initialize transmit and receive circular buffers
	CB_tx = malloc(sizeof(CB_t));
	CB_rx = malloc(sizeof(CB_t));
	CB_e status = CB_init(CB_tx, BUFLEN);
	if(status != SUCCESS) return;
	status = CB_init(CB_rx, BUFLEN);
	if(status != SUCCESS) return;

    // Enable the transmitter, receiver, and receive interrupts
    UART0_C2 = UARTLP_C2_RE_MASK | UARTLP_C2_TE_MASK | UART_C2_RIE_MASK;

    NVIC_ClearPendingIRQ(UART0_IRQn);
    NVIC_EnableIRQ(UART0_IRQn);
    NVIC_SetPriority(UART0_IRQn, 1);

	logging(LOGGER_INITIALIZED, 15, (uint32_t) RTC_TSR, 23, "NA", 1);
}

void UART_send (uint8_t * src){
	while(CB_is_full(CB_tx));
	CB_buffer_add_item(CB_tx, *src);
    UART0_C2 |= UART_C2_TIE_MASK;     // Signal Tx interrupts
}

void UART_send_n (uint8_t * src, int32_t length){
	while(0<length){
		while(CB_is_full(CB_tx));
		CB_buffer_add_item(CB_tx, *src++);
		UART0_C2 |= UART_C2_TIE_MASK;     // Signal Tx interrupts
		length--;
	}
}

void UART_receive(uint8_t * dst){
	while(CB_is_empty(CB_rx));
	CB_buffer_remove_item(CB_rx, dst);
    UART0_C2 |= UART_C2_RIE_MASK;           // Signal Rx interrupt
}

void UART_receive_n (uint8_t * dst, int32_t length ){
	while(0<length){
		while(CB_is_empty(CB_rx));
		CB_buffer_remove_item(CB_rx, dst++);
		UART0_C2 |= UART_C2_RIE_MASK;           // Signal Rx interrupt
		length--;
	}
}

void UART0_IRQHandler(){
	uint32_t status;
    status = UART0_S1;
    uint8_t out, in;
    // If transmit data register empty, and data in the transmit buffer,
    // send it.  If it leaves the buffer empty, disable the transmit interrupt.
    if ((status & UART_S1_TDRE_MASK) && !CB_is_empty(CB_tx)) {
        CB_buffer_remove_item(CB_tx, &out);
        UART0_D=out;
        if(CB_is_empty(CB_tx))
            UART0_C2 &= ~UART_C2_TIE_MASK;
    }

    // If there is received data, read it into the receive buffer.  If the
    // buffer is full, disable the receive interrupt.
    if ((status & UART_S1_RDRF_MASK) && !CB_is_full(CB_rx)) {
    	CB_buffer_add_item(CB_rx, UART0-> D);
        if(CB_is_full(CB_rx)){
            UART0_C2 &= ~UART_C2_RIE_MASK;
        }
    }
}

void UART_send_string(char * in){
	uint8_t n = 0;
	while(in[n]!='\0'){
		UART_send((uint8_t *) &in[n]);
    	n++;
	}
}
