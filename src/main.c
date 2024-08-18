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
	GPIO_setPinOutput(LED_WIFI_Port, LED_WIFI_Pin);
	
	/* Enable the PLL clock */
	if (CLOCK_configPLL(CLOCK_PLL_SRC_MSI, 1, 60, CLOCK_PLLR_2) != CLOCK_OK) ErrorHandler();
	CLOCK_activateClk(CLOCK_PLL);
	int pllSpeed = CLOCK_getPLLClockSpeed();
	CLOCK_activateClk(CLOCK_HSI);
	if (CLOCK_setSystemClock(CLOCK_SYSCLK_PLL) != CLOCK_OK) ErrorHandler();
	/* Check the system clock speed */
	int sysSpeed = CLOCK_getSystemClockSpeed();
	
	if (CLOCK_setAHBPrescaler(CLOCK_AHB_PRE_DIV_4) != CLOCK_OK) ErrorHandler();
	if (CLOCK_setAPB1Prescaler(CLOCK_APB1_PRE_DIV_4) != CLOCK_OK) ErrorHandler();
	if (CLOCK_setAPB2Prescaler(CLOCK_APB2_PRE_DIV_4) != CLOCK_OK) ErrorHandler();
	
	TIM_enableTimer(TIM_TIM2);
	TIM_disableTimer(TIM_TIM2);
	GPIO_setPinInterrupt(PB_Port, PB_Pin, GPIO_IT_TRIGGER_RISING);
	GPIO_setPinOutput(LED2_Port, LED2_Pin);
	
	while (1) {
	}
	
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