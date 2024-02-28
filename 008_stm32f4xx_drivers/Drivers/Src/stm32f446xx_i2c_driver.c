/*
 * stm32f446xx_i2c_driver.c
 *
 *  Created on: Feb 22, 2024
 *      Author: wyatt
 */

#include "stm32f446xx_i2c_driver.h"

// Private helper functions
static void I2C_GenerateStartCondition(I2C_RegDef_t *pI2Cx);
static void I2C_ExecuteAddressPhaseWrite(I2C_RegDef_t *pI2Cx, uint8_t SlaveAddr);
static void I2C_ExecuteAddressPhaseRead(I2C_RegDef_t *pI2Cx, uint8_t SlaveAddr);
static void I2C_ClearADDRFlag(I2C_RegDef_t *pI2Cx);
static void I2C_GenerateStopCondition(I2C_RegDef_t *pI2Cx);

static void I2C_GenerateStartCondition(I2C_RegDef_t *pI2Cx){
	pI2Cx->CR1 |= (1 << I2C_CR1_START);
}

static void I2C_ExecuteAddressPhaseWrite(I2C_RegDef_t *pI2Cx, uint8_t SlaveAddr)
{
	SlaveAddr = SlaveAddr << 1;
	SlaveAddr &= ~(1); //SlaveAddr is Slave address + r/nw bit=0
	pI2Cx->DR = SlaveAddr;
}


static void I2C_ExecuteAddressPhaseRead(I2C_RegDef_t *pI2Cx, uint8_t SlaveAddr)
{
	SlaveAddr = SlaveAddr << 1;
	SlaveAddr |= 1; //SlaveAddr is Slave address + r/nw bit=1
	pI2Cx->DR = SlaveAddr;
}

static void I2C_ClearADDRFlag(I2C_RegDef_t *pI2Cx){
	uint32_t dummyRead = pI2Cx->SR1;
	dummyRead = pI2Cx->SR2;
	(void)dummyRead;
}

static void I2C_GenerateStopCondition(I2C_RegDef_t *pI2Cx){
	pI2Cx->CR1 |= (1 << I2C_CR1_STOP);
}


// Peripheral Clock Setup
void I2C_PeriClockControl(I2C_RegDef_t *pI2Cx, uint8_t EnOrDi){
	if(EnOrDi == ENABLE){
		// Enable
		if(pI2Cx == I2C1){
			I2C1_PCLK_EN();
		}else if(pI2Cx == I2C2){
			I2C2_PCLK_EN();
		}else if(pI2Cx == I2C3){
			I2C3_PCLK_EN();
		}
	}else{
		// Disable
		if(pI2Cx == I2C1){
			I2C1_PCLK_DI();
		}else if(pI2Cx == I2C2){
			I2C2_PCLK_DI();
		}else if(pI2Cx == I2C3){
			I2C3_PCLK_DI();
		}
	}
}

// I2C Peripheral Control
void I2C_PeripheralControl(I2C_RegDef_t *pI2Cx, uint8_t EnOrDi){
	if(EnOrDi == ENABLE){
		// Enable
		pI2Cx->CR1 |= (1 << I2C_CR1_PE);
	}else{
		// Disable
		pI2Cx->CR1 &= ~(1 << I2C_CR1_PE);
	}

}

// Not implemented, just a placeholder
uint32_t RCC_GetPLLOutputClock(void){
	uint32_t temp = 0;
	return temp;
}

uint16_t AHB_PreScaler[8] = {2, 4, 8, 16, 64, 128, 512};
uint16_t APB1_PreScaler[4] = {2, 4, 8, 16};

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

