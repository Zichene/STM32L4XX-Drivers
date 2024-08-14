#include "gpio.h"

/***
*
* GPIO drivers for stm32l4xx devices.
* WARNING: These drivers have NOT been tested extensively. Use at own risk.
* Reference: https://www.youtube.com/playlist?list=PLtVUYRe-Z-mfKO0lg_-MBvwWl6VjWT8Dt
*
***/

static GPIO_TypeDef* getGPIO(GPIO_Port port);
static int getEXTI_IRQn(char pin);
static void setOutput_Speed_PUPD(GPIO_TypeDef* GPIOX, char pin, GPIO_PUPD_State pupd, GPIO_SPEED_State speed, GPIO_OUTPUT_TYPE_State output_t);

/****************************************************************************************************/
/*			              PRIVATE FUNCTIONS                                             */
/****************************************************************************************************/

/**
 * Returns the pointer to the GPIO_TypeDef object corresponding with the given port.
 */
static GPIO_TypeDef* getGPIO(GPIO_Port port) {
	switch(port){
		case GPIO_PORT_A:
			return GPIOA;
		case GPIO_PORT_B:
			return GPIOB;
		case GPIO_PORT_C:
			return GPIOC;
		case GPIO_PORT_D:
			return GPIOD;
		case GPIO_PORT_E:
			return GPIOE;
		case GPIO_PORT_F:
			return GPIOF;
		case GPIO_PORT_G:
			return GPIOG;
		case GPIO_PORT_H:
			return GPIOH;
		case GPIO_PORT_I:
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

/*
Sets the output type, speed and pupd states for a GPIO pin.
*/
static void setOutput_Speed_PUPD(GPIO_TypeDef* GPIOX, char pin, GPIO_PUPD_State pupd, GPIO_SPEED_State speed, GPIO_OUTPUT_TYPE_State output_t) {
	/* Output mode */
	if (output_t == GPIO_OUTPUT_PUSH_PULL) GPIOX->OTYPER &= ~(0b1 << pin); 
	else GPIOX->OTYPER |= 0b1 << pin;
	
	/* Speed */
	GPIOX->OSPEEDR &= ~(0b11 << 2*pin); 
	GPIOX->OSPEEDR |= (speed << 2*pin); 
	
	/* Set pupd  */	
	GPIOX->PUPDR &= ~(0b11 << 2*pin); 
	GPIOX->PUPDR |= (pupd << 2*pin); 
}



/****************************************************************************************************/
/*			              EXPORTED FUNCTIONS                                            */
/****************************************************************************************************/

GPIO_Status_State GPIO_setPinOutput(GPIO_Port port, char pin) {
	return GPIO_setPinOutput_FC(port, pin, GPIO_PUPD_NO_PULL_UP_PULL_DOWN, GPIO_SPEED_VERY_HIGH, GPIO_OUTPUT_PUSH_PULL);
}

GPIO_Status_State GPIO_setPinOutput_FC(GPIO_Port port, char pin, GPIO_PUPD_State pupd, GPIO_SPEED_State speed, GPIO_OUTPUT_TYPE_State output_t) {
	/* check args */
	if (!(port <= 8 && port >= 0 && pin <= 15 && pin >= 0 && pupd <= 2 && pupd >= 0 && speed <= 3 && speed >= 0 && output_t <= 1 && output_t >= 0))
		return GPIO_INVALID_ARGS;
	RCC->AHB2ENR |= (0b01 << port); // enable port
	GPIO_TypeDef* GPIOX = getGPIO(port);
	
	/* Mode set to output */
	GPIOX->MODER &= ~(0b11 << 2*pin); 
	GPIOX->MODER |= (0b01 << 2*pin); 
	
	/* Set remaining parameters */
	setOutput_Speed_PUPD(GPIOX, pin, pupd, speed, output_t);
	return GPIO_OK;
}

GPIO_Status_State GPIO_setPinInput(GPIO_Port port, char pin, GPIO_PUPD_State pupd) {
	return GPIO_setPinInput_FC(port, pin, pupd, GPIO_SPEED_VERY_HIGH, GPIO_OUTPUT_PUSH_PULL);
}


GPIO_Status_State GPIO_setPinInput_FC(GPIO_Port port, char pin,  GPIO_PUPD_State pupd,  GPIO_SPEED_State speed,  GPIO_OUTPUT_TYPE_State output_t) {
	/* check args */
	if (!(port <= 8 && port >= 0 && pin <= 15 && pin >= 0 && pupd <= 2 && pupd >= 0 && speed <= 3 && speed >= 0 && output_t <= 1 && output_t >= 0))
		return GPIO_INVALID_ARGS;
	RCC->AHB2ENR |= (0b01 << port); // enable port
	GPIO_TypeDef* GPIOX = getGPIO(port);
	
	/* Mode set to input */
	GPIOX->MODER &= ~(0b11 << 2*pin); 
	GPIOX->MODER |= (0b00 << 2*pin); 
	
	/* Set remaining parameters */
	setOutput_Speed_PUPD(GPIOX, pin, pupd, speed, output_t);
	return GPIO_OK;
}


GPIO_Status_State GPIO_writePin(GPIO_Port port, char pin, GPIO_PinState state) {
		/* check args */
		if (!(port <= 8 && port >= 0 && pin <= 15 && pin >= 0 && state <= 1 && state >= 0))
			return GPIO_INVALID_ARGS;
		/* This function should only be called if pin has been correctly set. */
		GPIO_TypeDef* GPIOX = getGPIO(port);
	  if (state == GPIO_HIGH) GPIOX->ODR |=  (0b1 << pin);
		else GPIOX->ODR &= ~(0b1 << pin);
		return GPIO_OK;
}


GPIO_PinState GPIO_readPin(GPIO_Port port, char pin) {
	/* This function should only be called if pin has been correctly set. */
	GPIO_TypeDef* GPIOX = getGPIO(port);
	// Shift the IDR until our desired bit is at LSB, then bitmask with 1
	return (GPIOX->IDR >> pin) & 0b1;
}

GPIO_Status_State GPIO_togglePin(GPIO_Port port, char pin) {
	/* check args */
	if (!(port <= 8 && port >= 0 && pin <= 15 && pin >= 0))
		return GPIO_INVALID_ARGS;
	/* This function should only be called if pin has been correctly set. */
	GPIO_writePin(port, pin, (GPIO_readPin(port, pin)+1)%2);
	return GPIO_OK;
}

GPIO_Status_State GPIO_setPinInterrupt(GPIO_Port port, char pin, GPIO_IT_TRIGGER_State trigger_state) {
	/* check args */
	if (!(port <= 8 && port >= 0 && pin <= 15 && pin >= 0 && trigger_state <= 1 && trigger_state >= 0))
		return GPIO_INVALID_ARGS;
	// Enable IRQ Clock
	RCC->APB2ENR |= 0b1;
	
	// Need to setup pin to external interrupt
	GPIO_setPinInput(port, pin, GPIO_PUPD_PULL_UP);
	SYSCFG->EXTICR[pin/4] &= ~(0b1111 << 4*(pin%4)); 
	SYSCFG->EXTICR[pin/4] |= (port << 4*(pin%4));
	
	// Enable interrupt using interrupt mask register
	EXTI->IMR1 |= (0b1 << pin);
	
	// Select interrupt trigger
	if (trigger_state == GPIO_IT_TRIGGER_FALLING) EXTI->FTSR1 |= (0b1 << pin);
	else EXTI->RTSR1 |= (0b1 << pin);
	
	// Enable the IRQ with NVIC
	__disable_irq();
	NVIC_EnableIRQ(getEXTI_IRQn(pin));
	__enable_irq();
	return GPIO_OK;
}


GPIO_Status_State GPIO_resetPinInterrupt(char pin) {
	/* check args */
	if (!(pin <= 15 && pin >= 0))
		return GPIO_INVALID_ARGS;
	// Set flag back to 1 in pending register to clear it and prepare for next interrupt
	EXTI->PR1 |= (0b1 << pin);
	return GPIO_OK;
}


GPIO_Status_State GPIO_setPinAF_Mode(GPIO_Port port, char pin, GPIO_PUPD_State pupd,  GPIO_SPEED_State speed,  GPIO_OUTPUT_TYPE_State output_t) {
	/* check args */
	if (!(port <= 8 && port >= 0 && pin <= 15 && pin >= 0 && pupd <= 2 && pupd >= 0 && speed <= 3 && speed >= 0 && output_t <= 1 && output_t >= 0))
		return GPIO_INVALID_ARGS;
	RCC->AHB2ENR |= (0b01 << port); // enable port
	GPIO_TypeDef* GPIOX = getGPIO(port);
	
	/* Mode set to AF */
	GPIOX->MODER &= ~(0b11 << 2*pin); 
	GPIOX->MODER |= (0b10 << 2*pin);
	
	/* Set remaining parameters */
	setOutput_Speed_PUPD(GPIOX, pin, pupd, speed, output_t);
	return GPIO_OK;
}

GPIO_Status_State GPIO_setPinAF_State(GPIO_Port port, char pin, GPIO_AF_State af_state) {
	/* check args */
	if (!(port <= 8 && port >= 0 && pin <= 15 && pin >= 0 && af_state <= 15 && af_state >= 0))
		return GPIO_INVALID_ARGS;
	GPIO_TypeDef* GPIOX = getGPIO(port);
	
	/* Set correct AF state in the AFR register */
	GPIOX->AFR[pin/8] &= ~(0b1111 << 4*(pin%8));
	GPIOX->AFR[pin/8] |= (af_state << 4*(pin%8));
	return GPIO_OK;
}
