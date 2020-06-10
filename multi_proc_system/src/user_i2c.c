/*
 * user_i2c.c
 *
 *  Created on: Jun 6, 2020
 *      Author: lbogdanov
 */
#include "user_i2c.h"

extern volatile uint32_t user_ticks;

volatile uint8_t slave_rx_buff_index;
volatile uint8_t slave_rx_buff[I2C_RX_BUFF];
volatile uint8_t slave_tx_buff_index;
volatile uint8_t slave_tx_buff[I2C_RX_BUFF];
volatile uint8_t slave_data_ready;
volatile uint8_t slave_rx_buff_len;

void user_i2c_slave_check_pending(void){
	uint8_t slave_pending = 0;
	while(!slave_pending){
		slave_pending = (LPC_I2C->STAT & I2C_STAT_SLVPENDING) >> 8;
 	}
}

void I2C_IRQHandler(void){
	uint32_t irq_status;
	uint32_t slave_status;

	irq_status = LPC_I2C->INTSTAT;

	if(irq_status & I2C_INTSTAT_SLVDESEL){
		LPC_I2C->STAT = I2C_STAT_SLVDESEL; //Clear status bit
		slave_rx_buff_len = slave_rx_buff_index;
		slave_rx_buff_index = 0;
		slave_tx_buff_index = 0;
		if(slave_rx_buff_len != 0){
			slave_data_ready = 1;
		}
	}
	else{
		slave_status = ((LPC_I2C->STAT & I2C_STAT_SLVSTATE) >> 9) & 0x03UL;

		switch (slave_status) {
		case I2C_STAT_SLVCODE_ADDR:		//Address byte match

			break;

		case I2C_STAT_SLVCODE_RX:		// Data byte received
			slave_rx_buff[slave_rx_buff_index] = LPC_I2C->SLVDAT & I2C_SLVDAT_DATAMASK;
			slave_rx_buff_index++;
			if(slave_rx_buff_index >= I2C_RX_BUFF){
				slave_rx_buff_index = 0;
			}
			break;

		case I2C_STAT_SLVCODE_TX:		// Data byte sending
			LPC_I2C->SLVDAT = slave_tx_buff[slave_tx_buff_index++];
			if(slave_tx_buff_index >= I2C_TX_BUFF){
				slave_tx_buff_index = 0;
			}
			break;
		}
		
		user_i2c_slave_check_pending();
		LPC_I2C->SLVCTL = I2C_SLVCTL_SLVCONTINUE;
	}
}

void user_i2c_init(void){
	slave_rx_buff_index = 0;
	slave_tx_buff_index = 0;
	slave_data_ready = 0;
	slave_rx_buff_len = 0;

	LPC_SYSCTL->SYSAHBCLKCTRL |= 1 << SYSCTL_CLOCK_SWM;
	LPC_SYSCTL->SYSAHBCLKCTRL |= 1 << SYSCTL_CLOCK_GPIO;
	LPC_SYSCTL->SYSAHBCLKCTRL |= 1 << SYSCTL_CLOCK_IOCON;
	LPC_SYSCTL->SYSAHBCLKCTRL |= 1 << SYSCTL_CLOCK_I2C0;

	LPC_SWM->PINASSIGN[7] &= 0x00FFFFFF;
	LPC_SWM->PINASSIGN[8] &= 0xFFFFFF00;
	LPC_SWM->PINASSIGN[7] |= 0x01 << 24; //P0.1 = I2C_SDA
	LPC_SWM->PINASSIGN[8] |= 0x00; //P0.0 = I2C_SCL
	LPC_IOCON->PIO0[0] |= PIN_OD_MASK;
	LPC_IOCON->PIO0[1] |= PIN_OD_MASK;

	LPC_SYSCON->PRESETCTRL &= ~(1 << 6);
	LPC_SYSCON->PRESETCTRL |= 1 << 6;

	LPC_I2C->CLKDIV = 20; //114 kHz
	LPC_I2C->MSTTIME = 0x01; //3 clocks SCL(high), 2 clocks SCL(low), do not use logic operators here

	LPC_I2C->STAT = I2C_STAT_SLVDESEL; //Clear status bit
}

void user_i2c_enable_master(void){
	LPC_I2C->CFG |= I2C_CFG_MSTEN;
}

void user_i2c_clear_status(void){
	LPC_I2C->STAT = (I2C_STAT_MSTRARBLOSS | I2C_STAT_MSTSTSTPERR);
}

uint32_t timeout_ticks;

void user_i2c_timeout_start(void){
	timeout_ticks = user_ticks + I2C_ACK_TIMEOUT_MS;
}

uint8_t user_i2c_timeout(void){
	if(user_ticks >= timeout_ticks){
		return 1;
	}
	else{
		return 0;
	}
}


/*!
 * \brief Wait for the acknowledge bit. If it is not present
 * within I2C_ACK_TIMEOUT_MS milliseconds, then return 0.
 *
 * \return 1 - the address/data was acknowledged, 0 - the address/data
 * was not acknowledged
 */
