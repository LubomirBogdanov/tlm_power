/*
    Copyright (C) 2020 Lubomir Bogdanov
    Contributor Lubomir Bogdanov <lbogdanov@tu-sofia.bg>
    This file is part of tlm_power project.
    tlm_power is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    tlm_power is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.
    You should have received a copy of the GNU Lesser General Public License
    along with tlm_power.  If not, see <http://www.gnu.org/licenses/>.
*/

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

