#include "common.h"
#include "gpio.h"

#ifdef PUSH_LED
/*
DESCRIPTION: Push the user button (blue) to toggle the LED. Uses interrupts. 
BOARD USED: B-L4S5I-IOT01A board
INTERNAL CONNECTIONS: The pin PB14 is connected to LED2 and PC13 is connected to user button.
REFERENCES: STM32 MB1297 (Internal Board Connections)
AUTHOR: Zichene
DATE: 8/20/2024
*/



/* On the board used for this example, LED2 (green) is connected to Pin B14 (Port B, Pin 14) */
#define LED2_Port GPIO_PORT_B
#define LED2_Pin 14

/* On the board used for this example, the Push Button (blue) is connected to Pin C13 (Port C, Pin 13) */
#define PB_Port GPIO_PORT_C
#define PB_Pin 13

int main(void)
{
	/* button and led interrupt gpio setup */
	GPIO_setPinInterrupt(PB_Port, PB_Pin, GPIO_IT_TRIGGER_RISING);
	GPIO_setPinOutput(LED2_Port, LED2_Pin);
	
	while (1) {
		/* Infinite while loop so that we don't exit main */
	}
}

/*
* Interrupt handler. Whenever the push button is pressed, an interrupt signal is fired and will call this function.
*/
void EXTI15_10_IRQHandler(){
	/* resetting Interrupt is very important */
	GPIO_resetPinInterrupt(PB_Pin);
	GPIO_togglePin(LED2_Port, LED2_Pin);
}
#endif