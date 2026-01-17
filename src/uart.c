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
/*			              PRIVATE FUNCTIONS                                                         */
/****************************************************************************************************/
static UART_Status_State configPeripheralClock(UART_DEVICE_State uart);
static UART_Status_State configGPIO(const UART_PinConfig_Typedef* pin_config);
static USART_TypeDef* getUSART(UART_DEVICE_State uart);
static int getUSART_IRQn(UART_DEVICE_State uart);

static uint8_t UART_INTERNAL_RXBUF[UART_RXBUF_SIZE];
static RING_BUF_Typedef ringbuf;
static volatile uint8_t rx_read_it = false;
static UART_DEVICE_State rx_usart_it;

/*
* Configures the peripheral clock for the selected UART device.
* Note: USART1 is on the APB2 bus and USART2, USART3, UART4, UART5 are on the APB1 bus.
*/
static UART_Status_State configPeripheralClock(const UART_DEVICE_State uart) {
    switch (uart) {
        case UART_USART1:
            RCC_CLK_EN_USART1();
            break;
        case UART_USART2:
            RCC_CLK_EN_USART2();
            break;
        case UART_USART3:
            RCC_CLK_EN_USART3();
            break;
        case UART_UART4:
            RCC_CLK_EN_UART4();
            break;
        case UART_UART5:
            RCC_CLK_EN_UART5();
            break;
        default:
            return UART_INVALID_ARGS;
    }
	return UART_OK;
}

