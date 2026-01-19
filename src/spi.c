#include "spi.h"

/***
*
* SPI drivers for stm32l4xx devices.
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
static SPI_Status_State configPeripheralClock(SPI_Device spi);
static SPI_Status_State configGPIO(const SPI_PinConfig_Typedef* pin_config);
static SPI_TypeDef* getSPI(SPI_Device spi);
static int getSPI_IRQn(SPI_Device spi);

static uint8_t SPI_INTERNAL_RXBUF[SPI_RXBUF_SIZE];
static RING_BUF_Typedef ringbuf;
static volatile uint8_t rx_read_it = false;
static SPI_Device rx_spi_it;

/*
* Configures the peripheral clock for the selected SPI device.
*/
static SPI_Status_State configPeripheralClock(const SPI_Device spi) {
    switch (spi) {
        case SPI_SPI1:
            RCC_CLK_EN_SPI1();
            break;
        case SPI_SPI2:
            RCC_CLK_EN_SPI2();
            break;
        case SPI_SPI3:
            RCC_CLK_EN_SPI3();
            break;
    }
    return SPI_OK;
}

/*
* Configures the GPIO to the correct AF state for the selected SPI device.
*/
static SPI_Status_State configGPIO(const SPI_PinConfig_Typedef* pin_config) {
	
	const GPIO_Port sclk_port = pin_config->sclk_port;
	const GPIO_Port sclk_pin = pin_config->sclk_pin;
	const GPIO_Port miso_port = pin_config->miso_port;
	const GPIO_Port miso_pin = pin_config->miso_pin;
	const GPIO_Port mosi_port = pin_config->mosi_port;
	const GPIO_Port mosi_pin = pin_config->mosi_pin;
	const GPIO_Port ssel_port = pin_config->ssel_port;
	const GPIO_Port ssel_pin = pin_config->ssel_pin;

	/* setup sclk pin to the correct AF state */
    if (pin_config->sclk_apply) {
        if (GPIO_setPinAF_Mode(sclk_port, sclk_pin, GPIO_PUPD_NO_PULL_UP_PULL_DOWN, GPIO_SPEED_VERY_HIGH, GPIO_OUTPUT_PUSH_PULL) != GPIO_OK)
		    return SPI_INVALID_ARGS;
	    if (GPIO_setPinAF_State(sclk_port, sclk_pin, pin_config->sclk_pin_af) != GPIO_OK)
		    return SPI_INVALID_ARGS;
    }

	/* setup miso pin to the correct AF state */
    if (pin_config->miso_apply) {
        if (GPIO_setPinAF_Mode(miso_port, miso_pin, GPIO_PUPD_NO_PULL_UP_PULL_DOWN, GPIO_SPEED_VERY_HIGH, GPIO_OUTPUT_PUSH_PULL) != GPIO_OK)
		    return SPI_INVALID_ARGS;
	    if (GPIO_setPinAF_State(miso_port, miso_pin, pin_config->miso_pin_af) != GPIO_OK)
		    return SPI_INVALID_ARGS;
    }

    /* setup mosi pin to the correct AF state */
    if (pin_config->mosi_apply) {
	    if (GPIO_setPinAF_Mode(mosi_port, mosi_pin, GPIO_PUPD_NO_PULL_UP_PULL_DOWN, GPIO_SPEED_VERY_HIGH, GPIO_OUTPUT_PUSH_PULL) != GPIO_OK)
		    return SPI_INVALID_ARGS;
	    if (GPIO_setPinAF_State(mosi_port, mosi_pin, pin_config->mosi_pin_af) != GPIO_OK)
		    return SPI_INVALID_ARGS;
    }

    /* setup ssel pin to the correct AF state */
    if (pin_config->ssel_apply) {
        if (GPIO_setPinAF_Mode(ssel_port, ssel_pin, GPIO_PUPD_NO_PULL_UP_PULL_DOWN, GPIO_SPEED_VERY_HIGH, GPIO_OUTPUT_PUSH_PULL) != GPIO_OK)
		    return SPI_INVALID_ARGS;
	    if (GPIO_setPinAF_State(ssel_port, ssel_pin, pin_config->ssel_pin_af) != GPIO_OK)
		    return SPI_INVALID_ARGS;
    }
	return SPI_OK;
}

