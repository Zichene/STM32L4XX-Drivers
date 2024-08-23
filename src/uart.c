#include "uart.h"

/***
*
* UART/USART drivers for stm32l4xx devices.
* WARNING: These drivers have NOT been tested extensively. Use at own risk.
* Reference: https://www.youtube.com/playlist?list=PLtVUYRe-Z-mfKO0lg_-MBvwWl6VjWT8Dt
* STM32 Reference Manual: RM0432
*
* FOR DETAILED DOCUMENTATION OF THIS FILE, SEE CORRESPONDING .h SOURCE CODE OR GENERATE DOCS WITH DOXYGEN.
*
***/

/****************************************************************************************************/
/*			              PRIVATE FUNCTIONS                                             */
/****************************************************************************************************/
static UART_Status_State configPeripheralClock(UART_Enable_State uart);
static UART_Status_State configGPIO(UART_PinConfig_Typedef* pin_config);

/*
* Configures the peripheral clock for the selected UART device.
* Note: USART1 is on the APB2 bus and USART2, USART3, UART4, UART5 are on the APB1 bus.
*/
static UART_Status_State configPeripheralClock(UART_Enable_State uart) {
	if (uart >= 17) {
		/* devices on the APB1 bus */
		RCC->APB1ENR1 |= (0b1 << uart);
	} else {
		/*  for USART1 */
		RCC->APB2ENR |= (0b1 << uart);
	}
	return UART_OK;
}

/*
* Configures the GPIO to the correct AF state for the selected UART device.
*/
static UART_Status_State configGPIO(UART_PinConfig_Typedef* pin_config) {
	
	GPIO_Port rx_port = pin_config->rx_port;
	GPIO_Port rx_pin = pin_config->rx_pin;
	GPIO_Port tx_port = pin_config->tx_port;
	GPIO_Port tx_pin = pin_config->tx_pin;
	
	/* setup RX pin to the correct AF state */
	if (GPIO_setPinAF_Mode(rx_port, rx_pin, GPIO_PUPD_NO_PULL_UP_PULL_DOWN, GPIO_SPEED_VERY_HIGH, GPIO_OUTPUT_PUSH_PULL) != GPIO_OK)
		return UART_INVALID_ARGS;
	if (GPIO_setPinAF_State(rx_port, rx_pin, pin_config->rx_pin_af) != GPIO_OK)
		return UART_INVALID_ARGS;
	
	/* setup TX pin to the correct AF state */
	if (GPIO_setPinAF_Mode(tx_port, tx_pin, GPIO_PUPD_NO_PULL_UP_PULL_DOWN, GPIO_SPEED_VERY_HIGH, GPIO_OUTPUT_PUSH_PULL) != GPIO_OK)
		return UART_INVALID_ARGS;
	if (GPIO_setPinAF_State(tx_port, tx_pin, pin_config->tx_pin_af) != GPIO_OK)
		return UART_INVALID_ARGS;
	
	return UART_OK;
}

/*
* Get the USART_Typedef pointer corresponding to the UART that we want.
*/
static USART_TypeDef* getUSART(UART_Enable_State uart) {
	switch(uart) {
		case UART_USART1:
			return USART1;
		case UART_USART2:
			return USART2;
		case UART_USART3:
			return USART3;
		case UART_UART4:
			return UART4;
		case UART_UART5:
			return UART5;
	}
}
/****************************************************************************************************/
/*			              EXPORTED FUNCTIONS                                            */
/****************************************************************************************************/

UART_Status_State UART_config(UART_Config_Typedef* uart_conf) {
	/* check args */
	UART_Enable_State uart = uart_conf->uart;
	uint32_t baud_rate = uart_conf->baud_rate;
	UART_DATABITS_State databits = uart_conf->databits;
	UART_PARITY_State parity = uart_conf->parity;
	UART_STOPBITS_State stopbits = uart_conf->stopbits;
	
	if (!(uart == 14 || (uart <= 20 && uart >= 17)))
		return UART_INVALID_ARGS;
	if(!(baud_rate <= UART_MAX_BAUDRATE))
		return UART_INVALID_ARGS;
	if(!(databits <= 2 && databits >= 0))
		return UART_INVALID_ARGS;
	if(!(parity <= 2 && parity >= 0))
		return UART_INVALID_ARGS;
	if(!(stopbits <= 3 && stopbits >= 0))
		return UART_INVALID_ARGS;
	
	
	/* enable peripheral clock */
	if (configPeripheralClock(uart_conf->uart) != UART_OK)
		return UART_INVALID_ARGS;
	
	/* setup GPIO pins */
	if (configGPIO(uart_conf->pin_config) != UART_OK)
		return UART_INVALID_ARGS;
	
	/* setup other UART params */
	USART_TypeDef* UARTx = getUSART(uart);
	UARTx->CR1 &= ~(0b1); // make sure the UART is disabled
	
	/* baud rate (UARTx->BRR register) */
	uint16_t brrDivisor = CLOCK_getSystemClockSpeed() / uart_conf->baud_rate; // assumes that the clocks fed to USART are the same speed as the sys clk 
	UARTx->BRR = brrDivisor;
	
	/* data bits (UARTx->CR1 register) */
	if (databits == UART_DATABITS_7) {
		/* M[1:0] = '10' */
		UARTx->CR1 |= (0b1 << 28);
		UARTx->CR1 &= ~(0b1 << 12);
	} else if (databits == UART_DATABITS_8) {
		/* M[1:0] = '00' */
		UARTx->CR1 &= ~(0b1 << 28);
		UARTx->CR1 &= ~(0b1 << 12);
	} else {
		/* M[0:1] == '01' */
		UARTx->CR1 &= ~(0b1 << 28);
		UARTx->CR1 |= (0b1 << 12);
	}
	
	/* parity bit selection (UARTx->CR1 register) */
	if (parity == UART_PARITY_NONE) {
		UARTx->CR1 &= ~(0b1 << 10); // disable PCE bit
	} else {
		UARTx->CR1 |= (0b1 << 10); // enable PCE bit
		UARTx->CR1 |= (parity << 9); // set PS bit
	}
	
	/* stop bits (UARTx->CR2 register) */
	UARTx->CR2 &= ~(0b11 << 12);
	UARTx->CR2 |= (stopbits << 12);
	
	/* enable USART and transmit enable (TE) and receive enable (RE) (UARTx->CR1 register) */
	UARTx->CR1 |= (0b1); // UE bit
	UARTx->CR1 |= (0b1 << 2); // RE bit
	UARTx->CR1 |= (0b1 << 3); // TE bit
	
	return UART_OK;
}
