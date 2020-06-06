/*
 * user_delay.h
 *
 *  Created on: Jun 6, 2020
 *      Author: lbogdanov
 */

#ifndef USER_DELAY_H_
#define USER_DELAY_H_

#include "main.h"

#define TICKRATE_HZ             (1000)

void user_delay_init(void);
void user_delay_ms(uint16_t delay_value);

#endif /* USER_DELAY_H_ */
