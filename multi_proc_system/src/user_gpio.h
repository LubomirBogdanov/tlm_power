/*
 * user_gpio.h
 *
 *  Created on: Jun 6, 2020
 *      Author: lbogdanov
 */

#ifndef USER_GPIO_H_
#define USER_GPIO_H_

#include "main.h"

void user_gpio_init(void);
void user_gpio_set(void);
void user_gpio_clear(void);
void user_gpio_toggle(void);

#endif /* USER_GPIO_H_ */
