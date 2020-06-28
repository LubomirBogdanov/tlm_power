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