void I2C_Init(I2C_Handle_t *pI2C_Handle){
	uint32_t tempreg = 0;

	// Enable the Clock for the I2Cx Peripheral
	I2C_PeriClockControl(pI2C_Handle->pI2Cx, ENABLE);

	// ACK Control Bit
	tempreg |= pI2C_Handle->I2C_Config.I2C_ACKControl << 10;
	pI2C_Handle->pI2Cx->CR1 = tempreg;

	// Configure the FREQ field of CR2
	tempreg = 0;
	tempreg |= (RCC_GetPCLK1Value() / 1000000U); // Divide by 1MHz to only get 16 instead of 16MHz
	pI2C_Handle->pI2Cx->CR2 = (tempreg & 0x3F);

	// Device Own Address
	tempreg |= pI2C_Handle->I2C_Config.I2C_DeviceAddress << 1;
	tempreg |= (1 << 14);
	pI2C_Handle->pI2Cx->OAR1 |= tempreg;

	// Clock Control Calculations
	uint16_t ccr_value = 0;
	tempreg = 0;
	if(pI2C_Handle->I2C_Config.I2C_SCLSpeed <= I2C_SCL_SPEED_SM){
		// Standard Mode
		tempreg &= ~(1 << 15);
		ccr_value = RCC_GetPCLK1Value() / (2 * pI2C_Handle->I2C_Config.I2C_SCLSpeed);
		tempreg |= (ccr_value & 0xFFF);
	}else{
		// Fast Mode
		tempreg |= (1 << 15);
		tempreg |= (pI2C_Handle->I2C_Config.I2C_FMDutyCycle << 14);
		if(pI2C_Handle->I2C_Config.I2C_FMDutyCycle == I2C_FM_DUTY_2){
			ccr_value = RCC_GetPCLK1Value() / (3 * pI2C_Handle->I2C_Config.I2C_SCLSpeed);
		}else{
			ccr_value = RCC_GetPCLK1Value() / (25 * pI2C_Handle->I2C_Config.I2C_SCLSpeed);
		}
		tempreg |= (ccr_value & 0xFFF);
	}

	pI2C_Handle->pI2Cx->CCR |= tempreg;

	// TRISE
	if(pI2C_Handle->I2C_Config.I2C_SCLSpeed <= I2C_SCL_SPEED_SM){
		// Standard Mode
		tempreg = (RCC_GetPCLK1Value() / 1000000U) + 1;
	}else{
		// Fast Mode
		tempreg = ((RCC_GetPCLK1Value() * 300) / 1000000000U) + 1;
	}

	pI2C_Handle->pI2Cx->TRISE |= (tempreg & 0x3F);
}

void I2C_DeInit(I2C_RegDef_t *pI2Cx){
	if(pI2Cx == I2C1){
		I2C1_REG_RESET();
	}else if(pI2Cx == I2C2){
		I2C2_REG_RESET();
	}else if(pI2Cx == I2C3){
		I2C3_REG_RESET();
	}
}




void I2C_MasterSendData(I2C_Handle_t *pI2C_Handle, uint8_t *pTxBuffer, uint8_t Length, uint8_t SlaveAddr, uint8_t Sr){
	// 1. Generate the Start Condition
	I2C_GenerateStartCondition(pI2C_Handle->pI2Cx);

	// 2. Confirm that start generation is completed by checking the SB Flag in the SR1
	while(! I2C_GetFlagStatus(pI2C_Handle->pI2Cx, I2C_FLAG_SB));

	// 3. Send the Address of the slave with R/nW bit set to W(0) (total 8 bits)
	I2C_ExecuteAddressPhaseWrite(pI2C_Handle->pI2Cx, SlaveAddr);

	// 4. Confirm that address phase is completed by checking the ADDR flag in the SR1
	while(! I2C_GetFlagStatus(pI2C_Handle->pI2Cx, I2C_FLAG_ADDR));

	// 5. Clear the ADDR Flag according to its software sequence
	I2C_ClearADDRFlag(pI2C_Handle->pI2Cx);

	// 6. Send the data until Length becomes 0
	while(Length > 0){
		while(! I2C_GetFlagStatus(pI2C_Handle->pI2Cx, I2C_FLAG_TXE)); // Wait till TXE is set
		pI2C_Handle->pI2Cx->DR = *pTxBuffer;
		pTxBuffer++;
		Length--;
	}

	// 7. When Length becomes zero wait for TXE=1 and BTF=1 before generating the STOP condition
	while(! I2C_GetFlagStatus(pI2C_Handle->pI2Cx, I2C_FLAG_TXE));
	while(! I2C_GetFlagStatus(pI2C_Handle->pI2Cx, I2C_FLAG_BTF));

	// 8. Generate STOP condition and master need not to wait for the completion of stop condition
	if(Sr == I2C_DISABLE_SR){
		I2C_GenerateStopCondition(pI2C_Handle->pI2Cx);
	}


}


