/*
 * 003_Led_Button_External.c
 *
 *  Created on: Feb 12, 2024
 *      Author: wyatt
 */


#include "stm32f446xx.h"


int main(void){


	return 0;
}


void EXTI0_IRQHandler(void){
	// Handle the Interrupt
	GPIO_IRQHandling(0);
}
