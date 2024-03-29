/*
 * 002_Led_Button.c
 *
 *  Created on: Feb 12, 2024
 *      Author: wyatt
 */


#include "stm32f446xx.h"

#define BUTTON_PRESSED GPIO_PIN_SET


void delay(void){
	for(uint32_t i=0; i<500000/2; i++){

	}
}

int main(void){

	GPIO_Handle_t GpioLed;
	GPIO_Handle_t GpioButton;

	// Configure the Led
	GpioLed.pGPIOx = GPIOA;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT;
	GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	// Configure the Button
	GpioButton.pGPIOx = GPIOC;
	GpioButton.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	GpioButton.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_INPUT;
	GpioButton.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	GpioButton.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	// Enable Port Clocks
	GPIO_PeriClockControl(GpioLed.pGPIOx, ENABLE);
	GPIO_PeriClockControl(GpioButton.pGPIOx, ENABLE);

	// Initialize the Led and Button
	GPIO_Init(&GpioLed);
	GPIO_Init(&GpioButton);


	while(1){

		// Toggle when Button Pressed
		if(GPIO_ReadFromInputPin(GpioButton.pGPIOx, GpioButton.GPIO_PinConfig.GPIO_PinNumber) == BUTTON_PRESSED){
			delay(); // For the De-bouncing of the Button
			GPIO_ToggleOutputPin(GpioLed.pGPIOx, GpioLed.GPIO_PinConfig.GPIO_PinNumber);
		}


		// Set when button Pressed
		/*
		if(GPIO_ReadFromInputPin(GpioButton.pGPIOx, GpioButton.GPIO_PinConfig.GPIO_PinNumber) == BUTTON_PRESSED){
			GPIO_WriteToOutputPin(GpioLed.pGPIOx, GpioLed.GPIO_PinConfig.GPIO_PinNumber, GPIO_PIN_SET);
		}else{
			GPIO_WriteToOutputPin(GpioLed.pGPIOx, GpioLed.GPIO_PinConfig.GPIO_PinNumber, GPIO_PIN_RESET);
		}
		 */


	}



	return 0;
}
