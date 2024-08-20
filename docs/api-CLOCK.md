# group `CLOCK` {#group___c_l_o_c_k}

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`enum `[`CLOCK_MCO_SELECT_State`](#group___c_l_o_c_k_1ga8fab271b291b83bd742e9099a9f20a59)            | Enum representing which clock is to be outputted to the Master Clock Output (MCO) pin.
`enum `[`CLOCK_MCO_PRESCALER_State`](#group___c_l_o_c_k_1gaaa0363e0e9775584599d94565f8e0e60)            | Enum representing a prescaler choice for the MCO output.
`enum `[`CLOCK_State`](#group___c_l_o_c_k_1ga63d31f75868a8d1e3b998ac5df3f6a36)            | Enum representing a choice of clock for activating and desactivating.
`enum `[`CLOCK_PLL_SOURCE_State`](#group___c_l_o_c_k_1gaceb416b702f94d30e139e49e8e10a76f)            | Enum representing a choice of clock as source for PLL.
`enum `[`CLOCK_PLLR_State`](#group___c_l_o_c_k_1ga9b771949ba6bccb42317a3e5e089cded)            | Enum representing choices for the PLL_R parameter.
`enum `[`CLOCK_Status_State`](#group___c_l_o_c_k_1ga5aa3fa30a332173aafcc460104d0a159)            | Enum representing the status of a function.
`enum `[`CLOCK_SYSCLK_State`](#group___c_l_o_c_k_1gab8ea3cd345873e8a031469d82633ee72)            | Enum representing clocks which can be chosen as the system clock.
`enum `[`CLOCK_AHB_PRESCALER_State`](#group___c_l_o_c_k_1ga8243c8d8e6717062f9949ee373a4a77f)            | Enum representing different values for the AHB prescaler.
`enum `[`CLOCK_APB1_PRESCALER_State`](#group___c_l_o_c_k_1ga65e4b024aee4244fb32f8c5c4ff05f9a)            | Enum representing different values for the APB1 prescaler.
`enum `[`CLOCK_APB2_PRESCALER_State`](#group___c_l_o_c_k_1ga95ae2e15b49c96956d53beae3975e517)            | Enum representing different values for the APB1 prescaler.
`public `[`CLOCK_Status_State`](api-undefined.md#group___c_l_o_c_k_1ga5aa3fa30a332173aafcc460104d0a159)` `[`CLOCK_activateMCO`](#group___c_l_o_c_k_1ga625103ea87a9510c347baaf2126d27e3)`(`[`GPIO_Port`](api-undefined.md#group___g_p_i_o_1gaf164c756418dde00ac07fd47d0962150)` port,uint8_t pin,`[`CLOCK_MCO_SELECT_State`](api-undefined.md#group___c_l_o_c_k_1ga8fab271b291b83bd742e9099a9f20a59)` mco_sel_state,`[`CLOCK_MCO_PRESCALER_State`](api-undefined.md#group___c_l_o_c_k_1gaaa0363e0e9775584599d94565f8e0e60)` mco_pre_state)`            | Activates the Master Clock Output pin to the selected output state.
`public `[`CLOCK_Status_State`](api-undefined.md#group___c_l_o_c_k_1ga5aa3fa30a332173aafcc460104d0a159)` `[`CLOCK_configPLL`](#group___c_l_o_c_k_1gaa11ce7252db60000e142bc3ff6aff0be)`(`[`CLOCK_PLL_SOURCE_State`](api-undefined.md#group___c_l_o_c_k_1gaceb416b702f94d30e139e49e8e10a76f)` pll_src,uint8_t PLL_M,uint8_t PLL_N,`[`CLOCK_PLLR_State`](api-undefined.md#group___c_l_o_c_k_1ga9b771949ba6bccb42317a3e5e089cded)` PLL_R)`            | Configures the PLL clock so that it may be used as the System clock.
`public uint8_t `[`CLOCK_isActivated`](#group___c_l_o_c_k_1gae9cd115f3011d6546563628b1da16eb4)`(`[`CLOCK_State`](api-undefined.md#group___c_l_o_c_k_1ga63d31f75868a8d1e3b998ac5df3f6a36)` clk)`            | Checks if a clock is activated or not by reading from RCC control registers.
`public `[`CLOCK_Status_State`](api-undefined.md#group___c_l_o_c_k_1ga5aa3fa30a332173aafcc460104d0a159)` `[`CLOCK_activateClk`](#group___c_l_o_c_k_1ga08716e6071c93768a4091dc5947e104f)`(`[`CLOCK_State`](api-undefined.md#group___c_l_o_c_k_1ga63d31f75868a8d1e3b998ac5df3f6a36)` clk)`            | Activates a desired clock.
`public `[`CLOCK_Status_State`](api-undefined.md#group___c_l_o_c_k_1ga5aa3fa30a332173aafcc460104d0a159)` `[`CLOCK_desactivateClk`](#group___c_l_o_c_k_1ga34f1183e02b1e5320ccf45c6e646b918)`(`[`CLOCK_State`](api-undefined.md#group___c_l_o_c_k_1ga63d31f75868a8d1e3b998ac5df3f6a36)` clk)`            | Desactivates a desired clock.
`public uint32_t `[`CLOCK_getPLLClockSpeed`](#group___c_l_o_c_k_1ga50f2307ce6d6b1285d62ba0fc709f680)`()`            | Gets the speed (frequency) in Hz of the PLL clock, if it is activated.
`public uint32_t `[`CLOCK_getMSIClockSpeed`](#group___c_l_o_c_k_1ga353083c3916c8933c43eb0a1c5c94052)`()`            | Gets the speed (frequency) in Hz of the MSI (Multi-Speed Internal) clock.
`public void `[`CLOCK_setHSEClockSpeed`](#group___c_l_o_c_k_1ga6da82f8e33ab80367bf38ea54592f240)`(uint32_t speed)`            | Set the speed of the external clock oscillator, if one is available.
`public uint32_t `[`CLOCK_getHSEClockSpeed`](#group___c_l_o_c_k_1gab7188c2da80700782ba6b028486e269c)`()`            | Gets the speed (frequency) in Hz of the HSE (High-Speed External) clock.
`public uint32_t `[`CLOCK_getSystemClockSpeed`](#group___c_l_o_c_k_1gada0674018763aa72b723804b8d8183eb)`()`            | Gets the speed (frequency) in Hz of the system clock.
`public `[`CLOCK_Status_State`](api-undefined.md#group___c_l_o_c_k_1ga5aa3fa30a332173aafcc460104d0a159)` `[`CLOCK_setSystemClock`](#group___c_l_o_c_k_1gad3f9097ce53adfff82cb70ddea07c27d)`(`[`CLOCK_SYSCLK_State`](api-undefined.md#group___c_l_o_c_k_1gab8ea3cd345873e8a031469d82633ee72)` sysclk)`            | Sets the system clock.
`public `[`CLOCK_Status_State`](api-undefined.md#group___c_l_o_c_k_1ga5aa3fa30a332173aafcc460104d0a159)` `[`CLOCK_setAHBPrescaler`](#group___c_l_o_c_k_1ga45f0f137fec72ca25a15471c536353ff)`(`[`CLOCK_AHB_PRESCALER_State`](api-undefined.md#group___c_l_o_c_k_1ga8243c8d8e6717062f9949ee373a4a77f)` ahb_prescaler)`            | Set the AHB prescaler for the AHB clock (HCLK).
`public `[`CLOCK_Status_State`](api-undefined.md#group___c_l_o_c_k_1ga5aa3fa30a332173aafcc460104d0a159)` `[`CLOCK_setAPB1Prescaler`](#group___c_l_o_c_k_1ga7eb6ba8a0c4959ea023982ff86287e5c)`(`[`CLOCK_APB1_PRESCALER_State`](api-undefined.md#group___c_l_o_c_k_1ga65e4b024aee4244fb32f8c5c4ff05f9a)` apb1_prescaler)`            | Set the APB1 prescaler for the APB1 clock (PCLK1).
`public `[`CLOCK_Status_State`](api-undefined.md#group___c_l_o_c_k_1ga5aa3fa30a332173aafcc460104d0a159)` `[`CLOCK_setAPB2Prescaler`](#group___c_l_o_c_k_1gaf2d3189cd4e74510c8d2136149148e0c)`(`[`CLOCK_APB2_PRESCALER_State`](api-undefined.md#group___c_l_o_c_k_1ga95ae2e15b49c96956d53beae3975e517)` apb2_prescaler)`            | Set the APB2 prescaler for the APB2 clock (PCLK2).

## Members

#### `enum `[`CLOCK_MCO_SELECT_State`](#group___c_l_o_c_k_1ga8fab271b291b83bd742e9099a9f20a59) {#group___c_l_o_c_k_1ga8fab271b291b83bd742e9099a9f20a59}

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
CLOCK_MCO_SELECT_NONE            | MCO output disabled, no clock on MCO.
CLOCK_MCO_SELECT_SYSCLK            | SYSCLK system clock selected.
CLOCK_MCO_SELECT_MSI            | MSI clock selected.
CLOCK_MCO_SELECT_HSI16            | HSI16 clock selected.
CLOCK_MCO_SELECT_HSE            | HSE clock selected.
CLOCK_MCO_SELECT_PLL            | Main PLL clock selected.
CLOCK_MCO_SELECT_LSI            | LSI clock selected.
CLOCK_MCO_SELECT_LSE            | LSE clock selected.
CLOCK_MCO_SELECT_HSI48            | Internal HSI48 clock selected.

Enum representing which clock is to be outputted to the Master Clock Output (MCO) pin.

#### `enum `[`CLOCK_MCO_PRESCALER_State`](#group___c_l_o_c_k_1gaaa0363e0e9775584599d94565f8e0e60) {#group___c_l_o_c_k_1gaaa0363e0e9775584599d94565f8e0e60}

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
CLOCK_MCO_PRE_DIV_1            | MCO is divided by 1.
CLOCK_MCO_PRE_DIV_2            | MCO is divided by 2.
CLOCK_MCO_PRE_DIV_4            | MCO is divided by 4.
CLOCK_MCO_PRE_DIV_8            | MCO is divided by 8.
CLOCK_MCO_PRE_DIV_16            | MCO is divided by 16.

Enum representing a prescaler choice for the MCO output.

#### `enum `[`CLOCK_State`](#group___c_l_o_c_k_1ga63d31f75868a8d1e3b998ac5df3f6a36) {#group___c_l_o_c_k_1ga63d31f75868a8d1e3b998ac5df3f6a36}

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
CLOCK_MSI            | The MSI clock is to be activated or desactivated.
CLOCK_LSE            | The LSE clock is to be activated or desactivated.
CLOCK_HSI            | The HSI clock is to be activated or desactivated.
CLOCK_HSE            | The HSE clock is to be activated or desactivated.
CLOCK_PLL            | The PLL clock is to be activated or desactivated.
CLOCK_PLLSAI1            | The PLLSAI1 clock is to be activated or desactivated.
CLOCK_PLLSAI2            | The PLLSAI2 clock is to be activated or desactivated.

Enum representing a choice of clock for activating and desactivating.

#### `enum `[`CLOCK_PLL_SOURCE_State`](#group___c_l_o_c_k_1gaceb416b702f94d30e139e49e8e10a76f) {#group___c_l_o_c_k_1gaceb416b702f94d30e139e49e8e10a76f}

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
CLOCK_PLL_SRC_NONE            | The source clock for the PLL is not selected.
CLOCK_PLL_SRC_MSI            | The source clock for the PLL is MSI.
CLOCK_PLL_SRC_HSI16            | The source clock for the PLL is HSI16.
CLOCK_PLL_SRC_HSE            | The source clock for the PLL is HSE.

Enum representing a choice of clock as source for PLL.

#### `enum `[`CLOCK_PLLR_State`](#group___c_l_o_c_k_1ga9b771949ba6bccb42317a3e5e089cded) {#group___c_l_o_c_k_1ga9b771949ba6bccb42317a3e5e089cded}

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
CLOCK_PLLR_2            | PLL_R is set to 2.
CLOCK_PLLR_4            | PLL_R is set to 4.
CLOCK_PLLR_6            | PLL_R is set to 6.
CLOCK_PLLR_8            | PLL_R is set to 8.

Enum representing choices for the PLL_R parameter.

#### `enum `[`CLOCK_Status_State`](#group___c_l_o_c_k_1ga5aa3fa30a332173aafcc460104d0a159) {#group___c_l_o_c_k_1ga5aa3fa30a332173aafcc460104d0a159}

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
CLOCK_OK            | Indicates that a function has returned successfully.
CLOCK_INVALID_ARGS            | Indicates that a function has been given invalid (out of range) arguments.
CLOCK_ERROR            | Indicates that a general error has occured.

Enum representing the status of a function.

#### `enum `[`CLOCK_SYSCLK_State`](#group___c_l_o_c_k_1gab8ea3cd345873e8a031469d82633ee72) {#group___c_l_o_c_k_1gab8ea3cd345873e8a031469d82633ee72}

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
CLOCK_SYSCLK_MSI            | MSI selected as system clock.
CLOCK_SYSCLK_HSI16            | HSI16 selected as system clock.
CLOCK_SYSCLK_HSE            | HSE selected as system clock.
CLOCK_SYSCLK_PLL            | PLL selected as system clock.

Enum representing clocks which can be chosen as the system clock.

#### `enum `[`CLOCK_AHB_PRESCALER_State`](#group___c_l_o_c_k_1ga8243c8d8e6717062f9949ee373a4a77f) {#group___c_l_o_c_k_1ga8243c8d8e6717062f9949ee373a4a77f}

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
CLOCK_AHB_PRE_DIV_1            | SYSCLK divided by 1.
CLOCK_AHB_PRE_DIV_2            | SYSCLK divided by 2.
CLOCK_AHB_PRE_DIV_4            | SYSCLK divided by 4.
CLOCK_AHB_PRE_DIV_8            | SYSCLK divided by 8.
CLOCK_AHB_PRE_DIV_16            | SYSCLK divided by 16.
CLOCK_AHB_PRE_DIV_64            | SYSCLK divided by 64.
CLOCK_AHB_PRE_DIV_128            | SYSCLK divided by 128.
CLOCK_AHB_PRE_DIV_256            | SYSCLK divided by 256.
CLOCK_AHB_PRE_DIV_512            | SYSCLK divided by 512.

Enum representing different values for the AHB prescaler.

#### `enum `[`CLOCK_APB1_PRESCALER_State`](#group___c_l_o_c_k_1ga65e4b024aee4244fb32f8c5c4ff05f9a) {#group___c_l_o_c_k_1ga65e4b024aee4244fb32f8c5c4ff05f9a}

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
CLOCK_APB1_PRE_DIV_1            | SYSCLK divided by 1.
CLOCK_APB1_PRE_DIV_2            | HCLK divided by 2.
CLOCK_APB1_PRE_DIV_4            | HCLK divided by 4.
CLOCK_APB1_PRE_DIV_8            | HCLK divided by 8.
CLOCK_APB1_PRE_DIV_16            | HCLK divided by 16.

Enum representing different values for the APB1 prescaler.

#### `enum `[`CLOCK_APB2_PRESCALER_State`](#group___c_l_o_c_k_1ga95ae2e15b49c96956d53beae3975e517) {#group___c_l_o_c_k_1ga95ae2e15b49c96956d53beae3975e517}

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
CLOCK_APB2_PRE_DIV_1            | SYSCLK divided by 1.
CLOCK_APB2_PRE_DIV_2            | HCLK divided by 2.
CLOCK_APB2_PRE_DIV_4            | HCLK divided by 4.
CLOCK_APB2_PRE_DIV_8            | HCLK divided by 8.
CLOCK_APB2_PRE_DIV_16            | HCLK divided by 16.

Enum representing different values for the APB1 prescaler.

#### `public `[`CLOCK_Status_State`](api-undefined.md#group___c_l_o_c_k_1ga5aa3fa30a332173aafcc460104d0a159)` `[`CLOCK_activateMCO`](#group___c_l_o_c_k_1ga625103ea87a9510c347baaf2126d27e3)`(`[`GPIO_Port`](api-undefined.md#group___g_p_i_o_1gaf164c756418dde00ac07fd47d0962150)` port,uint8_t pin,`[`CLOCK_MCO_SELECT_State`](api-undefined.md#group___c_l_o_c_k_1ga8fab271b291b83bd742e9099a9f20a59)` mco_sel_state,`[`CLOCK_MCO_PRESCALER_State`](api-undefined.md#group___c_l_o_c_k_1gaaa0363e0e9775584599d94565f8e0e60)` mco_pre_state)` {#group___c_l_o_c_k_1ga625103ea87a9510c347baaf2126d27e3}

Activates the Master Clock Output pin to the selected output state.

#### Parameters
* `port` port for the MCO pin. 

* `pin` pin number of the MCO pin. 

* `mco_sel_state` which clock should be outputed to MCO. 

* `mco_pre_state` prescaler for the MCO (divisions by powers of 2 up to 16 allowed). 

#### Returns
status 

Untested function due to lack of proper oscilloscope. 

Desired clock (mco_sel_state) needs to be properly activated via the RCC_CR register before use of this function. By default SYSCLK is already activated.

#### `public `[`CLOCK_Status_State`](api-undefined.md#group___c_l_o_c_k_1ga5aa3fa30a332173aafcc460104d0a159)` `[`CLOCK_configPLL`](#group___c_l_o_c_k_1gaa11ce7252db60000e142bc3ff6aff0be)`(`[`CLOCK_PLL_SOURCE_State`](api-undefined.md#group___c_l_o_c_k_1gaceb416b702f94d30e139e49e8e10a76f)` pll_src,uint8_t PLL_M,uint8_t PLL_N,`[`CLOCK_PLLR_State`](api-undefined.md#group___c_l_o_c_k_1ga9b771949ba6bccb42317a3e5e089cded)` PLL_R)` {#group___c_l_o_c_k_1gaa11ce7252db60000e142bc3ff6aff0be}

Configures the PLL clock so that it may be used as the System clock.

#### Parameters
* `pll_src` selects which clock will drive the PLL 

* `PLL_M` divsion factor for the main PLL clock. 1 <= PLL_M <= 16. 

* `PLL_N` main PLL multiplication factor. 8 <= PLLN <= 127. 

* `PLL_R` divsion factor for the main PLL clock. PLLR = {2, 4, 6, 8}. 

#### Returns
status 

This function can only be called if the PLL clock is disabled. Use [CLOCK_isActivated()](api-undefined.md#group___c_l_o_c_k_1gae9cd115f3011d6546563628b1da16eb4) and [CLOCK_desactivateClk()](api-undefined.md#group___c_l_o_c_k_1ga34f1183e02b1e5320ccf45c6e646b918) before calling this function.

#### `public uint8_t `[`CLOCK_isActivated`](#group___c_l_o_c_k_1gae9cd115f3011d6546563628b1da16eb4)`(`[`CLOCK_State`](api-undefined.md#group___c_l_o_c_k_1ga63d31f75868a8d1e3b998ac5df3f6a36)` clk)` {#group___c_l_o_c_k_1gae9cd115f3011d6546563628b1da16eb4}

Checks if a clock is activated or not by reading from RCC control registers.

#### Parameters
* `clk` which clock to check 

#### Parameters
* `0` the clock is not activated 

* `1` the clock is activated 

This function does not check correctness of arguments. This responsibility is given to the caller.

#### `public `[`CLOCK_Status_State`](api-undefined.md#group___c_l_o_c_k_1ga5aa3fa30a332173aafcc460104d0a159)` `[`CLOCK_activateClk`](#group___c_l_o_c_k_1ga08716e6071c93768a4091dc5947e104f)`(`[`CLOCK_State`](api-undefined.md#group___c_l_o_c_k_1ga63d31f75868a8d1e3b998ac5df3f6a36)` clk)` {#group___c_l_o_c_k_1ga08716e6071c93768a4091dc5947e104f}

Activates a desired clock.

#### Parameters
* `clk` clock to be activated 

#### Returns
status 

Untested function. 

Blocking function. Will only return once a 'RDY' flag has been raised by the clock hardware (clock stabilized). 

For the PLL clock, it is necessary to call [CLOCK_configPLL()](api-undefined.md#group___c_l_o_c_k_1gaa11ce7252db60000e142bc3ff6aff0be) first before calling this function.

#### `public `[`CLOCK_Status_State`](api-undefined.md#group___c_l_o_c_k_1ga5aa3fa30a332173aafcc460104d0a159)` `[`CLOCK_desactivateClk`](#group___c_l_o_c_k_1ga34f1183e02b1e5320ccf45c6e646b918)`(`[`CLOCK_State`](api-undefined.md#group___c_l_o_c_k_1ga63d31f75868a8d1e3b998ac5df3f6a36)` clk)` {#group___c_l_o_c_k_1ga34f1183e02b1e5320ccf45c6e646b918}

Desactivates a desired clock.

#### Parameters
* `clk` clock to be desactivated. 

#### Returns
status 

Untested function.

#### `public uint32_t `[`CLOCK_getPLLClockSpeed`](#group___c_l_o_c_k_1ga50f2307ce6d6b1285d62ba0fc709f680)`()` {#group___c_l_o_c_k_1ga50f2307ce6d6b1285d62ba0fc709f680}

Gets the speed (frequency) in Hz of the PLL clock, if it is activated.

#### Returns
frequency of PLL clock in Hz. If return value is 0, then PLL is not activated or has invalid PLL_N, PLL_M or PLL_R constants.

#### `public uint32_t `[`CLOCK_getMSIClockSpeed`](#group___c_l_o_c_k_1ga353083c3916c8933c43eb0a1c5c94052)`()` {#group___c_l_o_c_k_1ga353083c3916c8933c43eb0a1c5c94052}

Gets the speed (frequency) in Hz of the MSI (Multi-Speed Internal) clock.

#### Returns
frequency of MSI clock in Hz.

#### `public void `[`CLOCK_setHSEClockSpeed`](#group___c_l_o_c_k_1ga6da82f8e33ab80367bf38ea54592f240)`(uint32_t speed)` {#group___c_l_o_c_k_1ga6da82f8e33ab80367bf38ea54592f240}

Set the speed of the external clock oscillator, if one is available.

#### Parameters
* `speed` (in Hz) of the HSE

#### `public uint32_t `[`CLOCK_getHSEClockSpeed`](#group___c_l_o_c_k_1gab7188c2da80700782ba6b028486e269c)`()` {#group___c_l_o_c_k_1gab7188c2da80700782ba6b028486e269c}

Gets the speed (frequency) in Hz of the HSE (High-Speed External) clock.

#### Returns
frequency of HSE clock in Hz.

#### `public uint32_t `[`CLOCK_getSystemClockSpeed`](#group___c_l_o_c_k_1gada0674018763aa72b723804b8d8183eb)`()` {#group___c_l_o_c_k_1gada0674018763aa72b723804b8d8183eb}

Gets the speed (frequency) in Hz of the system clock.

The system clock can either be: MSI, HSI16, HSE or PLL. 
#### Returns
frequency of the system clock in Hz.

#### `public `[`CLOCK_Status_State`](api-undefined.md#group___c_l_o_c_k_1ga5aa3fa30a332173aafcc460104d0a159)` `[`CLOCK_setSystemClock`](#group___c_l_o_c_k_1gad3f9097ce53adfff82cb70ddea07c27d)`(`[`CLOCK_SYSCLK_State`](api-undefined.md#group___c_l_o_c_k_1gab8ea3cd345873e8a031469d82633ee72)` sysclk)` {#group___c_l_o_c_k_1gad3f9097ce53adfff82cb70ddea07c27d}

Sets the system clock.

#### Parameters
* `sysclk` The system clock to be selected 

#### Returns
status 

This function assumes that the clock has already been activated via [CLOCK_activateClk()](api-undefined.md#group___c_l_o_c_k_1ga08716e6071c93768a4091dc5947e104f). 

Blocking function. Will only return once a SWS flag has been set by hardware in the RCC_CFGR register.

#### `public `[`CLOCK_Status_State`](api-undefined.md#group___c_l_o_c_k_1ga5aa3fa30a332173aafcc460104d0a159)` `[`CLOCK_setAHBPrescaler`](#group___c_l_o_c_k_1ga45f0f137fec72ca25a15471c536353ff)`(`[`CLOCK_AHB_PRESCALER_State`](api-undefined.md#group___c_l_o_c_k_1ga8243c8d8e6717062f9949ee373a4a77f)` ahb_prescaler)` {#group___c_l_o_c_k_1ga45f0f137fec72ca25a15471c536353ff}

Set the AHB prescaler for the AHB clock (HCLK).

This clocks feeds the AHB1 and AHB2 buses. 
#### Parameters
* `ahb_prescaler` choice for the AHB_PRE value. 

#### Returns
status

#### `public `[`CLOCK_Status_State`](api-undefined.md#group___c_l_o_c_k_1ga5aa3fa30a332173aafcc460104d0a159)` `[`CLOCK_setAPB1Prescaler`](#group___c_l_o_c_k_1ga7eb6ba8a0c4959ea023982ff86287e5c)`(`[`CLOCK_APB1_PRESCALER_State`](api-undefined.md#group___c_l_o_c_k_1ga65e4b024aee4244fb32f8c5c4ff05f9a)` apb1_prescaler)` {#group___c_l_o_c_k_1ga7eb6ba8a0c4959ea023982ff86287e5c}

Set the APB1 prescaler for the APB1 clock (PCLK1).

This clocks feeds the AHB1 and AHB2 buses. 
#### Parameters
* `apb1_prescaler` choice for the APB1_PRE value. 

#### Returns
status

#### `public `[`CLOCK_Status_State`](api-undefined.md#group___c_l_o_c_k_1ga5aa3fa30a332173aafcc460104d0a159)` `[`CLOCK_setAPB2Prescaler`](#group___c_l_o_c_k_1gaf2d3189cd4e74510c8d2136149148e0c)`(`[`CLOCK_APB2_PRESCALER_State`](api-undefined.md#group___c_l_o_c_k_1ga95ae2e15b49c96956d53beae3975e517)` apb2_prescaler)` {#group___c_l_o_c_k_1gaf2d3189cd4e74510c8d2136149148e0c}

Set the APB2 prescaler for the APB2 clock (PCLK2).

This clocks feeds the AHB1 and AHB2 buses. 
#### Parameters
* `apb2_prescaler` choice for the APB2_PRE value. 

#### Returns
status

