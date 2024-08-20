#include "clock.h"
#include "gpio.h"
#include "tim.h"

/*
For the B-L4S5I-IOT01A board, the pin PB14 is connected to LED2 and PC13 is connected to user button.
*/

#define LED2_Port GPIO_PORT_B
#define LED2_Pin 14

#define LED_WIFI_Port GPIO_PORT_C
#define LED_WIFI_Pin 9

#define PB_Port GPIO_PORT_C
#define PB_Pin 13

#define MCO_Port GPIO_PORT_A
#define MCO_Pin 8

void ErrorHandler();



int main(void)
{
	/* DEBUG led pin */
	GPIO_setPinOutput(LED_WIFI_Port, LED_WIFI_Pin);
	
	/* Configure the system clock correctly for the pin */
	if (CLOCK_isActivated(CLOCK_PLL)) CLOCK_desactivateClk(CLOCK_PLL); // disable PLL if it is enabled
	if (!CLOCK_isActivated(CLOCK_MSI)) CLOCK_activateClk(CLOCK_MSI); // activate HSI if it is disabled
	if (CLOCK_configPLL(CLOCK_PLL_SRC_MSI, 1, 60, CLOCK_PLLR_2) != CLOCK_OK)
		 ErrorHandler();
	
	CLOCK_activateClk(CLOCK_PLL);
	CLOCK_setSystemClock(CLOCK_SYSCLK_PLL); // activate and set system clock to PLL
	
	/* sysclk should be 120 MHz */
	if (CLOCK_getSystemClockSpeed() != 120000000)
		ErrorHandler();
	
	/* make sure that bus prescalers are set to 1 */
	CLOCK_setAHBPrescaler(CLOCK_AHB_PRE_DIV_1);
	CLOCK_setAPB1Prescaler(CLOCK_APB1_PRE_DIV_1);
	
	/* Setup timer using TIM2 so that LED turns on or off every second */
	TIM_Config_Typedef tim2_config = {
	.ARR=3000, // Period of 3000
	.PSC=40000, // Prescaler of 40000
	.timer = TIM_TIM2,
	.enableInterrupt = true,
	};
	TIM_config(&tim2_config);
	
	/* button interrupt setup */
	GPIO_setPinInterrupt(PB_Port, PB_Pin, GPIO_IT_TRIGGER_RISING);
	GPIO_setPinOutput(LED2_Port, LED2_Pin);
	
	while (1) {
//		if (TIM_hasUpdated(TIM_TIM2, true)) {
//			GPIO_togglePin(LED2_Port, LED2_Pin);
//		}
	}
	
}

void TIM2_IRQHandler() {
	TIM_resetEventFlag(TIM_TIM2);
	GPIO_togglePin(LED2_Port, LED2_Pin);
}

void EXTI15_10_IRQHandler(){
	// Resetting Interrupt is very important
	GPIO_resetPinInterrupt(PB_Pin);
	GPIO_togglePin(LED2_Port, LED2_Pin);
}

void ErrorHandler() {
	GPIO_writePin(LED_WIFI_Port, LED_WIFI_Pin, GPIO_HIGH);
	while(1) {
	}
}