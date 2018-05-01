/**********************************
@file:
@brief:
@author: John Kim
@date:
***********************************/

#include <stdint.h>
#include <stdlib.h>
#include "nordic.h"
#include "spi.h"
#include "systick.h"

uint8_t nrf_read_register(uint8_t regist){
	uint8_t read;
	nrf_chip_enable();
	SPI_write_byte(R_REGISTER | regist);
	SPI_read_byte(&read);
	SPI_write_byte(DUMMY_VAR);
	SPI_read_byte(&read);
	nrf_chip_disable();
	tick3 = SYST_CVR&SysTick_CVR_CURRENT_MASK;
	while((tick3-(SYST_CVR&SysTick_CVR_CURRENT_MASK))<4000){}
	return read;
}

void nrf_write_register(uint8_t regist, uint8_t value){
	nrf_chip_enable();
	SPI_write_byte(W_REGISTER | regist);
	SPI_read_byte(&regist);
	SPI_write_byte(value);
	SPI_read_byte(&regist);
	nrf_chip_disable();
	tick3 = SYST_CVR&SysTick_CVR_CURRENT_MASK;
	while((tick3-(SYST_CVR&SysTick_CVR_CURRENT_MASK))<4000){}
	return;
}

uint8_t nrf_read_status(){
	uint8_t read;
	nrf_chip_enable();
	SPI_write_byte(DUMMY_VAR);
	SPI_read_byte(&read);
	nrf_chip_disable();
	tick3 = SYST_CVR&SysTick_CVR_CURRENT_MASK;
	while((tick3-(SYST_CVR&SysTick_CVR_CURRENT_MASK))<4000){}
	return read;
}

void nrf_write_config(uint8_t config){
	nrf_write_register(CONFIG_REG, config);
}

uint8_t nrf_read_config(){
	return nrf_read_register(CONFIG_REG);
}

uint8_t nrf_read_rf_setup(){
	return nrf_read_register(RF_SETUP_REG);
}

void nrf_write_rf_setup(uint8_t config){
	nrf_write_register(RF_SETUP_REG, config);
}

uint8_t nrf_read_rf_ch(){
	return nrf_read_register(RF_CH_REG);
}

void nrf_write_rf_ch(uint8_t channel){
	nrf_write_register(RF_CH_REG, channel);
}

void nrf_read_TX_ADDR(uint8_t * address){
	uint8_t i;
	nrf_chip_enable();
	SPI_write_byte(R_REGISTER | TX_ADDR);
	SPI_read_byte(address);
	for(i=0;i<5;i++){
		SPI_write_byte(DUMMY_VAR);
		SPI_read_byte(address);
		address++;
	}
	nrf_chip_disable();
}

void nrf_write_TX_ADDR(uint8_t * tx_addr){
	uint8_t i;
	nrf_chip_enable();
	SPI_write_byte(W_REGISTER | TX_ADDR);
	for(i=0;i<5;i++){
		SPI_write_byte(*tx_addr);
		tx_addr++;
	}
	nrf_chip_disable();
}

uint8_t nrf_read_fifo_status(){
	return nrf_read_register(FIFO_STATUS);
}

void nrf_flush_tx_fifo(){
	nrf_chip_enable();
	SPI_write_byte(FLUSH_TX);
	nrf_chip_disable();
}

void nrf_flush_rx_fifo(){
	nrf_chip_enable();
	SPI_write_byte(FLUSH_RX);
	nrf_chip_disable();
}
