#ifndef CLOCK_H
#define CLOCK_H
#include "gpio.h"

/***
*
* Clock drivers for stm32l4xx devices.
* WARNING: These drivers have NOT been tested extensively. Use at own risk.
* Reference: https://www.youtube.com/playlist?list=PLtVUYRe-Z-mfKO0lg_-MBvwWl6VjWT8Dt
*
***/

/****************************************************************************************************/
/*			                  TYPEDEFS                                                  */
/****************************************************************************************************/

/**@brief Enum representing which clock is to be outputted to the Master Clock Output (MCO) pin.
*/
typedef enum {
	CLOCK_MCO_SELECT_NONE = 0, ///< MCO output disabled, no clock on MCO
	CLOCK_MCO_SELECT_SYSCLK = 1, ///<  SYSCLK system clock selected
	CLOCK_MCO_SELECT_MSI = 2, ///< MSI clock selected
	CLOCK_MCO_SELECT_HSI16 = 3, ///<HSI16 clock selected
	CLOCK_MCO_SELECT_HSE = 4, ///< HSE clock selected
	CLOCK_MCO_SELECT_PLL = 5, ///< Main PLL clock selected
	CLOCK_MCO_SELECT_LSI = 6, ///< LSI clock selected
	CLOCK_MCO_SELECT_LSE = 7, ///< LSE clock selected
	CLOCK_MCO_SELECT_HSI48 = 8, ///< Internal HSI48 clock selected
} CLOCK_MCO_SELECT_State;

/**@brief Enum representing a prescaler choice for the MCO output.
*/
typedef enum {
	CLOCK_MCO_PRE_DIV_1 = 0, ///< MCO is divided by 1
	CLOCK_MCO_PRE_DIV_2 = 1, ///< MCO is divided by 2,
	CLOCK_MCO_PRE_DIV_4 = 2, ///< MCO is divided by 4,
	CLOCK_MCO_PRE_DIV_8 = 3, ///< MCO is divided by 8,
	CLOCK_MCO_PRE_DIV_16 = 4, ///< MCO is divided by 16,
} CLOCK_MCO_PRESCALER_State;

/**@brief Enum representing a choice of clock for activating and desactivating.
*/
typedef enum {
	CLOCK_LSE = 0,
	CLOCK_MSI = 0,
	CLOCK_HSI = 8,
	CLOCK_HSE = 16,
	CLOCK_PLL = 24,
	CLOCK_PLLSAI1 = 26,
	CLOCK_PLLSAI2 = 28,
}CLOCK_State;

/**@brief Enum representing a choice of clock as source for PLL
*/
typedef enum {
	CLOCK_PLL_SRC_NONE = 0,
	CLOCK_PLL_SRC_MSI = 1,
	CLOCK_PLL_SRC_HSI16 = 2,
	CLOCK_PLL_SRC_HSE = 3,
}CLOCK_PLL_SOURCE_State;

/**@brief Enum representing choices for the PLL_R parameter.
*/
typedef enum {
	CLOCK_PLLR_2 = 0,
	CLOCK_PLLR_4 = 1,
	CLOCK_PLLR_6 = 2,
	CLOCK_PLLR_8 = 3,
}CLOCK_PLLR_State;

/**@brief Enum representing the status of a function.
*/
typedef enum {
	CLOCK_OK = 0, ///< Indicates that a function has returned successfully.
	CLOCK_INVALID_ARGS = 1, ///< Indicates that a function has been given invalid (out of range) arguments.
	CLOCK_ERROR = 2, ///< Indicates that a general error has occured.
}CLOCK_Status_State;

/****************************************************************************************************/
/*				        FUNCTION PROTOTYPES                                         */
/****************************************************************************************************/

/**@brief Activates the Master Clock Output pin to the selected output state. 
* @param port port for the MCO pin.
* @param pin pin number of the MCO pin.
* @param mco_sel_state which clock should be outputed to MCO.
* @param mco_pre_state prescaler for the MCO (divisions by powers of 2 up to 16 allowed).
* @return status
* @warning Untested function due to lack of proper oscilloscope.
* @warning Desired clock (mco_sel_state) needs to be properly activated via the RCC_CR register before use of this function. By default SYSCLK is already activated.
*/
CLOCK_Status_State CLOCK_activateMCO(GPIO_Port port, char pin, CLOCK_MCO_SELECT_State mco_sel_state, CLOCK_MCO_PRESCALER_State mco_pre_state);

/**@brief Activates a desired clock. 
* @param clk clock to be activated
* @return status
* @warning Untested function.
* @warning Blocking function. Will only return once a 'RDY' flag has been raised by the clock hardware (clock stabilized).
* @warning For the PLL clock, it is necessary to call CLOCK_configPLL() first before calling this function.
*/
CLOCK_Status_State CLOCK_activateClk(CLOCK_State clk);

/**@brief Desactivates a desired clock. 
* @param clk clock to be desactivated.
* @return status
* @warning Untested function.
*/
CLOCK_Status_State CLOCK_desactivateClk(CLOCK_State clk);

/**@brief Gets the speed (frequency) in Hz of the system clock.
* @warning Not implemented yet.
*/
int CLOCK_getSystemClockSpeed();

/**@brief Configures the PLL clock so that it may be used as the System clock.
* @param pll_src selects which clock will drive the PLL
* @param PLL_M divsion factor for the main PLL clock. 1 <= PLL_M <= 16.
* @param PLL_N main PLL multiplication factor. 8 <= PLLN <= 127.
* @param PLL_R divsion factor for the main PLL clock. PLLR = {2, 4, 6, 8}.
* @return status 
*/
CLOCK_Status_State CLOCK_configPLL(CLOCK_PLL_SOURCE_State pll_src, char PLL_M, char PLL_N, CLOCK_PLLR_State PLL_R);
#endif