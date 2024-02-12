/*
 * 001_Led_Toggle.c
 *
 *  Created on: Feb 12, 2024
 *      Author: wyatt
 */

#include "stm32f446xx.h"


void delay(void){
	for(uint32_t i=0; i<500000/2; i++){

	}
}



int main(void){

	GPIO_Handle_t GpioLed;

	// Set the Port and Pin Configurations
	GpioLed.pGPIOx = GPIOA;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT;
	GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	// Enable the Port Clock
	GPIO_PeriClockControl(GPIOA, ENABLE);

	// Initialize
	GPIO_Init(&GpioLed);

	while(1){
		GPIO_ToggleOutputPin(GpioLed.pGPIOx, GpioLed.GPIO_PinConfig.GPIO_PinNumber);
		delay();
	}




	return 0;
}