static SPI_TypeDef* getSPI(const SPI_Device spi) {
    switch (spi) {
        case SPI_SPI1:
            return SPI1;
        case SPI_SPI2:
            return SPI2;
        case SPI_SPI3:
            return SPI3;
    }
    return NULL;
}

/*
* Get the SPI_IRQn corresponding to the SPI that we want.
*/
static int getSPI_IRQn(const SPI_Device spi) {
    switch(spi) {
        case SPI_SPI1:
            return SPI1_IRQn;
        case SPI_SPI2:
            return SPI2_IRQn;
        case SPI_SPI3:
            return SPI3_IRQn;
    }
    return 0;
}

/****************************************************************************************************/
/*			              EXPORTED FUNCTIONS                                                        */
/****************************************************************************************************/

SPI_Status_State SPI_config(const SPI_Config_Typedef* spi_conf) {
	/* local variables */
	const SPI_Device spi = spi_conf->spi;
    SPI_TypeDef* SPIx = getSPI(spi_conf->spi);
    if (SPIx == NULL) {
        return SPI_INVALID_ARGS;
    }

    /* enable peripheral clock */
    configPeripheralClock(spi);

    /* make sure SPI is disabled during configuration */
    CLEAR_BIT(SPIx->CR1, SPI_CR1_SPE_Msk);

	/* setup GPIO pins */
	if (configGPIO(spi_conf->pin_config) != SPI_OK)
		return SPI_INVALID_ARGS;

    /* configure baud rate divider */
    MODIFY_REG(SPIx->CR1, SPI_CR1_BR_Msk, spi_conf->br_divider << SPI_CR1_BR_Pos);

    /* configure spi mode */
    MODIFY_REG(SPIx->CR1, SPI_CR1_CPOL_Msk | SPI_CR1_CPHA_Msk, spi_conf->mode << SPI_CR1_CPHA_Pos);

    /* configure half-duplex vs. full duplex */
    if (spi_conf->full_duplex) {
        SET_BIT(SPIx->CR1, SPI_CR1_BIDIMODE_Msk);
        SET_BIT(SPIx->CR1, SPI_CR1_BIDIOE_Msk);
    } else {
        CLEAR_BIT(SPIx->CR1, SPI_CR1_BIDIMODE_Msk);
        CLEAR_BIT(SPIx->CR1, SPI_CR1_BIDIOE_Msk);
    }

    /* configure lsb-first */
    spi_conf->lsb_first ? SET_BIT(SPIx->CR1, SPI_CR1_LSBFIRST_Msk) : CLEAR_BIT(SPIx->CR1, SPI_CR1_LSBFIRST_Msk);

    /* configure CRC if needed */
    if (spi_conf->crc_config->enabled) {
        SET_BIT(SPIx->CR1, SPI_CR1_CRCEN_Msk); // Enable CRC hardware
        /* set crc length to 16 if requested */
        spi_conf->crc_config->crc_length_16_bit ? SET_BIT(SPIx->CR1, SPI_CR1_CRCL_Msk) : CLEAR_BIT(SPIx->CR1, SPI_CR1_CRCL_Msk);
        /* set the CRC polynomial */
        WRITE_REG(SPIx->CRCPR, spi_conf->crc_config->crc_polynomial);
    }

    /* configure the NSS management */
    switch (spi_conf->nss_management) {
        case SPI_NSS_SOFTWARE:
            /* set SSM bit to 1, and SSI bit to 1 */
            SET_BIT(SPIx->CR1, SPI_CR1_SSM_Msk);
            SET_BIT(SPIx->CR1, SPI_CR1_SSI_Msk);
            break;
        case SPI_NSS_HARDWARE_OUTPUT_EN:
            /* set SSM bit to 0, and SSOE bit to 1 */
            CLEAR_BIT(SPIx->CR1, SPI_CR1_SSM_Msk);
            SET_BIT(SPIx->CR2, SPI_CR2_SSOE_Msk);
            break;
        case SPI_NSS_HARDWARE_OUTPUT_DISABLED:
            /* set SSM bit to 0, and SSOE bit to 0 */
            CLEAR_BIT(SPIx->CR1, SPI_CR1_SSM_Msk);
            CLEAR_BIT(SPIx->CR2, SPI_CR2_SSOE_Msk);
            break;
    }

    /* configure MSTR bit */
    spi_conf->master ? SET_BIT(SPIx->CR1, SPI_CR1_MSTR_Msk) : CLEAR_BIT(SPIx->CR1, SPI_CR1_MSTR_Msk);

    /* configure data length */
    MODIFY_REG(SPIx->CR2, SPI_CR2_DS_Msk, spi_conf->data_size << SPI_CR2_DS_Pos);

    /* configure NSS pulse management */
    spi_conf->nss_pulse_mode ? SET_BIT(SPIx->CR2, SPI_CR2_NSSP_Msk) : CLEAR_BIT(SPIx->CR2, SPI_CR2_NSSP_Msk);

    /* configure FIFO threshold */
    spi_conf->fifo_threshold_8_bit ? SET_BIT(SPIx->CR2, SPI_CR2_FRXTH_Msk) : CLEAR_BIT(SPIx->CR2, SPI_CR2_FRXTH_Msk);

    /* configure interrupt if necessary */
    if (spi_conf->it_config->RXNEIE_enabled || spi_conf->it_config->TXEIE_enabled || spi_conf->it_config->ERRIE_enabled) {
        int SPIx_IRQn = getSPI_IRQn(spi_conf->spi);

        /* set priority */
        NVIC_SetPriorityGrouping(0);
        uint32_t spi_pri_encoding = NVIC_EncodePriority( 0, spi_conf->it_config->priority, 0 );
        NVIC_SetPriority(SPIx_IRQn, spi_pri_encoding);

        /* enable interrupts with NVIC */
        __disable_irq();
        NVIC_EnableIRQ(SPIx_IRQn);
        __enable_irq();

        /* enable requested interrupts */
        if (spi_conf->it_config->RXNEIE_enabled) {
            SET_BIT(SPIx->CR2, SPI_CR2_RXNEIE_Msk);
        }

        if (spi_conf->it_config->TXEIE_enabled) {
            SET_BIT(SPIx->CR2, SPI_CR2_TXEIE_Msk);
        }

        if (spi_conf->it_config->ERRIE_enabled) {
            SET_BIT(SPIx->CR2, SPI_CR2_ERRIE_Msk);
        }

        /* setup ring buffer */
        ringbuf = RING_BUF_init(SPI_INTERNAL_RXBUF, SPI_RXBUF_SIZE);
    }

    /* enable the SPI device */
    SET_BIT(SPIx->CR1, SPI_CR1_SPE_Msk);
	
	return SPI_OK;
}


