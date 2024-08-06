#include "gpio.h"

/*
For the B-L4S5I-IOT01A board, the pin PB14 is connected to LED2 and PC13 is connected to user button.
*/

#define LED2_Port B
#define LED2_Pin 14
#define PB_Port C
#define PB_Pin 13


int main(void)
{
	GPIO_setPinInterrupt(PB_Port, PB_Pin);
	GPIO_setPinOutput(LED2_Port, LED2_Pin);
	while(1) {
		
	}
}

void EXTI15_10_IRQHandler(){
	// Resetting Interrupt is very important
	GPIO_resetPinInterrupt(PB_Pin);
	GPIO_togglePin(LED2_Port, LED2_Pin);
}