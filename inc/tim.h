/** \addtogroup TIM
 *  @{
 */

#ifndef TIM_H
#define TIM_H
#include "common.h"
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
	TIM_TIM1 = 11, ///< TIM1 (advanced-control) timer selected. 
	TIM_TIM2 = 0, ///< TIM2 (general purpose) timer selected.
	TIM_TIM3 = 1, ///< TIM3 (general purpose) timer selected.
	TIM_TIM4 = 2, ///< TIM4 (general purpose) timer selected.
	TIM_TIM5 = 3, ///< TIM5 (general purpose) timer selected.
	TIM_TIM6 = 4, ///< TIM6 (basic) timer selected.
	TIM_TIM7 = 5, ///< TIM7 (basic) timer selected.
	TIM_TIM8 = 13, ///< TIM7 (advanced-control) timer selected.
	TIM_TIM15 = 16, ///< TIM15 (general purpose) timer selected.
	TIM_TIM16 = 17, ///< TIM16 (general purpose) timer selected.
	TIM_TIM17 = 18, ///< TIM17 (general purpose) timer selected.
} TIM_TIMER_State;

/**@brief Enum representing different function return statuses.
*/
typedef enum {
	TIM_OK = 0, ///< Indicates that a function has returned successfully.
	TIM_INVALID_ARGS = 1, ///< Indicates that a function has been given invalid (out of range) arguments.
	TIM_ERROR = 2, ///< Indicates that a general error has occured.
}TIM_Status_State;

/**@brief Struct representing configuration parameters for a timer. To be used with TIM_config().
*/
typedef struct {
	TIM_TIMER_State timer; ///< Timer. Which timer will be configured.
	uint16_t PSC; ///< Prescaler. The counter clock frequency CK_CNT is equal to fCK_PSC / (PSC[15:0] + 1).
	uint16_t ARR; ///< Auto-Reload register. Defines the maximum number that the timer will count up to (or down from).
	uint8_t enableInterrupt; ///< Boolean that controls whether or not the clock should generate interrupts. 
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



/**@brief Configure a timer with desired config parameters. See TIM_Config_Typedef for specific parameters.
* @param config pointer to a TIM_Config_Typedef object that contains the parameter configuration
* @return status
*/
TIM_Status_State TIM_config(TIM_Config_Typedef* config);



/**@brief Starts the timer by setting the CEN bit in the TIMx_CR1 register.
* @param timer timer.
* @return status
*/
TIM_Status_State TIM_startTimer(TIM_TIMER_State timer);



/**@brief Stops the timer by setting the CEN bit in the TIMx_CR1 register.
* @param timer timer.
* @return status
*/
TIM_Status_State TIM_stopTimer(TIM_TIMER_State timer);



/**@brief Checks the update interrupt flag (UIF) in the TIMx_SR register. Optionally, can choose to reset UIF to '0' if '1' is read.
* @param timer timer.
* @param reset_flag boolean to indicate whether we want to automatically reset the UIF flag to '0'.
* @return value of the UIF flag.
* @warning This function does not check correctness of arguments. This responsibility is given to the caller.
*/
uint8_t TIM_hasUpdated(TIM_TIMER_State timer, uint8_t reset_flag);



/**@brief Resets the UIF flag in the TIMx_SR register.
* @param timer timer.
* @return status 
*/
TIM_Status_State TIM_resetEventFlag(TIM_TIMER_State timer);
#endif
/** @}*/