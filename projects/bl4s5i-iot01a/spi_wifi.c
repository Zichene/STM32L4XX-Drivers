#include "common.h"
#include "uart.h"
#include "spi.h"
#include "string.h"
#include "gpio.h"
#include "tim.h"
#include "system.h"

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

#define RX_BUF_SIZE 1000
#define CMD_BUF_SIZE 100
#define WIFI_TIMEOUT 1000
static void ErrorHandler();
static void configUART();
static void configSPI();
static void wifiInit();
static void wifiSendATCommand(char* command, uint32_t command_size);

/* global variables */
volatile uint8_t usartIsIdle = true;
volatile uint8_t wifiDrdyFlag = false;
uint8_t rxBuf[RX_BUF_SIZE];
uint8_t commandBuf[CMD_BUF_SIZE];
uint16_t numBytes = 0;


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
* Use the UART_transmit() function and the string.h library to print a message!
*/
static void print(const char* message) {
	UART_transmit(UART_USART1, (uint8_t*) message, strlen(message));
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
        .RXNEIE_enabled = true,
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

static void wifiInit() {
    /* reset rx buffer */
    memset(rxBuf, 0, RX_BUF_SIZE);

    /* Initiating the Wi-Fi module */
    GPIO_writePin(WIFI_RESET_Port, WIFI_RESET_Pin, GPIO_LOW);
    SYST_sleepMs(10);
    GPIO_writePin(WIFI_RESET_Port, WIFI_RESET_Pin, GPIO_HIGH);
    SYST_sleepMs(500);

    /* Pull NSS Low */
    GPIO_writePin(SPI3_NSS_Port, SPI3_NSS_Pin, GPIO_LOW);
    SYST_sleepMs(10);

    /* Wait for Drdy to be set by Wi-Fi module */
    while (!wifiDrdyFlag) {}
    wifiDrdyFlag = false;

    SPI_transmitReceive(SPI_SPI3, 1, rxBuf, 6, WIFI_TIMEOUT);

    /* Pull NSS High */
    GPIO_writePin(SPI3_NSS_Port, SPI3_NSS_Pin, GPIO_HIGH);
    SYST_sleepMs(10);

    /* Messages from the Wi-Fi module are padded with two bytes of useless information */
    if (strcmp((char*) (rxBuf + 2), "\r\n> ") != 0) {
        print("Could not obtain correct power up sequence from WiFi module!\r\n");
    } else {
        print("Wi-Fi successfully powered up!\r\n");
    }
}

static void wifiSendATCommand(char* command, const uint32_t command_size) {
    /* Print info message */
    print("Sending command to Wi-Fi module: ");
    print(command);

    /* Try to send an AT command to the Wi-Fi module */
    memset(rxBuf, 0, RX_BUF_SIZE);
    numBytes = 0;

    /* Wait for Drdy to be set by Wi-Fi module */
    while (!wifiDrdyFlag) {}
    wifiDrdyFlag = false;

    /*!> SPI Command Phase */

    /* Pull NSS Low */
    GPIO_writePin(SPI3_NSS_Port, SPI3_NSS_Pin, GPIO_LOW);
    SYST_sleepMs(10);

    /* Send command */
    if (SPI_transmitReceive(SPI_SPI3, 0, (uint8_t*) command, command_size, WIFI_TIMEOUT) != SPI_OK) {
        ErrorHandler();
    }

    /* Pull NSS High */
    GPIO_writePin(SPI3_NSS_Port, SPI3_NSS_Pin, GPIO_HIGH);
    SYST_sleepMs(10);

    /*!> End of SPI Command Phase, Beginning of Data Phase */

    /* Pull NSS Low */
    GPIO_writePin(SPI3_NSS_Port, SPI3_NSS_Pin, GPIO_LOW);
    SYST_sleepMs(10);

    /* Wait for Drdy to be set by Wi-Fi module */
    while (!wifiDrdyFlag) {}
    wifiDrdyFlag = false;

    while (GPIO_readPin(WIFI_DRDY_Port, WIFI_DRDY_Pin) == GPIO_HIGH) {
        if (SPI_transmitReceive(SPI_SPI3, 1, rxBuf + numBytes, 2, WIFI_TIMEOUT) != SPI_OK) {
            ErrorHandler();
        }
        numBytes += 2;
    }

    /* Pull NSS High */
    GPIO_writePin(SPI3_NSS_Port, SPI3_NSS_Pin, GPIO_HIGH);
    SYST_sleepMs(10);

    print("Received from Wi-Fi module: \r\n");
    UART_transmit(UART_USART1, rxBuf, numBytes);
}

int main(void)
{
	/* configure system, uart and spi */
	SYST_init();
	configUART();
    configSPI();

    /* Initiating the Wi-Fi module */
    wifiInit();

    /* Try to send an AT command to the Wi-Fi module */
    wifiSendATCommand("I?\r\n", 4);

    /* Set up buffer to store user input */
    uint32_t commandBufBytes = 0;
    memset(commandBuf, 0, CMD_BUF_SIZE);

	while(1) {
	    /* Infinite loop so that we don't exit main */
	    if (UART_read(commandBuf + commandBufBytes, 1) == UART_OK) {
	        commandBufBytes += 1;

	        if (strstr((char*) commandBuf, "\r\n") != NULL) {
	            /* The user input has terminated with \r\n. Assume this is a command to be sent */
	            wifiSendATCommand((char*) commandBuf, commandBufBytes);
	            // Reset
	            commandBufBytes = 0;
	            memset(commandBuf, 0, CMD_BUF_SIZE);
	        }
	    }
	}	
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
	/* If you've ended up here, then a problem has occurred! */
	}
}

#endif