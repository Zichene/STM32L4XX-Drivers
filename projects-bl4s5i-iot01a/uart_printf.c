#include "common.h"
#include "gpio.h"
#include "clock.h"
#include "tim.h"
#include "uart.h"

#ifdef UART_PRINTF
/*
DESCRIPTION: Configure an USART peripheral to print some text!
BOARD USED: B-L4S5I-IOT01A board
INTERNAL CONNECTIONS: The virtual COM port for this board is connected to USART1. PA10->USART1_RX, PA9 -> USART1_TX
REFERENCES: ST MB1297 (Internal Board Connections), ST UM2708 (User Manual),  STM32L4S5xx, STM32L4S7xx and STM32L4S9xx Datasheet.
AUTHOR: Zichene
DATE: 8/20/2024
*/


/* On the board used for this example, LED2 (green) is connected to Pin B14 (Port B, Pin 14) */
#define LED2_Port GPIO_PORT_B
#define LED2_Pin 14

/* USART1_RX -> PA9 */
#define USART1_RX_Port GPIO_PORT_A
#define USART1_RX_Pin 9

/* USART1_TX -> PA10 */
#define USART1_TX_Port GPIO_PORT_A
#define USART1_TX_Pin 10

/* The AF (Alternate Function) modes for USART1 */
#define USART1_RX_AF GPIO_AF_7
#define USART1_TX_AF GPIO_AF_7

static void ErrorHandler();
static void configUART();

/*
* Configure the UART peripheral with its usual settings: 
*		- 115200 baud rate
*		- 8 bit data
*		- no parity
*		- one stop bit
*		- no flow control
*/
static void configUART() {
	
	/* Setup pin configuration as defined above (internal connections) */
	UART_PinConfig_Typedef pin_conf = {
		.rx_port = USART1_RX_Port,
		.rx_pin = USART1_RX_Pin,
		.tx_port = USART1_TX_Port,
		.tx_pin = USART1_TX_Pin,
	};

	/* Setup the UART configuration */
	UART_Config_Typedef uart_conf = {
		.uart = UART_USART1,
		.pin_config = &pin_conf,
		.baud_rate = 115200,
		.databits = UART_DATABITS_8,
		.parity = UART_PARITY_NONE,
		.stopbits = UART_STOPBITS_1,
	};
	
	UART_config(&uart_conf);
}

int main(void)
{
	configUART();

	while (1) {
		/* Infinite loop so that we don't exit main */
	}
	
}


void ErrorHandler() {
	while(1) {
	/* If you've ended up here, then a problem has occured! */
	}
}
#endif