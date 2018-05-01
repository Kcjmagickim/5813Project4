/****************************************************
@file: port.c
@brief: Provdies control over GPIO, including LED pins
@author: John Kim
@date: Feb 21st, 2018
Note: function description resides in the header file
****************************************************/

#include "MKL25Z4.h"
#include "port.h"
#include "logger.h"
#include "project4.h"
#include <stdint.h>

void GPIO_Configure(){
	SIM_SCGC5 |= (SIM_SCGC5_PORTB_MASK + SIM_SCGC5_PORTC_MASK + SIM_SCGC5_PORTD_MASK);
    PORTB_PCR18 |= (PORT_PCR_MUX(1));
    PORTB_PCR19 |= (PORT_PCR_MUX(1));
    PORTD_PCR1 |= (PORT_PCR_MUX(1));
	GPIOB_PDDR |= ((1 << RGB_RED_PIN) + (1 << RGB_GREEN_PIN));
	GPIOB_PSOR |= ((1 << RGB_RED_PIN) + (1 << RGB_GREEN_PIN));
	GPIOD_PDDR |= 1<<RGB_BLUE_PIN;
	GPIOD_PSOR |= 1<<RGB_BLUE_PIN;


	MCG_C1 |= MCG_C1_IRCLKEN_MASK;

	MCG_C2 &= ~(MCG_C2_IRCS_MASK);
    PORTC_PCR1 |= (PORT_PCR_MUX(0x1));

    SIM_SOPT1 |= SIM_SOPT1_OSC32KSEL(0b10);
    SIM_SOPT2 |= SIM_SOPT2_CLKOUTSEL(0b100);

    PORTC_PCR3 |= (PORT_PCR_MUX(0x5));

    logging(GPIO_INITIALIZED, 8, (uint32_t) RTC_TSR, 23, "NA", 1);
}

void Toggle_Red_LED(){
	uint32_t set = 0x1 << RGB_RED_PIN;
	PTB_BASE_PTR->PTOR ^= set;
}//Toggle the Red LED state. On to Off, or Off to on.

void PORTB_Set(uint8_t bit_num){
	uint32_t set = 0x1 << (bit_num);
	PTB_BASE_PTR->PSOR |= set;
}

void PORTD_Set(uint8_t bit_num){
	uint32_t set = 0x1 << bit_num;
	PTD_BASE_PTR->PSOR |= set;
}//These two functions should use the appropriate GPIO function to toggle the output (PSOR)

void PORTB_Clear(uint8_t bit_num){
	uint32_t clear = 0x1 << bit_num;
	PTB_BASE_PTR->PCOR |= clear;
}

void PORTD_Clear(uint8_t bit_num){
	uint32_t clear = 0x1 << bit_num;
	PTD_BASE_PTR->PCOR |= clear;
}//These two functions should use the appropriate GPIO function to toggle the output (PCOR)

void PORTB_Toggle(uint8_t bit_num){
	uint32_t clear = 0x1 << bit_num;
	PTB_BASE_PTR->PTOR |= clear;
}

void PORTD_Toggle(uint8_t bit_num){
	uint32_t clear = 0x1 << bit_num;
	PTD_BASE_PTR->PTOR |= clear;
}//These two functions should use the appropriate GPIO function to toggle the output (PTOR)

void GPIO_nrf_init(){
	//SPI0 clock
	SIM->SCGC4 |= SIM_SCGC4_SPI0_MASK;
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
	PORTC_PCR5 = PORT_PCR_MUX(2);  // SCLK
	PORTC_PCR6 = PORT_PCR_MUX(2);  // MOSI
	PORTC_PCR7 = PORT_PCR_MUX(2);  // MISO
	PORTB_PCR1 = PORT_PCR_MUX(1);  // CE
	PORTB_PCR2 = PORT_PCR_MUX(1);  // CSN
	GPIOB_PDDR |= ((1 << CE) + (1 << CSN));
}
