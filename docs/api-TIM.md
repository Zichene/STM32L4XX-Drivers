# group `TIM` {#group___t_i_m}

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`enum `[`TIM_TIMER_State`](#group___t_i_m_1ga5b31ce769abb7de5285cb952034a6629)            | Enum representing different timers on the chip.
`enum `[`TIM_Status_State`](#group___t_i_m_1gaa7bb33976f8d2b8535cb20917287e529)            | Enum representing different function return statuses.
`public `[`TIM_Status_State`](api-undefined.md#group___t_i_m_1gaa7bb33976f8d2b8535cb20917287e529)` `[`TIM_enablePeripheralClk`](#group___t_i_m_1ga7e436dcd8d1f9df35649297fc25de9c9)`(`[`TIM_TIMER_State`](api-undefined.md#group___t_i_m_1ga5b31ce769abb7de5285cb952034a6629)` timer)`            | Enable the peripheral clock for a timer by changing the bit on the APB1ENR or APB2ENR registers.
`public `[`TIM_Status_State`](api-undefined.md#group___t_i_m_1gaa7bb33976f8d2b8535cb20917287e529)` `[`TIM_disablePeripheralClk`](#group___t_i_m_1ga51fa45a8ad8271045073f95c61a75574)`(`[`TIM_TIMER_State`](api-undefined.md#group___t_i_m_1ga5b31ce769abb7de5285cb952034a6629)` timer)`            | Disable the peripheral clock for a timer by changing the bit on the APB1ENR or APB2ENR registers.
`public `[`TIM_Status_State`](api-undefined.md#group___t_i_m_1gaa7bb33976f8d2b8535cb20917287e529)` `[`TIM_config`](#group___t_i_m_1ga3ecfed8e3ce677c6f663d0dbec8219c4)`(`[`TIM_Config_Typedef`](api-TIM.md#struct_t_i_m___config___typedef)` * config)`            | Configure a timer with desired config parameters.
`public `[`TIM_Status_State`](api-undefined.md#group___t_i_m_1gaa7bb33976f8d2b8535cb20917287e529)` `[`TIM_startTimer`](#group___t_i_m_1ga9b79b449a6bad1fdcd3553cb8ad1787c)`(`[`TIM_TIMER_State`](api-undefined.md#group___t_i_m_1ga5b31ce769abb7de5285cb952034a6629)` timer)`            | Starts the timer by setting the CEN bit in the TIMx_CR1 register.
`public `[`TIM_Status_State`](api-undefined.md#group___t_i_m_1gaa7bb33976f8d2b8535cb20917287e529)` `[`TIM_stopTimer`](#group___t_i_m_1ga469e7c7abf13151452b4280eed1c7f24)`(`[`TIM_TIMER_State`](api-undefined.md#group___t_i_m_1ga5b31ce769abb7de5285cb952034a6629)` timer)`            | Stops the timer by setting the CEN bit in the TIMx_CR1 register.
`public uint8_t `[`TIM_hasUpdated`](#group___t_i_m_1ga9aefba36c49823c04220ebffd9426f81)`(`[`TIM_TIMER_State`](api-undefined.md#group___t_i_m_1ga5b31ce769abb7de5285cb952034a6629)` timer,uint8_t reset_flag)`            | Checks the update interrupt flag (UIF) in the TIMx_SR register.
`public `[`TIM_Status_State`](api-undefined.md#group___t_i_m_1gaa7bb33976f8d2b8535cb20917287e529)` `[`TIM_resetEventFlag`](#group___t_i_m_1ga678b5813bb7929232e9346038a6c756d)`(`[`TIM_TIMER_State`](api-undefined.md#group___t_i_m_1ga5b31ce769abb7de5285cb952034a6629)` timer)`            | Resets the UIF flag in the TIMx_SR register.
`struct `[`TIM_Config_Typedef`](#struct_t_i_m___config___typedef) | 

## Members

#### `enum `[`TIM_TIMER_State`](#group___t_i_m_1ga5b31ce769abb7de5285cb952034a6629) {#group___t_i_m_1ga5b31ce769abb7de5285cb952034a6629}

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
TIM_TIM1            | 
TIM_TIM2            | 
TIM_TIM3            | 
TIM_TIM4            | 
TIM_TIM5            | 
TIM_TIM6            | 
TIM_TIM7            | 
TIM_TIM8            | 
TIM_TIM15            | 
TIM_TIM16            | 
TIM_TIM17            | 

Enum representing different timers on the chip.

Timers 2-8 inclusive are connected to APB1 bus. Timers 1 and 15-17 inclusive are connected to the APB2 bus.

#### `enum `[`TIM_Status_State`](#group___t_i_m_1gaa7bb33976f8d2b8535cb20917287e529) {#group___t_i_m_1gaa7bb33976f8d2b8535cb20917287e529}

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
TIM_OK            | Indicates that a function has returned successfully.
TIM_INVALID_ARGS            | Indicates that a function has been given invalid (out of range) arguments.
TIM_ERROR            | Indicates that a general error has occured.

Enum representing different function return statuses.

#### `public `[`TIM_Status_State`](api-undefined.md#group___t_i_m_1gaa7bb33976f8d2b8535cb20917287e529)` `[`TIM_enablePeripheralClk`](#group___t_i_m_1ga7e436dcd8d1f9df35649297fc25de9c9)`(`[`TIM_TIMER_State`](api-undefined.md#group___t_i_m_1ga5b31ce769abb7de5285cb952034a6629)` timer)` {#group___t_i_m_1ga7e436dcd8d1f9df35649297fc25de9c9}

Enable the peripheral clock for a timer by changing the bit on the APB1ENR or APB2ENR registers.

#### Parameters
* `timer` which timer to enable 

#### Returns
status

#### `public `[`TIM_Status_State`](api-undefined.md#group___t_i_m_1gaa7bb33976f8d2b8535cb20917287e529)` `[`TIM_disablePeripheralClk`](#group___t_i_m_1ga51fa45a8ad8271045073f95c61a75574)`(`[`TIM_TIMER_State`](api-undefined.md#group___t_i_m_1ga5b31ce769abb7de5285cb952034a6629)` timer)` {#group___t_i_m_1ga51fa45a8ad8271045073f95c61a75574}

Disable the peripheral clock for a timer by changing the bit on the APB1ENR or APB2ENR registers.

#### Parameters
* `timer` which timer to disable 

#### Returns
status

#### `public `[`TIM_Status_State`](api-undefined.md#group___t_i_m_1gaa7bb33976f8d2b8535cb20917287e529)` `[`TIM_config`](#group___t_i_m_1ga3ecfed8e3ce677c6f663d0dbec8219c4)`(`[`TIM_Config_Typedef`](api-TIM.md#struct_t_i_m___config___typedef)` * config)` {#group___t_i_m_1ga3ecfed8e3ce677c6f663d0dbec8219c4}

Configure a timer with desired config parameters.

See [TIM_Config_Typedef](api-TIM.md#struct_t_i_m___config___typedef) for specific parameters. 
#### Parameters
* `config` pointer to a [TIM_Config_Typedef](api-TIM.md#struct_t_i_m___config___typedef) object that contains the parameter configuration 

#### Returns
status

#### `public `[`TIM_Status_State`](api-undefined.md#group___t_i_m_1gaa7bb33976f8d2b8535cb20917287e529)` `[`TIM_startTimer`](#group___t_i_m_1ga9b79b449a6bad1fdcd3553cb8ad1787c)`(`[`TIM_TIMER_State`](api-undefined.md#group___t_i_m_1ga5b31ce769abb7de5285cb952034a6629)` timer)` {#group___t_i_m_1ga9b79b449a6bad1fdcd3553cb8ad1787c}

Starts the timer by setting the CEN bit in the TIMx_CR1 register.

#### Parameters
* `timer` timer. 

#### Returns
status

#### `public `[`TIM_Status_State`](api-undefined.md#group___t_i_m_1gaa7bb33976f8d2b8535cb20917287e529)` `[`TIM_stopTimer`](#group___t_i_m_1ga469e7c7abf13151452b4280eed1c7f24)`(`[`TIM_TIMER_State`](api-undefined.md#group___t_i_m_1ga5b31ce769abb7de5285cb952034a6629)` timer)` {#group___t_i_m_1ga469e7c7abf13151452b4280eed1c7f24}

Stops the timer by setting the CEN bit in the TIMx_CR1 register.

#### Parameters
* `timer` timer. 

#### Returns
status

#### `public uint8_t `[`TIM_hasUpdated`](#group___t_i_m_1ga9aefba36c49823c04220ebffd9426f81)`(`[`TIM_TIMER_State`](api-undefined.md#group___t_i_m_1ga5b31ce769abb7de5285cb952034a6629)` timer,uint8_t reset_flag)` {#group___t_i_m_1ga9aefba36c49823c04220ebffd9426f81}

Checks the update interrupt flag (UIF) in the TIMx_SR register.

Optionally, can choose to reset UIF to '0' if '1' is read. 
#### Parameters
* `timer` timer. 

* `reset_flag` boolean to indicate whether we want to automatically reset the UIF flag to '0'. 

#### Returns
value of the UIF flag. 

This function does not check correctness of arguments. This responsibility is given to the caller.

#### `public `[`TIM_Status_State`](api-undefined.md#group___t_i_m_1gaa7bb33976f8d2b8535cb20917287e529)` `[`TIM_resetEventFlag`](#group___t_i_m_1ga678b5813bb7929232e9346038a6c756d)`(`[`TIM_TIMER_State`](api-undefined.md#group___t_i_m_1ga5b31ce769abb7de5285cb952034a6629)` timer)` {#group___t_i_m_1ga678b5813bb7929232e9346038a6c756d}

Resets the UIF flag in the TIMx_SR register.

#### Parameters
* `timer` timer. 

#### Returns
status

# struct `TIM_Config_Typedef` {#struct_t_i_m___config___typedef}

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public `[`TIM_TIMER_State`](api-undefined.md#group___t_i_m_1ga5b31ce769abb7de5285cb952034a6629)` `[`timer`](#struct_t_i_m___config___typedef_1ad9c393e32df95af2f6d18030bf82df98) | Timer. Which timer will be configured.
`public uint16_t `[`PSC`](#struct_t_i_m___config___typedef_1a85534f33328d4a0d1c9ef82558e33f78) | Prescaler. The counter clock frequency CK_CNT is equal to fCK_PSC / (PSC[15:0] + 1).
`public uint16_t `[`ARR`](#struct_t_i_m___config___typedef_1a0cffa5dda75b6b5e4a71f4fa6915203f) | Auto-Reload register. Defines the maximum number that the timer will count up to (or down from).
`public uint8_t `[`enableInterrupt`](#struct_t_i_m___config___typedef_1a000fcbd6dead41212e3191fc83830019) | Boolean that controls whether or not the clock should generate interrupts.

## Members

#### `public `[`TIM_TIMER_State`](api-undefined.md#group___t_i_m_1ga5b31ce769abb7de5285cb952034a6629)` `[`timer`](#struct_t_i_m___config___typedef_1ad9c393e32df95af2f6d18030bf82df98) {#struct_t_i_m___config___typedef_1ad9c393e32df95af2f6d18030bf82df98}

Timer. Which timer will be configured.

#### `public uint16_t `[`PSC`](#struct_t_i_m___config___typedef_1a85534f33328d4a0d1c9ef82558e33f78) {#struct_t_i_m___config___typedef_1a85534f33328d4a0d1c9ef82558e33f78}

Prescaler. The counter clock frequency CK_CNT is equal to fCK_PSC / (PSC[15:0] + 1).

#### `public uint16_t `[`ARR`](#struct_t_i_m___config___typedef_1a0cffa5dda75b6b5e4a71f4fa6915203f) {#struct_t_i_m___config___typedef_1a0cffa5dda75b6b5e4a71f4fa6915203f}

Auto-Reload register. Defines the maximum number that the timer will count up to (or down from).

#### `public uint8_t `[`enableInterrupt`](#struct_t_i_m___config___typedef_1a000fcbd6dead41212e3191fc83830019) {#struct_t_i_m___config___typedef_1a000fcbd6dead41212e3191fc83830019}

Boolean that controls whether or not the clock should generate interrupts.

