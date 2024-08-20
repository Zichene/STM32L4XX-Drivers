# STM32L4XX-Drivers 
Bare-metal implementation of some drivers for the STM32L4 family of devices. 
These drivers were mostly tested using the B-L4S5I-IOT01A development board from ST.
See example projects showcasing these drivers: [projects](projects-bl4s5i-iot01a).

⚠️ **WARNING** ⚠️ 
- The code was written for educational purposes.
- These have not been tested thoroughly, use at own risk.
- These drivers should only use on STM32L4XX devices. Specifically, most testing needs to be done for other devices of the STM32L4 family. 
  
# References 📕
All implementations follow closely from the ST reference manuals and datasheets. The following links are useful for reference:
- [STM32L4+ Series Reference Manual](https://www.st.com/resource/en/reference_manual/rm0432-stm32l4-series-advanced-armbased-32bit-mcus-stmicroelectronics.pdf)
- [Datasheet for some STM32L4 MCUs](https://www.st.com/resource/en/datasheet/stm32l4s5vi.pdf)
- **Board specific**: [Board schematic for B-L4S5I-IOT01A](https://www.st.com/content/ccc/resource/technical/layouts_and_diagrams/schematic_pack/group1/e0/ec/b7/71/06/33/44/87/MB1297-L4S5VI-E03_Schematic/files/MB1297-L4S5VI-E03_Schematic.PDF/jcr:content/translations/en.MB1297-L4S5VI-E03_Schematic.PDF)

# Usage 📗
- Clone the repo or download desired files.
- In your embedded project environment, simply add the desired `.h` and `.c` files. Make sure that you set up the include paths correctly!

# Documentation 📘
- Detailed documentation are in the header files `.h` in the [inc](inc) folder.
- Markdown converted documentation (originally doxygen xml) can be found in the [docs](docs) folder.
- Full Doxygen HTML documentation can be downloaded [here](docs/doxygen).

## GPIO
The General Purpose Input Output (GPIO) drivers currently implement functionalities such as:
- Pin output
- Pin input
- Interrupts
- Alternate Function (AF)

All GPIO pins can be set up with specific pull-up pull down mode, speed type and output type. 
See local [documentation](docs/gpio).

## CLOCK
The Clock drivers currently implement functionalities such as:
- Activating the MCO (Master Clock Output) for various clock sources.
- Configure the PLL (Phased Locked Loop) clock.
- Get the clock speeds for various clocks (system clock, HSI, PLL, MSI, etc.)
- Configure and set the system clock.
- Set various peripheral bus prescalers (AHB, APB1, APB2).
 
See local [documentation](docs/clock).

## TIMER
The Timer (TIM) drivers current implement functionalities such as:
- Configuring various timers with prescaler and period.
- Timer interrupt configuration.
- Starting and stopping interrupts.

See local [documentation](docs/tim).
