#include "user_system_init.h"

#ifndef MCU_TARGET_empty
void user_system_init(void){
   user_delay_init();
   user_gpio_init();
   user_gpio_clear();
   user_i2c_init();
   user_i2c_enable_monitor();
   user_i2c_enable_master();
   user_i2c_set_slave_address(I2C_OWN_ADDR_7BIT);
   user_i2c_enable_slave();
   user_i2c_enable_slave_interrupts();
   fifo_init();
}
#endif
