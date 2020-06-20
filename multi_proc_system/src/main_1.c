#include "main.h"
#include "ported.h"
#include "aux_func.h"
#include "straight_func.h"

#ifdef MCU_TARGET_1

int main(void){
    // Function's Input Arguments 
    static tCH_1 in_0ND_1;

   user_system_init();

    while( lpc_wait_start()) {}

    for( int c0 =  ceil1(0); c0 <=  floor1(4); c0 += 1 ) {
      readFSL(ND_1_IG_1_CH_1, &in_0ND_1, 1);
      _out_numbers_stream(in_0ND_1);
    } // for c0

    lpc_send_stop();

    while(1){ }
}


/*
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
*/

/*
int main(void){
	volatile uint8_t slave_data;
	uint32_t slave_state;

	user_delay_init();
	user_gpio_init();
	user_i2c_init();
	user_i2c_set_slave_address(I2C_OWN_ADDR_7BIT);
//	user_i2c_enable_monitor();
//	LPC_I2C->STAT = I2C_STAT_SLVSEL; //Clear status register
	user_i2c_enable_slave();
//	user_i2c_enable_slave_interrupts();

	//	SysTick_Config(SystemCoreClock / TICKRATE_HZ);

	user_gpio_set();

	while(1) {
		//delay_ms(1);

		while(!(LPC_I2C->STAT & I2C_INTSTAT_SLVPENDING)){ }

		slave_state = LPC_I2C->STAT & I2C_STAT_SLVSTATE >> 9;

		switch(slave_state){
		case I2C_STAT_SLVCODE_ADDR:
			LPC_I2C->SLVCTL = I2C_SLVCTL_SLVCONTINUE;
			break;
		case I2C_STAT_SLVCODE_RX:
			slave_data = LPC_I2C->SLVDAT;
			LPC_I2C->SLVCTL = I2C_SLVCTL_SLVCONTINUE;
			break;
		case I2C_STAT_SLVCODE_TX:
			LPC_I2C->SLVDAT = 0x7E;
			LPC_I2C->SLVCTL = I2C_SLVCTL_SLVCONTINUE;
			break;
		}
	}
}
*/
#endif
