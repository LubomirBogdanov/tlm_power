#include "main.h"
#include "ported.h"
#include "aux_func.h"

#ifdef MCU_TARGET_1


int main(void){
    while( lpc_wait_start() ) {}


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

    lpc_send_stop();
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
