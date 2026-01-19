#include "system.h"

/***
*
* SYSTEM drivers for stm32l4xx devices.
* WARNING: These drivers have NOT been tested extensively. Use at own risk.
* Reference: https://www.youtube.com/playlist?list=PLtVUYRe-Z-mfKO0lg_-MBvwWl6VjWT8Dt
* STM32 Reference Manual: RM0432
*
* FOR DETAILED DOCUMENTATION OF THIS FILE, SEE CORRESPONDING .h SOURCE CODE OR GENERATE DOCS WITH DOXYGEN.
*
***/


/****************************************************************************************************/
/*			              PRIVATE FUNCTIONS                                                         */
/****************************************************************************************************/
volatile uint32_t currentMs = 0; // Counter to track the sleep time

/****************************************************************************************************/
/*			              EXPORTED FUNCTIONS                                                        */
/****************************************************************************************************/

SYST_Status_State SYST_init() {
    SYST_Status_State status = SYST_OK;

    status = SYST_configClock120MHz();

    /* Setup timer using TIM2 to trigger an interrupt every 1 ms
    *
    * The prescaler (PSC) determines how many clock cycles pass before the counter goes up by one.
    * The period (ARR) determines how many times the counter needs to increment before an event (interrupt) is triggered.
    *
    * Since the clock reaching the TIM2 timer is at 120 MHz,
    * we can set our PSC and ARR to 40 and 3000 respectively so that an event is triggered every 1 ms.
    *
    */
    const TIM_Config_Typedef tim2_config = {
        .ARR=3000, // Period of 3000
        .PSC=40, // Prescaler of 40
        .timer = SYST_GLOBAL_TIMER,
        .enableInterrupt = true,
    };

    if (TIM_config(&tim2_config) != TIM_OK) {
        return SYST_ERROR;
    }

    return status;
}

/*
* Configure the system clock to its maximum speed (120 MHz).
*
*  We will be using the PLL clock as the system clock. In order to use this clock, we need to choose one of four clock sources for the PLL.
*  The source clock for the PLL will be the MSI (Multi Speed Internal) clock, which has a default speed of 4 MHz.
*  The speed of the MSI is modified by PLL_M, PLL_N and PLL_R, which are positive integers. The modification is as follows:
*
*  			output = input * PLL_N / (PLL_M * PLL_R)
*
*   MSI (default 4 MHz) -> divided by PLL_M = 1 -> multiplied by PLL_N = 60 -> divided by PLL_R = 2 -> 120 MHz
*
*/
SYST_Status_State SYST_configClock120MHz() {
    SYST_Status_State status = SYST_OK;

    /* Configure PLL with required parameters (PLL_M, PLL_N and PLL_R) */
    CLOCK_configPLL(CLOCK_PLL_SRC_MSI, 1, 60, CLOCK_PLLR_2);

    /* Activate and set the PLLCLK as the system clock */
    CLOCK_activateClk(CLOCK_PLL);
    CLOCK_setSystemClock(CLOCK_SYSCLK_PLL);

    /* Check that the system clock is indeed 120 MHz */
    if (CLOCK_getSystemClockSpeed() != 120000000)
        status = SYST_ERROR;

    /* Make sure that bus prescalers are set to 1. These prescalers control the speed of the clock that is passed to the timers and other peripherals. */
    CLOCK_setAHBPrescaler(CLOCK_AHB_PRE_DIV_1);
    CLOCK_setAPB1Prescaler(CLOCK_APB1_PRE_DIV_1);
    CLOCK_setAPB2Prescaler(CLOCK_APB2_PRE_DIV_1);

    return status;
}

void SYST_sleepMs(const uint32_t ms) {
    currentMs = 0;
    TIM_startTimer(SYST_GLOBAL_TIMER);
    while (currentMs < ms) {};
    TIM_stopTimer(SYST_GLOBAL_TIMER);
}

SYST_Status_State SYST_resetGlobalTimer() {
    SYST_Status_State status = SYST_OK;
    currentMs = 0;
    if (TIM_startTimer(SYST_GLOBAL_TIMER) != TIM_OK) {
        status = SYST_ERROR;
    }
    return status;
}

SYST_Status_State SYST_stopGlobalTimer() {
    SYST_Status_State status = SYST_OK;
    if (TIM_stopTimer(SYST_GLOBAL_TIMER) != TIM_OK) {
        status = SYST_ERROR;
    }
    return status;
}

uint32_t SYST_getCurrentMs() {
    return currentMs;
}

/*
* Interrupt handler for the TIM2 timer. Whenever a timer event occurs, this interrupt is triggered and this function is called.
*/
void TIM2_IRQHandler() {
    /* Reset the event flag and increment ms */
    TIM_resetEventFlag(SYST_GLOBAL_TIMER);
    currentMs++;
}