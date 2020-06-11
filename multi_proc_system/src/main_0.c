#include "main.h"

#ifdef MCU_TARGET_0

int main(void){
    while( lpc_wait_start() ) {}


    int clk_num;

    // Function's Input Arguments 
    static tCH_7 in_0ND_3;

    // Function's Output Arguments 
    static tCH_11 out_0ND_0;

    // Additional Local Variables 
    int e2;
    int e3;
    int e0;
    int e1;

    for( int c0 =  ceil1(1); c0 <=  floor1(17); c0 += 1 ) {
      for( int c1 =  ceil1(0); c1 <=  floor1(11); c1 += 1 ) {
        if( c0-1 == 0 ) {
          e2 = ddiv(c1,2);
          e3 = ddiv(c1 + 1,2);

          _in_numbers_stream(&out_0ND_0);
          if( c1-2*e2 == 0 ) {
            if( -e2 + 5 >= 0 ) {
              writeFSL(ND_0_OG_1_CH_11, &out_0ND_0, (sizeof(tCH_11)+(sizeof(tCH_11)%4)+3)/4);
            }
          }
          if( c1-2*e3 + 1 == 0 ) {
            if( e3-1 >= 0 ) {
              writeFSL(ND_0_OG_1_CH_11, &out_0ND_0, (sizeof(tCH_11)+(sizeof(tCH_11)%4)+3)/4);
            }
          }
        }
        if( c0-6 >= 0 ) {
          if( c1-6 == 0 ) {
            e0 = ddiv(c0 + 1,2);
            e1 = ddiv(c0,2);
            if( c0-6 == 0 ) {
              readFSL(ND_3_IG_1_CH_7, &in_0ND_3, (sizeof(tCH_7)+(sizeof(tCH_7)%4)+3)/4);
            }
            if( c0-17 == 0 ) {
              readFSL(ND_3_IG_2_CH_8, &in_0ND_3, (sizeof(tCH_8)+(sizeof(tCH_8)%4)+3)/4);
            }
            if( c0-2*e0 + 1 == 0 ) {
              if( e0-4 >= 0 ) {
                if( -e0 + 8 >= 0 ) {
                  readFSL(ND_3_IG_3_CH_9, &in_0ND_3, (sizeof(tCH_9)+(sizeof(tCH_9)%4)+3)/4);
                }
              }
            }
            if( c0-2*e1 == 0 ) {
              if( e1-4 >= 0 ) {
                if( -e1 + 8 >= 0 ) {
                  readFSL(ND_3_IG_4_CH_10, &in_0ND_3, (sizeof(tCH_10)+(sizeof(tCH_10)%4)+3)/4);
                }
              }
            }

            _out_numbers_stream(&in_0ND_3);
          }
        }
      } // for c1
    } // for c0

    lpc_set_stop();
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
