# `GPIO` Drivers

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`enum `[`GPIO_Port`](#group___g_p_i_o_1gaf164c756418dde00ac07fd47d0962150)            | Enum representing the port of a GPIO pin.
`enum `[`GPIO_PinState`](#group___g_p_i_o_1ga5b3ef0486b179415581eb342e0ea6b43)            | Enum representing the state of a pin.
`enum `[`GPIO_PUPD_State`](#group___g_p_i_o_1ga2266f25d4ba662cd4e40de36a5049167)            | Enum representing different PUPD states which are accepted by the GPIOx_PUPDR register.
`enum `[`GPIO_SPEED_State`](#group___g_p_i_o_1gaaf9978d8971c86f33115b493e5d6190f)            | Enum representing the speed of a GPIO pin which are accepted by the GPIOx_SPEEDR register.
`enum `[`GPIO_OUTPUT_TYPE_State`](#group___g_p_i_o_1gad95ee31148019b4ae8d63e5a3e0777ee)            | Enum representing the type of GPIO output driver which are accepted by the GPIOx_OTYPER register.
`enum `[`GPIO_AF_State`](#group___g_p_i_o_1ga50a2f4df54586ff8414f27fcb3f827db)            | Enum representing Alternate Function (AF) states for GPIO pins which are accepted by the GPIOx_AFRL and GPIOx_AFRH registers.
`enum `[`GPIO_IT_TRIGGER_State`](#group___g_p_i_o_1gace0c7e64d6c4e935151fbb7616fe540a)            | Enum to select interrupt trigger (falling or rising).
`enum `[`GPIO_Status_State`](#group___g_p_i_o_1ga3fdce057401bc547fc9d8692f2c27764)            | Enum to indicate the return status of a function.
`public `[`GPIO_Status_State`](api-undefined.md#group___g_p_i_o_1ga3fdce057401bc547fc9d8692f2c27764)` `[`GPIO_setPinOutput`](#group___g_p_i_o_1gab595615510195f9a4192c7a189678fab)`(`[`GPIO_Port`](api-undefined.md#group___g_p_i_o_1gaf164c756418dde00ac07fd47d0962150)` port,uint8_t pin)`            | Sets a pin to output mode.
`public `[`GPIO_Status_State`](api-undefined.md#group___g_p_i_o_1ga3fdce057401bc547fc9d8692f2c27764)` `[`GPIO_setPinOutput_FC`](#group___g_p_i_o_1ga882cc33c981cd7f8dfba88f860272d8a)`(`[`GPIO_Port`](api-undefined.md#group___g_p_i_o_1gaf164c756418dde00ac07fd47d0962150)` port,uint8_t pin,`[`GPIO_PUPD_State`](api-undefined.md#group___g_p_i_o_1ga2266f25d4ba662cd4e40de36a5049167)` pupd,`[`GPIO_SPEED_State`](api-undefined.md#group___g_p_i_o_1gaaf9978d8971c86f33115b493e5d6190f)` speed,`[`GPIO_OUTPUT_TYPE_State`](api-undefined.md#group___g_p_i_o_1gad95ee31148019b4ae8d63e5a3e0777ee)` output_t)`            | Sets a pin to output with Full Control (FC) mode, allowing specification of pupd, speed and output type.
`public `[`GPIO_Status_State`](api-undefined.md#group___g_p_i_o_1ga3fdce057401bc547fc9d8692f2c27764)` `[`GPIO_setPinInput`](#group___g_p_i_o_1gae6d9d08aa8ecf6a2f1237373ffe54dea)`(`[`GPIO_Port`](api-undefined.md#group___g_p_i_o_1gaf164c756418dde00ac07fd47d0962150)` port,uint8_t pin,`[`GPIO_PUPD_State`](api-undefined.md#group___g_p_i_o_1ga2266f25d4ba662cd4e40de36a5049167)` pupd)`            | Sets pin to input.
`public `[`GPIO_Status_State`](api-undefined.md#group___g_p_i_o_1ga3fdce057401bc547fc9d8692f2c27764)` `[`GPIO_setPinInput_FC`](#group___g_p_i_o_1ga18ca43b6164db4241faf900a1209013b)`(`[`GPIO_Port`](api-undefined.md#group___g_p_i_o_1gaf164c756418dde00ac07fd47d0962150)` port,uint8_t pin,`[`GPIO_PUPD_State`](api-undefined.md#group___g_p_i_o_1ga2266f25d4ba662cd4e40de36a5049167)` pupd,`[`GPIO_SPEED_State`](api-undefined.md#group___g_p_i_o_1gaaf9978d8971c86f33115b493e5d6190f)` speed,`[`GPIO_OUTPUT_TYPE_State`](api-undefined.md#group___g_p_i_o_1gad95ee31148019b4ae8d63e5a3e0777ee)` output_t)`            | Sets a pin to input with Full Control (FC) mode, allowing specification of pupd, speed and output type.
`public `[`GPIO_Status_State`](api-undefined.md#group___g_p_i_o_1ga3fdce057401bc547fc9d8692f2c27764)` `[`GPIO_writePin`](#group___g_p_i_o_1ga6f78d205e4179fc73f2515d21660accf)`(`[`GPIO_Port`](api-undefined.md#group___g_p_i_o_1gaf164c756418dde00ac07fd47d0962150)` port,uint8_t pin,`[`GPIO_PinState`](api-undefined.md#group___g_p_i_o_1ga5b3ef0486b179415581eb342e0ea6b43)` state)`            | Write a value to a specificed GPIO pin.
`public `[`GPIO_PinState`](api-undefined.md#group___g_p_i_o_1ga5b3ef0486b179415581eb342e0ea6b43)` `[`GPIO_readPin`](#group___g_p_i_o_1ga20f3f4cc40731487424a228070958166)`(`[`GPIO_Port`](api-undefined.md#group___g_p_i_o_1gaf164c756418dde00ac07fd47d0962150)` port,uint8_t pin)`            | Read a value from a specificed GPIO pin.
`public `[`GPIO_Status_State`](api-undefined.md#group___g_p_i_o_1ga3fdce057401bc547fc9d8692f2c27764)` `[`GPIO_togglePin`](#group___g_p_i_o_1ga2dbba2abe607108f74710b045b089c72)`(`[`GPIO_Port`](api-undefined.md#group___g_p_i_o_1gaf164c756418dde00ac07fd47d0962150)` port,uint8_t pin)`            | Toggles the state of a GPIO pin.
`public `[`GPIO_Status_State`](api-undefined.md#group___g_p_i_o_1ga3fdce057401bc547fc9d8692f2c27764)` `[`GPIO_setPinInterrupt`](#group___g_p_i_o_1ga232a16e1fe539abaaf2b4451039acbdd)`(`[`GPIO_Port`](api-undefined.md#group___g_p_i_o_1gaf164c756418dde00ac07fd47d0962150)` port,uint8_t pin,`[`GPIO_IT_TRIGGER_State`](api-undefined.md#group___g_p_i_o_1gace0c7e64d6c4e935151fbb7616fe540a)` trigger_state)`            | Sets a pin to input-interrupt mode.
`public `[`GPIO_Status_State`](api-undefined.md#group___g_p_i_o_1ga3fdce057401bc547fc9d8692f2c27764)` `[`GPIO_resetPinInterrupt`](#group___g_p_i_o_1ga93410b92827b20bc14b1ce1f54950f80)`(uint8_t pin)`            | Reset the flag corresponding to the pin in the EXTI Pending Register.
`public `[`GPIO_Status_State`](api-undefined.md#group___g_p_i_o_1ga3fdce057401bc547fc9d8692f2c27764)` `[`GPIO_setPinAF_Mode`](#group___g_p_i_o_1ga328c278fa96a3802882630ad49ee7ae3)`(`[`GPIO_Port`](api-undefined.md#group___g_p_i_o_1gaf164c756418dde00ac07fd47d0962150)` port,uint8_t pin,`[`GPIO_PUPD_State`](api-undefined.md#group___g_p_i_o_1ga2266f25d4ba662cd4e40de36a5049167)` pupd,`[`GPIO_SPEED_State`](api-undefined.md#group___g_p_i_o_1gaaf9978d8971c86f33115b493e5d6190f)` speed,`[`GPIO_OUTPUT_TYPE_State`](api-undefined.md#group___g_p_i_o_1gad95ee31148019b4ae8d63e5a3e0777ee)` output_t)`            | Sets the pin to the Alternate Function (AF) mode.
`public `[`GPIO_Status_State`](api-undefined.md#group___g_p_i_o_1ga3fdce057401bc547fc9d8692f2c27764)` `[`GPIO_setPinAF_State`](#group___g_p_i_o_1ga4ea71fe1e6545955e83ade36d2d9a053)`(`[`GPIO_Port`](api-undefined.md#group___g_p_i_o_1gaf164c756418dde00ac07fd47d0962150)` port,uint8_t pin,`[`GPIO_AF_State`](api-undefined.md#group___g_p_i_o_1ga50a2f4df54586ff8414f27fcb3f827db)` af_state)`            | Sets a pin in AF mode to the desired AF state.

## Members

#### `enum `[`GPIO_Port`](#group___g_p_i_o_1gaf164c756418dde00ac07fd47d0962150) 

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
GPIO_PORT_A            | GPIO port A.
GPIO_PORT_B            | GPIO port B.
GPIO_PORT_C            | GPIO port C.
GPIO_PORT_D            | GPIO port D.
GPIO_PORT_E            | GPIO port E.
GPIO_PORT_F            | GPIO port F.
GPIO_PORT_G            | GPIO port G.
GPIO_PORT_H            | GPIO port H.
GPIO_PORT_I            | GPIO port I.

Enum representing the port of a GPIO pin.

For this family of devices, ports A-I inclusive are supported.

#### `enum `[`GPIO_PinState`](#group___g_p_i_o_1ga5b3ef0486b179415581eb342e0ea6b43) 

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
GPIO_LOW            | The state of the pin is low.
GPIO_HIGH            | The state of the pin is high.

Enum representing the state of a pin.

#### `enum `[`GPIO_PUPD_State`](#group___g_p_i_o_1ga2266f25d4ba662cd4e40de36a5049167) 

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
GPIO_PUPD_NO_PULL_UP_PULL_DOWN            | No pull up or pull down chosen.
GPIO_PUPD_PULL_UP            | Pull up resistor chosen.
GPIO_PUPD_PULL_DOWN            | Pull down resistor chosen.

Enum representing different PUPD states which are accepted by the GPIOx_PUPDR register.

#### `enum `[`GPIO_SPEED_State`](#group___g_p_i_o_1gaaf9978d8971c86f33115b493e5d6190f) 

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
GPIO_SPEED_LOW            | Low speed chosen.
GPIO_SPEED_MEDIUM            | Medium speed chosen.
GPIO_SPEED_HIGH            | High speed chosen.
GPIO_SPEED_VERY_HIGH            | Very high speed chosen.

Enum representing the speed of a GPIO pin which are accepted by the GPIOx_SPEEDR register.

#### `enum `[`GPIO_OUTPUT_TYPE_State`](#group___g_p_i_o_1gad95ee31148019b4ae8d63e5a3e0777ee) 

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
GPIO_OUTPUT_PUSH_PULL            | Push pull mode.
GPIO_OUTPUT_OPEN_DRAIN            | Open drain mode.

Enum representing the type of GPIO output driver which are accepted by the GPIOx_OTYPER register.

#### `enum `[`GPIO_AF_State`](#group___g_p_i_o_1ga50a2f4df54586ff8414f27fcb3f827db) 

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
GPIO_AF_0            | Alternate Function 0.
GPIO_AF_1            | Alternate Function 1.
GPIO_AF_2            | Alternate Function 2.
GPIO_AF_3            | Alternate Function 3.
GPIO_AF_4            | Alternate Function 4.
GPIO_AF_5            | Alternate Function 5.
GPIO_AF_6            | Alternate Function 6.
GPIO_AF_7            | Alternate Function 7.
GPIO_AF_8            | Alternate Function 8.
GPIO_AF_9            | Alternate Function 9.
GPIO_AF_10            | Alternate Function 10.
GPIO_AF_11            | Alternate Function 11.
GPIO_AF_12            | Alternate Function 12.
GPIO_AF_13            | Alternate Function 13.
GPIO_AF_14            | Alternate Function 14.
GPIO_AF_15            | Alternate Function 15.

Enum representing Alternate Function (AF) states for GPIO pins which are accepted by the GPIOx_AFRL and GPIOx_AFRH registers.

#### `enum `[`GPIO_IT_TRIGGER_State`](#group___g_p_i_o_1gace0c7e64d6c4e935151fbb7616fe540a) 

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
GPIO_IT_TRIGGER_FALLING            | Interrupts on falling edge.
GPIO_IT_TRIGGER_RISING            | Interrupts on rising edge.

Enum to select interrupt trigger (falling or rising).

#### `enum `[`GPIO_Status_State`](#group___g_p_i_o_1ga3fdce057401bc547fc9d8692f2c27764) 

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
GPIO_OK            | Indicates that a function has returned successfully.
GPIO_INVALID_ARGS            | Indicates that a function has been given invalid (out of range) arguments.
GPIO_ERROR            | Indicates that a general error has occured.

Enum to indicate the return status of a function.

#### `public `[`GPIO_Status_State`](api-undefined.md#group___g_p_i_o_1ga3fdce057401bc547fc9d8692f2c27764)` `[`GPIO_setPinOutput`](#group___g_p_i_o_1gab595615510195f9a4192c7a189678fab)`(`[`GPIO_Port`](api-undefined.md#group___g_p_i_o_1gaf164c756418dde00ac07fd47d0962150)` port,uint8_t pin)` 

Sets a pin to output mode.

By default, output mode is set to PP, speed to very high and no pull up, pull down.

#### Parameters
* `port` port for the associated pin 

* `pin` pin number 

#### Returns
status

#### `public `[`GPIO_Status_State`](api-undefined.md#group___g_p_i_o_1ga3fdce057401bc547fc9d8692f2c27764)` `[`GPIO_setPinOutput_FC`](#group___g_p_i_o_1ga882cc33c981cd7f8dfba88f860272d8a)`(`[`GPIO_Port`](api-undefined.md#group___g_p_i_o_1gaf164c756418dde00ac07fd47d0962150)` port,uint8_t pin,`[`GPIO_PUPD_State`](api-undefined.md#group___g_p_i_o_1ga2266f25d4ba662cd4e40de36a5049167)` pupd,`[`GPIO_SPEED_State`](api-undefined.md#group___g_p_i_o_1gaaf9978d8971c86f33115b493e5d6190f)` speed,`[`GPIO_OUTPUT_TYPE_State`](api-undefined.md#group___g_p_i_o_1gad95ee31148019b4ae8d63e5a3e0777ee)` output_t)` 

Sets a pin to output with Full Control (FC) mode, allowing specification of pupd, speed and output type.

#### Parameters
* `port` port for the associated pin 

* `pin` pin number 

* `pupd` pull up or pull down resistor state 

* `speed` desired speed 

* `output_t` output type 

#### Returns
status

#### `public `[`GPIO_Status_State`](api-undefined.md#group___g_p_i_o_1ga3fdce057401bc547fc9d8692f2c27764)` `[`GPIO_setPinInput`](#group___g_p_i_o_1gae6d9d08aa8ecf6a2f1237373ffe54dea)`(`[`GPIO_Port`](api-undefined.md#group___g_p_i_o_1gaf164c756418dde00ac07fd47d0962150)` port,uint8_t pin,`[`GPIO_PUPD_State`](api-undefined.md#group___g_p_i_o_1ga2266f25d4ba662cd4e40de36a5049167)` pupd)` 

Sets pin to input.

By default, output mode is set to PP and speed to very high.

#### Parameters
* `port` port for the associated pin 

* `pin` pin number 

* `pupd` pull up or pull down resistor state 

#### Returns
status

#### `public `[`GPIO_Status_State`](api-undefined.md#group___g_p_i_o_1ga3fdce057401bc547fc9d8692f2c27764)` `[`GPIO_setPinInput_FC`](#group___g_p_i_o_1ga18ca43b6164db4241faf900a1209013b)`(`[`GPIO_Port`](api-undefined.md#group___g_p_i_o_1gaf164c756418dde00ac07fd47d0962150)` port,uint8_t pin,`[`GPIO_PUPD_State`](api-undefined.md#group___g_p_i_o_1ga2266f25d4ba662cd4e40de36a5049167)` pupd,`[`GPIO_SPEED_State`](api-undefined.md#group___g_p_i_o_1gaaf9978d8971c86f33115b493e5d6190f)` speed,`[`GPIO_OUTPUT_TYPE_State`](api-undefined.md#group___g_p_i_o_1gad95ee31148019b4ae8d63e5a3e0777ee)` output_t)` 

Sets a pin to input with Full Control (FC) mode, allowing specification of pupd, speed and output type.

#### Parameters
* `port` port for the associated pin 

* `pin` pin number 

* `pupd` pull up or pull down resistor state 

* `speed` desired speed 

* `output_t` output type 

#### Returns
status

#### `public `[`GPIO_Status_State`](api-undefined.md#group___g_p_i_o_1ga3fdce057401bc547fc9d8692f2c27764)` `[`GPIO_writePin`](#group___g_p_i_o_1ga6f78d205e4179fc73f2515d21660accf)`(`[`GPIO_Port`](api-undefined.md#group___g_p_i_o_1gaf164c756418dde00ac07fd47d0962150)` port,uint8_t pin,`[`GPIO_PinState`](api-undefined.md#group___g_p_i_o_1ga5b3ef0486b179415581eb342e0ea6b43)` state)` 

Write a value to a specificed GPIO pin.

The pin state to be set can either be HIGH or LOW.

#### Parameters
* `port` port for the associated pin 

* `pin` pin number 

* `state` desired state of the pin 

#### Returns
status 

This function should only be called if the pin has been correctly set with setPinInput, setPinOutput, setPinInput_FC or setPinOutput_FC.

#### `public `[`GPIO_PinState`](api-undefined.md#group___g_p_i_o_1ga5b3ef0486b179415581eb342e0ea6b43)` `[`GPIO_readPin`](#group___g_p_i_o_1ga20f3f4cc40731487424a228070958166)`(`[`GPIO_Port`](api-undefined.md#group___g_p_i_o_1gaf164c756418dde00ac07fd47d0962150)` port,uint8_t pin)` 

Read a value from a specificed GPIO pin.

The pin state returned can either be HIGH or LOW.

#### Parameters
* `port` port for the associated pin 

* `pin` pin number 

#### Returns
state of the pin 

This function should only be called if the pin has been correctly set with setPinInput, setPinOutput, setPinInput_FC or setPinOutput_FC. 

This function does not check correctness of arguments. This responsibility is given to the caller.

#### `public `[`GPIO_Status_State`](api-undefined.md#group___g_p_i_o_1ga3fdce057401bc547fc9d8692f2c27764)` `[`GPIO_togglePin`](#group___g_p_i_o_1ga2dbba2abe607108f74710b045b089c72)`(`[`GPIO_Port`](api-undefined.md#group___g_p_i_o_1gaf164c756418dde00ac07fd47d0962150)` port,uint8_t pin)` 

Toggles the state of a GPIO pin.

#### Parameters
* `port` port for the associated pin 

* `pin` pin number 

This function should only be called if the pin has been correctly set with setPinInput, setPinOutput, setPinInput_FC or setPinOutput_FC.

#### `public `[`GPIO_Status_State`](api-undefined.md#group___g_p_i_o_1ga3fdce057401bc547fc9d8692f2c27764)` `[`GPIO_setPinInterrupt`](#group___g_p_i_o_1ga232a16e1fe539abaaf2b4451039acbdd)`(`[`GPIO_Port`](api-undefined.md#group___g_p_i_o_1gaf164c756418dde00ac07fd47d0962150)` port,uint8_t pin,`[`GPIO_IT_TRIGGER_State`](api-undefined.md#group___g_p_i_o_1gace0c7e64d6c4e935151fbb7616fe540a)` trigger_state)` 

Sets a pin to input-interrupt mode.

By default, the interrupt trigger is set to rising trigger. 
#### Parameters
* `port` port for the associated pin 

* `pin` pin number 

#### Returns
status

#### `public `[`GPIO_Status_State`](api-undefined.md#group___g_p_i_o_1ga3fdce057401bc547fc9d8692f2c27764)` `[`GPIO_resetPinInterrupt`](#group___g_p_i_o_1ga93410b92827b20bc14b1ce1f54950f80)`(uint8_t pin)` 

Reset the flag corresponding to the pin in the EXTI Pending Register.

This function should be called in the EXTI_IRQ_Handler in order to allow repeated interrupts. 
#### Parameters
* `pin` pin number 

#### Returns
status

#### `public `[`GPIO_Status_State`](api-undefined.md#group___g_p_i_o_1ga3fdce057401bc547fc9d8692f2c27764)` `[`GPIO_setPinAF_Mode`](#group___g_p_i_o_1ga328c278fa96a3802882630ad49ee7ae3)`(`[`GPIO_Port`](api-undefined.md#group___g_p_i_o_1gaf164c756418dde00ac07fd47d0962150)` port,uint8_t pin,`[`GPIO_PUPD_State`](api-undefined.md#group___g_p_i_o_1ga2266f25d4ba662cd4e40de36a5049167)` pupd,`[`GPIO_SPEED_State`](api-undefined.md#group___g_p_i_o_1gaaf9978d8971c86f33115b493e5d6190f)` speed,`[`GPIO_OUTPUT_TYPE_State`](api-undefined.md#group___g_p_i_o_1gad95ee31148019b4ae8d63e5a3e0777ee)` output_t)` 

Sets the pin to the Alternate Function (AF) mode.

#### Parameters
* `port` port for the associated pin 

* `pin` pin number 

* `pupd` pull up or pull down resistor state 

* `speed` desired speed 

* `output_t` output type 

#### Returns
status

#### `public `[`GPIO_Status_State`](api-undefined.md#group___g_p_i_o_1ga3fdce057401bc547fc9d8692f2c27764)` `[`GPIO_setPinAF_State`](#group___g_p_i_o_1ga4ea71fe1e6545955e83ade36d2d9a053)`(`[`GPIO_Port`](api-undefined.md#group___g_p_i_o_1gaf164c756418dde00ac07fd47d0962150)` port,uint8_t pin,`[`GPIO_AF_State`](api-undefined.md#group___g_p_i_o_1ga50a2f4df54586ff8414f27fcb3f827db)` af_state)` 

Sets a pin in AF mode to the desired AF state.

#### Parameters
* `port` port for the associated pin 

* `pin` pin number 

* `af_state` the desired AF state 

#### Returns
status 

This function should only be called if the pin has been set to AF (Alternate Function) mode with setPinAF_Mode.

