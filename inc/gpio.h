#ifndef GPIO_H
#define GPIO_H
#include "stm32l4xx.h"

/***
*
* GPIO drivers for stm32l4xx devices.
* WARNING: These drivers have NOT been tested extensively. Use at own risk.
* Reference: https://www.youtube.com/playlist?list=PLtVUYRe-Z-mfKO0lg_-MBvwWl6VjWT8Dt
*
***/

/****************************************************************************************************/
/*															          TYPEDEFS                                                  */
/****************************************************************************************************/

/**@brief Enum representing the port of a GPIO pin. For this family of devices, ports A-I inclusive are supported.
*/
typedef enum{
	GPIO_PORT_A = 0, ///< GPIO port A
	GPIO_PORT_B = 1, ///< GPIO port B
	GPIO_PORT_C = 2, ///< GPIO port C
	GPIO_PORT_D = 3, ///< GPIO port D
	GPIO_PORT_E = 4, ///< GPIO port E
	GPIO_PORT_F = 5, ///< GPIO port F
	GPIO_PORT_G = 6, ///< GPIO port G
	GPIO_PORT_H = 7, ///< GPIO port H
	GPIO_PORT_I = 8, ///< GPIO port I
} GPIO_Port; 

/**@brief Enum representing the state of a pin.
*/
typedef enum {
	GPIO_LOW = 0, ///< The state of the pin is low
	GPIO_HIGH = 1, ///< The state of the pin is high
}GPIO_PinState ;

/**@brief Enum representing different PUPD states which are accepted by the GPIOx_PUPDR register. 
*/
typedef enum  {
	GPIO_PUPD_NO_PULL_UP_PULL_DOWN = 0, ///< No pull up or pull down chosen
	GPIO_PUPD_PULL_UP = 1, ///< Pull up resistor chosen
	GPIO_PUPD_PULL_DOWN = 2, ///< Pull down resistor chosen
}GPIO_PUPD_State;

/**@brief Enum representing the speed of a GPIO pin which are accepted by the GPIOx_SPEEDR register.
*/
typedef enum  {
	GPIO_SPEED_LOW = 0, ///< Low speed chosen
	GPIO_SPEED_MEDIUM = 1, ///< Medium speed chosen
	GPIO_SPEED_HIGH = 2, ///< High speed chosen
	GPIO_SPEED_VERY_HIGH = 3, ///< Very high speed chosen
}GPIO_SPEED_State;

/**@brief Enum representing the type of GPIO output driver which are accepted by the GPIOx_OTYPER register.
*/
typedef enum  {
	GPIO_OUTPUT_PUSH_PULL = 0, ///< Push pull mode
	GPIO_OUTPUT_OPEN_DRAIN = 1, ///< Open drain mode
}GPIO_OUTPUT_TYPE_State;

/**@brief Enum representing Alternate Function (AF) states for GPIO pins which are accepted by the GPIOx_AFRL and GPIOx_AFRH registers.
*/
typedef enum {
	GPIO_AF_0, ///< Alternate Function 0
	GPIO_AF_1, ///< Alternate Function 1
	GPIO_AF_2, ///< Alternate Function 2
	GPIO_AF_3, ///< Alternate Function 3
	GPIO_AF_4, ///< Alternate Function 4
	GPIO_AF_5, ///< Alternate Function 5
	GPIO_AF_6, ///< Alternate Function 6
	GPIO_AF_7, ///< Alternate Function 7
	GPIO_AF_8, ///< Alternate Function 8
	GPIO_AF_9, ///< Alternate Function 9
	GPIO_AF_10, ///< Alternate Function 10
	GPIO_AF_11, ///< Alternate Function 11
	GPIO_AF_12, ///< Alternate Function 12
	GPIO_AF_13, ///< Alternate Function 13
	GPIO_AF_14, ///< Alternate Function 14
	GPIO_AF_15, ///< Alternate Function 15
}GPIO_AF_State;

/**@brief Enum to select interrupt trigger (falling or rising).
*/
typedef enum {
	GPIO_IT_TRIGGER_FALLING = 0, ///< Interrupts on falling edge
	GPIO_IT_TRIGGER_RISING = 1, ///< Interrupts on rising edge
}GPIO_IT_TRIGGER_State;

