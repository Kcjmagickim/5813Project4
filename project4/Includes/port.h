/**********************************
@file: port.h
@brief: Provdies control over GPIO, including LED pins
@author: John Kim
@date: Feb 17th, 2018
***********************************/

#include "MKL25Z4.h"
#ifndef PORT_H
#define PORT_H

#define RGB_RED_PIN       18
#define RGB_GREEN_PIN     19
#define RGB_BLUE_PIN      1
#define CE				  1
#define CSN 			  2
#define SCLK			  5
#define MOSI			  6
#define MISO			  7

void GPIO_Configure();
/***************************************************************
@brief: sets GPIO pin configuration including RGB LED and its
		respective port control settings.
@no param and return:
****************************************************************/

void Toggle_Red_LED();
/***************************************************************
@brief: Toggles Red LED
@no param and return
****************************************************************/

void PORTB_Set(uint8_t bit_num);
/***************************************************************
@brief: sets port B's respective GPIO pin
@param: the bit number
****************************************************************/

void PORTD_Set(uint8_t bit_num);
/***************************************************************
@brief: sets port D's respective GPIO pin
@param: the bit number
****************************************************************/

void PORTB_Clear(uint8_t bit_num);
/***************************************************************
@brief: clears port B's respective GPIO pin
@param: the bit number
****************************************************************/

void PORTD_Clear(uint8_t bit_num);
/***************************************************************
@brief: clears port D's respective GPIO pin
@param: the bit number
****************************************************************/

void PORTB_Toggle(uint8_t bit_num);
/***************************************************************
@brief: toggles port B's respective GPIO pin
@param: the bit number
****************************************************************/

void PORTD_Toggle(uint8_t bit_num);
/***************************************************************
@brief: toggles port D's respective GPIO pin
@param: the bit number
****************************************************************/

void GPIO_nrf_init();

#define RGB_RED_ON()     (PORTB_Clear( RGB_RED_PIN ))
#define RGB_RED_OFF()    (PORTB_Set( RGB_RED_PIN ))
#define RGB_RED_TOGGLE() (PORTB_Toggle( RGB_RED_PIN ))

#define RGB_GREEN_ON()     (PORTB_Clear( RGB_GREEN_PIN ))
#define RGB_GREEN_OFF()    (PORTB_Set( RGB_GREEN_PIN ))
#define RGB_GREEN_TOGGLE() (PORTB_Toggle( RGB_GREEN_PIN ))

#define RGB_BLUE_ON()     (PORTD_Clear( RGB_BLUE_PIN ))
#define RGB_BLUE_OFF()    (PORTD_Set( RGB_BLUE_PIN ))
#define RGB_BLUE_TOGGLE() (PORTD_Toggle( RGB_BLUE_PIN ))
/***************************************************************
@brief: Macros that make LED controlling easy and readable
****************************************************************/

#endif /*port*/