/*
* Configures the GPIO to the correct AF state for the selected UART device.
*/
static UART_Status_State configGPIO(const UART_PinConfig_Typedef* pin_config) {
	
	const GPIO_Port rx_port = pin_config->rx_port;
	const GPIO_Port rx_pin = pin_config->rx_pin;
	const GPIO_Port tx_port = pin_config->tx_port;
	const GPIO_Port tx_pin = pin_config->tx_pin;
	
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
static USART_TypeDef* getUSART(const UART_DEVICE_State uart) {
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
    return NULL;
}


/*
* Get the USART_IRQn corresponding to the UART that we want.
*/
static int getUSART_IRQn(const UART_DEVICE_State uart) {
	switch(uart) {
		case UART_USART1:
			return USART1_IRQn;
		case UART_USART2:
			return USART2_IRQn;
		case UART_USART3:
			return USART3_IRQn;
		case UART_UART4:
			return UART4_IRQn;
		case UART_UART5:
			return UART5_IRQn;
	}
    return 0;
}

/****************************************************************************************************/
/*			              EXPORTED FUNCTIONS                                            */
/****************************************************************************************************/

UART_Status_State UART_config(const UART_Config_Typedef* uart_conf) {
	const UART_DEVICE_State uart = uart_conf->uart;
	const uint32_t baud_rate = uart_conf->baud_rate;
	const UART_DATABITS_State databits = uart_conf->databits;
	const UART_PARITY_State parity = uart_conf->parity;
	const UART_STOPBITS_State stopbits = uart_conf->stopbits;

#ifdef UART_CHECK_ARGS
    /* check args */
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
#endif /* UART_CHECK_ARGS */

	/* enable peripheral clock */
    configPeripheralClock(uart_conf->uart);
	
	/* setup GPIO pins */
	if (configGPIO(uart_conf->pin_config) != UART_OK)
		return UART_INVALID_ARGS;
	
	/* setup other UART params */
	USART_TypeDef* UARTx = getUSART(uart);
    if (UARTx == NULL) {
        return UART_INVALID_ARGS;
    }

    /* disable the UART: set UE bit to 0 */
    CLEAR_BIT(UARTx->CR1, USART_CR1_UE_Msk);
	
	/* baud rate (UARTx->BRR register) */
	const uint16_t brrDivisor = CLOCK_getSystemClockSpeed() / baud_rate; // assumes that the clocks fed to USART are the same speed as the sys clk
	UARTx->BRR = brrDivisor;
	
	/* data bits (UARTx->CR1 register) */
	if (databits == UART_DATABITS_7) {
		/* M[1:0] = '10' */
	    SET_BIT(UARTx->CR1, USART_CR1_M1_Msk);
	    CLEAR_BIT(UARTx->CR1, USART_CR1_M0_Msk);
	} else if (databits == UART_DATABITS_8) {
		/* M[1:0] = '00' */
	    CLEAR_BIT(UARTx->CR1, USART_CR1_M1_Msk);
	    CLEAR_BIT(UARTx->CR1, USART_CR1_M0_Msk);
	} else {
		/* M[1:0] == '01' */
	    CLEAR_BIT(UARTx->CR1, USART_CR1_M1_Msk);
	    SET_BIT(UARTx->CR1, USART_CR1_M0_Msk);
	}
	
	/* parity bit selection (UARTx->CR1 register) */
	if (parity == UART_PARITY_NONE) {
	    CLEAR_BIT(UARTx->CR1, USART_CR1_PCE_Msk);
	} else {
	    SET_BIT(UARTx->CR1, USART_CR1_PCE_Msk); // enable PCE bit
	    SET_BIT(UARTx->CR1, USART_CR1_PS_Msk);  // set PS bit
	}
	
	/* stop bits (UARTx->CR2 register) */
    MODIFY_REG(UARTx->CR2, USART_CR2_STOP_Msk, stopbits << USART_CR2_STOP_Pos);

	/* configure interrupt if necessary */
	if (uart_conf->it_config->RXNEIE_enabled || uart_conf->it_config->TXEIE_enabled || uart_conf->it_config->IDLEIE_enabled) {
		int UARTx_IRQn = getUSART_IRQn(uart);
		
		/* set priority */
		NVIC_SetPriorityGrouping(0);
		uint32_t uart_pri_encoding = NVIC_EncodePriority( 0, uart_conf->it_config->priority, 0 );
		NVIC_SetPriority(UARTx_IRQn, uart_pri_encoding);
		
		/* enable interrupts with NVIC */
		__disable_irq();
		NVIC_EnableIRQ(UARTx_IRQn);
		__enable_irq();
		
		/* enable requested interrupts */
		if (uart_conf->it_config->RXNEIE_enabled) {
		    SET_BIT(UARTx->CR1, USART_CR1_RXNEIE_RXFNEIE_Msk);
		}

		if (uart_conf->it_config->TXEIE_enabled) {
		    SET_BIT(UARTx->CR1, USART_CR1_TXEIE_TXFNFIE_Msk);
		}

		if (uart_conf->it_config->IDLEIE_enabled) {
		    SET_BIT(UARTx->CR1, USART_CR1_IDLEIE_Msk);
		}

		/* setup ring buffer */
		ringbuf = RING_BUF_init(UART_INTERNAL_RXBUF, UART_RXBUF_SIZE);
	}

	/* enable USART and transmit enable (TE) and receive enable (RE) (UARTx->CR1 register) */
    SET_BIT(UARTx->CR1, USART_CR1_UE_Msk);
    SET_BIT(UARTx->CR1, USART_CR1_RE_Msk);
    SET_BIT(UARTx->CR1, USART_CR1_TE_Msk);

	return UART_OK;
}


UART_Status_State UART_transmit(const UART_DEVICE_State uart, const uint8_t* tx_buf, const uint16_t length) {

#ifdef UART_CHECK_ARGS
    /* check args */
	if (!(uart == 14 || (uart <= 20 && uart >= 17)))
		return UART_INVALID_ARGS;
#endif /* UART_CHECK_ARGS */
	
	USART_TypeDef* UARTx = getUSART(uart);

    if (UARTx == NULL) {
        return UART_INVALID_ARGS;
    }
	
	/* check if UART is currently busy and return error in case */
	if (UARTx->ISR & USART_ISR_BUSY) return UART_BUSY;
	
	for (int i = 0; i<length; i++) {
		const uint8_t currentByte = tx_buf[i];
		/* wait until the TXE/TXFNF bit is 1, indicating that TDR is empty */
		while(!(UARTx->ISR & USART_ISR_TXE_TXFNF)) {}
		UARTx->TDR = currentByte;
	}
	return UART_OK;
}


UART_Status_State UART_receiveIT_Start(const UART_DEVICE_State uart) {
	rx_read_it = true;
	rx_usart_it = uart;
	return UART_OK;
}


UART_Status_State UART_receiveIT_Stop() {
	rx_read_it = false;
	return UART_OK;
}


uint8_t UART_receiveByte(const UART_DEVICE_State uart) {
#ifdef UART_CHECK_ARGS
	/* check args */
	if (!(uart == 14 || (uart <= 20 && uart >= 17)))
		return UART_INVALID_ARGS;
#endif /* UART_CHECK_ARGS */
	
	USART_TypeDef* UARTx = getUSART(uart);
	return UARTx->RDR;
}

uint8_t UART_hasData(const UART_DEVICE_State uart) {
#ifdef UART_CHECK_ARGS
	/* check args */
	if (!(uart == 14 || (uart <= 20 && uart >= 17)))
		return UART_INVALID_ARGS;
#endif /* UART_CHECK_ARGS */
	const USART_TypeDef* UARTx = getUSART(uart);

    if (UARTx == NULL) {
        return UART_INVALID_ARGS;
    }

	/* return the RXNE/RXFNE bit in the UARTx->ISR register */
	return UARTx->ISR & USART_ISR_RXNE_RXFNE;
}

uint8_t UART_isIdle(UART_DEVICE_State uart) {
	/* check args */
	if (!(uart == 14 || (uart <= 20 && uart >= 17)))
		return UART_INVALID_ARGS;

	const USART_TypeDef* UARTx = getUSART(uart);

    if (UARTx == NULL) {
        return UART_INVALID_ARGS;
    }

	/* return the IDLE bit in the UARTx->ISR register */
	return UARTx->ISR & USART_ISR_IDLE;
}

UART_Status_State UART_read(uint8_t* rx_buf, uint32_t length) {
	/* check args */
	if (length >= UART_RXBUF_SIZE) return UART_INVALID_ARGS;
	
	for (uint32_t i = 0; i<length; i++) {
		if (RING_BUF_readByteFromTail(&ringbuf, &rx_buf[i]) != RING_BUF_OK) {
			return UART_BUFFER_EMPTY;
		}
	}

	return UART_OK;
}

#ifdef UART_USING_INTERNAL_IT
void USART1_IRQHandler(void) {
	if (rx_read_it && UART_hasData(rx_usart_it)) {
		RING_BUF_writeByteToHead(&ringbuf, UART_receiveByte(rx_usart_it));
	}
}

void USART2_IRQHandler(void) {
	if (rx_read_it && UART_hasData(rx_usart_it)) {
		RING_BUF_writeByteToHead(&ringbuf, UART_receiveByte(rx_usart_it));
	}
}

void USART3_IRQHandler(void) {
	if (rx_read_it && UART_hasData(rx_usart_it)) {
		RING_BUF_writeByteToHead(&ringbuf, UART_receiveByte(rx_usart_it));
	}
}

void UART4_IRQHandler(void) {
	if (rx_read_it && UART_hasData(rx_usart_it)) {
		RING_BUF_writeByteToHead(&ringbuf, UART_receiveByte(rx_usart_it));
	}
}

void UART5_IRQHandler(void) {
	if (rx_read_it && UART_hasData(rx_usart_it)) {
		RING_BUF_writeByteToHead(&ringbuf, UART_receiveByte(rx_usart_it));
	}
}
#endif