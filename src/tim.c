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
static int32_t getTIM_IRQn(TIM_TIMER_State timer);


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

/** Get the IRQn number associated with the input timer.
*/
static int32_t getTIM_IRQn(TIM_TIMER_State timer) {
	switch(timer) {
		case TIM_TIM1:
			return TIM1_UP_TIM16_IRQn;
		
		case TIM_TIM2:
			return TIM2_IRQn;
		
		case TIM_TIM3:
			return TIM3_IRQn;
		
		case TIM_TIM4:
			return TIM4_IRQn;
		
		case TIM_TIM5:
			return TIM5_IRQn;
		
		case TIM_TIM6:
			return TIM6_IRQn;
		
		case TIM_TIM7:
			return TIM7_IRQn;
		
		case TIM_TIM8:
			return TIM8_IRQn;
		
		case TIM_TIM15:
			return TIM1_BRK_TIM15_IRQn;
		
		case TIM_TIM16:
			return TIM1_UP_TIM16_IRQn;
		
		case TIM_TIM17:
			return TIM1_TRG_COM_TIM17_IRQn;
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


TIM_Status_State TIM_config(TIM_Config_Typedef* config) {
	/* check args */
	TIM_TIMER_State timer = config->timer;
	if (!( (timer <= 5 && timer >= 0) || (timer <= 18 && timer >= 16) || timer == 11 || timer == 13))
		return TIM_INVALID_ARGS;
	
	/* enable periph clock */
	if (TIM_enablePeripheralClk(timer) != TIM_OK)
		return TIM_ERROR;
	
	TIM_TypeDef* TIM_X = getTIM(timer);
	/* set PSC and ARR */
	TIM_X->PSC = config->PSC;
	TIM_X->ARR = config->ARR;
	
	/* enable interrupt if necessary */
	if (config->enableInterrupt) {
		/* UIE bit in TIMx_DIER register */
		TIM_X->DIER |= 0b1;
		/* clear UIF */
		TIM_X->SR &= ~(0b1);
		/* enable NVIC */
		__disable_irq();
		NVIC_EnableIRQ(getTIM_IRQn(timer));
		__enable_irq();
	}
	
	/* enable counter */
	TIM_X->CR1 |= 0b1;
	return TIM_OK;
}


uint8_t TIM_hasUpdated(TIM_TIMER_State timer, uint8_t reset_flag) {
	/* UIF bit is in the TIMx_SR register */
	TIM_TypeDef* TIM_X = getTIM(timer);
	uint8_t UIF = (TIM_X->SR & 0b1);
	if (reset_flag && UIF == 1) TIM_X->SR &= ~(0b1);
	return UIF;
}


TIM_Status_State TIM_resetEventFlag(TIM_TIMER_State timer) {
	/* check args */
	if (!( (timer <= 5 && timer >= 0) || (timer <= 18 && timer >= 16) || timer == 11 || timer == 13))
		return TIM_INVALID_ARGS;
	
	/* set UIF flag in TIMx_SR register to 0 */
	TIM_TypeDef* TIM_X = getTIM(timer);
	TIM_X->SR &= ~(0b1);
	return TIM_OK;
}