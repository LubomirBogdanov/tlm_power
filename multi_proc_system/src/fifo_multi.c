/*
 * fifo_multi.c
 *
 *  Created on: Jun 18, 2020
 *      Author: lbogdanov
 */
#include "fifo_multi.h"

typedef struct {
	uint8_t overflow;
	uint8_t head_index;
	uint8_t tail_index;
	uint8_t data[FIFO_SIZE];
}fifo_buff_t;

fifo_buff_t fifo_bf[FIFO_NUMBERS];

void fifo_init(void){
	uint8_t i, j;

	for(i = 0; i < FIFO_NUMBERS; i++){
		fifo_bf[i].overflow = 0;
		fifo_bf[i].head_index = 0;
		fifo_bf[i].tail_index = 0;
		for(j = 0; j < FIFO_SIZE; j++){
			fifo_bf[i].data[j] = 0x00;
		}
	}
}

/*!
 * \brief
 *
 * \param fifo_number -
 *
 * \return 0 - element pushed successfully, 1 - fifo is full
 * and element was not pushed
 */
uint8_t fifo_push(uint8_t fifo_number, uint8_t element){
	uint8_t tmp_index;

	tmp_index = fifo_bf[fifo_number].head_index;

	if(tmp_index == FIFO_SIZE){
		if(fifo_bf[fifo_number].tail_index == 0){
			return 1;
		}
		else{
			tmp_index = 0;
			fifo_bf[fifo_number].overflow = 1;
		}
	}

	if(fifo_bf[fifo_number].overflow){
		if(tmp_index == fifo_bf[fifo_number].tail_index){
			return 1;
		}
	}

	fifo_bf[fifo_number].data[tmp_index] = element;

	tmp_index++;

	fifo_bf[fifo_number].head_index = tmp_index;

	return 0;
}

/*!
 * \brief
 *
 * \param fifo_number -
 *
 * \return 0 - element popped successfully, 1 - fifo is
 * empty and element was filled with zero.
 */
uint8_t fifo_pop(uint8_t fifo_number, uint8_t *element){
	uint8_t tmp_index;

	tmp_index = fifo_bf[fifo_number].tail_index;

	if(!fifo_bf[fifo_number].overflow){
		if(tmp_index == fifo_bf[fifo_number].head_index){
			*element = 0;
			return 1;
		}
	}

	*element = fifo_bf[fifo_number].data[tmp_index];

	tmp_index++;

	if(tmp_index == FIFO_SIZE){
		fifo_bf[fifo_number].overflow = 0;
		tmp_index = 0;
	}

	fifo_bf[fifo_number].tail_index = tmp_index;

	return 0;
}

/*!
 * \brief
 *
 * \return 0 - fifo has elements, 1 - fifo is empty
 */
uint8_t fifo_peek(uint8_t fifo_number){
	uint8_t tmp_index;

	tmp_index = fifo_bf[fifo_number].tail_index;

	if(!fifo_bf[fifo_number].overflow){
		if(tmp_index == fifo_bf[fifo_number].head_index){
			return 1;
		}
	}

	return 0;
}
