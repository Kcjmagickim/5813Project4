#include "MKL25Z4.h"
#include "systick.h"
#include "dma.h"
#include <stdlib.h>
#include "conversion.h"
#include "uart.h"
#include <string.h>
#include "memory.h"
#include "profile.h"

#define SIZE 10
#define MAX	0x3000
#define STACK 0x20003000

void profile()
{
	UART_configure(9600);
	//systick
	SYST_RVR = SysTick_RVR_RELOAD(20971520/4);
	SYST_CVR = SysTick_CVR_CURRENT(0);
	SYST_CSR |= SysTick_CSR_ENABLE_MASK | SysTick_CSR_TICKINT_MASK | SysTick_CSR_CLKSOURCE_MASK;

    NVIC_ClearPendingIRQ(DMA0_IRQn);
    NVIC_EnableIRQ(DMA0_IRQn);
    NVIC_SetPriority(DMA0_IRQn, 2);
    __enable_irq();

    dma_setup(4);

	char number1[10] = "";
	char number2[10] = "";
	char number3[10] = "";
	char number4[10] = "";
	char number5[10] = "";
	char number6[10] = "";
	char number7[10] = "";
	char c[50] = "Number of bytes Transferred: ";
	char c2[50] = "Number of bytes Set: ";
	char a[50] = "Number of clock cycles: ";
	char b[50] = "Time in nano seconds: ";
	char d[20] = "Stack usage: ";
	char e[10] = " bytes";
	char nline[3] = "\n";
	size_t ns;
	uint32_t tick, bytes = 0;
	uint8_t check, digits;
	uint8_t *dst, *off;
	uint32_t *watermark;

	uint8_t fill[MAX];
	uint32_t i;

	for(i=0; i<MAX; i++){
		fill[i]=0xcc;
	}

	tick1 = SYST_CVR&SysTick_CVR_CURRENT_MASK;

	//my_memset((uint8_t *) DESTINATION_ADDRESS, SIZE, 0x00);
	//memset((uint8_t *) DESTINATION_ADDRESS, 0x00, SIZE);
    memset_dma((uint8_t *) DESTINATION_ADDRESS, SIZE, 0x00);
	//tick2 = SYST_CVR&SysTick_CVR_CURRENT_MASK;

    while(tick2==0);	//while DMA in process
	tick = tick1-tick2;

    for(i=0; i<SIZE; i++){
		fill[i+20] = 0xAA;
	}
	UART_send_string(c2);	//profile memset
	digits=my_itoa(SIZE, number6, 10);
	UART_send_n(number6, digits-1);
	UART_send(nline);
	UART_send_string(a);
	digits=my_itoa(tick, number4, 10);
	UART_send_n(number4, digits-1);
	UART_send(nline);
	ns = tick*47.6837;
	UART_send_string(b);
	digits=my_itoa(ns, number5, 10);
	UART_send_n(number5, digits-1);
	UART_send(nline);

	tick1 = SYST_CVR&SysTick_CVR_CURRENT_MASK;

	//my_memmove(&fill[20], (uint8_t *) DESTINATION_ADDRESS, SIZE);
	//memmove ((uint8_t *) DESTINATION_ADDRESS, &fill[20], SIZE);
	memmove_dma(&fill[20], (uint8_t *) DESTINATION_ADDRESS, SIZE);
	while(tick2==0);
	//tick2 = SYST_CVR&SysTick_CVR_CURRENT_MASK;
	tick = tick1-tick2;

	UART_send_string(c);	//profile memmove
	digits=my_itoa(SIZE, number3, 10);
	UART_send_n(number3, digits-1);
	UART_send(nline);
	UART_send_string(a);
	digits=my_itoa(tick, number1, 10);
	UART_send_n(number1, digits-1);
	UART_send(nline);
	ns = tick*47.6837;
	UART_send_string(b);
	digits=my_itoa(ns, number2, 10);
	UART_send_n(number2, digits-1);
	UART_send(nline);

	watermark = (uint32_t *) STACK;
	watermark--;
	while(*watermark != 0xcccccccc){
		bytes=bytes+4;
		watermark--;
	}
	off = (uint8_t *) watermark;
	while(*off != 0xcc){
		bytes--;
		off++;
	}
	UART_send_string(d);
	digits=my_itoa(bytes, number7, 10);
	UART_send_n(number7, digits-1);
	UART_send_string(e);
	UART_send(nline);
}
