#ifndef COMMON_H
#define COMMON_H

/***
*
* Common defines and includes that are shared between all driver files.
* STM32 Reference Manual: RM0432
***/


/****************************************************************************************************/
/*			                  INCLUDES                                                 */
/****************************************************************************************************/
#include "stm32l4xx.h"


/****************************************************************************************************/
/*			                  DEFINES                                                */
/****************************************************************************************************/
#define true 1 ///< boolean true
#define false 0 ///< boolean false
	
/***************************************************************************************************/
/*                            ACTIVE MAIN FILE                                                     */
/*                                                                                                 */
/* ATTENTION: Only uncomment one of the following defines to select which project to run.          */
/***************************************************************************************************/
 #define PUSH_LED ///< Project 1: Push Led selected. Main driver(s) used: GPIO
// #define BLINKY_LED ///< Project 2: Blinky Led selected. Main driver(s) used: GPIO, CLOCK, TIM

#endif // COMMON_H