/****************************************************************************************************/
/*																			FUNCTION PROTOTYPES                                         */
/****************************************************************************************************/

/**@brief Sets a pin to output mode. By default, output mode is set to PP, speed to very high and no pull up, pull down.
*
* @param port port for the associated pin 
* @param pin pin number
*/
void GPIO_setPinOutput(GPIO_Port port, char pin);


/**@brief Sets a pin to output with Full Control (FC) mode, allowing specification of pupd, speed and output type.
*
* @param port port for the associated pin
* @param pin pin number
* @param pupd pull up or pull down resistor state
* @param speed desired speed
* @param output_t output type
*/
void GPIO_setPinOutput_FC(GPIO_Port port, char pin, GPIO_PUPD_State pupd, GPIO_SPEED_State speed, GPIO_OUTPUT_TYPE_State output_t);

/**@brief Sets pin to input. By default, output mode is set to PP and speed to very high.
* 
* @param port port for the associated pin
* @param pin pin number
* @param pupd pull up or pull down resistor state
*/
void GPIO_setPinInput(GPIO_Port port, char pin,  GPIO_PUPD_State pupd);

/**@brief Sets a pin to input with Full Control (FC) mode, allowing specification of pupd, speed and output type.
*
* @param port port for the associated pin
* @param pin pin number
* @param pupd pull up or pull down resistor state
* @param speed desired speed
* @param output_t output type
*/
void GPIO_setPinInput_FC(GPIO_Port port, char pin,  GPIO_PUPD_State pupd,  GPIO_SPEED_State speed,  GPIO_OUTPUT_TYPE_State output_t);

/**@brief Write a value to a specificed GPIO pin. The pin state to be set can either be HIGH or LOW.
* 
* @param port port for the associated pin
* @param pin pin number
* @param state desired state of the pin
* @warning This function should only be called if the pin has been correctly set with setPinInput, setPinOutput, setPinInput_FC or setPinOutput_FC. 
*/
void GPIO_writePin(GPIO_Port port, char pin,  GPIO_PinState state);

/**@brief Read a value from a specificed GPIO pin.  The pin state returned can either be HIGH or LOW.
* 
* @param port port for the associated pin
* @param pin pin number
* @return state of the pin 
* @warning This function should only be called if the pin has been correctly set with setPinInput, setPinOutput, setPinInput_FC or setPinOutput_FC.
*/
GPIO_PinState GPIO_readPin(GPIO_Port port, char pin);

/**@brief Toggles the state of a GPIO pin.
* @param port port for the associated pin
* @param pin pin number
* @warning This function should only be called if the pin has been correctly set with setPinInput, setPinOutput, setPinInput_FC or setPinOutput_FC.
*/
void GPIO_togglePin(GPIO_Port port, char pin);

/**@brief Sets a pin to input-interrupt mode. By default, the interrupt trigger is set to rising trigger.
* @param port port for the associated pin
* @param pin pin number
*/
void GPIO_setPinInterrupt(GPIO_Port port, char pin, GPIO_IT_TRIGGER_State trigger_state);

/**@brief Reset the flag corresponding to the pin in the EXTI Pending Register. This function should be called in the EXTI_IRQ_Handler in order to allow repeated interrupts. 
* @param pin pin number
*/
void GPIO_resetPinInterrupt(char pin);

/**@brief Sets the pin to the Alternate Function (AF) mode.
* @param port port for the associated pin
* @param pin pin number
* @param pupd pull up or pull down resistor state
* @param speed desired speed
* @param output_t output type
*/
void GPIO_setPinAF_Mode(GPIO_Port port, char pin, GPIO_PUPD_State pupd,  GPIO_SPEED_State speed,  GPIO_OUTPUT_TYPE_State output_t);

/**@brief Sets a pin in AF mode to the desired AF state. 
* @param port port for the associated pin
* @param pin pin number
* @param af_state the desired AF state
* @warning This function should only be called if the pin has been set to AF (Alternate Function) mode with setPinAF_Mode.
*/
void GPIO_setPinAF_State(GPIO_Port port, char pin, GPIO_AF_State af_state);
#endif