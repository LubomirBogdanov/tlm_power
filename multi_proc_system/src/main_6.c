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
#include "chip.h"

#ifdef MCU_TARGET_6

int main(void) {
	volatile unsigned long i;

	LPC_SYSCTL->SYSAHBCLKCTRL |= SYSCTL_CLOCK_SWM;
	LPC_SYSCTL->SYSAHBCLKCTRL |= SYSCTL_CLOCK_GPIO;
	LPC_GPIO_PORT->DIR[0] |= 1UL << 4;
	LPC_GPIO_PORT->DIR[0] &= ~(1UL << 0);
	LPC_GPIO_PORT->DIR[0] &= ~(1UL << 1);
	LPC_GPIO_PORT->CLR[0] = (1 << 4);

	while (1) {
		LPC_GPIO_PORT->SET[0] = (1 << 4);
		for(i = 0; i < 10000; i++){ }
		LPC_GPIO_PORT->CLR[0] = (1 << 4);
		for(i = 0; i < 10000; i++){ }
	}

	return 0;
}

#endif