uint8_t user_i2c_master_ack_get(void){
	uint8_t master_state = 0;
	uint8_t slave_ack = 0;
	uint32_t master_status = 0;

	user_i2c_timeout_start();
	while(!(LPC_I2C->STAT & I2C_STAT_MSTPENDING)) {
		if(user_i2c_timeout()){
			goto end;
		}
	}

	master_status = LPC_I2C->STAT;

	if(master_status & I2C_STAT_MSTRARBLOSS){

	}
	else if(master_status & I2C_STAT_MSTSTSTPERR){
		
	}
	else{
		master_state = (LPC_I2C->STAT & I2C_STAT_MSTSTATE) >> 1;

		if(master_state == I2C_STAT_MSTCODE_TXREADY){
			slave_ack = 1;
		}
		else if(master_state == I2C_STAT_MSTCODE_RXREADY){
			slave_ack = 1;
		}
		/*else if(master_state == I2C_STAT_MSTCODE_IDLE){

		}
		else if(master_state == I2C_STAT_MSTCODE_NACKADR){

		}
		else if(master_state == I2C_STAT_MSTCODE_NACKDAT){

		}*/
	}

	user_i2c_clear_status();

end:
	return slave_ack;
}

void user_i2c_master_check_pending(void){
	uint8_t master_pending = 0;
	while(!master_pending){
		master_pending = (LPC_I2C->STAT & I2C_STAT_MSTPENDING);
 	}
}

/*!
 * \brief Writes a number of bytes to a slave. This function is blocking
 * for at least of I2C_ACK_TIMEOUT_MS milliseconds if the slave does not
 * respond.
 *
 * \param slave_addr - the 7-bit address of the slave that will get the data
 * \param slave_data_len - number of bytes to be sent to the slave
 * \param slave_data - a pointer to an array with the bytes to be sent to the slave
 *
 * \return 0 - transmission was successful, 1 - transmission was incomplete (NACK was detected)
 */
uint8_t user_i2c_master_write(uint8_t slave_addr, uint16_t slave_data_len, uint8_t *slave_data){
	uint8_t err = 0;
	uint16_t i;

	user_i2c_clear_status();

	LPC_I2C->MSTDAT = slave_addr << 1; //Make 8-bit address

	user_i2c_monitor_wait_bus_idle();

	user_i2c_master_check_pending();

	LPC_I2C->MSTCTL = I2C_MSTCTL_MSTSTART; //Start

	if(user_i2c_master_ack_get()){
		for(i = 0; i < slave_data_len; i++){
			LPC_I2C->MSTDAT = slave_data[i];
			LPC_I2C->MSTCTL = I2C_MSTCTL_MSTCONTINUE;
			if(!user_i2c_master_ack_get()){
				err = 1;
				break;
			}
		}
	}

	user_i2c_master_check_pending();

	LPC_I2C->MSTCTL = I2C_MSTCTL_MSTSTOP; //Stop

	return err;
}

uint8_t user_i2c_master_read(uint8_t slave_addr, uint16_t slave_data_len, uint8_t *slave_data){
	uint8_t err = 0;
	uint16_t i;

	user_i2c_clear_status();

	LPC_I2C->MSTDAT = (slave_addr << 1) | 0x01; //Make 8-bit address

	user_i2c_monitor_wait_bus_idle();

	user_i2c_master_check_pending();

	LPC_I2C->MSTCTL = I2C_MSTCTL_MSTSTART; //Start

	if(user_i2c_master_ack_get()){
		slave_data[0] = LPC_I2C->MSTDAT;
	}

	for(i = 1; i < slave_data_len; i++){
		LPC_I2C->MSTCTL = I2C_MSTCTL_MSTCONTINUE;
		if(user_i2c_master_ack_get()){
			slave_data[i] = LPC_I2C->MSTDAT;
		}
		else{
			err = 1;
			break;
		}
	}

	user_i2c_master_check_pending();

	LPC_I2C->MSTCTL = I2C_MSTCTL_MSTSTOP; //Stop

	return err;
}

void user_i2c_enable_monitor(void){
	LPC_I2C->CFG |= I2C_CFG_MONEN;
}

void user_i2c_enable_slave(void){
	LPC_I2C->CFG |= I2C_CFG_SLVEN;
}

void user_i2c_enable_slave_interrupts(void){
	LPC_I2C->INTENSET = (I2C_INTENSET_SLVPENDING | I2C_INTENSET_SLVDESEL);
	NVIC_EnableIRQ(I2C_IRQn);
}

void user_i2c_set_slave_address(uint8_t slave_seven_bit_address){
	LPC_I2C->SLVADR[0] = (slave_seven_bit_address << 1); //Set address
	LPC_I2C->SLVADR[0] &= ~0x01UL; //Enable address
	LPC_I2C->SLVQUAL0 = 0;
}

uint8_t user_i2c_slave_data_ready(void){
	return slave_data_ready;
}

uint8_t user_i2c_slave_data_read(uint8_t *slave_data_buff){
	uint8_t i;

	for(i = 0; i < slave_rx_buff_len; i++){
		slave_data_buff[i] = slave_rx_buff[i];
	}

	slave_data_ready = 0;

	return slave_rx_buff_len;
}

void user_i2c_monitor_wait_bus_idle(void){
	uint32_t bus_status = 1;

	while(bus_status){
		bus_status = ((LPC_I2C->STAT & I2C_STAT_MONACTIVE) >> 18) & 0x01;		
	}
}
