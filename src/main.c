#include "clock.h"
#include "gpio.h"

/*
For the B-L4S5I-IOT01A board, the pin PB14 is connected to LED2 and PC13 is connected to user button.
*/

#define LED2_Port GPIO_PORT_B
#define LED2_Pin 14
#define PB_Port GPIO_PORT_C
#define PB_Pin 13

#define MCO_Port GPIO_PORT_A
#define MCO_Pin 8

int main(void)
{
	/* Enable the PLL clock */
	CLOCK_configPLL();
	CLOCK_activateClk(CLOCK_PLL);
	/* Check the Clock output */
	CLOCK_activateMCO(MCO_Port, MCO_Pin, CLOCK_MCO_SELECT_SYSCLK, CLOCK_MCO_PRE_DIV_1);
	GPIO_setPinInterrupt(PB_Port, PB_Pin, GPIO_IT_TRIGGER_RISING);
	GPIO_setPinOutput(LED2_Port, LED2_Pin);
	CLOCK_getSystemClockSpeed();
	while (1) {
	}
	
}

void EXTI15_10_IRQHandler(){
	// Resetting Interrupt is very important
	GPIO_resetPinInterrupt(PB_Pin);
	GPIO_togglePin(LED2_Port, LED2_Pin);
}