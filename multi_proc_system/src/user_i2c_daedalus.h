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
 * user_i2c.h
 *
 *  Created on: Jun 20, 2020
 *      Author: lbogdanov
 */

#ifndef USER_I2C_DAEDALUS_H_
#define USER_I2C_DAEDALUS_H_

#ifdef USE_USER_I2C_DAEDALUS

#include "main.h"

#define MCU_TARGET_0_ADDRESS		0x60
#define MCU_TARGET_1_ADDRESS		0x61
#define MCU_TARGET_2_ADDRESS		0x62
#define MCU_TARGET_3_ADDRESS		0x63
#define MCU_TARGET_4_ADDRESS		0x64
#define MCU_TARGET_5_ADDRESS		0x65
#define MCU_TARGET_6_ADDRESS		0x66
#define MCU_TARGET_7_ADDRESS		0x67
#define MCU_TARGET_8_ADDRESS		0x68
#define MCU_TARGET_9_ADDRESS		0x69

#if defined MCU_TARGET_0
	#define I2C_OWN_ADDR_7BIT       	(0x60)
#elif defined MCU_TARGET_1
	#define I2C_OWN_ADDR_7BIT           (0x61)
#elif defined MCU_TARGET_2
	#define I2C_OWN_ADDR_7BIT           (0x62)
#elif defined MCU_TARGET_3
	#define I2C_OWN_ADDR_7BIT           (0x63)
#elif defined MCU_TARGET_4
	#define I2C_OWN_ADDR_7BIT           (0x64)
#elif defined MCU_TARGET_5
	#define I2C_OWN_ADDR_7BIT           (0x65)
#elif defined MCU_TARGET_6
	#define I2C_OWN_ADDR_7BIT           (0x66)
#elif defined MCU_TARGET_7
	#define I2C_OWN_ADDR_7BIT           (0x67)
#elif defined MCU_TARGET_8
	#define I2C_OWN_ADDR_7BIT           (0x68)
#elif defined MCU_TARGET_9
	#define I2C_OWN_ADDR_7BIT           (0x69)
#endif

#define I2C_ACK_TIMEOUT_MS			1
#define I2C_RX_BUFF					16
#define I2C_TX_BUFF					16

void user_i2c_init(void);
void user_i2c_enable_master(void);
void user_i2c_enable_slave(void);
void user_i2c_enable_slave_interrupts(void);
void user_i2c_enable_monitor(void);
uint8_t user_i2c_master_write(uint8_t slave_addr, uint16_t slave_data_len, uint8_t *slave_data);
uint8_t user_i2c_master_read(uint8_t slave_addr, uint16_t slave_data_len, uint8_t *slave_data);
uint8_t user_i2c_slave_data_ready(void);
uint8_t user_i2c_slave_data_read(uint8_t *slave_data_buff);
void user_i2c_set_slave_address(uint8_t slave_seven_bit_address);

void user_i2c_clear_status(void);
void user_i2c_timeout_start(void);
uint8_t user_i2c_timeout(void);
uint8_t user_i2c_master_ack_get(void);
void user_i2c_monitor_wait_bus_idle(void);

#endif

#endif /* USER_I2C_H_ */
