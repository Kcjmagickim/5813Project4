/**********************************
@file:
@brief:
@author: John Kim
@date:
***********************************/
#ifndef NORDIC_H
#define NORDIC_H

#include <stdint.h>
#include <stdlib.h>
#include "core_cmFunc.h"
#include "port.h"

#define CONFIG_REG 0x00
#define MASK_RX_DR_bit 0x40
#define MASK_TX_DS_bit 0x20
#define MASK_MAX_RT_bit 0x10
#define EN_CRC_bit 0x08
#define CRCO_bit 0x04
#define PWR_UP_bit 0x02
#define PRIM_RX_bit 0x01

#define RF_CH_REG 0x05
#define RF_CH_bit 0x7F

#define RF_SETUP_REG 0x06
#define PLL_LOCK_bit 0x10
#define RF_DR_bit 0x08
#define RF_PWR_bit 0x06
#define LNA_HCURR_bit 0x01

#define STATUS_REG 0x07
#define RX_DR_bit 0x40
#define TX_DS_bit 0x20
#define MAX_RT_bit 0x10
#define RX_P_NO_bit 0x0E
#define TX_FULL_bit 0x01

#define TX_ADDR 0x10
#define TX_ADDR_bit 0xFFFFFFFFFF

#define FIFO_STATUS 0x17
#define TX_REUSE_bit 0x40
#define TX_FULL_bit2 0x20
#define TX_EMPTY_bit 0x10
#define RX_FULL_bit 0x02
#define RX_EMPTY_bit 0x01

//commands
#define R_REGISTER  0x00
#define W_REGISTER 	0x20
#define DUMMY_VAR   0xff
#define FLUSH_TX    0xE1
#define FLUSH_RX    0xE2

uint8_t nrf_read_register(uint8_t register);

void nrf_write_register(uint8_t register, uint8_t value);

uint8_t nrf_read_status();

void nrf_write_config(uint8_t config);

uint8_t nrf_read_config();

uint8_t nrf_read_rf_setup();

void nrf_write_rf_setup(uint8_t config);

uint8_t nrf_read_rf_ch();

void nrf_write_rf_ch(uint8_t channel);

void nrf_read_TX_ADDR(uint8_t * address);

void nrf_write_TX_ADDR(uint8_t * tx_addr);

uint8_t nrf_read_fifo_status();

void nrf_flush_tx_fifo();

void nrf_flush_rx_fifo();

__attribute__((always_inline)) static inline void nrf_chip_enable(){
	PTB_BASE_PTR->PCOR |= 0x1 << CSN;
}
__attribute__((always_inline)) static inline void nrf_chip_disable(){
	PTB_BASE_PTR->PSOR |= 0x1 << CSN;
}

__attribute__((always_inline)) static inline void nrf_transmit_enable(){
	PTB_BASE_PTR->PSOR |= 0x1 << CE;
}

__attribute__((always_inline)) static inline void nrf_transmit_disable(){
	PTB_BASE_PTR->PCOR |= 0x1 << CE;
}

#endif /*nordic*/
