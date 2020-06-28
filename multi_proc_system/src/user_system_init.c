/*
    Copyright (C) 2020 Lubomir Bogdanov
    Contributor Lubomir Bogdanov <lbogdanov@tu-sofia.bg>
    This file is part of tlm_power project.
    tlm_power is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    tlm_power is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.
    You should have received a copy of the GNU Lesser General Public License
    along with tlm_power.  If not, see <http://www.gnu.org/licenses/>.
*/

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
