#include "clock.h"

/***
*
* Clock drivers for stm32l4xx devices.
* WARNING: These drivers have NOT been tested extensively. Use at own risk.
* Reference: https://www.youtube.com/playlist?list=PLtVUYRe-Z-mfKO0lg_-MBvwWl6VjWT8Dt
*
***/

/****************************************************************************************************/
/*			              PRIVATE FUNCTIONS                                             */
/****************************************************************************************************/
static int HSE_CLOCK_SPEED = 0;
static int FLASH_MAX_FREQUENCY = 20000000; ///< Maximum memory accessing frequency for FLASH. See section 3.3.3 of RM0432
static int MAX_CLOCK_SPEED = 120000000;

static int getClkSpeed(CLOCK_SYSCLK_State clk);

/** Gets the speed of the input clock. The input clock needs to be a possible sysclk.
*/
static int getClkSpeed(CLOCK_SYSCLK_State clk) {
		switch (clk) {
		case 0:
			/* MSI selected as SYSCLK */
			return CLOCK_getMSIClockSpeed();
		
		case 1:
			/* HSI16 selected as SYSCLK */
			return 16000000;
		
		case 2:
			/* HSE selected as SYSCLK */
			return CLOCK_getHSEClockSpeed();
		
		case 3:
			/* PLL_CLK selected as SYSCLK */
			return CLOCK_getPLLClockSpeed();
	}
}

/****************************************************************************************************/
/*			              EXPORTED FUNCTIONS                                            */
/****************************************************************************************************/


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

int CLOCK_getPLLClockSpeed() {
	int clkSpeed = 0;
	/* see RCC_PLLCFGR documentation in reference manual */
	char PLL_M = ((RCC->PLLCFGR >> 4) & (0b1111)) + 1; 
	char PLL_N = (RCC->PLLCFGR >> 8) & (0b111111);
	char PLL_R = (((RCC->PLLCFGR >> 25) & (0b11)) + 1)*2;
	/* get pll_src */
	CLOCK_PLL_SOURCE_State pllSrc = RCC->PLLCFGR & 0b11;
	
	if (pllSrc == CLOCK_PLL_SRC_NONE) {
		return clkSpeed;
	} else if (pllSrc == CLOCK_PLL_SRC_MSI) {
		clkSpeed = CLOCK_getMSIClockSpeed();
	} else if (pllSrc == CLOCK_PLL_SRC_HSI16) {
		clkSpeed = 16000000;
  } else {
		clkSpeed = CLOCK_getHSEClockSpeed();
	}
	return clkSpeed * PLL_N / (PLL_M * PLL_R);
}

int CLOCK_getMSIClockSpeed() {
	/* read from MSIRANGE and determine frequency according to range, see reference manual */
	char msiRange = (RCC->CR >> 4) & (0b1111);
	switch (msiRange) {
		case 0:
			return 100000;
		case 1:
			return 200000;
		case 2:
			return 400000;
		case 3:
			return 800000;
		case 4:
			return 1000000;
		case 5:
			return 2000000;
		case 6:
			return 4000000;
		case 7:
			return 8000000;
		case 8:
			return 16000000;
		case 9:
			return 24000000;
		case 10:
			return 32000000;
		case 11:
			return 48000000;
		default:
			return 0;
	}
}

int CLOCK_getSystemClockSpeed() {
	char SWS = (RCC->CFGR >> 2) & (0b11);
	return getClkSpeed(SWS);
}

void CLOCK_setHSEClockSpeed(int speed) {
	HSE_CLOCK_SPEED = speed;
}


int CLOCK_getHSEClockSpeed() {
	return HSE_CLOCK_SPEED;
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
	
	/* Check if the speed is not too high */
	if (CLOCK_getPLLClockSpeed() > MAX_CLOCK_SPEED)
		return CLOCK_ERROR;
	
	/* Need to enable the PLL clock to be used as the main system clock */
	RCC->PLLCFGR |= (0b1 << 24);
	
	return CLOCK_OK;
}

CLOCK_Status_State CLOCK_setSystemClock(CLOCK_SYSCLK_State sysclk) {
	/* check args */
	if (!(sysclk <= 3 && sysclk >= 0))
		return CLOCK_INVALID_ARGS;	
	
	/* get the speed of the desired clock */
	int desiredSpeed = getClkSpeed(sysclk);
	
	if (desiredSpeed > MAX_CLOCK_SPEED)
		return CLOCK_ERROR;
	
	/* for freq. higher than 80 MHz, activate Range 1 boost mode. otherwise Range 1 normal mode */
	if (desiredSpeed >= 80000000) PWR->CR5 &= ~(0b1 << 8);
	else PWR -> CR5 |= (0b1 << 8);
	
	/* set the ACR flash register to enable extra wait states to compensate for high sys clock speeds */
	char numWaitStates = desiredSpeed/FLASH_MAX_FREQUENCY;
	FLASH->ACR &= ~(0b1111);
	FLASH->ACR |= numWaitStates;
	while(!((FLASH->ACR & 0b1111) == numWaitStates));
	
	/* set prefetch enable */
	FLASH->ACR |= (0b1 << 8);
	
	/* set the SW bits in RCC_CFGR register */
	RCC->CFGR &= ~(0b11);
	RCC->CFGR |= sysclk;
	
	/* poll for SWS to change */
	while(!((RCC->CFGR >> 2 & 0b11) == sysclk));
	return CLOCK_OK;
}
