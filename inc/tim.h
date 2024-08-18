#ifndef TIM_H
#define TIM_H
#include "stm32l4xx.h"
#include "clock.h"

/***
*
* Timer drivers for stm32l4xx devices.
* WARNING: These drivers have NOT been tested extensively. Use at own risk.
* Reference: https://www.youtube.com/playlist?list=PLtVUYRe-Z-mfKO0lg_-MBvwWl6VjWT8Dt
* STM32 Reference Manual: RM0432
*
***/

/****************************************************************************************************/
/*			                  TYPEDEFS                                                  */
/****************************************************************************************************/

/**@brief Enum representing different timers on the chip. Timers 2-8 inclusive are connected to APB1 bus. Timers 1 and 15-17 inclusive are connected to the APB2 bus.
*/
typedef enum {
	TIM_TIM1 = 11,
	TIM_TIM2 = 0,
	TIM_TIM3 = 1,
	TIM_TIM4 = 2,
	TIM_TIM5 = 3,
	TIM_TIM6 = 4,
	TIM_TIM7 = 5,
	TIM_TIM8 = 13,
	TIM_TIM15 = 16,
	TIM_TIM16 = 17,
	TIM_TIM17 = 18,
} TIM_TIMER_State;

/**@brief Enum representing different function return statuses.
*/
typedef enum {
	TIM_OK = 0, ///< Indicates that a function has returned successfully.
	TIM_INVALID_ARGS = 1, ///< Indicates that a function has been given invalid (out of range) arguments.
	TIM_ERROR = 2, ///< Indicates that a general error has occured.
}TIM_Status_State;

typedef struct {
}TIM_Config_Typedef;

/****************************************************************************************************/
/*				        FUNCTION PROTOTYPES                                         */
/****************************************************************************************************/

/**@brief Enable the peripheral clock for a timer by changing the bit on the APB1ENR or APB2ENR registers.
* @param timer which timer to enable
* @return status
*/
TIM_Status_State TIM_enablePeripheralClk(TIM_TIMER_State timer);



/**@brief Disable the peripheral clock for a timer by changing the bit on the APB1ENR or APB2ENR registers.
* @param timer which timer to disable
* @return status
*/
TIM_Status_State TIM_disablePeripheralClk(TIM_TIMER_State timer);

#endif