# STM32L4XX-Drivers
Bare-metal implementation of some drivers for the STM32L4 family of devices. 
These drivers were mostly tested using the B-L4S5I-IOT01A development board from ST.
See example projects showcasing these drivers: [projects](projects-bl4s5i-iot01a).

WARNING: 
- The code was written for educational purposes.
- These have not been tested thoroughly, use at own risk.
- These drivers should only use on STM32L4XX devices.

# Usage
- Clone the repo or download desired files.
- In your embedded project environment, simply add the desired `.h` and `.c` files. Make sure that you set up the include paths correctly!

# Documentation
- Detailed documentation are in the header files `.h` in the [inc](inc) folder.
- Markdown converted documentation (originally doxygen xml) can be found in the [docs](docs) folder.
- Full Doxygen HTML documentation can be downloaded [here](docs\doxygen).

## GPIO
The General Purpose Input Output (GPIO) drivers currently implement functionalities such as:
- Pin output
- Pin input
- Interrupts
- Alternate Function (AF)

All GPIO pins can be set up with specific pull-up pull down mode, speed type and output type. 
See local [documentation](docs\gpio).

## CLOCK
The Clock drivers currently implement functionalities such as:
- Activating the MCO (Master Clock Output) for various clock sources.
- Configure the PLL (Phased Locked Loop) clock.
- Get the clock speeds for various clocks (system clock, HSI, PLL, MSI, etc.)
- Configure and set the system clock.
- Set various peripheral bus prescalers (AHB, APB1, APB2).
 
See local [documentation](docs\clock).
