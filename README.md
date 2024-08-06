# STM32L4XX-Drivers
Bare-metal implementation of some drivers for the STM32L4 family of devices. 
See the `main.c` file for an example application showcasing the functionality of the GPIO driver.

WARNING: 
- These have not been tested thoroughly, use at own risk.
- These drivers should only use on STM32L4XX devices.

# Usage
- Clone the repo or download desired files.
- In your embedded project environment, simply add the desired `.h` and `.c` files. Make sure that you set up the include paths correctly!

## GPIO
The General Purpose Input Output (GPIO) drivers currently implement basic functionalities such as:
- Pin output
- Pin input
- Interrupts

For detailed Doxygen documentation, clone the repository and see the docs/html folder.

