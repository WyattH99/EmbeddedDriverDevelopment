/*
 * stm32f446xx_spi_driver.c
 *
 *  Created on: Feb 14, 2024
 *      Author: wyatt
 */

#include "stm32f446xx_spi_driver.h"

static void spi_txe_interrupt_handle(SPI_Handle_t *pSPIHandle);
static void spi_rxne_interrupt_handle(SPI_Handle_t *pSPIHandle);
static void spi_ovr_err_interrupt_handle(SPI_Handle_t *pSPIHandle);


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
	while(Length > 0){
		// Wait until RX Buffer is empty
		while(SPI_GetFlagStatus(pSPIx, SPI_RXNE_FLAG) == FLAG_RESET);

		// Check if 8bit or 16bit
		if((pSPIx->CR1 & (1 << SPI_CR1_DFF))){
			// 16bit
			// Load data from DR to RxBuffer Address
			*((uint16_t*)pRxBuffer) = pSPIx->DR;
			// Increment Buffer Address
			(uint16_t*)pRxBuffer++;
			// Length--
			Length--;
			Length--;
		}else{
			// 8bit
			*pRxBuffer = pSPIx->DR;
			pRxBuffer++;
			Length--;
		}
	}

}


// IRQ Configurations and ISR Handling
void SPI_IRQInterruptConfig(uint8_t IRQNumber,uint8_t EnOrDi){
	if(EnOrDi == ENABLE){
		// Enable
		if(IRQNumber <= 31){
			// Program ISER0 Register
			*NVIC_ISER0 |= (1 << IRQNumber);
		}else if(IRQNumber > 31 && IRQNumber < 64){
			// Program ISER1 Register
			*NVIC_ISER1 |= (1 << (IRQNumber % 32));
		}else if(IRQNumber >= 64 && IRQNumber < 96){
			// Program ISER2 Register
			*NVIC_ISER2 |= (1 << (IRQNumber % 32));
		}
	}else{
		// Disable
		if(IRQNumber <= 31){
			// Program ICER0 Register
			*NVIC_ICER0 |= (1 << IRQNumber);
		}else if(IRQNumber > 31 && IRQNumber < 64){
			// Program ICER1 Register
			*NVIC_ICER1 |= (1 << (IRQNumber % 32));
		}else if(IRQNumber >= 64 && IRQNumber < 96){
			// Program ICER2 Register
			*NVIC_ICER2 |= (1 << (IRQNumber % 32));
		}
	}
}


void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority){
	uint8_t iprx = IRQNumber / 4;
	uint8_t iprx_section = IRQNumber % 4;
	uint8_t shift_amount = (8 * iprx_section) + (8 - NUM_PR_BITS_IMPLEMENTED);
	*(NVIC_IPR_BASE_ADDR + iprx) |= (IRQPriority << shift_amount);
}


void SPI_IRQHandling(SPI_Handle_t *pHandle){
	uint8_t txe = pHandle->pSPIx->SR & (1 << SPI_SR_TXE);
	uint8_t txeie = pHandle->pSPIx->CR2 & (1 << SPI_CR2_TXEIE);
	if(txe && txeie){
		// Handle TXE
		spi_txe_interrupt_handle(pHandle);
	}

	uint8_t rxne = pHandle->pSPIx->SR & (1 << SPI_SR_RXNE);
	uint8_t rxneie = pHandle->pSPIx->CR2 & (1 << SPI_CR2_RXNEIE);
	if(rxne && rxneie){
		// Handle RXNE
		spi_rxne_interrupt_handle(pHandle);
	}

	uint8_t ovr = pHandle->pSPIx->SR & (1 << SPI_SR_OVR);
	uint8_t errie = pHandle->pSPIx->CR2 & (1 << SPI_CR2_ERRIE);
	if(ovr && errie){
		// Handle ovr
		spi_ovr_err_interrupt_handle(pHandle);
	}

}


uint8_t SPI_SendDataIT(SPI_Handle_t *pSPIHandle, uint8_t *pTxBuffer, uint32_t Length){
	uint8_t state = pSPIHandle->TxState;
	if( state != SPI_BUSY_IN_TX){
		// 1. Save the Tx Buffer Address and Length
		pSPIHandle->pTxBuffer = pTxBuffer;
		pSPIHandle->TxLength = Length;

		// 2. Update SPI State as busy in Tx so no other code can take over
		pSPIHandle->TxState = SPI_BUSY_IN_TX;

		// 3. Enable TXEIE Control Bit to get Interrupt whenever TXE flag is set in SR
		pSPIHandle->pSPIx->CR2 |= (1 << SPI_CR2_TXEIE);
	}

	return state;

}

