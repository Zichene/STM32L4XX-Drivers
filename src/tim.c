#include "tim.h"


/***
*
* Timer drivers for stm32l4xx devices.
* WARNING: These drivers have NOT been tested extensively. Use at own risk.
* Reference: https://www.youtube.com/playlist?list=PLtVUYRe-Z-mfKO0lg_-MBvwWl6VjWT8Dt
* STM32 Reference Manual: RM0432
*
***/

/****************************************************************************************************/
/*			              PRIVATE FUNCTIONS                                             */
/****************************************************************************************************/
static TIM_TypeDef* getTIM(TIM_TIMER_State timer);


/** Get the TIM_TypeDef object associated with the input timer.
*/
static TIM_TypeDef* getTIM(TIM_TIMER_State timer) {
	switch(timer) {
		case TIM_TIM1:
			return TIM1;
		
		case TIM_TIM2:
			return TIM2;
		
		case TIM_TIM3:
			return TIM3;
		
		case TIM_TIM4:
			return TIM4;
		
		case TIM_TIM5:
			return TIM5;
		
		case TIM_TIM6:
			return TIM6;
		
		case TIM_TIM7:
			return TIM7;
		
		case TIM_TIM8:
			return TIM8;
		
		case TIM_TIM15:
			return TIM15;
		
		case TIM_TIM16:
			return TIM16;
		
		case TIM_TIM17:
			return TIM17;
	}
}


/****************************************************************************************************/
/*			              EXPORTED FUNCTIONS                                            */
/****************************************************************************************************/


TIM_Status_State TIM_enablePeripheralClk(TIM_TIMER_State timer) {
	/* check args */
	if (!( (timer <= 5 && timer >= 0) || (timer <= 18 && timer >= 16) || timer == 11 || timer == 13))
		return TIM_INVALID_ARGS;
	
	/* depending on which timers, the enable bit is in a different register */
	if (timer <= 5) {
		/* timers on the APB1 bus (TIM2-TIM8 inclusive) */
		RCC->APB1ENR1 |= (0b1 << timer);
		while(!((RCC->APB1ENR1 >> timer & 0b1) == 1));
	} else {
		/* timers on the APB2 bus (TIM1, TIM15-17) */
		RCC->APB2ENR |= (0b1 << timer);
		while(!((RCC->APB2ENR >> timer & 0b1) == 1));
	}
	return TIM_OK;
}


TIM_Status_State TIM_disablePeripheralClk(TIM_TIMER_State timer) {
	/* check args */
	if (!( (timer <= 5 && timer >= 0) || (timer <= 18 && timer >= 16) || timer == 11 || timer == 13))
		return TIM_INVALID_ARGS;
	
	/* depending on which timers, the enable bit is in a different register */
	if (timer <= 5) {
		/* timers on the APB1 bus (TIM2-TIM8 inclusive) */
		RCC->APB1ENR1 &= ~(0b1 << timer);
		while(!((RCC->APB1ENR1 >> timer & 0b1) == 0));
	} else {
		/* timers on the APB2 bus (TIM1, TIM15-17) */
		RCC->APB2ENR &= ~(0b1 << timer);
		while(!((RCC->APB2ENR >> timer & 0b1) == 0));
	}
	return TIM_OK;
}