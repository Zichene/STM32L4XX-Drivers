/** \addtogroup SPI
 * \brief SPI drivers for stm32l4xx devices.
 *  @{
 */
#ifndef SPI_H
#define SPI_H

#include "common.h"
#include "gpio.h"
#include "rcc.h"
#include "ringbuffer.h"
#include "system.h"

/***
*
* SPI drivers for stm32l4xx devices.
* WARNING: These drivers have NOT been tested extensively. Use at own risk.
* Reference: https://www.youtube.com/playlist?list=PLtVUYRe-Z-mfKO0lg_-MBvwWl6VjWT8Dt
* STM32 Reference Manual: RM0432
*
***/

#define SPI_RXBUF_SIZE 1000
/****************************************************************************************************/
/*			                  TYPEDEFS                                                              */
/****************************************************************************************************/

/**@brief Enum representing different function return statuses.
*/
typedef enum {
	SPI_OK = 0, ///< Indicates that a function has returned successfully.
	SPI_INVALID_ARGS = 1, ///< Indicates that a function has been given invalid (out of range) arguments.
	SPI_ERROR = 2, ///< Indicates that a general error has occured.
    SPI_ERROR_READ_EMPTY_BUFFER = 3, ///< Indicates that we tried to read when the RXFIFO was empty.
    SPI_ERROR_WRITE_NON_EMPTY_BUFFER = 4, ///< Indicates that we tried to write when the TXFIFO was non-empty.
    SPI_ERROR_TIMEOUT = 5 ///< Indicates that a timeout event has occurred.
} SPI_Status_State;


/**@brief Enum representing which SPI device is selected.
*/
typedef enum {
	SPI_SPI1 = 12, ///< SPI1 is selected.
	SPI_SPI2 = 14, ///< SPI2 is selected.
	SPI_SPI3 = 15, ///< SPI3 is selected.
} SPI_Device;

typedef enum {
    SPI_BR_DIV_2    = 0b000, ///< Baud rate = PCLK/2
    SPI_BR_DIV_4    = 0b001, ///< Baud rate = PCLK/4
    SPI_BR_DIV_8    = 0b010, ///< Baud rate = PCLK/8
    SPI_BR_DIV_16   = 0b011, ///< Baud rate = PCLK/16
    SPI_BR_DIV_32   = 0b100, ///< Baud rate = PCLK/32
    SPI_BR_DIV_64   = 0b101, ///< Baud rate = PCLK/64
    SPI_BR_DIV_128  = 0b110, ///< Baud rate = PCLK/128
    SPI_BR_DIV_256  = 0b111, ///< Baud rate = PCLK/256
} SPI_BR_Divider;

typedef enum {
    SPI_MODE_0  = 0, ///< CPOL = 0, CPHA = 0
    SPI_MODE_1  = 1, ///< CPOL = 0, CPHA = 1
    SPI_MODE_2  = 2, ///< CPOL = 1, CPHA = 0
    SPI_MODE_3  = 3, ///< CPOL = 1, CPHA = 1
} SPI_Mode;

typedef enum {
    SPI_NSS_SOFTWARE = 0, ///< SSM=1:  in this configuration, slave select information is driven internally (by software)
    SPI_NSS_HARDWARE_OUTPUT_EN, ///< SSM=0, SSOE=1
    SPI_NSS_HARDWARE_OUTPUT_DISABLED, ///< SSM=0, SSOE=0
} SPI_NSS_Management;


typedef enum {
    SPI_DATA_SIZE_4_BIT = 3,    ///< SPI Data length of 4 bits
    SPI_DATA_SIZE_5_BIT = 4,    ///< SPI Data length of 4 bits
    SPI_DATA_SIZE_6_BIT = 5,    ///< SPI Data length of 4 bits
    SPI_DATA_SIZE_7_BIT = 6,    ///< SPI Data length of 4 bits
    SPI_DATA_SIZE_8_BIT = 7,    ///< SPI Data length of 4 bits
    SPI_DATA_SIZE_9_BIT = 8,    ///< SPI Data length of 4 bits
    SPI_DATA_SIZE_10_BIT = 9,   ///< SPI Data length of 4 bits
    SPI_DATA_SIZE_11_BIT = 10,  ///< SPI Data length of 4 bits
    SPI_DATA_SIZE_12_BIT = 11,  ///< SPI Data length of 4 bits
    SPI_DATA_SIZE_13_BIT = 12,  ///< SPI Data length of 4 bits
    SPI_DATA_SIZE_14_BIT = 13,  ///< SPI Data length of 4 bits
    SPI_DATA_SIZE_15_BIT = 14,  ///< SPI Data length of 4 bits
    SPI_DATA_SIZE_16_BIT = 15,  ///< SPI Data length of 4 bits
} SPI_Data_Size;

