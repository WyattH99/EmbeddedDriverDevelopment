/*
 * 013_I2C_Slave_Tx_String.c
 *
 *  Created on: Feb 28, 2024
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


#define SLAVE_ADDR		0x69
#define MY_ADDR			SLAVE_ADDR

I2C_Handle_t I2C1Handle;

// Receive Buffer
uint8_t Tx_buf[32] = "STM32 Slave Testing";

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

	// I2C IRQ Configurations
	I2C_IRQInterruptConfig(IRQ_NUM_I2C1_EV, ENABLE);
	I2C_IRQInterruptConfig(IRQ_NUM_I2C1_ER, ENABLE);

	I2C_SlaveEnableDisableCallbackEvents(I2C1, ENABLE);

	// Enable the I2C1 Peripheral
	I2C_PeripheralControl(I2C1, ENABLE);

	// Enable ACKing after PE bit is set
	I2C_ManageAcking(I2C1, I2C_ACK_ENABLE);

	while(1);


	return 0;
}


void I2C1_EV_IRQHandler(void){
	I2C_EV_IRQHandling(&I2C1Handle);
}


void I2C1_ER_IRQHandler(void){
	I2C_ER_IRQHandling(&I2C1Handle);
}


void I2C_ApplicationEventCallback(I2C_Handle_t *pI2CHandle, uint8_t AppEvent){
	static uint8_t commandCode = 0;
	static uint8_t Cnt = 0;

	if(AppEvent == I2C_EV_DATA_REQ){
		// Master wants some data
		// Slave sends it
		if(commandCode == 0x51){
			// Send length information to master
			I2C_SlaveSendData(pI2CHandle->pI2Cx, strlen((char*)Tx_buf));
		}else if(commandCode == 0x52){
			// Send the Data
			I2C_SlaveSendData(pI2CHandle->pI2Cx, Tx_buf[Cnt++]);
		}

	}else if(AppEvent == I2C_EV_DATA_RCV){
		// Master is waiting for slave to read
		// Slave Reads it
		commandCode = I2C_SlaveReceiveData(pI2CHandle->pI2Cx);

	}else if(AppEvent == I2C_ERROR_AF){
		// This happens only during slave Txing
		// Master sent NACK.
		// Slave doesn't send more data
		commandCode = 0xff;
		Cnt = 0;

	}else if(AppEvent == I2C_EV_STOP){
		// Happens during slave Rxing
		// Master has ended the I2C communication with slave
	}
}

