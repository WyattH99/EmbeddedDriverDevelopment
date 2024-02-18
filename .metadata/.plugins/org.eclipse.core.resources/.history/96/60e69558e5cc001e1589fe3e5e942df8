/*
 * stm32f446xx_spi_driver.h
 *
 *  Created on: Feb 14, 2024
 *      Author: wyatt
 */

#ifndef INC_STM32F446XX_SPI_DRIVER_H_
#define INC_STM32F446XX_SPI_DRIVER_H_



/*
 * SPI Configuration
 */
typedef struct{
	uint8_t SPI_DeviceMode;			// Master or Slave
	uint8_t SPI_BusConfig;			//
	uint8_t SPI_SclkSpeed;			// Baud Rate
	uint8_t	SPI_DFF;				// Data Frame Configuration
	uint8_t	SPI_CPOL;				// Clock Polarity
	uint8_t SPI_CPHA;				// Clock Phase
	uint8_t SPI_SSM;				// Software Slave Select
} SPI_Config_t;


/*
 * SPI Handle
 */
typedef struct{
	SPI_RegDef_t *pSPIx;			// Base Address of SPIx (1, 2, 3, and 4) Peripheral
	SPI_Config_t SPIConfig;			// Configuration Structure
} SPI_Handle_t;


/*
 * API Prototypes
 */

// Peripheral Clock Setup
void SPI_PeriClkControl(SPI_RegDef_t *pSPIx, uint8_t EnOrDi);

// Initialize and De-Initialize
void SPI_Init(SPI_Handle_t);
void SPI_DeInit(SPI_Handle_t);

// Data Send and Receive
void SPI_DataSend(SPI_Handle, uint8_t Data);
uint8_t SPI_DataReceive(SPI_Handle);

// IRQ Configurations and ISR Handling
void SPI_IRQ_Config();

void SPI_ISR_Handle();


#endif /* INC_STM32F446XX_SPI_DRIVER_H_ */
