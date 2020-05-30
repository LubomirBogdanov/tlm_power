#include "chip.h"

#ifdef MCU_TARGET_1


static I2CM_XFER_T  		i2cmXferRec;
#define SLAVE_ADDRESS       (0x60)

const uint32_t OscRateIn = 0;
const uint32_t ExtRateIn = 0;

static void setupI2CMaster(void)
{
	Chip_I2C_Init(LPC_I2C);
	Chip_I2C_SetClockDiv(LPC_I2C, 40);
	Chip_I2CM_SetBusSpeed(LPC_I2C, 100000);
	Chip_I2CM_Enable(LPC_I2C);
}

static void setupI2CSlave(void)
{
	Chip_I2CS_SetSlaveAddr(LPC_I2C, 0, SLAVE_ADDRESS);
	Chip_I2CS_SetSlaveQual0(LPC_I2C, false, 0);	// Disable Qualifier for Slave Address 0
	Chip_I2CS_EnableSlaveAddr(LPC_I2C, 0);

	Chip_I2CS_ClearStatus(LPC_I2C, I2C_STAT_SLVDESEL);
	Chip_I2C_EnableInt(LPC_I2C, I2C_INTENSET_SLVPENDING | I2C_INTENSET_SLVDESEL);
	Chip_I2CS_Enable(LPC_I2C);
}

static void WaitForI2cXferComplete(I2CM_XFER_T *xferRecPtr)
{
	// Test for still transferring data
	while (xferRecPtr->status == I2CM_STATUS_BUSY) {

	}
}

static void SetupXferRecAndExecute(uint8_t devAddr,
								   uint8_t *txBuffPtr,
								   uint16_t txSize,
								   uint8_t *rxBuffPtr,
								   uint16_t rxSize)
{
	i2cmXferRec.slaveAddr = devAddr;
	i2cmXferRec.status = 0;
	i2cmXferRec.txSz = txSize;
	i2cmXferRec.rxSz = rxSize;
	i2cmXferRec.txBuff = txBuffPtr;
	i2cmXferRec.rxBuff = rxBuffPtr;

	// Wait for master to go pending - needed in mixed master/slave mode on single I2C bus
	while (Chip_I2CM_IsMasterPending(LPC_I2C) == false) {}

	Chip_I2CM_Xfer(LPC_I2C, &i2cmXferRec);
	// Enable Master Interrupts
	Chip_I2C_EnableInt(LPC_I2C, I2C_INTENSET_MSTPENDING | I2C_INTENSET_MSTRARBLOSS | I2C_INTENSET_MSTSTSTPERR);
	// Wait for transfer completion
	WaitForI2cXferComplete(&i2cmXferRec);
	// Disable all Interrupts
	Chip_I2C_DisableInt(LPC_I2C, I2C_INTENSET_MSTPENDING | I2C_INTENSET_MSTRARBLOSS | I2C_INTENSET_MSTSTSTPERR);
}

void processSlaveTransferStart(){

}

void processSlaveTransferSend(){

}

void processSlaveTransferRecv(void){

}

void processSlaveTransferDone(void){

}

const static I2CS_XFER_T i2csCallBacks = {
	&processSlaveTransferStart,
	&processSlaveTransferSend,
	&processSlaveTransferRecv,
	&processSlaveTransferDone
};

void I2C_IRQHandler(void)
{
	uint32_t state = Chip_I2C_GetPendingInt(LPC_I2C);

	// Error handling
	if (state & (I2C_INTSTAT_MSTRARBLOSS | I2C_INTSTAT_MSTSTSTPERR)) {
		Chip_I2CM_ClearStatus(LPC_I2C, I2C_STAT_MSTRARBLOSS | I2C_STAT_MSTSTSTPERR);
	}

	// Call I2CM ISR function with the I2C device and transfer rec
	if (state & I2C_INTENSET_MSTPENDING) {
		Chip_I2CM_XferHandler(LPC_I2C, &i2cmXferRec);
	}

	// I2C slave related interrupt
	while (state & (I2C_INTENSET_SLVPENDING | I2C_INTENSET_SLVDESEL)) {
		Chip_I2CS_XferHandler(LPC_I2C, &i2csCallBacks);
		state = Chip_I2C_GetPendingInt(LPC_I2C);
	}
}

