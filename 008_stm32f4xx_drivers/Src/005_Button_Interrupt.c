/*
 * 005_Button_Interrupt.c
 *
 *  Created on: Feb 14, 2024
 *      Author: wyatt
 */

#include <string.h>
#include "stm32f446xx.h"


// Delay for the Button De-bounce
void delay(void){
	for(uint32_t i=0; i<500000/2; i++){

	}
}


int main(void){

	// Configure the Button
	GPIO_Handle_t Btn;
	memset(&Btn, 0, sizeof(Btn)); // Set the Registers to 0 so no Corruption happens
	Btn.pGPIOx = GPIOB;
	Btn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_6;
	Btn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
	Btn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	Btn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;

	// Configure the LED
	GPIO_Handle_t Led;
	memset(&Led, 0, sizeof(Led));
	Led.pGPIOx = GPIOA;
	Led.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_6;
	Led.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT;
	Led.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	Led.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	Led.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	// Enable Peripheral Clocks
	GPIO_PeriClockControl(Btn.pGPIOx, ENABLE);
	GPIO_PeriClockControl(Led.pGPIOx, ENABLE);

	// Initialize Peripherals
	GPIO_Init(&Btn);
	GPIO_Init(&Led);

	// Configure the Interrupt
	GPIO_IRQPriorityConfig(IRQ_NUM_EXTI9_5, NVIC_IRQ_PRIO15);
	GPIO_IRQInterruptConfig(IRQ_NUM_EXTI9_5, ENABLE);


	while(1);


	return 0;
}


// ISR (Interrupt Service Request)
void EXTI9_5_IRQHandler(void){
	delay();
	GPIO_IRQHandling(GPIO_PIN_NO_6);
	GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_NO_6);
}