void I2C_MasterReceiveData(I2C_Handle_t *pI2C_Handle, uint8_t *pRxBuffer, uint8_t Length, uint8_t SlaveAddr, uint8_t Sr){

	// 1. Generate the Start Condition
	I2C_GenerateStartCondition(pI2C_Handle->pI2Cx);

	// 2. Confirm that start generation is completed by checking the SB Flag in the SR1
	while(! I2C_GetFlagStatus(pI2C_Handle->pI2Cx, I2C_FLAG_SB));

	// 3. Send the Address of the slave with R/nW bit set to R(1) (total 8 bits)
	I2C_ExecuteAddressPhaseRead(pI2C_Handle->pI2Cx, SlaveAddr);

	// 4. Confirm that address phase is completed by checking the ADDR flag in the SR1
	while(! I2C_GetFlagStatus(pI2C_Handle->pI2Cx, I2C_FLAG_ADDR));

	// if Reading Length only 1 Byte
	if(Length == 1){
		// Disable ACKing
		I2C_ManageAcking(pI2C_Handle->pI2Cx, I2C_ACK_DISABLE);

		// Clear the ADDR Flag
		I2C_ClearADDRFlag(pI2C_Handle->pI2Cx);

		// Wait until RXNE Becomes 1
		while(! I2C_GetFlagStatus(pI2C_Handle->pI2Cx, I2C_FLAG_RXNE));

		// Generate STOP Condition
		if(Sr == I2C_DISABLE_SR){
			I2C_GenerateStopCondition(pI2C_Handle->pI2Cx);
		}

		// Read Data into Buffer
		*pRxBuffer = pI2C_Handle->pI2Cx->DR;

	}

	// if Reading Length > 1
	if(Length > 1){
		// Clear the ADDR Flag
		I2C_ClearADDRFlag(pI2C_Handle->pI2Cx);

		// Read the Data until Length becomes zero
		for(uint32_t i = Length; i > 0; i--){
			// wait for RXNE becomes 1
			while(! I2C_GetFlagStatus(pI2C_Handle->pI2Cx, I2C_FLAG_RXNE));

			// Last 2 Bytes remaining
			if(i == 2){
				// Clear the ACK bit
				I2C_ManageAcking(pI2C_Handle->pI2Cx, I2C_ACK_DISABLE);

				// Generate STOP Condition
				if(Sr == I2C_DISABLE_SR){
					I2C_GenerateStopCondition(pI2C_Handle->pI2Cx);
				}
			}

			// Read the Data from the Data Register into Buffer
			*pRxBuffer = pI2C_Handle->pI2Cx->DR;

			// Increment the Buffer Address
			pRxBuffer++;

		}
	}

	// Re-Enable ACKing
	if(pI2C_Handle->I2C_Config.I2C_ACKControl == I2C_ACK_ENABLE){
		I2C_ManageAcking(pI2C_Handle->pI2Cx, I2C_ACK_ENABLE);
	}


}


uint8_t I2C_MasterSendDataIT(I2C_Handle_t *pI2CHandle, uint8_t *pTxBuffer, uint8_t Length, uint8_t SlaveAddr, uint8_t Sr){
	uint8_t busystate = pI2CHandle->TxRxState;

	if( (busystate != I2C_BUSY_IN_TX) && (busystate != I2C_BUSY_IN_RX))
	{
		pI2CHandle->pTxBuffer = pTxBuffer;
		pI2CHandle->TxLength = Length;
		pI2CHandle->TxRxState = I2C_BUSY_IN_TX;
		pI2CHandle->DevAddr = SlaveAddr;
		pI2CHandle->Sr = Sr;

		//Implement code to Generate START Condition
		I2C_GenerateStartCondition(pI2CHandle->pI2Cx);


		//Implement the code to enable ITBUFEN Control Bit
		pI2CHandle->pI2Cx->CR2 |= ( 1 << I2C_CR2_ITBUFEN);

		//Implement the code to enable ITEVFEN Control Bit
		pI2CHandle->pI2Cx->CR2 |= ( 1 << I2C_CR2_ITEVTEN);

		//Implement the code to enable ITERREN Control Bit
		pI2CHandle->pI2Cx->CR2 |= ( 1 << I2C_CR2_ITERREN);


	}

	return busystate;
}


