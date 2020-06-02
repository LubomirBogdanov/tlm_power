#include "chip.h"

#ifdef MCU_TARGET_0

const uint32_t OscRateIn = 0;
const uint32_t ExtRateIn = 0;

#define I2C_ADDR_7BIT           (0x50)
#define TICKRATE_HZ             (1000)

static volatile uint32_t ticks;

void SysTick_Handler(void){
	ticks++;
}

void delay_ms(uint16_t delay_value){
	uint32_t ticks_timeout = ticks;
	ticks_timeout += delay_value;
	while(ticks < ticks_timeout){
		__WFI();
	}
}

void user_i2c_init(void){
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
}

void user_i2c_enable_master(void){
	LPC_I2C->CFG |= 0x01; //Enable master
}

void user_i2c_clear_status(void){
	LPC_I2C->STAT = (I2C_STAT_MSTRARBLOSS | I2C_STAT_MSTSTSTPERR);
}

/*!
 * \brief
 *
 * \return 1 - the address/data was acknowledged, 0 - the address/data
 * was not acknowledged
 */
uint8_t user_i2c_master_ack_get(void){
	uint8_t master_state = 0;
	uint8_t slave_ack = 0;
	uint32_t master_status = 0;

	while(!(LPC_I2C->STAT & I2C_STAT_MSTPENDING)) { }

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

	return slave_ack;
}

/*!
 * \brief
 *
 * \param slave_addr -
 * \param slave_data_len -
 * \param slave_data -
 *
 * \return 0 - transmission was successful, 1 - transmission was incomplete (NACK was detected)
 */
uint8_t user_i2c_master_write(uint8_t slave_addr, uint16_t slave_data_len, uint8_t *slave_data){
	uint8_t err = 0;
	uint16_t i;

	user_i2c_clear_status();

	LPC_I2C->MSTDAT = slave_addr << 1; //Make 8-bit address

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

	LPC_I2C->MSTCTL = I2C_MSTCTL_MSTSTOP; //Stop

	return err;
}

uint8_t user_i2c_master_read(uint8_t slave_addr, uint16_t slave_data_len, uint8_t *slave_data){
	uint8_t err = 0;
	uint16_t i;

	user_i2c_clear_status();

	LPC_I2C->MSTDAT = (slave_addr << 1) | 0x01; //Make 8-bit address

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

	LPC_I2C->MSTCTL = I2C_MSTCTL_MSTSTOP; //Stop

	return err;
}

void user_gpio_init(void){
	LPC_GPIO_PORT->DIR[0] |= 1 << 4;
	LPC_GPIO_PORT->CLR[0] = 1 << 4;
}

void user_gpio_set(void){
	LPC_GPIO_PORT->SET[0] = (1 << 4);
}

void user_gpio_clear(void){
	LPC_GPIO_PORT->CLR[0] = (1 << 4);
}

int main(void){
	uint8_t i;
	uint8_t slv_data_tx[3] = {0x01, 0x33, 0x55};
	uint8_t slv_data_rx[4] = {0x00, 0x00, 0x00, 0x00};

	SystemCoreClockUpdate();

	user_gpio_init();
	user_i2c_init();
	user_i2c_enable_master();

	NVIC_DisableIRQ(I2C_IRQn);
	SysTick_Config(SystemCoreClock / TICKRATE_HZ);

	user_i2c_master_write(I2C_ADDR_7BIT, 3, slv_data_tx);
	delay_ms(100);

	while(1) {
		user_i2c_master_write(I2C_ADDR_7BIT, 2, slv_data_tx);
		user_i2c_master_read(I2C_ADDR_7BIT, 4, slv_data_rx);

		if(slv_data_tx[2] != slv_data_rx[0]){
			user_gpio_set();
		}
		else{
			user_gpio_clear();
		}

		delay_ms(1000);
	}
}
#endif


