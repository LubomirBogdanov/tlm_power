#include "main.h"
#include "ported.h"
#include "aux_func.h"
#include "straight_func.h"
#include "fifo_multi.h"

#ifdef MCU_TARGET_0

int main(void){
    // Function's Output Arguments 
    static tCH_1 out_0ND_0;

    user_system_init();

    while( lpc_wait_start()) {}

    for( int c0 =  ceil1(0); c0 <=  floor1(4); c0 += 1 ) {
      _in_numbers_stream(&out_0ND_0);
      writeFSL(ND_0_OG_1_CH_1, &out_0ND_0, 1);
    } // for c0

    lpc_send_stop();

    while(1){ }
}


/*
int main(void){
	uint8_t slv_data_tx[4] = {0x33, 0x7f, 0x55, 0x3e};
	uint8_t slv_data_rx[4] = {0x00, 0x00, 0x00, 0x00};

	user_delay_init();
	user_gpio_init();
	user_i2c_init();
	user_i2c_enable_monitor();
	user_i2c_enable_master();
	user_i2c_set_slave_address(I2C_OWN_ADDR_7BIT);
	user_i2c_enable_slave();
	user_i2c_enable_slave_interrupts();

	user_gpio_set();

	while(1) {
		//user_gpio_set();
		for(uint32_t i = 0; i < 1000; i++){
			user_i2c_master_write(MCU_TARGET_1_ADDRESS, 4, slv_data_tx);
			user_delay_ms(2);
		}
		//user_gpio_clear();
		//user_delay_ms(1000);

		//user_gpio_set();
		for(uint32_t i = 0; i < 1000; i++){
			user_i2c_master_read(MCU_TARGET_1_ADDRESS, 4, slv_data_rx);
			user_delay_ms(2);
		}
		//user_gpio_clear();
		//user_delay_ms(1000);
	}
}
*/
#endif
