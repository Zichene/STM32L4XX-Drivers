#include "common.h"
#include "uart.h"
#include "spi.h"
#include "string.h"
#include "gpio.h"
#include "tim.h"

#ifdef SPI_WIFI
/*
DESCRIPTION: Configure an SPI peripheral to communicate with the on-board Wi-Fi module (es-Wifi).
BOARD USED: B-L4S5I-IOT01A board
INTERNAL CONNECTIONS: The ST-Link virtual COM port for this board is connected to USART1. PB7->USART1_RX, PB6 -> USART1_TX
REFERENCES: ST MB1297 (Internal Board Connections), ST UM2708 (User Manual),  STM32L4S5xx, STM32L4S7xx and STM32L4S9xx Datasheet.
AUTHOR: Zichene
DATE: 1/27/2026
*/


/* On the board used for this example, LED2 (green) is connected to Pin B14 (Port B, Pin 14) */
#define LED2_Port GPIO_PORT_B
#define LED2_Pin 14

/* LED3 (WiFi and Bluetooth) used as error indicator is connected to Pin C9 (Port C, Pin 9) */
#define LEDError_Port GPIO_PORT_C
#define LEDError_Pin 9


/* 
The following USART1 internal connections are found in MB1297 
*/

/* USART1_TX -> PB6 */
#define USART1_TX_Port GPIO_PORT_B
#define USART1_TX_Pin 6

/* USART1_RX -> PB7 */
#define USART1_RX_Port GPIO_PORT_B
#define USART1_RX_Pin 7

/* The AF (Alternate Function) modes for USART1 */
#define USART1_RX_AF GPIO_AF_7
#define USART1_TX_AF GPIO_AF_7

/* SPI3_MOSI -> PC12 */
#define SPI3_MOSI_Port GPIO_PORT_C
#define SPI3_MOSI_Pin 12
#define SPI3_MOSI_AF GPIO_AF_6

/* SPI3_MISO -> PC11 */
#define SPI3_MISO_Port GPIO_PORT_C
#define SPI3_MISO_Pin 11
#define SPI3_MISO_AF GPIO_AF_6

/* SPI3_SCK -> PC10 */
#define SPI3_SCK_Port GPIO_PORT_C
#define SPI3_SCK_Pin 10
#define SPI3_SCK_AF GPIO_AF_6

/* SPI3_NSS -> PE0. NOTE: Not an AF pin. Configure as regular GPIO output. */
#define SPI3_NSS_Port GPIO_PORT_E
#define SPI3_NSS_Pin 0

/* WIFI_DRDY -> PE1 */
#define WIFI_DRDY_Port GPIO_PORT_E
#define WIFI_DRDY_Pin 1

/* WIFI_RESET -> PE8 */
#define WIFI_RESET_Port GPIO_PORT_E
#define WIFI_RESET_Pin 8

static void ErrorHandler();
static void configUART();
static void configSystemClock120MHz();
static void configSPI();
static void configTimer();
static void sleepBlockingMs(uint32_t ms);

/* global variables */
uint32_t RX_BUF_SIZE = 1000;
volatile uint8_t usartIsIdle = true;
volatile uint32_t currentMs = 0;
volatile uint8_t wifiDrdyFlag = false;

/*
* Configure the UART peripheral with its usual settings: 
*		- 115200 baud rate
*		- 8 bit data
*		- no parity
*		- one stop bit
*		- no flow control
*
* Here we will disable interrupt.
*/
static void configUART() {
	/* Interrupts */
	UART_ITConfig_Typedef it_conf = {
		.RXNEIE_enabled = true,
		.priority = 1,
	};
	
	/* Setup pin configuration as defined above (internal connections) */
	UART_PinConfig_Typedef pin_conf = {
		.rx_port = USART1_RX_Port,
		.rx_pin = USART1_RX_Pin,
		.tx_port = USART1_TX_Port,
		.tx_pin = USART1_TX_Pin,
		.rx_pin_af = USART1_RX_AF,
		.tx_pin_af = USART1_TX_AF,
	};

	/* Setup the UART configuration */
	UART_Config_Typedef uart_conf = {
		.uart = UART_USART1,
		.pin_config = &pin_conf,
		.it_config = &it_conf,
		.baud_rate = 115200,
		.databits = UART_DATABITS_8,
		.parity = UART_PARITY_NONE,
		.stopbits = UART_STOPBITS_1,
	};
	
	if (UART_config(&uart_conf) != UART_OK)
		ErrorHandler();
	
	/* Enable the internal rx buffer to be filled by interrupt */
	UART_receiveIT_Start(uart_conf.uart);
}


