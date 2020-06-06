#include "main.h"

#ifdef MCU_TARGET_0

int main(void){
	uint8_t slv_data_tx[4] = {0x33, 0x7f, 0x55, 0x3e};
	uint8_t slv_data_rx[4] = {0x00, 0x00, 0x00, 0x00};

	SystemCoreClockUpdate();

	user_delay_init();
	user_gpio_init();
	user_i2c_init();
	user_i2c_enable_master();
	user_i2c_set_slave_address(I2C_OWN_ADDR_7BIT);
	user_i2c_enable_slave();
	user_i2c_enable_slave_interrupts();
	user_i2c_enable_monitor();

	user_gpio_set();

	while(1) {
		user_gpio_set();
		for(uint32_t i = 0; i < 1000; i++){
			user_i2c_master_write(MCU_TARGET_1_ADDRESS, 4, slv_data_tx);
			user_delay_ms(1);
		}
		user_gpio_clear();
		user_delay_ms(1000);

		user_gpio_set();
		for(uint32_t i = 0; i < 1000; i++){
			user_i2c_master_read(MCU_TARGET_1_ADDRESS, 4, slv_data_rx);
			user_delay_ms(1);
		}
		user_gpio_clear();
		user_delay_ms(1000);
	}
}

#endif
