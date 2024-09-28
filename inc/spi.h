/** \addtogroup UART
 * \brief UART drivers for stm32l4xx devices.
 *  @{
 */
#ifndef SPI_H
#define SPI_H

#include "common.h"
#include "gpio.h"

/***
*
* SPI drivers for stm32l4xx devices.
* WARNING: These drivers have NOT been tested extensively. Use at own risk.
* Reference: https://www.youtube.com/playlist?list=PLtVUYRe-Z-mfKO0lg_-MBvwWl6VjWT8Dt
* STM32 Reference Manual: RM0432
*
***/


/****************************************************************************************************/
/*			                  TYPEDEFS                                                  */
/****************************************************************************************************/

/**@brief Enum representing different function return statuses.
*/
typedef enum {
	SPI_OK = 0, ///< Indicates that a function has returned successfully.
	SPI_INVALID_ARGS = 1, ///< Indicates that a function has been given invalid (out of range) arguments.
	SPI_ERROR = 2, ///< Indicates that a general error has occured.
} SPI_Status_State;


/**@brief Enum representing which SPI device is selected.
*/
typedef enum {
	SPI_SPI1 = 12, ///< SPI1 is selected.
	SPI_SPI2 = 14, ///< SPI2 is selected.
	SPI_SPI3 = 15, ///< SPI3 is selected.
} SPI_DEVICE_State;

/**@brief Struct representing the pin configuration parameters for the SPI.
*/
typedef struct {
	GPIO_Port sclk_port; ///< The GPIO port for the SCLK pin.
	uint8_t sclk_pin; ///< The GPIO pin # for the SCLK pin.
	GPIO_AF_State sclk_pin_af; ///< The Alternate Function (AF) mode number for the SCLK pin.
	
	GPIO_Port miso_port; ///< The GPIO port for the MISO pin.
	uint8_t miso_pin; ///< The GPIO pin # for the MISO pin.
	GPIO_AF_State miso_pin_af; ///< The Alternate Function (AF) mode number for the MISO pin.
	
	GPIO_Port mosi_port; ///< The GPIO port for the MOSI pin.
	uint8_t mosi_pin; ///< The GPIO pin # for the MOSI pin.
	GPIO_AF_State mosi_pin_af; ///< The Alternate Function (AF) mode number for the MOSI pin.
	
	GPIO_Port ssel_port; ///< The GPIO port for the SSEL pin.
	uint8_t ssel_pin; ///< The GPIO pin # for the SSEL pin.
	GPIO_AF_State ssel_pin_af; ///< The Alternate Function (AF) mode number for the SSEL pin.
} SPI_PinConfig_Typedef;


/**@brief Struct representing configuration parameters for the SPI. To be used with SPI_config().
*/
typedef struct {
	SPI_DEVICE_State spi; ///< Which SPI device is to be configured.
	SPI_PinConfig_Typedef* pin_config; ///< GPIO pin configuration of the device
} SPI_Config_Typedef;

/****************************************************************************************************/
/*				        FUNCTION PROTOTYPES                                         */
/****************************************************************************************************/


/**@brief Configures the desired SPI peripheral and activates it. See SPI_Config_Typedef for parameters.
* @param spi_conf configuration object
* @return status
*/
SPI_Status_State SPI_config(const SPI_Config_Typedef* spi_conf);



#endif
/** @}*/