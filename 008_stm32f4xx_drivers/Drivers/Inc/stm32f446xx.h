/*
 * stm32f446xx.h
 *
 *  Created on: Jan 27, 2024
 *      Author: wyatt
 */

#ifndef INC_STM32F446XX_H_
#define INC_STM32F446XX_H_


#include <stdint.h>


/*
 * Base Addresses of FLash and SRAM Memories
 */
#define FLASH_BASEADDR		0x08000000U
#define SRAM1_BASEADDR		0x20000000U // 112KB
#define SRAM2_BASEADDR		0x2001C000U // 16KB
#define ROM					0x1FFF0000U // "System Memory" on the Memory Map
#define SRAM_BASEADDR		SRAM1_BASEADDR


/*
 * Base Addresses of APB and AHB Busses
 */
#define PERIPH_BASE			0x40000000U
#define APB1PERIPH_BASE		PERIPH_BASE
#define APB2PERIPH_BASE		0x40010000U
#define AHB1PERIPH_BASE		0x40020000U
#define AHB2PERIPH_BASE		0x50000000U


/*
 * Base Addresses of Peripherals on AHB1 Bus
 * BaseAddr + OFFSETS
 */
#define GPIOA_BASEADDR		(AHB1PERIPH_BASE + 0x0000)
#define GPIOB_BASEADDR		(AHB1PERIPH_BASE + 0x0400)
#define GPIOC_BASEADDR		(AHB1PERIPH_BASE + 0x0800)
#define GPIOD_BASEADDR		(AHB1PERIPH_BASE + 0x0C00)
#define GPIOE_BASEADDR		(AHB1PERIPH_BASE + 0x1000)
#define GPIOF_BASEADDR		(AHB1PERIPH_BASE + 0x1400)
#define GPIOG_BASEADDR		(AHB1PERIPH_BASE + 0x1800)
#define GPIOH_BASEADDR		(AHB1PERIPH_BASE + 0x1C00)
#define RCC_BASEADDR		(AHB1PERIPH_BASE + 0x3800)


/*
 * Base Addresses of Peripherals on APB1 Bus
 * BaseAddr + OFFSETS
 */
#define I2C1_BASEADDR		(APB1PERIPH_BASE + 0x5400)
#define I2C2_BASEADDR		(APB1PERIPH_BASE + 0x5800)
#define I2C3_BASEADDR		(APB1PERIPH_BASE + 0x5C00)
#define SPI2_BASEADDR		(APB1PERIPH_BASE + 0x3800)
#define SPI3_BASEADDR		(APB1PERIPH_BASE + 0x3C00)
#define USART2_BASEADDR		(APB1PERIPH_BASE + 0x4400)
#define USART3_BASEADDR		(APB1PERIPH_BASE + 0x4800)
#define UART4_BASEADDR		(APB1PERIPH_BASE + 0x4C00)
#define UART5_BASEADDR		(APB1PERIPH_BASE + 0x5000)

/*
 * Base Addresses of Peripherals on APB2 Bus
 * BaseAddr + OFFSETS
 */
#define SPI1_BASEADDR		(APB2PERIPH_BASE + 0x3000)
#define USART1_BASEADDR		(APB2PERIPH_BASE + 0x1000)
#define USART6_BASEADDR		(APB2PERIPH_BASE + 0x1400)
#define EXTI_BASEADDR		(APB2PERIPH_BASE + 0x3C00)
#define SYSCFG_BASEADDR		(APB2PERIPH_BASE + 0x3800)


/*
 * Peripheral Register Definition Structures
 * Use Volatile as the data could update very fast for some of the GPIO Registers
 * The uint32_t data type will space the variables 0x04 apart from one another
 */

// GPIOx
typedef struct{
	volatile uint32_t MODER;		// I/O Direction Mode.					OFFSET: 0x00
	volatile uint32_t OTYPER;		// Output Type. 						OFFSET: 0x04
	volatile uint32_t OSPEEDR;		// Output Speed. 						OFFSET: 0x08
	volatile uint32_t PUPDR;		// Pull-up or Pull-down.				OFFSET: 0x0C
	volatile uint32_t IDR;			// Read-only Input Data.				OFFSET: 0x10
	volatile uint32_t ODR;			// Read and Write Output Data.			OFFSET: 0x14
	volatile uint32_t BSRR;			// Write-only Reset or Set the ODR.		OFFSET: 0x18
	volatile uint32_t LCKR;			// Lock the Configuration of the port.	OFFSET: 0x1C
	volatile uint32_t AFRL;			// Alternate Function Selection Low.	OFFSET: 0x10
	volatile uint32_t AFRH;			// Alternate Function Selection High.	OFFSET: 0x24

} GPIO_RegDef_t;

