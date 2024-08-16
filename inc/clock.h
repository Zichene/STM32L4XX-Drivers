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
	CLOCK_MCO_PRE_DIV_2 = 1, ///< MCO is divided by 2
	CLOCK_MCO_PRE_DIV_4 = 2, ///< MCO is divided by 4
	CLOCK_MCO_PRE_DIV_8 = 3, ///< MCO is divided by 8
	CLOCK_MCO_PRE_DIV_16 = 4, ///< MCO is divided by 16
} CLOCK_MCO_PRESCALER_State;

/**@brief Enum representing a choice of clock for activating and desactivating.
*/
typedef enum {
	CLOCK_LSE = 0, ///< The LSE clock is to be activated or desactivated
	CLOCK_MSI = 0, ///< The MSI clock is to be activated or desactivated
	CLOCK_HSI = 8, ///< The HSI clock is to be activated or desactivated
	CLOCK_HSE = 16, ///< The HSE clock is to be activated or desactivated
	CLOCK_PLL = 24, ///< The PLL clock is to be activated or desactivated
	CLOCK_PLLSAI1 = 26, ///< The PLLSAI1 clock is to be activated or desactivated
	CLOCK_PLLSAI2 = 28, ///< The PLLSAI2 clock is to be activated or desactivated
}CLOCK_State;

/**@brief Enum representing a choice of clock as source for PLL
*/
typedef enum {
	CLOCK_PLL_SRC_NONE = 0, ///< The source clock for the PLL is not selected
	CLOCK_PLL_SRC_MSI = 1, ///< The source clock for the PLL is MSI
	CLOCK_PLL_SRC_HSI16 = 2, ///< The source clock for the PLL is HSI16
	CLOCK_PLL_SRC_HSE = 3, ///< The source clock for the PLL is HSE
}CLOCK_PLL_SOURCE_State;

/**@brief Enum representing choices for the PLL_R parameter.
*/
typedef enum {
	CLOCK_PLLR_2 = 0, ///< PLL_R is set to 2
	CLOCK_PLLR_4 = 1, ///< PLL_R is set to 4
	CLOCK_PLLR_6 = 2, ///< PLL_R is set to 6
	CLOCK_PLLR_8 = 3, ///< PLL_R is set to 8
}CLOCK_PLLR_State;

/**@brief Enum representing the status of a function.
*/
typedef enum {
	CLOCK_OK = 0, ///< Indicates that a function has returned successfully.
	CLOCK_INVALID_ARGS = 1, ///< Indicates that a function has been given invalid (out of range) arguments.
	CLOCK_ERROR = 2, ///< Indicates that a general error has occured.
}CLOCK_Status_State;

/**@brief Enum representing clocks which can be chosen as the system clock.
*/
typedef enum {
	CLOCK_SYSCLK_MSI = 0, ///< MSI selected as system clock
  CLOCK_SYSCLK_HSI16 = 1, ///< HSI16 selected as system clock
  CLOCK_SYSCLK_HSE = 2, ///< HSE selected as system clock
  CLOCK_SYSCLK_PLL = 3, ///< PLL selected as system clock
}CLOCK_SYSCLK_State;


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



/**@brief Configures the PLL clock so that it may be used as the System clock.
* @param pll_src selects which clock will drive the PLL
* @param PLL_M divsion factor for the main PLL clock. 1 <= PLL_M <= 16.
* @param PLL_N main PLL multiplication factor. 8 <= PLLN <= 127.
* @param PLL_R divsion factor for the main PLL clock. PLLR = {2, 4, 6, 8}.
* @return status 
*/
CLOCK_Status_State CLOCK_configPLL(CLOCK_PLL_SOURCE_State pll_src, char PLL_M, char PLL_N, CLOCK_PLLR_State PLL_R);



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


/**@brief Gets the speed (frequency) in Hz of the PLL clock, if it is activated.
* @return frequency of PLL clock in Hz. If return value is 0, then PLL is not activated or has invalid PLL_N, PLL_M or PLL_R constants.
*/
int CLOCK_getPLLClockSpeed();



/**@brief Gets the speed (frequency) in Hz of the MSI (Multi-Speed Internal) clock.
* @return frequency of MSI clock in Hz. 
*/
int CLOCK_getMSIClockSpeed();


/**@brief Set the speed of the external clock oscillator, if one is available.
* @param speed (in Hz) of the HSE 
*/
void CLOCK_setHSEClockSpeed(int speed);



/**@brief Gets the speed (frequency) in Hz of the HSE (High-Speed External) clock.
* @return frequency of HSE clock in Hz. 
*/
int CLOCK_getHSEClockSpeed();



/**@brief Gets the speed (frequency) in Hz of the system clock. The system clock can either be: MSI, HSI16, HSE or PLL.
* @return frequency of the system clock in Hz.
*/
int CLOCK_getSystemClockSpeed();



/**@brief Sets the system clock.
* @param sysclk The system clock to be selected
* @return status
* @warning This function assumes that the clock has already been activated via CLOCK_activateClk().
* @warning Blocking function. Will only return once a SWS flag has been set by hardware in the RCC_CFGR register.
*/
CLOCK_Status_State CLOCK_setSystemClock(CLOCK_SYSCLK_State sysclk);


#endif