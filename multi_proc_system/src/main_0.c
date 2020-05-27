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

int main(void){
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
	Chip_GPIO_Init(LPC_GPIO_PORT);

	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_SWM);
	Chip_SWM_MovablePinAssign(SWM_I2C_SDA_IO, 0);
	Chip_SWM_MovablePinAssign(SWM_I2C_SCL_IO, 1);
	Chip_IOCON_PinSetI2CMode(LPC_IOCON, IOCON_PIO0, PIN_I2CMODE_FASTPLUS);
	Chip_IOCON_PinSetI2CMode(LPC_IOCON, IOCON_PIO1, PIN_I2CMODE_FASTPLUS);
	Chip_Clock_DisablePeriphClock(SYSCTL_CLOCK_SWM);

	Chip_I2C_Init(LPC_I2C);
	Chip_I2C_SetClockDiv(LPC_I2C, 40);
	Chip_I2CM_SetBusSpeed(LPC_I2C, 100000);
	Chip_I2CM_Enable(LPC_I2C);

	NVIC_DisableIRQ(I2C_IRQn);
	SysTick_Config(SystemCoreClock / TICKRATE_HZ);

	while(1) {
		Chip_I2CM_XferBlocking(LPC_I2C, &i2cmXferRec);
		__WFI();
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
