#include "common.h"
#include "uart.h"
#include "string.h"


#ifdef UART_PRINTF
/*
DESCRIPTION: Configure an USART peripheral to print some text!
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
static void print(const char* message);

/* flag to show that we have received something */
volatile uint8_t rxReceivedFlag = false;

/*
* Configure the UART peripheral with its usual settings: 
*		- 115200 baud rate
*		- 8 bit data
*		- no parity
*		- one stop bit
*		- no flow control
*/
static void configUART() {
	/* Interrupts */
	UART_ITConfig_Typedef it_conf = {
		.is_enabled = true,
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
	
	/* printing using UART! */
	print("Hello World \r\n");
	
	while(1) {
		/* Infinite loop so that we don't exit main */
		if (rxReceivedFlag) {
			print("Received a bit \r\n");
			rxReceivedFlag = false;
		}
	}	
}


void USART1_IRQHandler(void) {
	if (UART_hasData(UART_USART1)) {
		/* Important: Until all the bytes have been received, the USART cannot send data */
		uint8_t rxb = UART_receiveByte(UART_USART1);
		rxReceivedFlag = true;
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