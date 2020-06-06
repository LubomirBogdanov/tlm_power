/*
 * user_i2c.h
 *
 *  Created on: Jun 6, 2020
 *      Author: lbogdanov
 */

#ifndef USER_I2C_H_
#define USER_I2C_H_

#include "main.h"

#if defined MCU_TARGET_0
	#define I2C_ADDR_7BIT           (0x60)
#elif defined MCU_TARGET_1
	#define I2C_ADDR_7BIT           (0x61)
#elif defined MCU_TARGET_2
	#define I2C_ADDR_7BIT           (0x62)
#elif defined MCU_TARGET_3
	#define I2C_ADDR_7BIT           (0x63)
#elif defined MCU_TARGET_4
	#define I2C_ADDR_7BIT           (0x64)
#elif defined MCU_TARGET_5
	#define I2C_ADDR_7BIT           (0x65)
#elif defined MCU_TARGET_6
	#define I2C_ADDR_7BIT           (0x66)
#elif defined MCU_TARGET_7
	#define I2C_ADDR_7BIT           (0x67)
#elif defined MCU_TARGET_8
	#define I2C_ADDR_7BIT           (0x68)
#elif defined MCU_TARGET_9
	#define I2C_ADDR_7BIT           (0x69)
#endif

#define I2C_ACK_TIMEOUT_MS			1
#define I2C_RX_BUFF					16
#define I2C_TX_BUFF					16

void user_i2c_init(void);
void user_i2c_enable_master(void);
void user_i2c_enable_monitor(void);
void user_i2c_enable_slave(void);
void user_i2c_enable_slave_interrupts(void);
uint8_t user_i2c_master_write(uint8_t slave_addr, uint16_t slave_data_len, uint8_t *slave_data);
uint8_t user_i2c_master_read(uint8_t slave_addr, uint16_t slave_data_len, uint8_t *slave_data);
uint8_t user_i2c_slave_data_ready(void);
uint8_t user_i2c_slave_data_read(uint8_t *slave_data_buff);
void user_i2c_set_slave_address(uint8_t slave_seven_bit_address);

void user_i2c_clear_status(void);
void user_i2c_timeout_start(void);
uint8_t user_i2c_timeout(void);
uint8_t user_i2c_master_ack_get(void);


#endif /* USER_I2C_H_ */
