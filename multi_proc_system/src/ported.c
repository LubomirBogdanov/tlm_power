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
#include "ported.h"

int lpc_wait_start(void){
	return 0;
}

void lpc_send_stop(void){
	user_gpio_set();
}

void microblaze_bread_datafsl(int *value, int fifo_channel_number){
	uint8_t slave_response[2]; //[REQUEST] [BYTE_READ]

	user_i2c_master_write(MCU_TARGET_0_ADDRESS, 1, (uint8_t *)&fifo_channel_number);
	user_i2c_master_read(MCU_TARGET_0_ADDRESS, 2, slave_response);
	
	while(slave_response[0]){
		user_delay_ms(1);
		user_i2c_master_write(MCU_TARGET_0_ADDRESS, 1, (uint8_t *)&fifo_channel_number);
		user_i2c_master_read(MCU_TARGET_0_ADDRESS, 2, slave_response);
	}

	*value = slave_response[1];
}

//void microblaze_bwrite_datafsl(int value, int pos){
void microblaze_bwrite_datafsl(int value, int fifo_channel_number){
	while(fifo_push(fifo_channel_number, value)) { }
}
