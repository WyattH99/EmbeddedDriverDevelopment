/*
 * 008_SPI_Cmd_Handling.c
 *
 *  Created on: Feb 20, 2024
 *      Author: wyatt
 */



#include "stm32f446xx.h"
#include <string.h>

/*
 * SPI2 Pins:
 * MISO --> PB14
 * MOSI --> PB15
 * SCLK --> PB13
 * NSS  --> PB12
 * ALT Function Mode: 5
 */

#define BUTTON_PRESSED GPIO_PIN_RESET

// Command Codes
#define COMMAND_LED_CTRL		0x50
#define COMMAND_SENSOR_READ		0x51
#define COMMAND_LED_READ		0x52
#define	COMMAND_PRINT			0x53
#define COMMAND_ID_READ			0x54

#define ACKBYTE					0xF5
#define NACKBYTE				0xA5

// Arduino Pins
#define ANALOG_PIN0			0
#define ANALOG_PIN1			1
#define ANALOG_PIN2			2
#define ANALOG_PIN3			3
#define ANALOG_PIN4			4

#define LED_PIN		9
#define LED_ON		1
#define LED_OFF		0



void delay(void){
	for(uint32_t i=0; i<500000/2; i++){

	}
}

void SPI2_GPIOInits(void){

	GPIO_Handle_t SPIPins;

	// Common Settings between Pins
	SPIPins.pGPIOx = GPIOB;
	SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFUN;
	SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
	SPIPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	SPIPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	SPIPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	// MISO
	GPIO_Handle_t SPI_MISO_Pin = SPIPins;
	SPI_MISO_Pin.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;
	GPIO_Init(&SPI_MISO_Pin);

	// MOSI
	GPIO_Handle_t SPI_MOSI_Pin = SPIPins;
	SPI_MOSI_Pin.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15;
	GPIO_Init(&SPI_MOSI_Pin);

	// SCLK
	GPIO_Handle_t SPI_SCLK_Pin = SPIPins;
	SPI_SCLK_Pin.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	GPIO_Init(&SPI_SCLK_Pin);

	// NSS
	GPIO_Handle_t SPI_NSS_Pin = SPIPins;
	SPI_NSS_Pin.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	GPIO_Init(&SPI_NSS_Pin);

}


void SPI2_Inits(void){
	SPI_Handle_t SPI2Handle;

	SPI2Handle.pSPIx = SPI2;

	SPI2Handle.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FULL_DUPLEX;
	SPI2Handle.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI2Handle.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV8; // Generates sclk of 2MHz
	SPI2Handle.SPIConfig.SPI_DFF = SPI_DFF_8BITS;
	SPI2Handle.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;
	SPI2Handle.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
	SPI2Handle.SPIConfig.SPI_SSM = SPI_SSM_DI; // Hardware slave management

	SPI_Init(&SPI2Handle);

}

void GPIO_ButtonInit(void){

	GPIO_Handle_t GpioButton;
	// Configure the Button
	GpioButton.pGPIOx = GPIOC;
	GpioButton.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	GpioButton.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_INPUT;
	GpioButton.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	GpioButton.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIO_Init(&GpioButton);
}


uint8_t SPI_VerifyResponse(uint8_t ackbyte){
	if(ackbyte == ACKBYTE){
		// ack
		return 1;
	}
	// nack
	return 0;
}

