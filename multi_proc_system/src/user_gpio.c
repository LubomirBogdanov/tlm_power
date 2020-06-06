/*
 * user_gpio.c
 *
 *  Created on: Jun 6, 2020
 *      Author: lbogdanov
 */
#include "user_gpio.h"

void user_gpio_init(void){
	LPC_SYSCTL->SYSAHBCLKCTRL |= SYSCTL_CLOCK_SWM;
	LPC_SYSCTL->SYSAHBCLKCTRL |= SYSCTL_CLOCK_GPIO;

	LPC_GPIO_PORT->DIR[0] |= 1 << 4;
	LPC_GPIO_PORT->CLR[0] = 1 << 4;
}

void user_gpio_set(void){
	LPC_GPIO_PORT->SET[0] = (1 << 4);
}

void user_gpio_clear(void){
	LPC_GPIO_PORT->CLR[0] = (1 << 4);
}

void user_gpio_toggle(void){
	LPC_GPIO_PORT->NOT[0] = (1 << 4);
}

