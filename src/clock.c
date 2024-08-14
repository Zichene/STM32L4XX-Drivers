#include "clock.h"

/***
*
* Clock drivers for stm32l4xx devices.
* WARNING: These drivers have NOT been tested extensively. Use at own risk.
* Reference: https://www.youtube.com/playlist?list=PLtVUYRe-Z-mfKO0lg_-MBvwWl6VjWT8Dt
*
***/


CLOCK_Status_State CLOCK_activateMCO(GPIO_Port port, char pin, CLOCK_MCO_SELECT_State mco_sel_state, CLOCK_MCO_PRESCALER_State mco_pre_state) {
	/* check args */
	if (!(port <= 8 && port >= 0 && pin <= 15 && pin >= 0 && mco_sel_state <= 8 && mco_sel_state >= 0 && mco_pre_state <= 4 && mco_pre_state >= 0))
		return CLOCK_INVALID_ARGS;
	/* Set the pin to AF mode with very high speed */
	GPIO_setPinAF_Mode(port, pin, GPIO_PUPD_NO_PULL_UP_PULL_DOWN, GPIO_SPEED_VERY_HIGH, GPIO_OUTPUT_PUSH_PULL);
	
	/* Modify clock config register MCOSEL[3:0] */
	RCC->CFGR &= ~(0b1111 << 24);
	RCC->CFGR |= (mco_sel_state << 24);
	
	/* Modify clock config register MCOPRE[2:0] */
	RCC->CFGR &= ~(0b111 << 28);
	RCC->CFGR |= (mco_pre_state << 28);
	return CLOCK_OK;
}

CLOCK_Status_State CLOCK_activateClk(CLOCK_State clk) {
	/* check args*/
	if (!(clk == 0 || clk == 8 || clk == 16 || clk == 24 || clk == 26 || clk == 28))
			return CLOCK_INVALID_ARGS;
	if (clk == CLOCK_LSE) {
		/* for the LSE the clkON bit is in the BDCR register */
		RCC->BDCR |= (1 << clk);
		while (!(RCC->BDCR & (1 << (clk+1))));
		return CLOCK_OK;
	}
	/* normally the clkON and clkRDY flags are offset by one bit. exception is the HSI clk */
	char offset = 1;
	if (clk == CLOCK_HSI) offset=2;
	/* set clkON flag to true */
	RCC->CR |= (1 << clk);
	/* wait for clkRDY */
	while (!(RCC->CR & (1 << (clk+offset))));
	return CLOCK_OK;
}

CLOCK_Status_State CLOCK_desactivateClk(CLOCK_State clk) {
	/* check args */
	if (!(clk == 0 || clk == 8 || clk == 16 || clk == 24 || clk == 26 || clk == 28))
		return CLOCK_INVALID_ARGS;
	/* special case for the LSE clock, whose clkON bit is in the BDCR register */
	if (clk == CLOCK_LSE) {
		RCC->BDCR |= (1 << clk);
		return CLOCK_OK;
	}
	/* set clkON flag to false */
	RCC->CR &= ~(1 << clk);
	return CLOCK_OK;
	/* wait for clkRDY */
	//while (!(RCC->CR & (1 << (clk+1))));
}

int CLOCK_getSystemClockSpeed() {
	int clock_speed = 0; 
	char SWS = (RCC->CFGR >> 2) & (0b11);
	switch (SWS) {
		case 0:
			/* MSI selected as SYSCLK */
			// Need to get the MSIRANGE
			break;
		
		case 1:
			/* HSI16 selected as SYSCLK */
			break;
		
		case 2:
			/* HSE selected as SYSCLK */
			break;
		
		case 3:
			/* PLL selected as SYSCLK */
			break;
	}
	return clock_speed;
}

CLOCK_Status_State CLOCK_configPLL(CLOCK_PLL_SOURCE_State pll_src, char PLL_M, char PLL_N, CLOCK_PLLR_State PLL_R) {
	/* check args */
	if (!(pll_src <= 3 && pll_src >= 0 && PLL_M <= 16 && PLL_M >= 1 && PLL_N <= 127 && PLL_N >= 8 && PLL_R <= 3 && PLL_R >= 0))
		return CLOCK_INVALID_ARGS;
		
	/* configure pll source */
	RCC->PLLCFGR &= ~(0b11);
	RCC->PLLCFGR |= (pll_src);
	
	/* Setting PLL_M (division factor) */
	RCC->PLLCFGR &= ~(0b1111 << 4);
	RCC->PLLCFGR |= ((PLL_M-1) << 4); // for PLL_M, we need to subtract 1 
	
	/* Setting PLL_N (multiplication factor) */
	RCC->PLLCFGR &= ~(0b111111 << 8);
	RCC->PLLCFGR |= (PLL_N << 8);
	
	/* Setting PLL_R (division factor) */
	RCC->PLLCFGR &= ~(0b11 << 25);
	RCC->PLLCFGR |= (PLL_R << 25);
	
	return CLOCK_OK;
}