uint8_t I2C_MasterReceiveDataIT(I2C_Handle_t *pI2CHandle, uint8_t *pRxBuffer, uint8_t Length, uint8_t SlaveAddr, uint8_t Sr){
	uint8_t busystate = pI2CHandle->TxRxState;

	if( (busystate != I2C_BUSY_IN_TX) && (busystate != I2C_BUSY_IN_RX))
	{
		pI2CHandle->pRxBuffer = pRxBuffer;
		pI2CHandle->RxLength = Length;
		pI2CHandle->TxRxState = I2C_BUSY_IN_RX;
		pI2CHandle->RxSize = Length; //Rxsize is used in the ISR code to manage the data reception
		pI2CHandle->DevAddr = SlaveAddr;
		pI2CHandle->Sr = Sr;

		//Implement code to Generate START Condition
		I2C_GenerateStartCondition(pI2CHandle->pI2Cx);


		//Implement the code to enable ITBUFEN Control Bit
		pI2CHandle->pI2Cx->CR2 |= ( 1 << I2C_CR2_ITBUFEN);

		//Implement the code to enable ITEVFEN Control Bit
		pI2CHandle->pI2Cx->CR2 |= ( 1 << I2C_CR2_ITEVTEN);

		//Implement the code to enable ITERREN Control Bit
		pI2CHandle->pI2Cx->CR2 |= ( 1 << I2C_CR2_ITERREN);

	}

	return busystate;
}



void I2C_IRQInterruptConfig(uint8_t IRQNumber,uint8_t EnOrDi){
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


void I2C_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority){
	uint8_t iprx = IRQNumber / 4;
	uint8_t iprx_section = IRQNumber % 4;
	uint8_t shift_amount = (8 * iprx_section) + (8 - NUM_PR_BITS_IMPLEMENTED);
	*(NVIC_IPR_BASE_ADDR + iprx) |= (IRQPriority << shift_amount);
}


void I2C_EV_IRQHandling(I2C_Handle_t *pI2CHandle){
	// Interrupt handling for both master and slave mode of a device
	uint32_t temp1, temp2, temp3;

	temp1 = pI2CHandle->pI2Cx->CR2 & (1 << I2C_CR2_ITEVTEN);
	temp2 = pI2CHandle->pI2Cx->CR2 & (1 << I2C_CR2_ITBUFEN);

	// 1. Handle for Interrupt generated by SB event
	temp3 = pI2CHandle->pI2Cx->SR1 & (1 << I2C_SR1_SB);
	if(temp1 && temp3){
		// SB Flag is set
		if(pI2CHandle->TxRxState == I2C_BUSY_IN_TX){
			I2C_ExecuteAddressPhaseWrite(pI2CHandle->pI2Cx, pI2CHandle->DevAddr);
		}else if(pI2CHandle->TxRxState == I2C_BUSY_IN_RX){
			I2C_ExecuteAddressPhaseRead(pI2CHandle->pI2Cx, pI2CHandle->DevAddr);
		}
	}

	// 2. Handle for interrupt generated by ADDR event
	temp3 = pI2CHandle->pI2Cx->SR1 & (1 << I2C_SR1_ADDR);
	if(temp1 && temp3){
		// ADDR Flag is set
	}

	// 3. Handle for interrupt generated by BTF (Byte Transfer Finished) event
	temp3 = pI2CHandle->pI2Cx->SR1 & (1 << I2C_SR1_BTF);
	if(temp1 && temp3){
		// BTF Flag is set
	}

	// 4. Handle for interrupt generated by STOPF Event
	temp3 = pI2CHandle->pI2Cx->SR1 & (1 << I2C_SR1_STOPF);
	if(temp1 && temp3){
		// STOPF Flag is set
	}

	// 5. Handle for interrupt generated by TXE event
	temp3 = pI2CHandle->pI2Cx->SR1 & (1 << I2C_SR1_TXE);
	if(temp1 && temp2 && temp3){
		// TXE Flag is set
	}

	// 6. Handle for interrupt generated by RXNE event
	temp3 = pI2CHandle->pI2Cx->SR1 & (1 << I2C_SR1_RXNE);
	if(temp1 && temp2 && temp3){
		// RXNE Flag is set
	}
}


void I2C_ER_IRQHandling(I2C_Handle_t *pI2CHandle){

}


void I2C_ManageAcking(I2C_RegDef_t *pI2Cx, uint8_t EnOrDi){
	if(EnOrDi == I2C_ACK_ENABLE){
		// Enable ACKing
		pI2Cx->CR1 |= (1 << I2C_CR1_ACK);
	}else{
		// Disable ACKing
		pI2Cx->CR1 &= ~(1 << I2C_CR1_ACK);
	}
}

uint8_t I2C_GetFlagStatus(I2C_RegDef_t *pI2Cx, uint32_t FlagName){
	if(pI2Cx->SR1 & FlagName){
		return FLAG_SET;
	}
	return FLAG_RESET;
}


