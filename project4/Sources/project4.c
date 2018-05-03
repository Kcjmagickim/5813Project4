#include "logger.h"
#include "uart.h"
#include <stddef.h>
#include <stdlib.h>
#include "project2.h"
#include "project4.h"
#include "circbuf.h"
#include "port.h"
#include "conversion.h"
#include "systick.h"
#include "rtc.h"

int quart;
char data[100] = "";

uint8_t heartbeat, gpio, rtc;
uint32_t alph1 = 0;
uint32_t numb1 = 0;
uint32_t punc1 = 0;
uint32_t misc1 = 0;
uint32_t * pc = 0x00000000;

char number22[20] = "";
char number23[10] = "";
char number24[10] = "";

char number11[10] = "";
char number21[10] = "";
char number31[10] = "";
char number41[10] = "";
char number51[10] = "";
char number61[10] = "";
char number71[10] = "";

uint32_t seconds = 0;
uint32_t alarm = 0;
uint32_t minutes = 0;
uint8_t interrupt = 0;

void project4(){
	rtc_init(); rtc=1;
	UART_configure(9600);
	GPIO_Configure(); gpio=1;

	SYST_RVR = SysTick_RVR_RELOAD(20971520/4);
	SYST_CVR = SysTick_CVR_CURRENT(0);
	SYST_CSR |= SysTick_CSR_ENABLE_MASK | SysTick_CSR_CLKSOURCE_MASK;

	if(!rtc){
		logging(ERROR, 11, 0, 23, "RTC not Initialized", 1);
	}

	logging(SYSTEM_INITIALIZED, 13, (uint32_t) RTC_TSR + (minutes +1)*100, 23, "NA", 1);

	logging(SYSTEM_ID, 13, (uint32_t) RTC_TSR + (minutes +1)*100, 37, "Code by John Kim", 1);
	logging(SYSTEM_VERSION, 13, (uint32_t) RTC_TSR + (minutes +1)*100, 44, "Running on kl25z128vlk4", 1);
	logging(INFO, 12, (uint32_t) RTC_TSR + (minutes +1)*100, 23, "Logger Flushed", 1);
	logging(PROFILING_STARTED , 13, (uint32_t) RTC_TSR + (minutes +1)*100, 43, "Starting runtime timer", 1);

	tick1 = SYST_CVR&SysTick_CVR_CURRENT_MASK;
    uint8_t stat = 0;
	uint8_t out;
	uint8_t end;

	#ifdef ESC
		end=0x1b;
	#elif ENTER
		end=0x0d;
	#else
		end=0x1b;
	#endif

	uint8_t count=0;
	uint32_t index = 0;
	uint32_t sp, pcr;
	uint8_t * input;
	while(stat != 1){
		input  = ((CB_rx)->tail);
		input--;
    	if(*input == end){
    		stat = 1;
    	}
	}
	input  = ((CB_rx)->head);
	while(*input != end){
		data[index]= * (char*) input;
		input++;
		index++;
	}
	data[index] = '\0';

	logging(DATA_RECEIVED, 13, (uint32_t) RTC_TSR + (minutes +1)*100, 20 + index, data, 1);

	logging(DATA_ANALYSIS_STARTED, 13, (uint32_t) RTC_TSR + (minutes +1)*100, 23, "NA", 1);

	SYST_CSR |= SysTick_CSR_ENABLE_MASK | SysTick_CSR_TICKINT_MASK | SysTick_CSR_CLKSOURCE_MASK;

	while(*(CB_rx->head) != end){
		UART_receive(&out);
		stat_update1(out);
	}

	DUMP_STAT2();

	tick2 = SYST_CVR&SysTick_CVR_CURRENT_MASK;

	logging(DATA_ANALYSIS_COMPLETED, 13, (uint32_t) RTC_TSR + (minutes +1)*100, 23, "NA", 1);

	tick = tick1-tick2;
	my_itoa(tick + 20971520/4*quart, number22, 10);
	logging2(PROFILING_RESULT , 13, (uint32_t) RTC_TSR + (minutes +1)*100, 43, number22, 1);

	sp = __get_MSP();
	pcr = *(pc);
	my_itoa(sp, number23, 10);
	my_itoa(pcr, number24, 10);

	logging(PROFILING_COMPLETED , 13, (uint32_t) RTC_TSR + (minutes +1)*100, 23, "NA", 1);

	logging3(CORE_DUMP , 13, (uint32_t) RTC_TSR + (minutes +1)*100, 23, number23, number24, 1);

	logging(SYSTEM_HALTED, 13, (uint32_t) RTC_TSR + (minutes +1)*100, 23, "NA", 1);

	logging(INFO, 12, (uint32_t) RTC_TSR + (minutes +1)*100, 23, "Logger Flushed", 1);

	while(1){
		if (interrupt==1){
			logging(HEARTBEAT, 11, (uint32_t) RTC_TSR + (minutes +1)*100, 23, "NA", 1);
			interrupt=0;
		}
	}

	return;
}

void DUMP_STAT2(){
	uint8_t digits;

	digits=my_itoa(alph1, number11, 10);
	logging(DATA_ALPHA_COUNT, 13, (uint32_t) RTC_TSR + (minutes +1)*100, 20 + digits, number11, 1);

	digits=my_itoa(punc1, number21, 10);
	logging(DATA_PUNCTUATION_COUNT, 13, (uint32_t) RTC_TSR + (minutes +1)*100, 20 + digits, number21, 1);

	digits=my_itoa(numb1, number31, 10);
	logging(DATA_NUMERIC_COUNT, 13, (uint32_t) RTC_TSR + (minutes +1)*100, 20 + digits, number31, 1);

	digits=my_itoa(misc1, number41, 10);
	logging(DATA_MISC_COUNT, 13, (uint32_t) RTC_TSR + (minutes +1)*100, 20 + digits, number41, 1);

	return;
}

void stat_update1(uint8_t data){
	if (0x30<=data && data<=0x39)
		numb1++;
	else if ((0x41<=data && data<=0x5A) || (0x61<=data && data<=0x7A))
		alph1++;
	else if (ispunc(data) == 1)
		punc1++;
	else
		misc1++;
}

void SysTick_Handler(){
	quart++;
	if (quart==4){
		heartbeat = 1;
		quart = 0;
	}
}

void RTC_Seconds_IRQHandler(void)
{
	if(!gpio){
		logging(WARNING, 18, (uint32_t) RTC_TSR + (minutes +1)*100, 23, "GPIO not Initialized", 1);
	}else{
		interrupt = 1;
		RGB_BLUE_TOGGLE();
	}

	seconds = (uint32_t) RTC_TSR;
    if (seconds >59){
    	minutes++;
    	RTC_SR &= ~RTC_SR_TCE_MASK;
    	RTC_TSR = 0x00; //Reset counter
    	seconds = (uint32_t) RTC_TSR;
    	RTC_SR |= RTC_SR_TCE_MASK;
    }
}
