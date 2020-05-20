#include "main.h"

volatile uint8_t uart_cmd;
volatile uint8_t uart_rx_byte_arrived;

void __attribute__ ((interrupt(PORT1_VECTOR))) port1_isr (void){
	uint8_t error = 0;

	__disable_interrupt();

	uart_cmd = 0x00;

	//Start bit
	timer_delay(12);

	//8 data bits
	for(uint8_t i = 0; i < 8; i++){
		timer_delay(12);
		uart_cmd |= soft_uart_read_rx(i);
	}

	//Stop bit
	timer_delay(12);

	soft_uart_write_tx(uart_cmd);

	switch(uart_cmd){
	case '0':
		LED_OUTREG &= ~LED_PIN;
		enable_chip(1);
		set_channel(0);
		break;
	case '1':
		LED_OUTREG &= ~LED_PIN;
		enable_chip(1);
		set_channel(1);
		break;
	case '2':
		LED_OUTREG &= ~LED_PIN;
		enable_chip(2);
		set_channel(0);
		break;
	case '3':
		LED_OUTREG &= ~LED_PIN;
		enable_chip(2);
		set_channel(1);
		break;
	case '4':
		LED_OUTREG &= ~LED_PIN;
		enable_chip(2);
		set_channel(2);
		break;
	case '5':
		LED_OUTREG &= ~LED_PIN;
		enable_chip(2);
		set_channel(3);
		break;
	case '6':
		LED_OUTREG &= ~LED_PIN;
		enable_chip(3);
		set_channel(0);
		break;
	case '7':
		LED_OUTREG &= ~LED_PIN;
		enable_chip(3);
		set_channel(1);
		break;
	case '8':
		LED_OUTREG &= ~LED_PIN;
		enable_chip(3);
		set_channel(2);
		break;
	case '9':
		LED_OUTREG &= ~LED_PIN;
		enable_chip(3);
		set_channel(3);
		break;
	default:			
		error = 1;
		break;
	}

	P1IFG = 0x00;

	__enable_interrupt();

	if(error){
		//Unsupported command, turn off led for now
		LED_OUTREG &= ~LED_PIN;
	}
	else{
		LED_OUTREG |= LED_PIN;
	}
}

void init_gpio(void){
	LED_PORT |= LED_PIN;
	LED_OUTREG |= LED_PIN;
}

void init_enable_pins(void){
	ICs_EN_PORT |= (IC1_EN | IC2_EN | IC3_EN);
	ICs_EN_OUTREG |= (IC2_EN | IC3_EN); //Start with IC1 upon reset
	ICs_EN_OUTREG &= ~IC1_EN;
}

void init_channel_select_pins(void){
	CHAN_SEL_PORT |= (CHAN_SEL_0 | CHAN_SEL_1);
}

void init_clocks(void){
	__bic_SR_register(OSCOFF); //Turn on LFXT1
	
	//Multiplex P2.6 and P2.7 to external XTAL
	P2DIR &= BIT6;
	P2DIR |= BIT7;
	P2SEL |= (BIT6 | BIT7);
	//Set XT1 = 32.768 kHz, XTAL
	BCSCTL1 &= ~XTS;
	BCSCTL3 &= ~LFXT1S_0; //Select 32.768 kHz for LFXT1
	BCSCTL3 |= XCAP_3; //Select 12.5 pF internal caps
	while(BCSCTL3 & LFXT1OF){ } //Wait for osc to stabilize

	//Set DCO = 15.25 MHz
	DCOCTL = 0x60; //DCO = 3, MOD = 0
	BCSCTL1 |= 0x0F; //RSEL = 15

	BCSCTL2 |= SELS; //SMCLK = LFXT1
	BCSCTL2 |= SELM_1; //MCLK = DCO
}

void init_timer(void){
	TACTL = 0x00;
	TACTL |= (TASSEL_2 | MC_1); //SMCLK, Up mode, div = 1
}

/*
 * \brief
 * \param delay_val - 6 = 212 us, 5 = 184 us, 4 = 156 us, 3 = 123 us, 2 = 92 us
 */
void timer_delay(uint16_t delay_val){
	TACCR0 = delay_val;
	TAR = 0;
	TACCTL0 &= ~CCIFG;
	while(!(TACCTL0 & CCIFG)){ }
}

void init_soft_uart(void){
	SOFT_UART_PORT &= ~SOFT_UART_MCU_RX_PIN;
	SOFT_UART_PORT |= SOFT_UART_MCU_TX_PIN;
	SOFT_UART_OUTREG |= SOFT_UART_MCU_TX_PIN;
	SOFT_UART_IESREG |= SOFT_UART_MCU_RX_PIN; //High-to-low transition
	SOFT_UART_IEREG |= SOFT_UART_MCU_RX_PIN; //Enable interrupt
}

void init(void){
	WDTCTL = WDTPW | WDTHOLD;

	init_clocks();
	init_enable_pins();
	init_channel_select_pins();
	init_soft_uart(); //2400-8-N-1, raw input (and no "\r\n"): '0' - '9'
	init_timer();
	init_gpio();

	uart_cmd = 0;
	uart_rx_byte_arrived = 0;
}

void enable_chip(uint8_t chip_num){
	switch(chip_num){
	case 1:
		ICs_EN_OUTREG |= (IC2_EN | IC3_EN);
		ICs_EN_OUTREG &= ~IC1_EN;
		break;
	case 2:
		ICs_EN_OUTREG |= (IC1_EN | IC3_EN);
		ICs_EN_OUTREG &= ~IC2_EN;
		break;
	case 3:
		ICs_EN_OUTREG |= (IC1_EN | IC2_EN);
		ICs_EN_OUTREG &= ~IC3_EN;
		break;
	}
}

void set_channel(uint8_t chan_num){
	switch(chan_num){
	case 0:
		CHAN_SEL_OUTREG &= ~(CHAN_SEL_0 | CHAN_SEL_1);
		break;
	case 1:
		CHAN_SEL_OUTREG |= CHAN_SEL_0;
		CHAN_SEL_OUTREG &= ~CHAN_SEL_1;
		break;
	case 2:
		CHAN_SEL_OUTREG &= ~CHAN_SEL_0;
		CHAN_SEL_OUTREG |= CHAN_SEL_1;
		break;
	case 3:
		CHAN_SEL_OUTREG |= (CHAN_SEL_0 | CHAN_SEL_1);
		break;
	}
}

uint8_t soft_uart_read_rx(uint8_t bit_position){
	return (((SOFT_UART_INREG & SOFT_UART_MCU_RX_PIN) >> 6) <<bit_position);
}

void soft_uart_write_tx(uint8_t byte){
	uint8_t i;

	//Start bit
	SOFT_UART_OUTREG &= ~SOFT_UART_MCU_TX_PIN;
	timer_delay(13);
	
	//8 data bits
	for(i = 0; i < 8; i++){
		//LSB first
		if((byte >> i) & 0x01){
			SOFT_UART_OUTREG |= SOFT_UART_MCU_TX_PIN;
		} 
		else{
			SOFT_UART_OUTREG &= ~SOFT_UART_MCU_TX_PIN;
		}
		timer_delay(12);		
	}

	SOFT_UART_OUTREG |= SOFT_UART_MCU_TX_PIN;
	timer_delay(12);	
}

void display_msg(void){
	char *start_up_msg = "SWD";

	while(*start_up_msg){
		soft_uart_write_tx(*start_up_msg++);
		timer_delay(100);
	}
}

int main(void){	
	init();

	display_msg();

	__enable_interrupt();

	while(1){ }
}
