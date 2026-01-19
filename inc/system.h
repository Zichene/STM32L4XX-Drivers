/** \addtogroup System
 * \brief System drivers for stm32l4xx devices.
 *  @{
 */
#ifndef SYSTEM_H
#define SYSTEM_H

#include "common.h"
#include "clock.h"
#include "tim.h"

/***
*
* System drivers for stm32l4xx devices.
* WARNING: These drivers have NOT been tested extensively. Use at own risk.
* Reference: https://www.youtube.com/playlist?list=PLtVUYRe-Z-mfKO0lg_-MBvwWl6VjWT8Dt
* STM32 Reference Manual: RM0432
*
***/

// The global timer shall be set to TIM2. Changing this will require modifying the IRQ Handler in system.c
#define SYST_GLOBAL_TIMER TIM_TIM2

/****************************************************************************************************/
/*			                  TYPEDEFS                                                              */
/****************************************************************************************************/
/**@brief Enum representing different function return statuses.
*/
typedef enum {
    SYST_OK = 0, ///< Indicates that a function has returned successfully.
    SYST_INVALID_ARGS = 1, ///< Indicates that a function has been given invalid (out of range) arguments.
    SYST_ERROR = 2, ///< Indicates that a general error has occured.
} SYST_Status_State;

/****************************************************************************************************/
/*				        FUNCTION PROTOTYPES                                                         */
/****************************************************************************************************/

// Configure the system. Calls the SYST_configClock120MHz function and starts the timer for the global sleep function.
SYST_Status_State SYST_init(void);

// Configures the system clock to its maximum speed: 120 MHz
SYST_Status_State SYST_configClock120MHz(void);

// Blocking sleep for specified milliseconds
void SYST_sleepMs(uint32_t ms);

// Start the global timer. Will reset the current Ms counter to 0.
SYST_Status_State SYST_resetGlobalTimer(void);

// Stop the global timer.
SYST_Status_State SYST_stopGlobalTimer(void);

// Get the current time elapsed since the start of the global timer.
uint32_t SYST_getCurrentMs(void);

#endif
/** @}*/