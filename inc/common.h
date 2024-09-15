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
 * The General Purpose Input Output (GPIO) drivers currently implement functionalities such as:
 *	- Pin output
 *	- Pin input
 *	- Interrupts
 *	- Alternate Function (AF)
 *
 * All GPIO pins can be set up with specific pull-up pull down mode, speed type and output type. 
 * See local [documentation](group___g_p_i_o.html).
 *
 * \section clock_sec CLOCK Drivers
 *
 * The Clock drivers currently implement functionalities such as:
 * - Activating the MCO (Master Clock Output) for various clock sources.
 * - Configure the PLL (Phased Locked Loop) clock.
 * - Get the clock speeds for various clocks (system clock, HSI, PLL, MSI, etc.)
 * - Configure and set the system clock.
 * - Set various peripheral bus prescalers (AHB, APB1, APB2).
 
 * See local [documentation](group___c_l_o_c_k.html).
 *
 * \section timer_sec TIMER Drivers
 * The Timer (TIM) drivers currently implement functionalities such as:
 * - Configuring various timers with prescaler and period.
 * - Timer interrupt configuration.
 * - Starting and stopping interrupts.
 * 
 * See local [documentation](group___t_i_m.html).
 * 
 * \section uart_sec UART Drivers
 * The Universal Asynchronous Receivier Transmitter (UART) drivers currently implement functionalities such as:
 * - Sending data (blocking mode)
 * - Receiving data (blocking mode)
 * - Custom configuration of baud rate, parity bit, stop bits, number of bits per word, etc.
 * - Receiving data in interrupt mode. Ringbuffer implemented internally.
 *
 * See local [documentation](group___u_a_r_t.html).
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
// #define PUSH_LED 			///< Project 1: Push Led selected. Main driver(s) used: GPIO
// #define BLINKY_LED 		///< Project 2: Blinky Led selected. Main driver(s) used: GPIO, CLOCK, TIM
// #define UART_PRINTF  	///< Project 3: Printing to UART. Main drivers(s) used: GPIO, CLOCK, UART
 #define UART_RECEIVE 	///< Project 3.5: Receiving from UART. Main drivers(s) used: GPIO, CLOCK, UART
// #define RINGBUF_TEST 			///< Project 4: Ring Buffer. Main drivers(s) used: GPIO, CLOCK, UART
#endif // COMMON_H