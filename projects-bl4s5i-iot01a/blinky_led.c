#include "common.h"
#include "gpio.h"
#include "clock.h"
#include "tim.h"

#ifdef BLINKY_LED
/*
DESCRIPTION: Configure the system clock to its maximum speed (120 MHz for this board) and timer interrupt to make the LED blink once per second.
BOARD USED: B-L4S5I-IOT01A board
INTERNAL CONNECTIONS: The pin PB14 is connected to LED2.
REFERENCES: STM32 MB1297 (Internal Board Connections)
AUTHOR: Zichene
DATE: 8/20/2024
*/


/* On the board used for this example, LED2 (green) is connected to Pin B14 (Port B, Pin 14) */
#define LED2_Port GPIO_PORT_B
#define LED2_Pin 14


static void configureSystemClock120MHz();
static void ErrorHandler();

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
static void configureSystemClock120MHz() {

	/* Configure PLL with required parameters (PLL_M, PLL_N and PLL_R) */
	CLOCK_configPLL(CLOCK_PLL_SRC_MSI, 1, 60, CLOCK_PLLR_2);
	
	/* Activate and set the PLLCLK as the system clock */
	CLOCK_activateClk(CLOCK_PLL);
	CLOCK_setSystemClock(CLOCK_SYSCLK_PLL); 
	
	/* Check that the system clock is indeed 120 MHz */
	if (CLOCK_getSystemClockSpeed() != 120000000)
		ErrorHandler();
	
	/* Make sure that bus prescalers are set to 1. These prescalers control the speed of the clock that is passed to the timers. */
	CLOCK_setAHBPrescaler(CLOCK_AHB_PRE_DIV_1);
	CLOCK_setAPB1Prescaler(CLOCK_APB1_PRE_DIV_1);
}



/* Setup timer using TIM2 so that LED turns on or off every second.
* 
* The prescaler (PSC) determines how many clock cycles pass before the counter goes up by one.
* The period (ARR) determines how many times the counter needs to increment before an event (interrupt) is triggered.
*
* Since the clock reaching the TIM2 timer is at 120 MHz, we can set our PSC and ARR to 40000 and 3000 respectively so that an event is triggered every 1 second. 
*
*/
static void configureTimer() {
	TIM_Config_Typedef tim2_config = {
	.ARR=3000, // Period of 3000
	.PSC=40000, // Prescaler of 40000
	.timer = TIM_TIM2,
	.enableInterrupt = true,
	};
	
	TIM_config(&tim2_config);
	TIM_startTimer(TIM_TIM2);
}


int main(void)
{
	/* Configure the system clock to be 120 MHz */
	configureSystemClock120MHz();
	
	/* Configure the timer so it raises an interrupt every 1 second */
	configureTimer();
	
	/* Configure the GPIO for the LED */
	GPIO_setPinOutput(LED2_Port, LED2_Pin);
	
	while (1) {
		/* Infinite loop so that we don't exit main */
	}
	
}

/*
* Interrupt handler for the TIM2 timer. Whenver a timer event occurs, this interrupt is triggered and this function is called.
*/
void TIM2_IRQHandler() {
	/* Reset the event flag and toggle the LED pin */
	TIM_resetEventFlag(TIM_TIM2);
	GPIO_togglePin(LED2_Port, LED2_Pin);
}


void ErrorHandler() {
	while(1) {
	/* If you've ended up here, then a problem has occured! */
	}
}
#endif