int main(void)
{
	uint8_t tx_buff[16];
	uint8_t rx_buff[16];

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

	// Setup I2C, master, and slave
	setupI2CMaster();
	setupI2CSlave();

	NVIC_EnableIRQ(I2C_IRQn);

	while (1) {
		SetupXferRecAndExecute(SLAVE_ADDRESS, tx_buff, 16, rx_buff, 16);
	}
}




/*
const uint32_t OscRateIn = 0;
const uint32_t ExtRateIn = 0;

#define I2C_ADDR_7BIT           	(0x60)
#define TICKRATE_HZ             	(1000)
#define MONRDYEN					(1 << 16)
#define MONRDY						(1 << 16)
#define SLVPENDING					(1 << 8)
#define SLVSTATE					(3 << 9)
#define SLVCONTINUE					(1 << 0)
#define SLVIDX						(3 << 12)
#define SLVMONOV					(1 << 17)

#define SLVSTATE_ADDR				0x00
#define SLVSTATE_RECEIVE			0x01
#define SLVSTATE_TRANSMIT			0x02
#define SLVSTATE_RESERVED			0x03

#define SLVIDX_0					0x00
#define SLVIDX_1					0x01
#define SLVIDX_2					0x02
#define SLVIDX_3					0x03

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

void I2C_IRQHandler(void){
	volatile uint32_t irq_status;
	volatile uint32_t slave_status;
	volatile uint32_t requested_slave_address;
	volatile uint8_t slave_data = 0;

	irq_status = LPC_I2C->INTSTAT;

	while (irq_status & (I2C_INTENSET_SLVPENDING | I2C_INTENSET_SLVDESEL)) {
		//Chip_I2CS_XferHandler(LPC_I2C, &i2csCallBacks);
		if(irq_status & I2C_INTENSET_SLVDESEL){
			LPC_I2C->STAT &= ~I2C_STAT_SLVDESEL;
			//Slave is done
		}
		else{
			slave_status = LPC_I2C->STAT & I2C_STAT_SLVSTATE >> 9;

			switch (slave_status) {
			case I2C_STAT_SLVCODE_ADDR:		// Slave address received
				requested_slave_address = LPC_I2C->STAT & I2C_STAT_SLVIDX >> 12;
				break;

			case I2C_STAT_SLVCODE_RX:		// Data byte received
				slave_data = LPC_I2C->SLVDAT & I2C_SLVDAT_DATAMASK;
				break;

			case I2C_STAT_SLVCODE_TX:		// Get byte that needs to be sent
				LPC_I2C->SLVDAT = slave_data;
				break;
			}
		}

		irq_status = LPC_I2C->INTSTAT;
	}

	LPC_I2C->SLVCTL = I2C_SLVCTL_SLVCONTINUE;
}

int main(void){
	uint32_t ret = 0;

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
	LPC_I2C->CFG |= 0x04; //Enable monitor

	LPC_I2C->SLVADR[0] = (I2C_ADDR_7BIT << 1); //Set address
	LPC_I2C->SLVADR[0] &= ~0x01UL; //Enable address
	LPC_I2C->SLVQUAL0 = 0;
	LPC_I2C->STAT = I2C_STAT_SLVDESEL; //Clear status register

	LPC_I2C->INTENSET = (I2C_INTENSET_SLVPENDING | I2C_INTENSET_SLVDESEL);

	NVIC_EnableIRQ(I2C_IRQn);

	LPC_I2C->CFG |= 0x03; //Enable i2c master & slave

	SysTick_Config(SystemCoreClock / TICKRATE_HZ);

	while(1) {
		delay_ms(1);
	}
}
*/

#endif