/* 
* Configure the system clock to its maximum speed (120 MHz).
*
*  We will be using the PLL clock as the system clock. In order to use this clock, we need to choose one of four clock sources for the PLL.
*  The source clock for the PLL will be the MSI (Multi Speed Internal) clock, which has a default speed of 4 MHz. 
*  The speed of the MSI is modified by PLL_M, PLL_N and PLL_R, which are positive integers. The modification is as follows:
*
*  			output = input * PLL_N / (PLL_M * PLL_R)
*
*   MSI (default 4 MHz) -> divided by PLL_M = 1 -> multiplied by PLL_N = 60 -> divided by PLL_R = 2 -> 120 MHz
*
*/
static void configSystemClock120MHz() {

	/* Configure PLL with required parameters (PLL_M, PLL_N and PLL_R) */
	CLOCK_configPLL(CLOCK_PLL_SRC_MSI, 1, 60, CLOCK_PLLR_2);
	
	/* Activate and set the PLLCLK as the system clock */
	CLOCK_activateClk(CLOCK_PLL);
	CLOCK_setSystemClock(CLOCK_SYSCLK_PLL); 
	
	/* Check that the system clock is indeed 120 MHz */
	if (CLOCK_getSystemClockSpeed() != 120000000)
		ErrorHandler();
	
	/* Make sure that bus prescalers are set to 1. These prescalers control the speed of the clock that is passed to the timers and other peripherals. */
	CLOCK_setAHBPrescaler(CLOCK_AHB_PRE_DIV_1);
	CLOCK_setAPB1Prescaler(CLOCK_APB1_PRE_DIV_1);
	CLOCK_setAPB2Prescaler(CLOCK_APB2_PRE_DIV_1);
}

/*
* Use the UART_transmit() function and the string.h library to print a message!
*/
static void print(const char* message) {
	UART_transmit(UART_USART1, (uint8_t*) message, strlen(message));
}

/* Setup timer using TIM2 to trigger an interrupt every 1 ms
*
* The prescaler (PSC) determines how many clock cycles pass before the counter goes up by one.
* The period (ARR) determines how many times the counter needs to increment before an event (interrupt) is triggered.
*
* Since the clock reaching the TIM2 timer is at 120 MHz,
* we can set our PSC and ARR to 40 and 3000 respectively so that an event is triggered every 1 ms.
*
*/
static void configTimer() {
    const TIM_Config_Typedef tim2_config = {
        .ARR=3000, // Period of 3000
        .PSC=40, // Prescaler of 40
        .timer = TIM_TIM2,
        .enableInterrupt = true,
    };

    TIM_config(&tim2_config);
}

static void sleepBlockingMs(const uint32_t ms) {
    currentMs = 0;
    TIM_startTimer(TIM_TIM2);
    while (currentMs < ms) {};
    TIM_stopTimer(TIM_TIM2);
}

