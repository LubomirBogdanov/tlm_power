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
