#ifndef CLOCK_H
#define CLOCK_H
#include "stm32l4xx.h"
#include "gpio.h"

/***
*
* Clock drivers for stm32l4xx devices.
* WARNING: These drivers have NOT been tested extensively. Use at own risk.
* Reference: https://www.youtube.com/playlist?list=PLtVUYRe-Z-mfKO0lg_-MBvwWl6VjWT8Dt
* STM32 Reference Manual: RM0432
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
	CLOCK_MSI = 0, ///< The MSI clock is to be activated or desactivated
	CLOCK_LSE = 1, ///< The LSE clock is to be activated or desactivated
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

/**@brief Enum representing different values for the AHB prescaler.
*/
typedef enum {
	CLOCK_AHB_PRE_DIV_1 = 0, ///<SYSCLK divided by 1
	CLOCK_AHB_PRE_DIV_2 = 8, ///<SYSCLK divided by 2
	CLOCK_AHB_PRE_DIV_4 = 9, ///<SYSCLK divided by 4
	CLOCK_AHB_PRE_DIV_8 = 10, ///<SYSCLK divided by 8
	CLOCK_AHB_PRE_DIV_16 = 11, ///<SYSCLK divided by 16
	CLOCK_AHB_PRE_DIV_64 = 12, ///<SYSCLK divided by 64
	CLOCK_AHB_PRE_DIV_128 = 13, ///<SYSCLK divided by 128
	CLOCK_AHB_PRE_DIV_256 = 14, ///<SYSCLK divided by 256
	CLOCK_AHB_PRE_DIV_512 = 15, ///<SYSCLK divided by 512
}CLOCK_AHB_PRESCALER_State;

/**@brief Enum representing different values for the APB1 prescaler.
*/
typedef enum {
	CLOCK_APB1_PRE_DIV_1 = 0, ///<SYSCLK divided by 1
	CLOCK_APB1_PRE_DIV_2 = 4, ///<HCLK divided by 2
	CLOCK_APB1_PRE_DIV_4 = 5, ///<HCLK divided by 4
	CLOCK_APB1_PRE_DIV_8 = 6, ///<HCLK divided by 8
	CLOCK_APB1_PRE_DIV_16 = 7, ///<HCLK divided by 16
}CLOCK_APB1_PRESCALER_State;

/**@brief Enum representing different values for the APB1 prescaler.
*/
typedef enum {
	CLOCK_APB2_PRE_DIV_1 = 0, ///<SYSCLK divided by 1
	CLOCK_APB2_PRE_DIV_2 = 4, ///<HCLK divided by 2
	CLOCK_APB2_PRE_DIV_4 = 5, ///<HCLK divided by 4
	CLOCK_APB2_PRE_DIV_8 = 6, ///<HCLK divided by 8
	CLOCK_APB2_PRE_DIV_16 = 7, ///<HCLK divided by 16
}CLOCK_APB2_PRESCALER_State;

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
CLOCK_Status_State CLOCK_activateMCO(GPIO_Port port, uint8_t pin, CLOCK_MCO_SELECT_State mco_sel_state, CLOCK_MCO_PRESCALER_State mco_pre_state);



/**@brief Configures the PLL clock so that it may be used as the System clock.
* @param pll_src selects which clock will drive the PLL
* @param PLL_M divsion factor for the main PLL clock. 1 <= PLL_M <= 16.
* @param PLL_N main PLL multiplication factor. 8 <= PLLN <= 127.
* @param PLL_R divsion factor for the main PLL clock. PLLR = {2, 4, 6, 8}.
* @return status 
* @warning This function can only be called if the PLL clock is disabled. Use CLOCK_isActivated() and CLOCK_desactivateClk() before calling this function.
*/
CLOCK_Status_State CLOCK_configPLL(CLOCK_PLL_SOURCE_State pll_src, uint8_t PLL_M, uint8_t PLL_N, CLOCK_PLLR_State PLL_R);



/**@brief Checks if a clock is activated or not by reading from RCC control registers.
* @param clk which clock to check
* @retval 0 the clock is not activated
* @retval 1 the clock is activated
*/
uint8_t CLOCK_isActivated(CLOCK_State clk);



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
uint32_t CLOCK_getPLLClockSpeed();



/**@brief Gets the speed (frequency) in Hz of the MSI (Multi-Speed Internal) clock.
* @return frequency of MSI clock in Hz. 
*/
uint32_t CLOCK_getMSIClockSpeed();


/**@brief Set the speed of the external clock oscillator, if one is available.
* @param speed (in Hz) of the HSE 
*/
void CLOCK_setHSEClockSpeed(uint32_t speed);



/**@brief Gets the speed (frequency) in Hz of the HSE (High-Speed External) clock.
* @return frequency of HSE clock in Hz. 
*/
uint32_t CLOCK_getHSEClockSpeed();



/**@brief Gets the speed (frequency) in Hz of the system clock. The system clock can either be: MSI, HSI16, HSE or PLL.
* @return frequency of the system clock in Hz.
*/
uint32_t CLOCK_getSystemClockSpeed();



/**@brief Sets the system clock.
* @param sysclk The system clock to be selected
* @return status
* @warning This function assumes that the clock has already been activated via CLOCK_activateClk().
* @warning Blocking function. Will only return once a SWS flag has been set by hardware in the RCC_CFGR register.
*/
CLOCK_Status_State CLOCK_setSystemClock(CLOCK_SYSCLK_State sysclk);



/**@brief Set the AHB prescaler for the AHB clock (HCLK). This clocks feeds the AHB1 and AHB2 buses.
* @param ahb_prescaler choice for the AHB_PRE value.
* @return status
*/
CLOCK_Status_State CLOCK_setAHBPrescaler(CLOCK_AHB_PRESCALER_State ahb_prescaler);



/**@brief Set the APB1 prescaler for the APB1 clock (PCLK1). This clocks feeds the AHB1 and AHB2 buses.
* @param apb1_prescaler choice for the APB1_PRE value.
* @return status
*/
CLOCK_Status_State CLOCK_setAPB1Prescaler(CLOCK_APB1_PRESCALER_State apb1_prescaler);



/**@brief Set the APB2 prescaler for the APB2 clock (PCLK2). This clocks feeds the AHB1 and AHB2 buses.
* @param apb2_prescaler choice for the APB2_PRE value.
* @return status
*/
CLOCK_Status_State CLOCK_setAPB2Prescaler(CLOCK_APB2_PRESCALER_State apb2_prescaler);
#endif