int main(void){

	// GPIO Button
	GPIO_ButtonInit();

	// Initialize the GPIO pins
	SPI2_GPIOInits();

	// Initialize the SPI2 Peripheral
	SPI2_Inits();

	// SSOE 1 Enables the NSS Output
	SPI_SSOEConfig(SPI2, ENABLE);


	uint8_t dummy_write = 0xff;
	uint8_t dummy_read;

	while(1){


		// Wait for button press
		while(GPIO_ReadFromInputPin(GPIOC, GPIO_PIN_NO_13) != BUTTON_PRESSED);
		// For the De-bouncing of the Button
		delay();

		// Enable the SPI2 Peripheral
		SPI_PeripheralControl(SPI2, ENABLE);

		// Execute CMD_LED_CTRL <pin no(1)> <value(1)>
		uint8_t command_code = COMMAND_LED_CTRL;
		uint8_t ackbyte;
		uint8_t args[2];
		// Send Data
		SPI_SendData(SPI2, &command_code, 1);
		SPI_ReceiveData(SPI2, &dummy_read, 1); // Dummy Read to clear the RXNE
		// Receive Data
		SPI_SendData(SPI2, &dummy_write, 1); // Send dummy byte to fetch the response from the slave
		SPI_ReceiveData(SPI2, &ackbyte, 1);
		if( SPI_VerifyResponse(ackbyte) ){
			// Send Arguments
			args[0] = LED_PIN;
			args[1] = LED_ON;
			SPI_SendData(SPI2, args, 2);
		}


		// Wait for button press
		while(GPIO_ReadFromInputPin(GPIOC, GPIO_PIN_NO_13) != BUTTON_PRESSED);
		// For the De-bouncing of the Button
		delay();


		// Execute CMD_SENSOR_READ <analog pin number(1)>
		command_code = COMMAND_SENSOR_READ;
		// Send Data
		SPI_SendData(SPI2, &command_code, 1);
		SPI_ReceiveData(SPI2, &dummy_read, 1); // Dummy Read to clear the RXNE
		// Receive Data
		SPI_SendData(SPI2, &dummy_write, 1); // Send dummy byte to fetch the response from the slave
		SPI_ReceiveData(SPI2, &ackbyte, 1);
		if( SPI_VerifyResponse(ackbyte) ){
			// Send Arguments
			args[0] = ANALOG_PIN0;
			SPI_SendData(SPI2, args, 1);
			SPI_ReceiveData(SPI2, &dummy_read, 1); // Dummy Read to clear the RXNE
			delay();
			// Receive Data
			SPI_SendData(SPI2, &dummy_write, 1); // Send dummy byte to fetch the response from the slave
			uint8_t analog_read;
			SPI_ReceiveData(SPI2, &analog_read, 1);
		}


		// Wait for button press
		while(GPIO_ReadFromInputPin(GPIOC, GPIO_PIN_NO_13) != BUTTON_PRESSED);
		// For the De-bouncing of the Button
		delay();

		//-----------------------------------------
		// Execute CMD_LED_READ <pin no(1)>
		command_code = COMMAND_LED_READ;
		// Send Data
		SPI_SendData(SPI2, &command_code, 1);
		SPI_ReceiveData(SPI2, &dummy_read, 1); // Dummy Read to clear the RXNE
		// Receive Data
		SPI_SendData(SPI2, &dummy_write, 1); // Send dummy byte to fetch the response from the slave
		SPI_ReceiveData(SPI2, &ackbyte, 1);
		if( SPI_VerifyResponse(ackbyte) ){
			// Send Arguments
			args[0] = LED_PIN;
			SPI_SendData(SPI2, args, 1);
			SPI_ReceiveData(SPI2, &dummy_read, 1); // Dummy Read to clear the RXNE
			delay();
			// Receive Data
			SPI_SendData(SPI2, &dummy_write, 1); // Send dummy byte to fetch the response from the slave
			uint8_t led_read;
			SPI_ReceiveData(SPI2, &led_read, 1);
		}


		// Wait for button press
		while(GPIO_ReadFromInputPin(GPIOC, GPIO_PIN_NO_13) != BUTTON_PRESSED);
		// For the De-bouncing of the Button
		delay();


		// Execute CMD_PRINT <length(2)> <message(length)>
		command_code = COMMAND_PRINT;
		// Send Data
		SPI_SendData(SPI2, &command_code, 1);
		SPI_ReceiveData(SPI2, &dummy_read, 1); // Dummy Read to clear the RXNE
		// Receive Data
		SPI_SendData(SPI2, &dummy_write, 1); // Send dummy byte to fetch the response from the slave
		SPI_ReceiveData(SPI2, &ackbyte, 1);
		if( SPI_VerifyResponse(ackbyte) ){
			// Send Arguments
			char secret_message[] = "This is a Secrete Message for the Arduino";
			args[0] = strlen(secret_message);
			SPI_SendData(SPI2, args, 1);
			SPI_ReceiveData(SPI2, &dummy_read, 1); // Dummy Read to clear the RXNE
			SPI_SendData(SPI2, (uint8_t*)secret_message, strlen(secret_message));
		}


		// Wait for button press
		while(GPIO_ReadFromInputPin(GPIOC, GPIO_PIN_NO_13) != BUTTON_PRESSED);
		// For the De-bouncing of the Button
		delay();


		// Execute CMD_ID_READ
		command_code = COMMAND_ID_READ;
		// Send Data
		SPI_SendData(SPI2, &command_code, 1);
		SPI_ReceiveData(SPI2, &dummy_read, 1); // Dummy Read to clear the RXNE
		// Receive Data
		SPI_SendData(SPI2, &dummy_write, 1); // Send dummy byte to fetch the response from the slave
		SPI_ReceiveData(SPI2, &ackbyte, 1);
		if( SPI_VerifyResponse(ackbyte) ){
			uint8_t board_id[10];
			for(int i=0; i<10; i++){
				// Receive A Byte
				SPI_SendData(SPI2, &dummy_write, 1); // Send dummy byte to fetch the response from the slave
				SPI_ReceiveData(SPI2, &board_id[i], 1);
			}

		}




		// Wait until SPI is not Busy
		while(SPI_GetFlagStatus(SPI2, SPI_BUSY_FLAG));
		// Disable the SPI2 Peripheral
		SPI_PeripheralControl(SPI2, DISABLE);
	}


	return 0;
}

