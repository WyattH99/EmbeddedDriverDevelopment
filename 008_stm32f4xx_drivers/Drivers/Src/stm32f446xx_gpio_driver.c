/*
 * stm32f446xx_gpio_driver.c
 *
 *  Created on: Feb 10, 2024
 *      Author: wyatt
 */


#include "stm32f446xx_gpio_driver.h"



/*
 * Peripheral Clock Control
 */
// Commenting done in this format to be able to auto-generate the Documentation with Doxygen
/*********************************************************************
 * @fn      		  - GPIO_PeriClockControl
 *
 * @brief             - This function enables or disables peripheral clock for the given GPIO port
 *
 * @param[in]         - Base Address of the GPIO Peripheral
 * @param[in]         - ENABLE or DISABLE macros
 * @param[in]         -
 *
 * @return            -  void
 *
 * @Note              -  none

 */
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnOrDi){
	if(EnOrDi == ENABLE){ // Enable
		if(pGPIOx == GPIOA){
			GPIOA_PCLK_EN();
		}else if(pGPIOx == GPIOB){
			GPIOB_PCLK_EN();
		}else if(pGPIOx == GPIOC){
			GPIOC_PCLK_EN();
		}else if(pGPIOx == GPIOD){
			GPIOD_PCLK_EN();
		}else if(pGPIOx == GPIOE){
			GPIOE_PCLK_EN();
		}else if(pGPIOx == GPIOF){
			GPIOF_PCLK_EN();
		}else if(pGPIOx == GPIOG){
			GPIOG_PCLK_EN();
		}else if(pGPIOx == GPIOH){
			GPIOH_PCLK_EN();
		}
	}else{ // Disable
		if(pGPIOx == GPIOA){
			GPIOA_PCLK_DI();
		}else if(pGPIOx == GPIOB){
			GPIOB_PCLK_DI();
		}else if(pGPIOx == GPIOC){
			GPIOC_PCLK_DI();
		}else if(pGPIOx == GPIOD){
			GPIOD_PCLK_DI();
		}else if(pGPIOx == GPIOE){
			GPIOE_PCLK_DI();
		}else if(pGPIOx == GPIOF){
			GPIOF_PCLK_DI();
		}else if(pGPIOx == GPIOG){
			GPIOG_PCLK_DI();
		}else if(pGPIOx == GPIOH){
			GPIOH_PCLK_DI();
		}
	}

}


/*
 * Initialize and De-Initialize
 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle){
	uint32_t temp = 0; // Temporary Register

	// 1. Configure Mode of GPIO Pin
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG){
		temp = pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		pGPIOHandle->pGPIOx->MODER &= ~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); // Clear
		pGPIOHandle->pGPIOx->MODER |= temp; // Set
		temp = 0;
	}else{
		// TODO: Interrupt Mode
	}

	// 2. Configure Speed
	temp = pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->OSPEEDR &= ~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); // Clear
	pGPIOHandle->pGPIOx->OSPEEDR |= temp;
	temp = 0;

	// 3. Configure Pull-up Pull-down Settings
	temp = pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->PUPDR &= ~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); // Clear
	pGPIOHandle->pGPIOx->PUPDR |= temp;
	temp = 0;

	// 4. Configure the Output Type
	temp = pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber;
	pGPIOHandle->pGPIOx->OTYPER &= ~(0x1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); // Clear
	pGPIOHandle->pGPIOx->OTYPER |= temp;
	temp = 0;

	// 5. Configure Alternate Functionality
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFUN){
		if(pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber <= GPIO_PIN_NO_7){
				// AFRL Registers
				temp = pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << (4 * (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8));
				pGPIOHandle->pGPIOx->AFRL &= ~(0xF << (4 * (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8))); // Clear
				pGPIOHandle->pGPIOx->AFRL |= temp;
				temp = 0;
			}else{
				// AFRH Registers
				temp = pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << (4 * (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8));
				pGPIOHandle->pGPIOx->AFRH &= ~(0xF << (4 * (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8))); // Clear
				pGPIOHandle->pGPIOx->AFRH |= temp;
				temp = 0;
			}
	}

}

void GPIO_DeInit(GPIO_RegDef_t *pGPIOx){
		if(pGPIOx == GPIOA){
			GPIOA_REG_RESET();
		}else if(pGPIOx == GPIOB){
			GPIOB_REG_RESET();
		}else if(pGPIOx == GPIOC){
			GPIOC_REG_RESET();
		}else if(pGPIOx == GPIOD){
			GPIOD_REG_RESET();
		}else if(pGPIOx == GPIOE){
			GPIOE_REG_RESET();
		}else if(pGPIOx == GPIOF){
			GPIOF_REG_RESET();
		}else if(pGPIOx == GPIOG){
			GPIOG_REG_RESET();
		}else if(pGPIOx == GPIOH){
			GPIOH_REG_RESET();
		}
}


/*
 * Data Read and Write
 */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber){
	uint8_t value;
	value = (uint8_t)((pGPIOx->IDR >> PinNumber) & 0x00000001);
	return value;
}

uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx){
	uint16_t value;
	value = (uint16_t)pGPIOx->IDR;
	return value;

}

void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value){
	if(Value == GPIO_PIN_SET){
		// Set 1
		pGPIOx->ODR |= (1 << PinNumber);
	}else{
		// Set 0
		pGPIOx->ODR &= ~(1 << PinNumber);
	}

}

void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value){
	pGPIOx->ODR = Value;
}

void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber){
	pGPIOx->ODR ^= (1 << PinNumber);
}


/*
 * IRQ Configuration and ISR Handling
 */
void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnOrDi){

}

void GPIO_IRQHandling(uint8_t PinNumber){

}










