/*
 * stm32f446xx_rcc_driver.c
 *
 *  Created on: Feb 29, 2024
 *      Author: wyatt
 */

#include "stm32f446xx_rcc_driver.h"



// Not implemented, just a placeholder
uint32_t RCC_GetPLLOutputClock(void){
	uint32_t temp = 0;
	return temp;
}

uint16_t AHB_PreScaler[8] = {2, 4, 8, 16, 64, 128, 512};
uint16_t APB1_PreScaler[4] = {2, 4, 8, 16};
uint16_t APB2_PreScaler[4] = {2, 4, 8, 16};

uint32_t RCC_GetPCLK1Value(void){
	uint32_t pclk1, SystemClk;

	uint8_t clksrc, temp, ahbp, apb1p;
	clksrc = (RCC->CFGR >> 2) & 0x3;

	if(clksrc == 0){
		SystemClk = 16000000;
	}else if(clksrc == 1){
		SystemClk = 8000000;
	}else if(clksrc == 2){
		SystemClk = RCC_GetPLLOutputClock();
	}

	// AHB Pre-scaler
	temp = (RCC->CFGR >> 4) & 0xF;
	if(temp < 8){
		ahbp = 1;
	}else{
		ahbp = AHB_PreScaler[temp-8];
	}

	// APB1 Pre-scaler
	temp = (RCC->CFGR >> 10) & 0x7;
	if(temp < 8){
		apb1p = 1;
	}else{
		apb1p = APB1_PreScaler[temp-4];
	}

	pclk1 = (SystemClk / ahbp) / apb1p;

	return pclk1;
}


uint32_t RCC_GetPCLK2Value(void){
	uint32_t pclk2, SystemClk;

	uint8_t clksrc, temp, ahbp, apb2p;
	clksrc = (RCC->CFGR >> 2) & 0x3;

	if(clksrc == 0){
		SystemClk = 16000000;
	}else if(clksrc == 1){
		SystemClk = 8000000;
	}else if(clksrc == 2){
		SystemClk = RCC_GetPLLOutputClock();
	}

	// AHB Pre-scaler
	temp = (RCC->CFGR >> 4) & 0xF;
	if(temp < 0x08){
		ahbp = 1;
	}else{
		ahbp = AHB_PreScaler[temp-8];
	}

	// APB2 Pre-scaler
	temp = (RCC->CFGR >> 13) & 0x7;
	if(temp < 0x04){
		apb2p = 1;
	}else{
		apb2p = APB2_PreScaler[temp-4];
	}

	pclk2 = (SystemClk / ahbp) / apb2p;

	return pclk2;
}













