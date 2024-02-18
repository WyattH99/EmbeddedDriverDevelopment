/*
 * stm32f446xx_spi_driver.c
 *
 *  Created on: Feb 14, 2024
 *      Author: wyatt
 */

#include "stm32f446xx_spi_driver.h"


// Peripheral Clock Setup
void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnOrDi){
	if(EnOrDi == ENABLE){
		// Enable
		if(pSPIx == SPI1){
			SPI1_PCLK_EN();
		}else if(pSPIx == SPI2){
			SPI2_PCLK_EN();
		}else if(pSPIx == SPI3){
			SPI3_PCLK_EN();
		}
	}else{
		// Disable
		if(pSPIx == SPI1){
			SPI1_PCLK_DI();
		}else if(pSPIx == SPI2){
			SPI2_PCLK_DI();
		}else if(pSPIx == SPI3){
			SPI3_PCLK_DI();
		}
	}
}


// Initialize and De-Initialize
void SPI_Init(SPI_Handle_t *pSPI_Handle){
	// Enable Peripheral Clock
	SPI_PeriClockControl(pSPI_Handle->pSPIx, ENABLE);

	// Configure the SPI_CR1 Register
	uint32_t tempreg = 0;

	// 1. Device Mode
	tempreg |= pSPI_Handle->SPIConfig.SPI_DeviceMode << SPI_CR1_MSTR;

	// 2. BusConfig
	if(pSPI_Handle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_FULL_DUPLEX){
		// BIDI mode should be cleared
		tempreg &= ~(1 << SPI_CR1_BIDIMODE);

	}else if(pSPI_Handle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_HALF_DUPLEX){
		// BIDI mode should be set
		tempreg |= (1 << SPI_CR1_BIDIMODE);

	}else if(pSPI_Handle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_SIMPLEX_RXONLY){
		// BIDI mode should be cleared
		tempreg &= ~(1 << SPI_CR1_BIDIMODE);
		// RXONLY bit must be set
		tempreg |= (1 << SPI_CR1_RXONLY);
	}

	// 3. SclkSpeed (Baud Rate)
	tempreg |= pSPI_Handle->SPIConfig.SPI_SclkSpeed << SPI_CR1_BR;

	// 4. DFF (Data Frame Configuration)
	tempreg |= pSPI_Handle->SPIConfig.SPI_DFF << SPI_CR1_DFF;

	// 5. CPOL (Polarity)
	tempreg |= pSPI_Handle->SPIConfig.SPI_DFF << SPI_CR1_CPOL;

	// 6. CPHA (Phase)
	tempreg |= pSPI_Handle->SPIConfig.SPI_CPHA << SPI_CR1_CPHA;

	// 7. SSM
	tempreg |= pSPI_Handle->SPIConfig.SPI_SSM << SPI_CR1_SSM;

	pSPI_Handle->pSPIx->CR1 = tempreg;


}

void SPI_DeInit(SPI_RegDef_t *pSPIx){
	if(pSPIx == SPI1){
		SPI1_REG_RESET();
	}else if(pSPIx == SPI2){
		SPI2_REG_RESET();
	}else if(pSPIx == SPI3){
		SPI3_REG_RESET();
	}

}


uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, uint32_t FlagName){
	if(pSPIx->SR & FlagName){
		return FLAG_SET;
	}
	return FLAG_RESET;
}


// Data Send and Receive
// This is a blocking call
// Polling for the TXE Flag to be Set
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Length){
	while(Length > 0){
		// Wait until TX Buffer is empty
		while(SPI_GetFlagStatus(pSPIx, SPI_TXE_FLAG) == FLAG_RESET);

		// Check if 8bit or 16bit
		if((pSPIx->CR1 & (1 << SPI_CR1_DFF))){
			// 16bit
			// Load DR with 2 byte of data
			pSPIx->DR = *((uint16_t*)pTxBuffer);
			// Increment Buffer Address
			(uint16_t*)pTxBuffer++;
			// Length--
			Length--;
			Length--;
		}else{
			// 8bit
			pSPIx->DR = *pTxBuffer;
			pTxBuffer++;
			Length--;
		}
	}

}

void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Length){

}


// IRQ Configurations and ISR Handling
void SPI_IRQInterruptConfig(uint8_t IRQNumber,uint8_t EnOrDi){

}

void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority){

}

void SPI_IRQHandling(SPI_Handle_t *pHandle){

}

void SPI_PeripheralControl(SPI_RegDef_t *pSPIx, uint8_t EnOrDi){
	if(EnOrDi == ENABLE){
		// Enable
		pSPIx->CR1 |= (1 << SPI_CR1_SPE);
	}else{
		// Disable
		pSPIx->CR1 &= ~(1 << SPI_CR1_SPE);
	}
}

void SPI_SSIConfig(SPI_RegDef_t *pSPIx, uint8_t EnOrDi){
	if(EnOrDi == ENABLE){
		// Enable
		pSPIx->CR1 |= (1 << SPI_CR1_SSI);
	}else{
		// Disable
		pSPIx->CR1 &= ~(1 << SPI_CR1_SSI);
	}
}
