/*
 * 007_SPI_TxOnly_Arduino.c
 *
 *  Created on: Feb 19, 2024
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
//	GPIO_Handle_t SPI_MISO_Pin = SPIPins;
//	SPI_MISO_Pin.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;
//	GPIO_Init(&SPI_MISO_Pin);

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


int main(void){

	// GPIO Button
	GPIO_ButtonInit();

	char user_data[] = "Hello World! I'm an STM32";

	// Initialize the GPIO pins
	SPI2_GPIOInits();

	// Initialize the SPI2 Peripheral
	SPI2_Inits();

	// SSOE 1 Enables the NSS Output
	SPI_SSOEConfig(SPI2, ENABLE);



	while(1){
		// Wait for button press
		while(GPIO_ReadFromInputPin(GPIOC, GPIO_PIN_NO_13) != BUTTON_PRESSED);

		// For the De-bouncing of the Button
		delay();

		// Enable the SPI2 Peripheral
		SPI_PeripheralControl(SPI2, ENABLE);

		// Send Length Information
		uint8_t dataLength = strlen(user_data);
		SPI_SendData(SPI2, &dataLength, 1);

		// Send Data
		SPI_SendData(SPI2, (uint8_t*)user_data, strlen(user_data));

		// Wait until SPI is not Busy
		while(SPI_GetFlagStatus(SPI2, SPI_BUSY_FLAG));

		// Disable the SPI2 Peripheral
		SPI_PeripheralControl(SPI2, DISABLE);
	}


	return 0;
}