uint8_t SPI_ReceiveDataIT(SPI_Handle_t *pSPIHandle, uint8_t *pRxBuffer, uint32_t Length){
	uint8_t state = pSPIHandle->RxState;
	if( state != SPI_BUSY_IN_RX){
		// 1. Save the Rx Buffer Address and Length
		pSPIHandle->pRxBuffer = pRxBuffer;
		pSPIHandle->RxLength = Length;

		// 2. Update SPI State as busy in Rx so no other code can take over
		pSPIHandle->RxState = SPI_BUSY_IN_RX;

		// 3. Enable TXEIE Control Bit to get Interrupt whenever RXNEIE flag is set in SR
		pSPIHandle->pSPIx->CR2 |= (1 << SPI_CR2_RXNEIE);
	}

	return state;

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


void SPI_SSOEConfig(SPI_RegDef_t *pSPIx, uint8_t EnOrDi){
	if(EnOrDi == ENABLE){
		// Enable
		pSPIx->CR2 |= (1 << SPI_CR2_SSOE);
	}else{
		// Disable
		pSPIx->CR2 &= ~(1 << SPI_CR2_SSOE);
	}
}


/*
 * SPI ISR Helper Functions
 */
static void spi_txe_interrupt_handle(SPI_Handle_t *pSPIHandle){
	// Check if 8bit or 16bit
	if((pSPIHandle->pSPIx->CR1 & (1 << SPI_CR1_DFF))){
		// 16bit
		// Load DR with 2 byte of data
		pSPIHandle->pSPIx->DR = *((uint16_t*)pSPIHandle->pTxBuffer);
		// Increment Buffer Address
		(uint16_t*)pSPIHandle->pTxBuffer++;
		// Length-- both bytes
		pSPIHandle->TxLength -= 2;
	}else{
		// 8bit
		pSPIHandle->pSPIx->DR = *pSPIHandle->pTxBuffer;
		pSPIHandle->pTxBuffer++;
		pSPIHandle->TxLength--;
	}

	if(! pSPIHandle->TxLength){
		// TxLength is zero, close the SPI Transmission
		SPI_CloseTransmission(pSPIHandle);
		SPI_ApplicationEventCallback(pSPIHandle, SPI_EVENT_TX_COMPLETE);
	}

}

static void spi_rxne_interrupt_handle(SPI_Handle_t *pSPIHandle){
	// Check if 8bit or 16bit
	if((pSPIHandle->pSPIx->CR1 & (1 << SPI_CR1_DFF))){
		// 16bit
		// Load data from DR to RxBuffer Address
		*((uint16_t*)pSPIHandle->pRxBuffer) = pSPIHandle->pSPIx->DR;
		// Increment Buffer Address
		(uint16_t*)pSPIHandle->pRxBuffer++;
		// Length--
		pSPIHandle->RxLength -= 2;
	}else{
		// 8bit
		*pSPIHandle->pRxBuffer = pSPIHandle->pSPIx->DR;
		pSPIHandle->pRxBuffer++;
		pSPIHandle->RxLength--;
	}
	if(! pSPIHandle->RxLength){
		// Reception is complete
		SPI_CloseReception(pSPIHandle);
		SPI_ApplicationEventCallback(pSPIHandle, SPI_EVENT_RX_COMPLETE);
	}

}

static void spi_ovr_err_interrupt_handle(SPI_Handle_t *pSPIHandle){
	uint8_t temp;
	// Clear ovr flag
	if(pSPIHandle->TxState != SPI_BUSY_IN_TX){
		temp = pSPIHandle->pSPIx->DR;
		temp = pSPIHandle->pSPIx->SR;
	}
	(void)temp;
	// Inform the Application
	SPI_ApplicationEventCallback(pSPIHandle, SPI_EVENT_OVR_ERR);
}


void SPI_ClearOVRFlag(SPI_RegDef_t *pSPIx){
	uint8_t temp;
	temp = pSPIx->DR;
	temp = pSPIx->SR;
	(void)temp;
}

void SPI_CloseTransmission(SPI_Handle_t *pSPIHandle){
	pSPIHandle->pSPIx->CR2 &= ~(1 << SPI_CR2_TXEIE); // Prevents interrupts from setting up TXE flag
	pSPIHandle->pTxBuffer = NULL;
	pSPIHandle->TxLength = 0;
	pSPIHandle->TxState = SPI_READY;
}

void SPI_CloseReception(SPI_Handle_t *pSPIHandle){
	pSPIHandle->pSPIx->CR2 &= ~(1 << SPI_CR2_RXNEIE); // Prevents interrupts from setting up TXE flag
	pSPIHandle->pRxBuffer = NULL;
	pSPIHandle->RxLength = 0;
	pSPIHandle->RxState = SPI_READY;
}



__attribute__((weak)) void SPI_ApplicationEventCallback(SPI_Handle_t *pSPIHandle, uint8_t AppEvent){
	// weak implementation that the application can override
}



