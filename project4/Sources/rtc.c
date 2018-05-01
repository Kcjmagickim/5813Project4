#include "rtc.h"
#include "MKL25Z4.h"
#include "port.h"

void rtc_init()
{
    /*enable the clock to SRTC module register space*/
	SIM_SCGC6 |= SIM_SCGC6_RTC_MASK;

	/*Clear Registers*/
    RTC_CR  = RTC_CR_SWR_MASK;
    RTC_CR  &= ~RTC_CR_SWR_MASK;

    if (RTC_SR & RTC_SR_TIF_MASK){
        RTC_TSR = 0x00000000;   //  this action clears the TIF
    }

    /*Set time compensation parameters*/
    RTC_TCR = RTC_TCR_CIR(1) | RTC_TCR_TCR(0xFF);

    /*Enable RTC seconds irq*/
    NVIC_EnableIRQ(RTC_Seconds_IRQn);

    /*Enable Seconds Interrupt*/
    RTC_IER |= RTC_IER_TSIE_MASK; //Seconds interrupt enable

    /*Timer enable*/
    RTC_SR |= RTC_SR_TCE_MASK;

    /*Configure the timer seconds and alarm registers*/
    RTC_TSR = 0xFF;

}