// RCC
typedef struct{
	volatile uint32_t CR;				// Clock Control Register											OFFSET: 0x00
	volatile uint32_t PLLCFGR;			// PLL Configuration Register										OFFSET: 0x04
	volatile uint32_t CFGR;				// Clock Configuration Register										OFFSET: 0x08
	volatile uint32_t CIR;				// Clock Interrupt Register											OFFSET: 0x0C
	volatile uint32_t AHB1RSTR;			// AHB1 Peripheral Reset Register									OFFSET: 0x10
	volatile uint32_t AHB2RSTR;			// AHB2 Peripheral Reset Register									OFFSET: 0x14
	volatile uint32_t AHB3RSTR;			// AHB3 Peripheral Reset Register									OFFSET: 0x18
	uint32_t RESERVED0;					// Reserved															OFFSET: 0x1C
	volatile uint32_t APB1RSTR;			// APB1 Peripheral Reset Register									OFFSET: 0x20
	volatile uint32_t APB2RSTR;			// APB2 Peripheral Reset Register									OFFSET: 0x24
	uint32_t RESERVED1[2];				// Reserved															OFFSET: 0x28-0x2C
	volatile uint32_t AHB1ENR;			// AHB1 Clock Enable Register										OFFSET: 0x30
	volatile uint32_t AHB2ENR;			// AHB2 Clock Enable Register										OFFSET: 0x34
	volatile uint32_t AHB3ENR;			// AHB3 Clock Enable Register										OFFSET: 0x38
	uint32_t RESERVED2;					// Reserved															OFFSET: 0x3C
	volatile uint32_t APB1ENR;			// APB1 Clock Enable Register										OFFSET: 0x40
	volatile uint32_t APB2ENR;			// APB2 Clock Enable Register										OFFSET: 0x44
	uint32_t RESERVED3[2];				// Reserved															OFFSET: 0x48-0x4C
	volatile uint32_t AHB1LPENR;		// AHB1 Peripheral Clock Enable in Low Power Mode Register			OFFSET: 0x50
	volatile uint32_t AHB2LPENR;		// AHB2 Peripheral Clock Enable in Low Power Mode Register			OFFSET: 0x54
	volatile uint32_t AHB3LPENR;		// AHB3 Peripheral Clock Enable in Low Power Mode Register			OFFSET: 0x58
	uint32_t RESERVED4;					// Reserved															OFFSET: 0x5C
	volatile uint32_t APB1LPENR;		// APB1 Peripheral Clock Enable in Low Power Mode Register			OFFSET: 0x60
	volatile uint32_t APB2LPENR;		// APB2 Peripheral Clock Enable in Low Power Mode Register			OFFSET: 0x64
	uint32_t RESERVED5[2];				// Reserved															OFFSET: 0x68-0x6C
	volatile uint32_t BDCR;				// Backup Domain Control Register									OFFSET: 0x70
	volatile uint32_t CSR;				// Clock Control & Status Register									OFFSET: 0x74
	uint32_t RESERVED6[2];				// Reserved															OFFSET: 0x78-0x7C
	volatile uint32_t SSCGR;			// Spread Spectrum Clock Generation Register						OFFSET: 0x80
	volatile uint32_t PLLI2SCFGR;		// PLLI2S Configuration Register									OFFSET: 0x84
	volatile uint32_t PLLSAICFGR;		// PLL Configuration Register										OFFSET: 0x88
	volatile uint32_t DCKCFGR;			// Dedicated Clock Configuration Register							OFFSET: 0x8C
	volatile uint32_t CKGATENR;			// Clocks Gated Enable Register										OFFSET: 0x90
	volatile uint32_t DCKCFGR2;			// Dedicated Clocks Configuration Register 2						OFFSET: 0x94
} RCC_RegDef_t;

/*
 * Peripheral Definitions Base Addresses Type-casted to xxxx_RegDef_t
 */

#define GPIOA 		((GPIO_RegDef_t*) GPIOA_BASEADDR)
#define GPIOB 		((GPIO_RegDef_t*) GPIOB_BASEADDR)
#define GPIOC 		((GPIO_RegDef_t*) GPIOC_BASEADDR)
#define GPIOD 		((GPIO_RegDef_t*) GPIOD_BASEADDR)
#define GPIOE 		((GPIO_RegDef_t*) GPIOE_BASEADDR)
#define GPIOF 		((GPIO_RegDef_t*) GPIOF_BASEADDR)
#define GPIOG 		((GPIO_RegDef_t*) GPIOG_BASEADDR)
#define GPIOH 		((GPIO_RegDef_t*) GPIOH_BASEADDR)

#define RCC			((RCC_RegDef_t*) RCC_BASEADDR)


/*
 * Clock Enable Macros for GPIOx Peripherals
 */
