/*
 * user_delay.c
 *
 *  Created on: Jun 6, 2020
 *      Author: lbogdanov
 */
#include "user_delay.h"

//Required by LPCOpen
const uint32_t OscRateIn = 0;
const uint32_t ExtRateIn = 0;

volatile uint32_t user_ticks;

void SysTick_Handler(void){
	user_ticks++;
}

void user_delay_init(void){
	SysTick_Config(IRC_CLOCK_RATE_HZ / TICKRATE_HZ);
}

void user_delay_ms(uint16_t delay_value){
	uint32_t ticks_timeout = user_ticks;
	ticks_timeout += delay_value;
	while(user_ticks < ticks_timeout){
		__WFI();
	}
}