static void configSPI() {
    SPI_PinConfig_Typedef pin_conf = {
        .miso_apply = true,
        .miso_port = SPI3_MISO_Port,
        .miso_pin = SPI3_MISO_Pin,
        .miso_pin_af = SPI3_MISO_AF,
        .mosi_apply = true,
        .mosi_port = SPI3_MOSI_Port,
        .mosi_pin = SPI3_MOSI_Pin,
        .mosi_pin_af = SPI3_MOSI_AF,
        .sclk_apply = true,
        .sclk_port = SPI3_SCK_Port,
        .sclk_pin = SPI3_SCK_Pin,
        .sclk_pin_af = SPI3_SCK_AF,
        .ssel_apply = false
    };

    SPI_ITConfig_Typedef it_conf = {
        .ERRIE_enabled = false,
        .RXNEIE_enabled = false,
        .TXEIE_enabled = false,
        .priority = 1,
    };

    SPI_CRCConfig_Typedef crc_conf = {
        .enabled = false,
    };

    SPI_Config_Typedef spi_conf = {
        .spi = SPI_SPI3,
        .pin_config = &pin_conf,
        .it_config = &it_conf,
        .crc_config = &crc_conf,
        .mode = SPI_MODE_0,
        .master = true,
        .full_duplex = false,
        .lsb_first = false,
        .nss_pulse_mode = true,
        .nss_management = SPI_NSS_SOFTWARE,
        .br_divider = SPI_BR_DIV_16,
        .fifo_threshold_8_bit = false,
        .data_size = SPI_DATA_SIZE_16_BIT
    };

    if (SPI_config(&spi_conf) != SPI_OK) {
        ErrorHandler();
    }

    /* Also need to configure some other GPIOs */
    GPIO_setPinOutput_FC(SPI3_NSS_Port,
                     SPI3_NSS_Pin,
                         GPIO_PUPD_NO_PULL_UP_PULL_DOWN,
                         GPIO_SPEED_LOW,
                         GPIO_OUTPUT_PUSH_PULL);

    GPIO_setPinOutput_FC(WIFI_RESET_Port,
                     WIFI_RESET_Pin,
                         GPIO_PUPD_NO_PULL_UP_PULL_DOWN,
                         GPIO_SPEED_LOW,
                         GPIO_OUTPUT_PUSH_PULL);

    /* Configure Wifi DRDY pin to interrupt */
    GPIO_setPinInterrupt(WIFI_DRDY_Port,WIFI_DRDY_Pin, GPIO_IT_TRIGGER_RISING);
}

int main(void)
{
	/* configure clock, uart and spi and timer */
	configSystemClock120MHz();
	configUART();
    configSPI();
    configTimer();

	/* rx buffer */
	uint8_t rxBuf[RX_BUF_SIZE];

	/* printing using UART! */
	print("Hello World \r\n");

    /* Initiating the Wi-Fi module */
    GPIO_writePin(WIFI_RESET_Port, WIFI_RESET_Pin, GPIO_LOW);
    sleepBlockingMs(10);
    GPIO_writePin(WIFI_RESET_Port, WIFI_RESET_Pin, GPIO_HIGH);
    sleepBlockingMs(500);

    /* Pull NSS Low */
    GPIO_writePin(SPI3_NSS_Port, SPI3_NSS_Pin, GPIO_LOW);
    sleepBlockingMs(10);

    /* Wait for Drdy to be set by Wi-Fi module */
    while (!wifiDrdyFlag) {}
    wifiDrdyFlag = false;

    uint16_t data = 7820;
    SPI3->DR = data; /* dummy write to initiate clock */
	
	while(1) {
	    /* Infinite loop so that we don't exit main */
	    const SPI_Status_State result = SPI_read(SPI_SPI3, &data);
	    if (result == SPI_OK) {
	        print("Received something\r\n");
	        SPI3->DR = data; /* dummy write to initiate clock */
	    }
	}	
}

/*
* Interrupt handler for the TIM2 timer. Whenver a timer event occurs, this interrupt is triggered and this function is called.
*/
void TIM2_IRQHandler() {
    /* Reset the event flag and increment ms */
    TIM_resetEventFlag(TIM_TIM2);
    currentMs++;
}

/*
 * Interrupt handler for the EXTI1 interrupt.
 */
void EXTI1_IRQHandler() {
    /* Reset the interrupt */
    SET_BIT(EXTI->PR1, EXTI_PR1_PIF1_Msk);
    wifiDrdyFlag = true;
}

void ErrorHandler() {
	/* Light up the yellow LED on board */
	GPIO_setPinOutput(LEDError_Port, LEDError_Pin);
	GPIO_togglePin(LEDError_Port, LEDError_Pin);
	while(1) {
	/* If you've ended up here, then a problem has occured! */
	}
}

#endif