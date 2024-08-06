#include "gpio.h"

/***
*
* GPIO drivers for stm32l4xx devices.
* WARNING: These drivers have NOT been tested extensively. Use at own risk.
* Reference: https://www.youtube.com/playlist?list=PLtVUYRe-Z-mfKO0lg_-MBvwWl6VjWT8Dt
*
***/

static GPIO_TypeDef* getGPIO(Port port);
static int getEXTI_IRQn(char pin);

/**
 * Returns the pointer to the GPIO_TypeDef object corresponding with the given port.
 */
static GPIO_TypeDef* getGPIO(Port port) {
	switch(port){
		case A:
			return GPIOA;
		case B:
			return GPIOB;
		case C:
			return GPIOC;
		case D:
			return GPIOD;
		case E:
			return GPIOE;
		case F:
			return GPIOF;
		case G:
			return GPIOG;
		case H:
			return GPIOH;
		case I:
			return GPIOI;
	}
}

/* 
Returns the EXTIX_IRQn depending on pin X. Note that pins 5-9 inclusive and 10-15 inclusive have a combined EXTI_IRQn,
*/
static int getEXTI_IRQn(char pin) {
	switch(pin) {
		case 0:
			return EXTI0_IRQn;
		case 1:
			return EXTI1_IRQn;
		case 2:
			return EXTI2_IRQn;
		case 3:
			return EXTI3_IRQn;
		case 4:
			return EXTI4_IRQn;
	}
	if (pin <= 9) return EXTI9_5_IRQn;
	else return EXTI15_10_IRQn;
}


void GPIO_setPinOutput(Port port, char pin) {
	GPIO_setPinOutput_FC(port, pin, PUPD_NO_PULL_UP_PULL_DOWN, SPEED_VERY_HIGH, OUTPUT_PUSH_PULL);
}

void GPIO_setPinOutput_FC(Port port, char pin, PUPD_State pupd, SPEED_State speed, OUTPUT_TYPE_State output_t) {
	RCC->AHB2ENR |= (0b01 << port); // enable port
	GPIO_TypeDef* GPIOX = getGPIO(port);
	
	/* Mode set to output */
	GPIOX->MODER &= ~(0b11 << 2*pin); 
	GPIOX->MODER |= (0b01 << 2*pin); 
	
	/* Output mode */
	if (output_t == OUTPUT_PUSH_PULL) GPIOX->OTYPER &= ~(0b1 << pin); 
	else GPIOX->OTYPER |= 0b1 << pin;
	
	/* Speed */
	GPIOX->OSPEEDR &= ~(0b11 << 2*pin); 
	GPIOX->OSPEEDR |= (speed << 2*pin); 
	
	/* Set pupd  */	
	GPIOX->PUPDR &= ~(0b11 << 2*pin); 
	GPIOX->PUPDR |= (pupd << 2*pin); 
}

void GPIO_setPinInput(Port port, char pin, PUPD_State pupd) {
	GPIO_setPinInput_FC(port, pin, pupd, SPEED_VERY_HIGH, OUTPUT_PUSH_PULL);
}


void GPIO_setPinInput_FC(Port port, char pin,  PUPD_State pupd,  SPEED_State speed,  OUTPUT_TYPE_State output_t) {
	RCC->AHB2ENR |= (0b01 << port); // enable port
	GPIO_TypeDef* GPIOX = getGPIO(port);
	
	/* Mode set to input */
	GPIOX->MODER &= ~(0b11 << 2*pin); 
	GPIOX->MODER |= (0b00 << 2*pin); 
	
	/* Output mode */
  if (output_t == OUTPUT_PUSH_PULL) GPIOX->OTYPER &= ~(0b1 << pin); 
	else GPIOX->OTYPER |= 0b1 << pin;
	
	/* Speed */
	GPIOX->OSPEEDR &= ~(0b11 << 2*pin); 
	GPIOX->OSPEEDR |= (speed << 2*pin); 
	
	/* Set pupd */
	GPIOX->PUPDR &= ~(0b11 << 2*pin); 
	GPIOX->PUPDR |= (pupd << 2*pin); 
}


void GPIO_writePin(Port port, char pin, PinState state) {
		/* This function should only be called if pin has been correctly set. */
		GPIO_TypeDef* GPIOX = getGPIO(port);
	  if (state == HIGH) GPIOX->ODR |=  (0b1 << pin);
		else GPIOX->ODR &= ~(0b1 << pin);
}


PinState GPIO_readPin(Port port, char pin) {
	/* This function should only be called if pin has been correctly set. */
	GPIO_TypeDef* GPIOX = getGPIO(port);
	// Shift the IDR until our desired bit is at LSB, then bitmask with 1
	return (GPIOX->IDR >> pin) & 0b1;
}

void GPIO_togglePin(Port port, char pin) {
	/* This function should only be called if pin has been correctly set. */
	GPIO_writePin(port, pin, (GPIO_readPin(port, pin)+1)%2);
}

void GPIO_setPinInterrupt(Port port, char pin) {
	// Enable IRQ Clock
	RCC->APB2ENR |= 0b1;
	
	// Need to setup pin to external interrupt
	GPIO_setPinInput(port, pin, PUPD_PULL_UP);
	SYSCFG->EXTICR[pin/4] &= ~(0b1111 << 4*(pin%4)); 
	SYSCFG->EXTICR[pin/4] |= (port << 4*(pin%4));
	
	// Enable interrupt using interrupt mask register
	EXTI->IMR1 |= (0b1 << pin);
	
	// Select interrupt trigger to rising trigger
	EXTI->RTSR1 |= (0b1 << pin);
	
	// Enable the IRQ with NVIC
	__disable_irq();
	NVIC_EnableIRQ(getEXTI_IRQn(pin));
	__enable_irq();
}


void GPIO_resetPinInterrupt(char pin) {
	// Set flag back to 1 in pending register to clear it and prepare for next interrupt
	EXTI->PR1 |= (0b1 << pin);
}
