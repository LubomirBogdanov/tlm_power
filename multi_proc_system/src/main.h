/*
 * main.h
 *
 *  Created on: Jun 6, 2020
 *      Author: lbogdanov
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <stdint.h>
#include "chip.h"
#include "user_gpio.h"
#include "user_delay.h"

#ifdef USE_USER_I2C_STANDARD
	#include "user_i2c_standard.h"
#endif

#ifdef USE_USER_I2C_DAEDALUS
	#include "user_i2c_daedalus.h"
#endif

#include "fifo_multi.h"
#include "user_system_init.h"

#define IRC_CLOCK_RATE_HZ		12000000

#endif /* MAIN_H_ */
