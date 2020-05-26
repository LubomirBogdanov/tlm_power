#include "chip.h"

#ifdef MCU_TARGET_0

int main(void) {
	volatile unsigned long i;

	LPC_SYSCTL->SYSAHBCLKCTRL |= 1 << SYSCTL_CLOCK_SWM;
	LPC_SYSCTL->SYSAHBCLKCTRL |= 1 << SYSCTL_CLOCK_I2C0;
	LPC_SYSCTL->SYSAHBCLKCTRL |= 1 << SYSCTL_CLOCK_GPIO;
	LPC_SYSCTL->SYSAHBCLKCTRL |= 1 << SYSCTL_CLOCK_IOCON;
	LPC_GPIO_PORT->DIR[0] |= 1 << 4;
	LPC_GPIO_PORT->CLR[0] = 1 << 4;

//LPC_GPIO_PORT->DIR[0] |= 1 << 0;
//LPC_GPIO_PORT->DIR[0] |= 1 << 1;

//	while (1) {
//		LPC_GPIO_PORT->SET[0] = (1 << 0);
//		LPC_GPIO_PORT->SET[0] = (1 << 1);
//		for(i = 0; i < 10000; i++){ }
//		LPC_GPIO_PORT->CLR[0] = (1 << 0);
//		LPC_GPIO_PORT->CLR[0] = (1 << 1);
//		for(i = 0; i < 10000; i++){ }
//	}

	LPC_SWM->PINASSIGN[7] &= 0x00FFFFFF;
	LPC_SWM->PINASSIGN[8] &= 0xFFFFFF00;
	LPC_SWM->PINASSIGN[7] |= 0x01 << 24; //P0.1 = I2C_SDA
	LPC_SWM->PINASSIGN[8] |= 0x00 << 0; //P0.0 = I2C_SCL

	LPC_IOCON->PIO0[0] |= PIN_OD_MASK;
	LPC_IOCON->PIO0[1] |= PIN_OD_MASK;

	LPC_SYSCON->PRESETCTRL &= 1 << 6;

	LPC_I2C->CFG |= 1 << 0; //Enable master
	LPC_I2C->CLKDIV = 64; //Set divider

	LPC_SYSCON->PRESETCTRL |= 1 << 6;

	while (1) {
		LPC_GPIO_PORT->SET[0] = (1 << 4);


		LPC_I2C->MSTDAT = 0x70;
		LPC_I2C->MSTCTL |= 1 << 1; //Start

		while(!(LPC_I2C->STAT & 0x01)){ }

		//LPC_I2C->MSTDAT = 0x55;

		//while(!(LPC_I2C->STAT & 0x01)){ }
		//LPC_I2C->MSTCTL |= 1 << 2; //Stop

		LPC_GPIO_PORT->CLR[0] = (1 << 4);

//		for(i = 0; i < 100000; i++){ }
//		for(i = 0; i < 100000; i++){ }
	}


	return 0;
}

#endif

/*
int main(void) {
	volatile unsigned long i;

	LPC_SYSCTL->SYSAHBCLKCTRL |= SYSCTL_CLOCK_SWM;
	LPC_SYSCTL->SYSAHBCLKCTRL |= SYSCTL_CLOCK_GPIO;
	LPC_GPIO_PORT->DIR[0] |= 1UL << 4;
	//LPC_GPIO_PORT->DIR[0] |= 1UL << 4;
	LPC_GPIO_PORT->CLR[0] = (1 << 4);

	while (1) {
//		LPC_GPIO_PORT->SET[0] = (1 << 4);
//		for(i = 0; i < 10000; i++){ }
//		LPC_GPIO_PORT->CLR[0] = (1 << 4);
//		for(i = 0; i < 10000; i++){ }
	}

	return 0;
}
*/
