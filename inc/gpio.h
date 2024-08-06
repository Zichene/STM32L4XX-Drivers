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
	A = 0, ///< GPIO port A
	B = 1, ///< GPIO port B
	C = 2, ///< GPIO port C
	D = 3, ///< GPIO port D
	E = 4, ///< GPIO port E
	F = 5, ///< GPIO port F
	G = 6, ///< GPIO port G
	H = 7, ///< GPIO port H
	I = 8, ///< GPIO port I
} Port; 

/**@brief Enum representing the state of a pin.
*/
typedef enum {
	LOW = 0, ///< The state of the pin is low
	HIGH = 1, ///< The state of the pin is high
}PinState ;

/**@brief Enum representing different PUPD states which are accepted by the GPIOx_PUPDR register. 
*/
typedef enum  {
	PUPD_NO_PULL_UP_PULL_DOWN = 0, ///< No pull up or pull down chosen
	PUPD_PULL_UP = 1, ///< Pull up resistor chosen
	PUPD_PULL_DOWN = 2, ///< Pull down resistor chosen
}PUPD_State;

/**@brief Enum representing the speed of a GPIO pin which are accepted by the GPIOx_SPEEDR register.
*/
typedef enum  {
	SPEED_LOW = 0, ///< Low speed chosen
	SPEED_MEDIUM = 1, ///< Medium speed chosen
	SPEED_HIGH = 2, ///< High speed chosen
	SPEED_VERY_HIGH = 3, ///< Very high speed chosen
}SPEED_State;

/**@brief Enum representing the type of GPIO output driver which are accepted by the GPIOx_OTYPER register.
*/
typedef enum  {
	OUTPUT_PUSH_PULL = 0, ///< Push pull mode
	OUTPUT_OPEN_DRAIN = 1, ///< Open drain mode
}OUTPUT_TYPE_State;

/****************************************************************************************************/
/*																			FUNCTION PROTOTYPES                                         */
/****************************************************************************************************/

/**@brief Sets a pin to output mode. By default, output mode is set to PP, speed to very high and no pull up, pull down.
*
* @param port port for the associated pin 
* @param pin pin number
*/
void GPIO_setPinOutput(Port port, char pin);


/**@brief Sets a pin to output with Full Control (FC) mode, allowing specification of pupd, speed and output type.
*
* @param port port for the associated pin
* @param pin pin number
* @param pupd pull up or pull down resistor state
* @param speed desired speed
* @param output_t output type
*/
void GPIO_setPinOutput_FC(Port port, char pin, PUPD_State pupd, SPEED_State speed, OUTPUT_TYPE_State output_t);

/**@brief Sets pin to input. By default, output mode is set to PP and speed to very high.
* 
* @param port port for the associated pin
* @param pin pin number
* @param pupd pull up or pull down resistor state
*/
void GPIO_setPinInput(Port port, char pin,  PUPD_State pupd);

/**@brief Sets a pin to input with Full Control (FC) mode, allowing specification of pupd, speed and output type.
*
* @param port port for the associated pin
* @param pin pin number
* @param pupd pull up or pull down resistor state
* @param speed desired speed
* @param output_t output type
*/
void GPIO_setPinInput_FC(Port port, char pin,  PUPD_State pupd,  SPEED_State speed,  OUTPUT_TYPE_State output_t);

/**@brief Write a value to a specificed GPIO pin. This function should only be called if the pin has been correctly set with setPinInput, setPinOutput, setPinInput_FC or setPinOutput_FC. The pin state to be set can either be HIGH or LOW.
* 
* @param port port for the associated pin
* @param pin pin number
* @param state desired state of the pin
*/
void GPIO_writePin(Port port, char pin,  PinState state);

/**@brief Read a value from a specificed GPIO pin. This function should only be called if the pin has been correctly set with either setPinInput, setPinOutput, setPinInput_FC or setPinOutput_FC. The pin state returned can either be HIGH or LOW.
* 
* @param port port for the associated pin
* @param pin pin number
* @return state of the pin 
*/
PinState GPIO_readPin(Port port, char pin);

/**@brief Toggles the state of a GPIO pin. This function should only be called if the pin has been correctly set with either setPinInput, setPinOutput, setPinInput_FC or setPinOutput_FC.
* @param port port for the associated pin
* @param pin pin number
*/
void GPIO_togglePin(Port port, char pin);

/**@brief Sets a pin to input-interrupt mode. By default, the interrupt trigger is set to rising trigger.
* @param port port for the associated pin
* @param pin pin number
*/
void GPIO_setPinInterrupt(Port port, char pin);

/**@brief Reset the flag corresponding to the pin in the EXTI Pending Register. This function should be called in the EXTI_IRQ_Handler in order to allow repeated interrupts. 
* @param pin pin number
*/
void GPIO_resetPinInterrupt(char pin);



