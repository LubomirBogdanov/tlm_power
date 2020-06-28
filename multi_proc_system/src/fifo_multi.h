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
 * fifo_multi.h
 *
 *  Created on: Jun 18, 2020
 *      Author: lbogdanov
 */

#ifndef FIFO_MULTI_H_
#define FIFO_MULTI_H_

#include <stdint.h>

#define FIFO_SIZE		8
#define FIFO_NUMBERS	4

void fifo_init(void);
uint8_t fifo_push(uint8_t fifo_number, uint8_t element);
uint8_t fifo_pop(uint8_t fifo_number, uint8_t *element);
uint8_t fifo_peek(uint8_t fifo_number);

#endif /* FIFO_MULTI_H_ */
