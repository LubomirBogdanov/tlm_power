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

#include "main.h"

#ifdef MCU_TARGET_1

extern volatile uint8_t slave_tx_buff[I2C_RX_BUFF];

int main(void){
	volatile uint8_t my_rx_data[I2C_RX_BUFF];
	volatile uint8_t my_rx_data_len;

	slave_tx_buff[0] = 0x30;
	slave_tx_buff[1] = 0x31;
	slave_tx_buff[2] = 0x32;
	slave_tx_buff[3] = 0x33;

	user_gpio_init();
	user_i2c_init();
	user_i2c_enable_monitor();
	user_i2c_enable_master();
	user_i2c_set_slave_address(I2C_OWN_ADDR_7BIT);
	user_i2c_enable_slave();
	user_i2c_enable_slave_interrupts();

	user_gpio_set();

	while(1) {
		if(user_i2c_slave_data_ready()){
			my_rx_data_len = user_i2c_slave_data_read(my_rx_data);

			if(my_rx_data[0] == 0x33){
				if(my_rx_data[1] == 0x7f){
					if(my_rx_data[2] == 0x55){
						if(my_rx_data[3] == 0x3E){
							user_gpio_toggle();
						}
					}
				}
			}

			my_rx_data_len = my_rx_data_len;
		}
	}
}

#endif
