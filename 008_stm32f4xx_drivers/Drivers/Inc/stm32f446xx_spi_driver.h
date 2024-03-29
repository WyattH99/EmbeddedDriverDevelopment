/*
 * stm32f446xx_spi_driver.h
 *
 *  Created on: Feb 14, 2024
 *      Author: wyatt
 */

#ifndef INC_STM32F446XX_SPI_DRIVER_H_
#define INC_STM32F446XX_SPI_DRIVER_H_

#include "stm32f446xx.h"

/*
 * SPI Configuration
 */
typedef struct{
	uint8_t SPI_DeviceMode;			// Master or Slave
	uint8_t SPI_BusConfig;			// Full Duplex, Half Duplex, or Simplex
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
	uint8_t *pTxBuffer;				// Store Application's Tx Buffer Address
	uint8_t *pRxBuffer;				// Store Application's Rx Buffer Address
	uint32_t TxLength;				// Tx Length
	uint32_t RxLength;				// Rx Length
	uint8_t TxState;				// Tx State
	uint8_t RxState;				// Rx Length
} SPI_Handle_t;


/*
 * @SPI_AppStates
 */
#define SPI_READY			0
#define SPI_BUSY_IN_RX		1
#define SPI_BUSY_IN_TX		2

/*
 * Possible SPI Application events
 */
#define SPI_EVENT_TX_COMPLETE		1
#define SPI_EVENT_RX_COMPLETE		2
#define SPI_EVENT_OVR_ERR			3
#define SPI_EVENT_CRC_ERR			4



/*
 * @SPI_DeviceMode
 */
#define SPI_DEVICE_MODE_MASTER		1
#define SPI_DEVICE_MODE_SLAVE		0

/*
 * @SPI_BusConfig
 */
#define SPI_BUS_CONFIG_FULL_DUPLEX			1
#define SPI_BUS_CONFIG_HALF_DUPLEX			2
#define SPI_BUS_CONFIG_SIMPLEX_RXONLY		3

/*
 * @SPI_SclkSpeed
 */
#define SPI_SCLK_SPEED_DIV2				0
#define SPI_SCLK_SPEED_DIV4				1
#define SPI_SCLK_SPEED_DIV8				2
#define SPI_SCLK_SPEED_DIV16			3
#define SPI_SCLK_SPEED_DIV32			4
#define SPI_SCLK_SPEED_DIV64			5
#define SPI_SCLK_SPEED_DIV128			6
#define SPI_SCLK_SPEED_DIV256			7

/*
 * @SPI_DFF
 */
#define SPI_DFF_8BITS		0
#define SPI_DFF_16BITS		1

/*
 * @SPI_CPOL
 */
#define SPI_CPOL_HIGH		1
#define	SPI_CPOL_LOW		0

/*
 * @SPI_CPHA
 */
#define SPI_CPHA_HIGH		1
#define SPI_CPHA_LOW		0

/*
 * @SPI_SSM
 */
#define SPI_SSM_EN			1
#define SPI_SSM_DI			0


/*
 * SPI Related Status Flags Definitions
 */
#define SPI_RXNE_FLAG		( 1 << SPI_SR_RXNE )
#define SPI_TXE_FLAG		( 1 << SPI_SR_TXE )
#define SPI_CHSIDE_FLAG		( 1 << SPI_SR_CHSIDE )
#define SPI_UDR_FLAG		( 1 << SPI_SR_UDR )
#define SPI_CRCERR_FLAG		( 1 << SPI_SR_CRCERR )
#define SPI_MODF_FLAG		( 1 << SPI_SR_MODF )
#define SPI_OVR_FLAG		( 1 << SPI_SR_OVR )
#define SPI_BUSY_FLAG		( 1 << SPI_SR_BSY )
#define SPI_FRE_FLAG		( 1 << SPI_SR_FRE )



/*
 * API Prototypes
 */

// Peripheral Clock Setup
void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnOrDi);

// Initialize and De-Initialize
void SPI_Init(SPI_Handle_t *pSPI_Handle);
void SPI_DeInit(SPI_RegDef_t *pSPIx);

// Data Send and Receive
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Length);
void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Length);

// IRQ Configurations and ISR Handling
void SPI_IRQInterruptConfig(uint8_t IRQNumber,uint8_t EnOrDi);
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void SPI_IRQHandling(SPI_Handle_t *pHandle);
uint8_t SPI_SendDataIT(SPI_Handle_t *pSPIHandle, uint8_t *pTxBuffer, uint32_t Length);
uint8_t SPI_ReceiveDataIT(SPI_Handle_t *pSPIHandle, uint8_t *pRxBuffer, uint32_t Length);

// SPI Peripheral Control
void SPI_PeripheralControl(SPI_RegDef_t *pSPIx, uint8_t EnOrDi);

// Configure SSI
void SPI_SSIConfig(SPI_RegDef_t *pSPIx, uint8_t EnOrDi);

// Configure SSOE
void SPI_SSOEConfig(SPI_RegDef_t *pSPIx, uint8_t EnOrDi);

uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, uint32_t FlagName);

void SPI_ClearOVRFlag(SPI_RegDef_t *pSPIx);
void SPI_CloseTransmission(SPI_Handle_t *pSPIHandle);
void SPI_CloseReception(SPI_Handle_t *pSPIHandle);

/*
 * Application Callback
 */
void SPI_ApplicationEventCallback(SPI_Handle_t *pSPIHandle, uint8_t AppEvent);



#endif /* INC_STM32F446XX_SPI_DRIVER_H_ */
