/** \addtogroup RCC
 *  \brief RCC drivers for stm32l4xx devices.
 *  @{
 */

/***
*
* RCC drivers for stm32l4xx devices.
* WARNING: These drivers have NOT been tested extensively. Use at own risk.
* Reference: https://www.youtube.com/playlist?list=PLtVUYRe-Z-mfKO0lg_-MBvwWl6VjWT8Dt
* STM32 Reference Manual: RM0432
*
***/

#ifndef RCC_H
#define RCC_H
#include "common.h"

/**
 * @defgroup  RCC_CLK_USART
 * @brief Macros to enable/disable the RCC CLK for the USART.
 */

/**
 * @addtogroup  RCC_CLK_USART
 * @brief Macro to set the USART1EN bit to 1.
 */
#define RCC_CLK_EN_USART1()        SET_BIT(RCC->APB2ENR, RCC_APB2ENR_USART1EN_Msk)

/**
 * @addtogroup  RCC_CLK_USART
 * @brief Macro to set the USART1EN bit to 0.
 */
#define RCC_CLK_DISABLE_USART1()   CLEAR_BIT(RCC->APB2ENR, RCC_APB2ENR_USART1EN_Msk)

/**
 * @addtogroup  RCC_CLK_USART
 * @brief Macro to set the USART2EN bit to 1.
 */
#define RCC_CLK_EN_USART2()        SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_USART2EN_Msk)

/**
 * @addtogroup  RCC_CLK_USART
 * @brief Macro to set the USART2EN bit to 0.
 */
#define RCC_CLK_DISABLE_USART2()   CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_USART2EN_Msk)

/**
 * @addtogroup  RCC_CLK_USART
 * @brief Macro to set the USART3EN bit to 1.
 */
#define RCC_CLK_EN_USART3()        SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_USART3EN_Msk)

/**
 * @addtogroup  RCC_CLK_USART
 * @brief Macro to set the USART3EN bit to 0.
 */
#define RCC_CLK_DISABLE_USART3()   CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_USART3EN_Msk)

/**
 * @addtogroup  RCC_CLK_USART
 * @brief Macro to set the UART4EN bit to 1.
 */
#define RCC_CLK_EN_UART4()         SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_UART4EN_Msk)

/**
 * @addtogroup  RCC_CLK_USART
 * @brief Macro to set the UART4EN bit to 0.
 */
#define RCC_CLK_DISABLE_UART4()    CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_UART4EN_Msk)

/**
 * @addtogroup  RCC_CLK_USART
 * @brief Macro to set the UART5EN bit to 1.
 */
#define RCC_CLK_EN_UART5()         SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_UART5EN_Msk)

/**
 * @addtogroup  RCC_CLK_USART
 * @brief Macro to set the UART5EN bit to 0.
 */
#define RCC_CLK_DISABLE_UART5()    CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_UART5EN_Msk)

#define RCC_CLK_EN_SPI1()          SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI1EN_Msk)

#define RCC_CLK_DISABLE_SPI1()     CLEAR_BIT(RCC->APB1ENR1, RCC_APB2ENR_SPI1EN_Msk)

#define RCC_CLK_EN_SPI2()          SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_SPI2EN_Msk)

#define RCC_CLK_DISABLE_SPI2()     CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_SPI2EN_Msk)

#define RCC_CLK_EN_SPI3()          SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_SPI3EN_Msk)

#define RCC_CLK_DISABLE_SPI3()     CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_SPI3EN_Msk)

/****************************************************************************************************/
/*					                        TYPEDEFS                                                */
/****************************************************************************************************/

/**@brief Enum to indicate the return status of a function.
*/
typedef enum {
    RCC_OK = 0, ///< Indicates that a function has returned successfully.
    RCC_INVALID_ARGS = 1, ///< Indicates that a function has been given invalid (out of range) arguments.
    RCC_ERROR = 2, ///< Indicates that a general error has occured.
}RCC_Status_State;

/****************************************************************************************************/
/*						             FUNCTION PROTOTYPES                                            */
/****************************************************************************************************/


#endif //RCC_H