SPI_Status_State SPI_receive(const SPI_Device spi, uint16_t *data) {
    *data = 0;
    SPI_Status_State status = SPI_OK;
    const SPI_TypeDef* SPIx = getSPI(spi);
    if (SPIx == NULL) {
        return SPI_INVALID_ARGS;
    }
    /* Check if RXNE event exists */
    if (READ_BIT(SPIx->SR, SPI_SR_RXNE_Msk)) {
        *data = SPIx->DR;
        status = SPI_OK;
    } else {
        status = SPI_ERROR_READ_EMPTY_BUFFER;
    }
    return status;
}

SPI_Status_State SPI_transmit(const SPI_Device spi, const uint16_t data) {
    SPI_Status_State status = SPI_OK;
    SPI_TypeDef* SPIx = getSPI(spi);
    if (SPIx == NULL) {
        return SPI_INVALID_ARGS;
    }
    /* Check if TXNE event exists */
    if (READ_BIT(SPIx->SR, SPI_SR_TXE_Msk)) {
        SPIx->DR = data;
        status = SPI_OK;
    } else {
        status = SPI_ERROR_WRITE_NON_EMPTY_BUFFER;
    }
    return status;
}

SPI_Status_State SPI_transmitReceive(const SPI_Device spi, const uint8_t rw, uint8_t *data, const uint16_t size) {
    const SPI_TypeDef* SPIx = getSPI(spi);
    SPI_Status_State status = SPI_OK;
    uint32_t numBytes = 0;

    if (SPIx == NULL) {
        return SPI_INVALID_ARGS;
    }

    /* We are reading. Assume we need to transmit dummy data */
    if (rw == true) {
        /* Blocking until we read the correct number of bytes. TODO: This is dangerous, we should add a timeout here. */
        // Dummy transmit to initiate next clock cycle.
        status = SPI_transmit(SPI_SPI3, 0xFFFF);
        if (status != SPI_OK) {
            return status;
        }
        while (numBytes < size) {
            const SPI_Status_State result = SPI_read(data + numBytes, 2);
            if (result == SPI_OK) {
                numBytes += 2;
                /* Break out of while early if we reached size */
                if (numBytes == size) {
                    break;
                }
                // Dummy transmit to initiate next clock cycle.
                status = SPI_transmit(SPI_SPI3, 0xFFFF);
                if (status != SPI_OK) {
                    return status;
                }
            }
        }
    } else {
        /* We are writing */
        while (numBytes < size) {
            /* Send data */
            const SPI_Status_State result = SPI_transmit(spi, *(uint16_t*)(data + numBytes));
            if (result == SPI_OK) {
                numBytes += 2;
            }
        }
    }
    const uint32_t ring_buf_size = RING_BUF_size(&ringbuf);
    if (ring_buf_size != 0) {
        // Need to clear the ring buffer for data that was unread.
        RING_BUF_clear(&ringbuf);
    }
    return status;
}

