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
#include "main.h"
#include "ported.h"
#include "aux_func.h"
#include "straight_func.h"

#ifdef MCU_TARGET_1

int main(void){
    // Function's Input Arguments 
    static tCH_1 in_0ND_1;

   user_system_init();

    //while( lpc_wait_start()) {}

#if NUM_OF_TOKENS == 5
    for( int c0 =  ceil1(0); c0 <=  floor1(4); c0 += 1 ) {
#endif

#if NUM_OF_TOKENS == 50
    for( int c0 =  ceil1(0); c0 <=  floor1(49); c0 += 1 ) {
#endif

#if NUM_OF_TOKENS == 500
    for( int c0 =  ceil1(0); c0 <=  floor1(499); c0 += 1 ) {
#endif
      	readFSL(ND_1_IG_1_CH_1, &in_0ND_1, 1);//READ
	user_gpio_set();
	user_delay_ms(5);
	user_gpio_clear();
	user_delay_ms(5);


      	_out_numbers_stream(in_0ND_1); //EXEC
	user_gpio_set();
	user_delay_ms(5);
	user_gpio_clear();
	user_delay_ms(5);

	//WRITE - none

    } // for c0

    //lpc_send_stop();

    while(1){ }
}

#endif
