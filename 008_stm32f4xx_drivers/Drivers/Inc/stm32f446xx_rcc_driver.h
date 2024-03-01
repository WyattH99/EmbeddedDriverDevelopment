/*
 * stm32f446xx_rcc_driver.h
 *
 *  Created on: Feb 29, 2024
 *      Author: wyatt
 */

#ifndef INC_STM32F446XX_RCC_DRIVER_H_
#define INC_STM32F446XX_RCC_DRIVER_H_


#include "stm32f446xx.h"




uint32_t RCC_GetPLLOutputClock(void);
uint32_t RCC_GetPCLK1Value(void);
uint32_t RCC_GetPCLK2Value(void);













#endif /* INC_STM32F446XX_RCC_DRIVER_H_ */