#define GPIOA_PCLK_EN()		( RCC->AHB1ENR |= (1 << 0) ) // GPIOA Peripheral Clock Enable
#define GPIOB_PCLK_EN()		( RCC->AHB1ENR |= (1 << 1) )
#define GPIOC_PCLK_EN()		( RCC->AHB1ENR |= (1 << 2) )
#define GPIOD_PCLK_EN()		( RCC->AHB1ENR |= (1 << 3) )
#define GPIOE_PCLK_EN()		( RCC->AHB1ENR |= (1 << 4) )
#define GPIOF_PCLK_EN()		( RCC->AHB1ENR |= (1 << 5) )
#define GPIOG_PCLK_EN()		( RCC->AHB1ENR |= (1 << 6) )
#define GPIOH_PCLK_EN()		( RCC->AHB1ENR |= (1 << 7) )


/*
 * Clock Enable Macros for I2Cx Peripherals
 */
#define I2C1_PCLK_EN()		( RCC->APB1ENR |= (1 << 21) )
#define I2C2_PCLK_EN()		( RCC->APB1ENR |= (1 << 22) )
#define I2C3_PCLK_EN()		( RCC->APB1ENR |= (1 << 23) )


/*
 * Clock Enable Macros for SPIx Peripherals
 */
#define SPI1_PCLK_EN()		( RCC->APB2ENR |= (1 << 12) )
#define SPI2_PCLK_EN()		( RCC->APB1ENR |= (1 << 14) )
#define SPI3_PCLK_EN()		( RCC->APB1ENR |= (1 << 15) )
#define SPI4_PCLK_EN()		( RCC->APB2ENR |= (1 << 13) )


/*
 * Clock Enable Macros for USARTx Peripherals
 */
#define USART1_PCLK_EN()	( RCC->APB2ENR |= (1 << 4)  )
#define USART2_PCLK_EN()	( RCC->APB1ENR |= (1 << 17) )
#define USART3_PCLK_EN()	( RCC->APB1ENR |= (1 << 18) )
#define USART6_PCLK_EN()	( RCC->APB2ENR |= (1 << 5)  )


/*
 * Clock Enable Macros for SYSCFG Peripherals
 */
#define SYSCFG_PCLK_EN()	( RCC->APB2ENR |= (1 << 14) )




/*
 * Clock Disable Macros for GPIOx Peripherals
 */
#define GPIOA_PCLK_DI()		( RCC->AHB1ENR &= ~(1 << 0) ) // GPIOA Peripheral Clock Disable
#define GPIOB_PCLK_DI()		( RCC->AHB1ENR &= ~(1 << 1) )
#define GPIOC_PCLK_DI()		( RCC->AHB1ENR &= ~(1 << 2) )
#define GPIOD_PCLK_DI()		( RCC->AHB1ENR &= ~(1 << 3) )
#define GPIOE_PCLK_DI()		( RCC->AHB1ENR &= ~(1 << 4) )
#define GPIOF_PCLK_DI()		( RCC->AHB1ENR &= ~(1 << 5) )
#define GPIOG_PCLK_DI()		( RCC->AHB1ENR &= ~(1 << 6) )
#define GPIOH_PCLK_DI()		( RCC->AHB1ENR &= ~(1 << 7) )


/*
 * Clock Disable Macros for I2Cx Peripherals
 */
#define I2C1_PCLK_DI()		( RCC->APB1ENR &= ~(1 << 21) )
#define I2C2_PCLK_DI()		( RCC->APB1ENR &= ~(1 << 22) )
#define I2C3_PCLK_DI()		( RCC->APB1ENR &= ~(1 << 23) )


/*
 * Clock Disable Macros for SPIx Peripherals
 */
#define SPI1_PCLK_DI()		( RCC->APB2ENR &= ~(1 << 12) )
#define SPI2_PCLK_DI()		( RCC->APB1ENR &= ~(1 << 14) )
#define SPI3_PCLK_DI()		( RCC->APB1ENR &= ~(1 << 15) )
#define SPI4_PCLK_DI()		( RCC->APB2ENR &= ~(1 << 13) )


/*
 * Clock Disable Macros for USARTx Peripherals
 */
#define USART1_PCLK_DI()	( RCC->APB2ENR &= ~(1 << 4)  )
#define USART2_PCLK_DI()	( RCC->APB1ENR &= ~(1 << 17) )
#define USART3_PCLK_DI()	( RCC->APB1ENR &= ~(1 << 18) )
#define USART6_PCLK_DI()	( RCC->APB2ENR &= ~(1 << 5)  )


/*
 * Clock Disable Macros for SYSCFG Peripherals
 */
#define SYSCFG_PCLK_DI()	( RCC->APB2ENR &= ~(1 << 14) )



#endif /* INC_STM32F446XX_H_ */










