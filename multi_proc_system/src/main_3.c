#include "main.h"

#ifdef MCU_TARGET_3

extern volatile uint8_t slave_tx_buff[I2C_RX_BUFF];

int main(void) {
	volatile uint8_t my_rx_data[I2C_RX_BUFF];
	volatile uint8_t my_rx_data_len;

	slave_tx_buff[0] = 0x70;
	slave_tx_buff[1] = 0x71;
	slave_tx_buff[2] = 0x72;
	slave_tx_buff[3] = 0x73;

	user_gpio_init();
	user_delay_init();
	user_i2c_init();
	user_i2c_enable_monitor();
	user_i2c_enable_master();
	user_i2c_set_slave_address(I2C_OWN_ADDR_7BIT);
	user_i2c_enable_slave();
	user_i2c_enable_slave_interrupts();

	user_gpio_clear();

	while(1) {
		if(user_i2c_slave_data_ready()){
			my_rx_data_len = user_i2c_slave_data_read(my_rx_data);

			if(my_rx_data[0] == 0x55){
				if(my_rx_data[1] == 0x12){
					if(my_rx_data[2] == 0x14){
						if(my_rx_data[3] == 0x16){
							user_gpio_toggle();
						}
					}
				}
			}

			my_rx_data_len = my_rx_data_len;
		}
	}

	return 0;
}

#endif
