#include "common.h"
#include "uart.h"
#include "string.h"
#include "ringbuffer.h"

#ifdef UART_RECEIVE
/*
DESCRIPTION: Configure an USART peripheral to receive input!
BOARD USED: B-L4S5I-IOT01A board
INTERNAL CONNECTIONS: The ST-Link virtual COM port for this board is connected to USART1. PB7->USART1_RX, PB6 -> USART1_TX
REFERENCES: ST MB1297 (Internal Board Connections), ST UM2708 (User Manual),  STM32L4S5xx, STM32L4S7xx and STM32L4S9xx Datasheet.
AUTHOR: Zichene
DATE: 8/20/2024
*/


/* On the board used for this example, LED2 (green) is connected to Pin B14 (Port B, Pin 14) */
#define LED2_Port GPIO_PORT_B
#define LED2_Pin 14

/* LED3 (WiFi and Bluetooth) used as error indicator is connected to Pin C9 (Port C, Pin 9) */
#define LEDError_Port GPIO_PORT_C
#define LEDError_Pin 9


/* 
The following USART1 internal connections are found in MB1297 
*/

/* USART1_TX -> PB6 */
#define USART1_TX_Port GPIO_PORT_B
#define USART1_TX_Pin 6

/* USART1_RX -> PB7 */
#define USART1_RX_Port GPIO_PORT_B
#define USART1_RX_Pin 7

/* The AF (Alternate Function) modes for USART1 */
#define USART1_RX_AF GPIO_AF_7
#define USART1_TX_AF GPIO_AF_7

static void ErrorHandler();
static void configUART();
static void configureSystemClock120MHz();


/* global variables */
uint32_t RX_BUF_SIZE = 1000;
volatile uint8_t usartIsIdle = true;

/*
* Configure the UART peripheral with its usual settings: 
*		- 115200 baud rate
*		- 8 bit data
*		- no parity
*		- one stop bit
*		- no flow control
*
* Here we will disable interrupt.
*/
static void configUART() {
	/* Interrupts */
	UART_ITConfig_Typedef it_conf = {
		.RXNEIE_enabled = true,
		.priority = 1,
	};
	
	/* Setup pin configuration as defined above (internal connections) */
	UART_PinConfig_Typedef pin_conf = {
		.rx_port = USART1_RX_Port,
		.rx_pin = USART1_RX_Pin,
		.tx_port = USART1_TX_Port,
		.tx_pin = USART1_TX_Pin,
		.rx_pin_af = USART1_RX_AF,
		.tx_pin_af = USART1_TX_AF,
	};

	/* Setup the UART configuration */
	UART_Config_Typedef uart_conf = {
		.uart = UART_USART1,
		.pin_config = &pin_conf,
		.it_config = &it_conf,
		.baud_rate = 115200,
		.databits = UART_DATABITS_8,
		.parity = UART_PARITY_NONE,
		.stopbits = UART_STOPBITS_1,
	};
	
	if (UART_config(&uart_conf) != UART_OK)
		ErrorHandler();
	
	/* Enable the internal rx buffer to be filled by interrupt */
	UART_receiveIT_Start(uart_conf.uart);
	UART_receiveIT_Stop();
	UART_receiveIT_Start(uart_conf.uart);
}


/* 
* Configure the system clock to its maximum speed (120 MHz).
*
*  We will be using the PLL clock as the system clock. In order to use this clock, we need to choose one of four clock sources for the PLL.
*  The source clock for the PLL will be the MSI (Multi Speed Internal) clock, which has a default speed of 4 MHz. 
*  The speed of the MSI is modified by PLL_M, PLL_N and PLL_R, which are positive integers. The modification is as follows:
*
*  			output = input * PLL_N / (PLL_M * PLL_R)
*
*   MSI (default 4 MHz) -> divided by PLL_M = 1 -> multiplied by PLL_N = 60 -> divided by PLL_R = 2 -> 120 MHz
*
*/
static void configureSystemClock120MHz() {

	/* Configure PLL with required parameters (PLL_M, PLL_N and PLL_R) */
	CLOCK_configPLL(CLOCK_PLL_SRC_MSI, 1, 60, CLOCK_PLLR_2);
	
	/* Activate and set the PLLCLK as the system clock */
	CLOCK_activateClk(CLOCK_PLL);
	CLOCK_setSystemClock(CLOCK_SYSCLK_PLL); 
	
	/* Check that the system clock is indeed 120 MHz */
	if (CLOCK_getSystemClockSpeed() != 120000000)
		ErrorHandler();
	
	/* Make sure that bus prescalers are set to 1. These prescalers control the speed of the clock that is passed to the timers and other peripherals. */
	CLOCK_setAHBPrescaler(CLOCK_AHB_PRE_DIV_1);
	CLOCK_setAPB1Prescaler(CLOCK_APB1_PRE_DIV_1);
	CLOCK_setAPB2Prescaler(CLOCK_APB2_PRE_DIV_1);
}

/*
* Use the UART_transmit() function and the string.h library to print a message!
*/
static void print(const char* message) {
	UART_transmit(UART_USART1, (uint8_t*) message, strlen(message));
}

int main(void)
{
	/* configure clock and uart */
	configureSystemClock120MHz();
	configUART();
	
	/* rx buffer */
	uint8_t rxBuf[10];
	uint8_t txBuf[10];
	RING_BUF_Typedef ringBuffer = RING_BUF_init(rxBuf, 10);
	for (int i = 0; i < 11; i++) {
		if (RING_BUF_writeByteToHead(&ringBuffer, i) == RING_BUF_WRITE_ERROR) {
			print("Buffer has overflowed! \r\n");
			break;
		}
	}
	
	for (int j = 0; j < 5; j++) {
		if (RING_BUF_readByteFromTail(&ringBuffer, txBuf+j) == RING_BUF_READ_ERROR) {
			print("Buffer is empty! \r\n");
			break;
		}
	}
	
	for (int i = 0; i < 11; i++) {
		if (RING_BUF_writeByteToHead(&ringBuffer, 'a'+ i) == RING_BUF_WRITE_ERROR) {
			print("Buffer has overflowed! \r\n");
			break;
		}
	}
	
	for (int j = 0; j < 11; j++) {
		if (RING_BUF_readByteFromTail(&ringBuffer, txBuf+j) == RING_BUF_READ_ERROR) {
			print("Buffer is empty! \r\n");
			break;
		}
	}

	
	/* printing using UART! */
	print("Hello World \r\n");
	
	while(1) {
	/* Infinite loop so that we don't exit main */
		if (UART_isIdle(UART_USART1)) {
			/* Reading one byte at a time and retransmitting to UART */
			if (UART_read(rxBuf, 1) == UART_OK)
				UART_transmit(UART_USART1, rxBuf, 1);
		}
	}	
}


void ErrorHandler() {
	/* Light up the yellow LED on board */
	GPIO_setPinOutput(LEDError_Port, LEDError_Pin);
	GPIO_togglePin(LEDError_Port, LEDError_Pin);
	while(1) {
	/* If you've ended up here, then a problem has occured! */
	}
}

#endif