/**@brief Struct representing the pin configuration parameters for the SPI.
*/
typedef struct {
    uint8_t sclk_apply; ///< Settings will be applied to SCLK pin.
	GPIO_Port sclk_port; ///< The GPIO port for the SCLK pin.
	uint8_t sclk_pin; ///< The GPIO pin # for the SCLK pin.
	GPIO_AF_State sclk_pin_af; ///< The Alternate Function (AF) mode number for the SCLK pin.

    uint8_t miso_apply; ///< Settings will be applied to MISO pin.
	GPIO_Port miso_port; ///< The GPIO port for the MISO pin.
	uint8_t miso_pin; ///< The GPIO pin # for the MISO pin.
	GPIO_AF_State miso_pin_af; ///< The Alternate Function (AF) mode number for the MISO pin.

    uint8_t mosi_apply; ///< Settings will be applied to MOSI pin.
	GPIO_Port mosi_port; ///< The GPIO port for the MOSI pin.
	uint8_t mosi_pin; ///< The GPIO pin # for the MOSI pin.
	GPIO_AF_State mosi_pin_af; ///< The Alternate Function (AF) mode number for the MOSI pin.

    uint8_t ssel_apply; ///< Settings will be applied to SSEL pin.
	GPIO_Port ssel_port; ///< The GPIO port for the SSEL pin.
	uint8_t ssel_pin; ///< The GPIO pin # for the SSEL pin.
	GPIO_AF_State ssel_pin_af; ///< The Alternate Function (AF) mode number for the SSEL pin.
} SPI_PinConfig_Typedef;


typedef struct {
    uint8_t enabled; ///< Boolean. Set to True to enabled CRC calculation.
    uint8_t crc_length_16_bit; ///< Boolean, if set to True will use 16-bit CRC length. Otherwise, use 8-bit CRC length.
    uint16_t crc_polynomial; ///< Represents the CRC polynomial. Reset value is 0x0007. Note: the polynomial must be odd.
} SPI_CRCConfig_Typedef;

/**@brief Struct representing interrupt configuration parameters for the SPI.
*/
typedef struct {
    uint8_t RXNEIE_enabled; ///< Used to generate an interrupt request when the RXNE flag is set.
    uint8_t TXEIE_enabled;  ///< Used to generate an interrupt request when the TXE flag is set.
    uint8_t ERRIE_enabled;  ///< Used to generate an interrupt when an error condition occurs (CRCERR, OVR, MODF in SPI mode, FRE at TI mode).
    uint8_t priority;       ///< Set the priority of the interrupt. Lower numbers are higher priority.
} SPI_ITConfig_Typedef;

/**@brief Struct representing configuration parameters for the SPI. To be used with SPI_config().
*/
typedef struct {
	SPI_Device spi; ///< Which SPI device is to be configured.
	SPI_PinConfig_Typedef* pin_config; ///< GPIO pin configuration of the device
    SPI_CRCConfig_Typedef* crc_config; ///< CRC configuration of the device
    SPI_ITConfig_Typedef* it_config; ///< Interrupt configuration of the device
    SPI_BR_Divider br_divider; ///< Divider value to configure the baud rate
    SPI_Mode mode; ///< SPI Mode (CPHA and CPOL values)
    SPI_NSS_Management nss_management; ///< Specified NSS management type
    SPI_Data_Size data_size; ///< SPI data transfer length
    uint8_t full_duplex; ///< Boolean. If True then we wish to use full duplex mode. Otherwise, half-duplex
    uint8_t lsb_first; ///< Boolean. If True then data transfers with the LSB first. Otherwise, MSB first
    uint8_t master; ///< Boolean. If True then configure SPI as Master. Otherwise, slave.
    uint8_t nss_pulse_mode; ///< Boolean. If True then allows SPI to generate an NSS pulse.
    uint8_t fifo_threshold_8_bit; ///< Boolean. If True, RXNE event is generated when FIFO level is greater than or equal to 8-bits. Otherwise, 16-bits.
} SPI_Config_Typedef;

/****************************************************************************************************/
/*				        FUNCTION PROTOTYPES                                         */
/****************************************************************************************************/


/**@brief Configures the desired SPI peripheral and activates it. See SPI_Config_Typedef for parameters.
* @param spi_conf configuration object
* @return status
*/
SPI_Status_State SPI_config(const SPI_Config_Typedef* spi_conf);

// Directly read from the SPI->DR register.
SPI_Status_State SPI_receive(SPI_Device spi, uint16_t *data);

// Directly write to the SPI->DR register.
SPI_Status_State SPI_transmit(SPI_Device spi, uint16_t data);

// Read from the ring buffer. Will only be populated if interrupts are activated.
SPI_Status_State SPI_read(uint8_t* rx_buf, uint32_t length);

// Read multiple bytes or write multiple bytes. Assume that we need to send dummy data to keep clock active.
SPI_Status_State SPI_transmitReceive(SPI_Device spi, uint8_t rw, uint8_t *data, uint16_t size, uint32_t timeout);

#endif
/** @}*/