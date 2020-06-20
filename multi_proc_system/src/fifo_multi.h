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
