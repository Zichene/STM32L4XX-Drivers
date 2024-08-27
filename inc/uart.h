/** \addtogroup UART
 * \brief UART drivers for stm32l4xx devices.
 *  @{
 */

#ifndef UART_H
#define UART_H

#include "common.h"
#include "gpio.h"
#include "clock.h"

/***
*
* UART drivers for stm32l4xx devices.
* WARNING: These drivers have NOT been tested extensively. Use at own risk.
* Reference: https://www.youtube.com/playlist?list=PLtVUYRe-Z-mfKO0lg_-MBvwWl6VjWT8Dt
* STM32 Reference Manual: RM0432
*
***/

#define UART_MAX_BAUDRATE (120000000/16) ///< Maximum allowed baudrate for USART. TODO: temporary fix, max baudrate actually depends on oversampling and system clock system

/****************************************************************************************************/
/*			                  TYPEDEFS                                                  */
/****************************************************************************************************/


/**@brief Enum representing different function return statuses.
*/
typedef enum {
	UART_OK = 0, ///< Indicates that a function has returned successfully.
	UART_INVALID_ARGS = 1, ///< Indicates that a function has been given invalid (out of range) arguments.
	UART_ERROR = 2, ///< Indicates that a general error has occured.
} UART_Status_State;

/**@brief Enum representing which UART/USART device is selected.
*/
typedef enum {
	UART_USART1 = 14, ///< USART1 is selected.
	UART_USART2 = 17, ///< USART2 is selected.
	UART_USART3 = 18, ///< USART3 is selected.
	UART_UART4 = 19, ///< UART4 is selected (note: not synchronous)
	UART_UART5 = 20, ///< UART5 is selected (note: not synchronous)
} UART_DEVICE_State;

/**@brief Enum representing how many databits to be used during communication (default=8).
*/
typedef enum {
	UART_DATABITS_7 = 2, ///< 7 databits per word.
	UART_DATABITS_8 = 0, ///< 8 databits per word (default).
	UART_DATABITS_9 = 1, ///< 9 databits per word.
} UART_DATABITS_State;

/**@brief Enum representing type of parity check to be used, if any (default=None).
*/
typedef enum {
	UART_PARITY_NONE = 2, ///< Parity bit is disabled (default).
	UART_PARITY_EVEN = 0, ///< Even parity is used.
	UART_PARITY_ODD = 1, ///< Odd parity is used.
} UART_PARITY_State;

/**@brief Enum representing number of stopbits to be used during communication (default=1).
*/
typedef enum {
	UART_STOPBITS_1 = 0, ///< 1 stop bit (default).
	UART_STOPBITS_0_5 = 1, ///< 0.5 stop bits.
	UART_STOPBITS_2 = 2, ///< 2 stop bits.
	UART_STOPBITS_1_5 = 3, ///< 1.5 stop bits.
} UART_STOPBITS_State;

/**@brief Struct representing the pin configuration parameters for the U(S)ART.
*/
typedef struct {
	GPIO_Port rx_port; ///< The GPIO port for the RX pin.
	uint8_t rx_pin; ///< The GPIO pin # for the RX pin.
	GPIO_AF_State rx_pin_af; ///< The Alternate Function (AF) mode number for the RX pin.
	GPIO_Port tx_port; ///< The GPIO port for the TX pin.
	uint8_t tx_pin; ///< The GPIO pin # for the TX pin.
	GPIO_AF_State tx_pin_af; ///< The Alternate Function (AF) mode number for the TX pin.
} UART_PinConfig_Typedef;

/**@brief Struct representing interrupt configuration parameters for the U(S)ART.
*/
typedef struct {
	uint8_t is_enabled; ///< Boolean representing whether or not interrupts should be enabled or not.
	uint8_t priority; ///< Set the priority of the interrupt. Lower numbers are higher priority.
} UART_ITConfig_Typedef;

/**@brief Struct representing configuration parameters for the U(S)ART. To be used with UART_config().
*/
typedef struct {
	UART_DEVICE_State uart; ///< Which UART/USART device is to be configured.
	UART_PinConfig_Typedef* pin_config; ///< Pin configuration object. See UART_PinConfig_Typedef.
	UART_ITConfig_Typedef* it_config; ///< Interrupt configuration object. See UART_ITConfig_Typedef.
	uint32_t baud_rate; ///< Baud rate for the UART/USART.
	UART_DATABITS_State databits; ///< Number of databits to be sent every word.
	UART_PARITY_State parity; ///< Parity bit setting.
	UART_STOPBITS_State stopbits; ///< Number of stopbits.
} UART_Config_Typedef;

/****************************************************************************************************/
/*				        FUNCTION PROTOTYPES                                         */
/****************************************************************************************************/

/**@brief Configures the desired UART/USART peripheral and activates it. See UART_Config_Typedef for parameters.
* @param uart_conf configuration object
* @return status
*/
UART_Status_State UART_config(const UART_Config_Typedef* uart_conf);



/**@brief Transmits data over UART/USART.
* @param uart UART/USART device.
* @param tx_buf pointer to the data transmission buffer.
* @param length length of tx_buf
* @return status
* @warning blocking function.
*/
UART_Status_State UART_transmit(UART_DEVICE_State uart, const uint8_t* tx_buf, uint16_t length);



/**@brief Reads and returns from the UARTx->RDR register.
* @param uart UART/USART device.
* @return value read from the RDR register.
*/
uint8_t UART_receiveByte(UART_DEVICE_State uart);



/**@brief Reads and returns the RXNE/RXFNE bit in the UARTx->ISR register. This determines whether or not data has been received and is ready to be
* read from the RDR register.
* @param uart UART/USART device.
* @retval 1 Data has been received and is ready to be read.
* @retval 0 Data has not been received.
*/
uint8_t UART_hasData(UART_DEVICE_State uart);

#endif
/** @}*/