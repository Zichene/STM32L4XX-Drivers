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
static void configPeripheralClock(SPI_DEVICE_State spi);


/*
* Configures the peripheral clock for the selected SPI device.
*/
static void configPeripheralClock(SPI_DEVICE_State spi) {
		if (spi == SPI_SPI1) {
		/* devices on the APB2 bus */
		RCC->APB2ENR |= (0b1 << spi);
	} else {
		/*  for SPI2 and SPI3 */
		RCC->APB1ENR1 |= (0b1 << spi);
	}
}


/*
* Configures the GPIO to the correct AF state for the selected SPI device.
*/
static SPI_Status_State configGPIO(SPI_PinConfig_Typedef* pin_config) {
	
	GPIO_Port sclk_port = pin_config->sclk_port;
	GPIO_Port sclk_pin = pin_config->sclk_pin;
	GPIO_Port miso_port = pin_config->miso_port;
	GPIO_Port miso_pin = pin_config->miso_pin;
	GPIO_Port mosi_port = pin_config->mosi_port;
	GPIO_Port mosi_pin = pin_config->mosi_pin;
	GPIO_Port ssel_port = pin_config->ssel_port;
	GPIO_Port ssel_pin = pin_config->ssel_pin;
	
	/* setup sclk pin to the correct AF state */
	if (GPIO_setPinAF_Mode(sclk_port, sclk_pin, GPIO_PUPD_NO_PULL_UP_PULL_DOWN, GPIO_SPEED_VERY_HIGH, GPIO_OUTPUT_PUSH_PULL) != GPIO_OK)
		return SPI_INVALID_ARGS;
	if (GPIO_setPinAF_State(sclk_port, sclk_pin, pin_config->sclk_pin_af) != GPIO_OK)
		return SPI_INVALID_ARGS;
	
	/* setup miso pin to the correct AF state */
	if (GPIO_setPinAF_Mode(miso_port, miso_pin, GPIO_PUPD_NO_PULL_UP_PULL_DOWN, GPIO_SPEED_VERY_HIGH, GPIO_OUTPUT_PUSH_PULL) != GPIO_OK)
		return SPI_INVALID_ARGS;
	if (GPIO_setPinAF_State(miso_port, miso_pin, pin_config->miso_pin_af) != GPIO_OK)
		return SPI_INVALID_ARGS;
	
		/* setup mosi pin to the correct AF state */
	if (GPIO_setPinAF_Mode(mosi_port, mosi_pin, GPIO_PUPD_NO_PULL_UP_PULL_DOWN, GPIO_SPEED_VERY_HIGH, GPIO_OUTPUT_PUSH_PULL) != GPIO_OK)
		return SPI_INVALID_ARGS;
	if (GPIO_setPinAF_State(mosi_port, mosi_pin, pin_config->mosi_pin_af) != GPIO_OK)
		return SPI_INVALID_ARGS;
	
		/* setup ssel pin to the correct AF state */
	if (GPIO_setPinAF_Mode(ssel_port, ssel_pin, GPIO_PUPD_NO_PULL_UP_PULL_DOWN, GPIO_SPEED_VERY_HIGH, GPIO_OUTPUT_PUSH_PULL) != GPIO_OK)
		return SPI_INVALID_ARGS;
	if (GPIO_setPinAF_State(ssel_port, ssel_pin, pin_config->ssel_pin_af) != GPIO_OK)
		return SPI_INVALID_ARGS;
	
	return SPI_OK;
}

/****************************************************************************************************/
/*			              EXPORTED FUNCTIONS                                            */
/****************************************************************************************************/


SPI_Status_State SPI_config(const SPI_Config_Typedef* spi_conf) {
	/* check args */
	SPI_DEVICE_State spi = spi_conf->spi;
	
	/* enable peripheral clock */
	configPeripheralClock(spi);
	
	/* setup GPIO pins */
	if (configGPIO(spi_conf->pin_config) != SPI_OK)
		return SPI_INVALID_ARGS;
	
	
	return SPI_OK;
}