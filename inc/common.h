#ifndef COMMON_H
#define COMMON_H

/*! \mainpage STM32L4XX Drivers Documentation
 *
 * \section intro_sec Introduction
 *
 * Bare-metal implementation of some drivers for the STM32L4 family of devices. See example projects showcasing these drivers at 
 * https://github.com/Zichene/STM32L4XX-Drivers/tree/main/projects-bl4s5i-iot01a.
 * These drivers were mostly tested using the B-L4S5I-IOT01A development board from ST.
 *
 * 
 * WARNING:
 * These drivers were written for educational purposes. These have not been tested thoroughly, use at own risk.
 * These drivers should only use on STM32L4XX devices.
 *
 * \section install_sec Installation
 * 
 * - Clone the repo or download desired files.
 * - In your embedded project environment, simply add the desired `.h` and `.c` files. Make sure that you set up the include paths correctly!
 *
 * \section gpio_sec GPIO Drivers
 * 
 * etc...
 */
 

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
// #define PUSH_LED ///< Project 1: Push Led selected. Main driver(s) used: GPIO
// #define BLINKY_LED ///< Project 2: Blinky Led selected. Main driver(s) used: GPIO, CLOCK, TIM
#define UART_PRINTF ///< Project 3: Printing to UART. Main drivers(s) used: TODO
#endif // COMMON_H