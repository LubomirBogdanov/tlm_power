#include "chip.h"

#ifdef MCU_TARGET_0

const uint32_t OscRateIn = 0;
const uint32_t ExtRateIn = 0;

#define I2C_ADDR_7BIT           (0x60)
#define TICKRATE_HZ             (1000)

static volatile uint32_t ticks;

void SysTick_Handler(void){
	ticks++;
}

void delay_ms(uint16_t delay_value){
	uint32_t ticks_timeout = ticks;
	ticks_timeout += delay_value;
	while(ticks < ticks_timeout){
		__WFI();
	}
}

int main(void){
	uint32_t ret = 0;
	uint8_t txData[16];
	uint8_t rxData[16];
	I2CM_XFER_T i2cmXferRec;

	i2cmXferRec.slaveAddr = I2C_ADDR_7BIT;
	i2cmXferRec.status = 0;
	i2cmXferRec.txSz = 1;
	i2cmXferRec.rxSz = 1;
	i2cmXferRec.txBuff = txData;
	i2cmXferRec.rxBuff = rxData;

	SystemCoreClockUpdate();

	LPC_SYSCTL->SYSAHBCLKCTRL |= 1 << SYSCTL_CLOCK_SWM;
	LPC_SYSCTL->SYSAHBCLKCTRL |= 1 << SYSCTL_CLOCK_GPIO;
	LPC_SYSCTL->SYSAHBCLKCTRL |= 1 << SYSCTL_CLOCK_IOCON;
	LPC_SYSCTL->SYSAHBCLKCTRL |= 1 << SYSCTL_CLOCK_I2C0;

	LPC_SWM->PINASSIGN[7] &= 0x00FFFFFF;
	LPC_SWM->PINASSIGN[8] &= 0xFFFFFF00;
	LPC_SWM->PINASSIGN[7] |= 0x01 << 24; //P0.1 = I2C_SDA
	LPC_SWM->PINASSIGN[8] |= 0x00; //P0.0 = I2C_SCL
	LPC_IOCON->PIO0[0] |= PIN_OD_MASK;
	LPC_IOCON->PIO0[1] |= PIN_OD_MASK;

	LPC_SYSCON->PRESETCTRL &= ~(1 << 6);
	LPC_SYSCON->PRESETCTRL |= 1 << 6;

	LPC_I2C->CLKDIV = 20; //114 kHz
	LPC_I2C->MSTTIME = 0x01; //3 clocks SCL(high), 2 clocks SCL(low), do not use logic operators here
	LPC_I2C->CFG |= 0x01; //Enable master

	NVIC_DisableIRQ(I2C_IRQn);
	SysTick_Config(SystemCoreClock / TICKRATE_HZ);

	while(1) {
		//Chip_I2CM_XferBlocking(LPC_I2C, &i2cmXferRec);

		LPC_I2C->STAT |= (I2C_STAT_MSTRARBLOSS | I2C_STAT_MSTSTSTPERR);
		LPC_I2C->MSTDAT = 0xC0; //Write to 0x60 7-bit
		LPC_I2C->MSTCTL |= I2C_MSTCTL_MSTSTART; //Start

		//while (ret == 0) {
			/* wait for status change interrupt */
			while(!(LPC_I2C->STAT & I2C_STAT_MSTPENDING)) { }
			/* call state change handler */
			//ret = Chip_I2CM_XferHandler(LPC_I2C, &i2cmXferRec);
			LPC_I2C->MSTCTL |= I2C_MSTCTL_MSTSTOP; //Stop
		//}

		delay_ms(1);
	}
}


/*
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
 */
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