SPI_Status_State SPI_read(uint8_t* rx_buf, const uint32_t length) {
    /* check args */
    if (length >= SPI_RXBUF_SIZE) return SPI_INVALID_ARGS;

    /* only put data if the number of requested bytes are present in the buffer */
    if (RING_BUF_size(&ringbuf) < length) {
        return SPI_ERROR_READ_EMPTY_BUFFER;
    }

    for (uint32_t i = 0; i<length; i++) {
        if (RING_BUF_readByteFromTail(&ringbuf, &rx_buf[i]) != RING_BUF_OK) {
            return SPI_ERROR_READ_EMPTY_BUFFER;
        }
    }

    return SPI_OK;
}

void SPI1_IRQHandler(void) {
    if (READ_BIT(SPI1->SR, SPI_SR_RXNE_Msk)) {
        /* RX FIFO is not empty. We are ready to read. */
        const uint16_t data = SPI1->DR;
        RING_BUF_writeByteToHead(&ringbuf, (uint8_t) (data & 0xFF));
        RING_BUF_writeByteToHead(&ringbuf, (uint8_t) ((data >> 8) & 0xFF));
    }
}

void SPI2_IRQHandler(void) {
    if (READ_BIT(SPI2->SR, SPI_SR_RXNE_Msk)) {
        /* RX FIFO is not empty. We are ready to read. */
        const uint16_t data = SPI2->DR;
        RING_BUF_writeByteToHead(&ringbuf, (uint8_t) (data & 0xFF));
        RING_BUF_writeByteToHead(&ringbuf, (uint8_t) ((data >> 8) & 0xFF));
    }
}

void SPI3_IRQHandler(void) {
    if (READ_BIT(SPI3->SR, SPI_SR_RXNE_Msk)) {
        /* RX FIFO is not empty. We are ready to read. */
        const uint16_t data = SPI3->DR;
        RING_BUF_writeByteToHead(&ringbuf, (uint8_t) (data & 0xFF));
        RING_BUF_writeByteToHead(&ringbuf, (uint8_t) ((data >> 8) & 0xFF));
    }
}