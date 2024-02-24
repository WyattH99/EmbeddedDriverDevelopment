/*
 * 011_I2C_Master_Rx_Testing.c
 *
 *  Created on: Feb 23, 2024
 *      Author: wyatt
 */




#include "stm32f446xx.h"
#include <string.h>

/*
 * I2C1 Pins:
 * SCL --> PB8
 * SDA --> PB9
 * ALT Function Mode: 5
 */

#define BUTTON_PRESSED GPIO_PIN_RESET

#define MY_ADDR 		0x61
#define SLAVE_ADDR		0x68


I2C_Handle_t I2C1Handle;

// Receive Buffer
uint8_t rcv_buf[32];

void delay(void){
	for(uint32_t i=0; i<500000/2; i++){

	}
}

void I2C1_GPIOInits(void){

	GPIO_Handle_t I2CPins;

	// Common Settings between Pins
	I2CPins.pGPIOx = GPIOB;
	I2CPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFUN;
	I2CPins.GPIO_PinConfig.GPIO_PinAltFunMode = 4;
	I2CPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_OD;
	I2CPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD; // External Pull-UP Used
	I2CPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;


	// SCL
	GPIO_Handle_t I2C_SCL_Pin = I2CPins;
	I2C_SCL_Pin.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_8;
	GPIO_Init(&I2C_SCL_Pin);

	// SDA
	GPIO_Handle_t I2C_SDA_Pin = I2CPins;
	I2C_SDA_Pin.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_9;
	GPIO_Init(&I2C_SDA_Pin);

}


void I2C1_Inits(void){

	I2C1Handle.pI2Cx = I2C1;
	I2C1Handle.I2C_Config.I2C_ACKControl = I2C_ACK_ENABLE;
	I2C1Handle.I2C_Config.I2C_DeviceAddress = MY_ADDR;
	I2C1Handle.I2C_Config.I2C_FMDutyCycle = I2C_FM_DUTY_2;
	I2C1Handle.I2C_Config.I2C_SCLSpeed = I2C_SCL_SPEED_SM;

	I2C_Init(&I2C1Handle);

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

	// Initialize the GPIO pins
	I2C1_GPIOInits();

	// Initialize the I2C1 Peripheral
	I2C1_Inits();

	// Enable the I2C1 Peripheral
	I2C_PeripheralControl(I2C1, ENABLE);

	// Enable ACKing after PE bit is set
	I2C_ManageAcking(I2C1, I2C_ACK_ENABLE);

	uint8_t commandcode, length;

	while(1){
		// Wait for button press
		while(GPIO_ReadFromInputPin(GPIOC, GPIO_PIN_NO_13) != BUTTON_PRESSED);
		// For the De-bouncing of the Button
		delay();

		// Request the Length (0x51)
		commandcode = 0x51;
		I2C_MasterSendData(&I2C1Handle, &commandcode, 1, SLAVE_ADDR, I2C_ENABLE_SR);
		I2C_MasterReceiveData(&I2C1Handle, &length, 1, SLAVE_ADDR, I2C_ENABLE_SR);

		// Read the Message (0x52)
		commandcode = 0x52;
		I2C_MasterSendData(&I2C1Handle, &commandcode, 1, SLAVE_ADDR, I2C_ENABLE_SR);
		I2C_MasterReceiveData(&I2C1Handle, rcv_buf, length, SLAVE_ADDR, I2C_DISABLE_SR);


		// Printf

	}



	return 0;
}
