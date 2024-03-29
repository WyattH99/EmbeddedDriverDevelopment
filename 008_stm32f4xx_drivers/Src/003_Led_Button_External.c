/*
 * 003_Led_Button_External.c
 *
 *  Created on: Feb 12, 2024
 *      Author: wyatt
 */


#include "stm32f446xx.h"

#define BUTTON_PRESSED GPIO_PIN_RESET


void delay(void){
	for(uint32_t i=0; i<500000/2; i++){

	}
}

int main(void){

	// Declare External Led and External Button
	GPIO_Handle_t Led_Ext;
	GPIO_Handle_t Btn_Ext;

	// Configure External Led PA6
	Led_Ext.pGPIOx = GPIOA;
	Led_Ext.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_6;
	Led_Ext.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT;
	Led_Ext.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	Led_Ext.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	Led_Ext.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	// Configure the Button
	Btn_Ext.pGPIOx = GPIOB;
	Btn_Ext.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_6;
	Btn_Ext.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_INPUT;
	Btn_Ext.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	Btn_Ext.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	// Enable Port A Clock
	GPIO_PeriClockControl(Led_Ext.pGPIOx, ENABLE);
	GPIO_PeriClockControl(Btn_Ext.pGPIOx, ENABLE);

	// Initialize External Led and Button
	GPIO_Init(&Led_Ext);
	GPIO_Init(&Btn_Ext);

	while(1){

		// Toggle External Led when Button Pressed
		if(GPIO_ReadFromInputPin(Btn_Ext.pGPIOx, Btn_Ext.GPIO_PinConfig.GPIO_PinNumber) == BUTTON_PRESSED){
			delay();
			GPIO_ToggleOutputPin(Led_Ext.pGPIOx, Led_Ext.GPIO_PinConfig.GPIO_PinNumber);
		}

	}

	return 0;
}

