/*
 * stm32f446xx.h
 *
 *  Created on: Jan 27, 2024
 *      Author: wyatt
 */

#ifndef INC_STM32F446XX_H_
#define INC_STM32F446XX_H_


#include <stdint.h>
#include <stddef.h>


/***************** PROCESSOR SPECIFIC DETAILS *****************/

/*
 * ARM Cortex Mx Processor NVIC Interrupt Set-enable Register Addresses
 */
#define NVIC_ISER0			((volatile uint32_t*)0xE000E100)
#define NVIC_ISER1			((volatile uint32_t*)0xE000E104)
#define NVIC_ISER2			((volatile uint32_t*)0xE000E108)
#define NVIC_ISER3			((volatile uint32_t*)0xE000E10C)


/*
 * ARM Cortex Mx Processor NVIC Interrupt Clear-enable Register Addresses
 */
#define NVIC_ICER0			((volatile uint32_t*)0XE000E180)
#define NVIC_ICER1			((volatile uint32_t*)0XE000E184)
#define NVIC_ICER2			((volatile uint32_t*)0xE000E188)
#define NVIC_ICER3			((volatile uint32_t*)0xE000E18C)

/*
 * ARM Cortex Mx Processor NVIC Interrupt Priority Register Base Address
 */
#define NVIC_IPR_BASE_ADDR	((volatile uint32_t*)0xE000E400)


#define NUM_PR_BITS_IMPLEMENTED		4



/***************** Peripheral SPECIFIC DETAILS *****************/

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

// GPIOx Register Definition
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


// SPI Register Definition
typedef struct{
	volatile uint32_t CR1;			// Control Register 1					OFFSET: 0x00
	volatile uint32_t CR2;			// Control Register 2					OFFSET: 0x04
	volatile uint32_t SR;			// Status Register						OFFSET: 0x08
	volatile uint32_t DR;			// Data Register						OFFSET: 0x0C
	volatile uint32_t CRCPR;		// CRC Polynomial Register				OFFSET: 0x10
	volatile uint32_t RXCRCR;		// RX CRC Polynomial Register			OFFSET: 0x14
	volatile uint32_t TXCRCR;		// TX CRC Register						OFFSET: 0x18
	volatile uint32_t I2SCFGR;		// I^2S Configuration Register			OFFSET: 0x1C
	volatile uint32_t I2SPR;		// I^2S PreScaler Register				OFFSET: 0x20
} SPI_RegDef_t;


// I2C Register Definition
typedef struct{
	volatile uint32_t CR1;			// Control Register 1					OFFSET: 0x00
	volatile uint32_t CR2;			// Control Register 2					OFFSET: 0x04
	volatile uint32_t OAR1;			// Own Address Register 1				OFFSET: 0x08
	volatile uint32_t OAR2;			// Own Address Register 2				OFFSET: 0x0C
	volatile uint32_t DR;			// Data Register						OFFSET: 0x10
	volatile uint32_t SR1;			// Status Register 1					OFFSET: 0x14
	volatile uint32_t SR2;			// Status Register 2					OFFSET: 0x18
	volatile uint32_t CCR;			// Clock Control Register				OFFSET: 0x1C
	volatile uint32_t TRISE;		// TRISE Register						OFFSET: 0x20
	volatile uint32_t FLTR;			// FLTR Register						OFFSET: 0x24
} I2C_RegDef_t;


// USART Register Definition
typedef struct{
	volatile uint32_t SR;			// Status Register						OFFSET: 0x00
	volatile uint32_t DR;			// Data Register						OFFSET: 0x04
	volatile uint32_t BRR;			// Baud Rate Register					OFFSET: 0x08
	volatile uint32_t CR1;			// Control Register 1					OFFSET: 0x0C
	volatile uint32_t CR2;			// Control Register 2					OFFSET: 0x10
	volatile uint32_t CR3;			// Control Register 3					OFFSET: 0x14
	volatile uint32_t GTPR;			// Guard Time and Pre-scaler Register	OFFSET: 0x18
} USART_RegDef_t;


// RCC Register Definition
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
 * Peripheral Register Definition Structure for EXTI
 */
typedef struct{
	volatile uint32_t IMR;				// Interrupt Mask Register					OFFSET: 0x00
	volatile uint32_t EMR;				// Event Mask Register						OFFSET: 0x04
	volatile uint32_t RTSR;				// Rising Trigger Selection Register		OFFSET: 0x08
	volatile uint32_t FTSR;				// Falling Trigger Selection Register		OFFSET: 0x0C
	volatile uint32_t SWIER;			// Software Interrupt Event Register		OFFSET: 0x10
	volatile uint32_t PR;				// Pending Register							OFFSET: 0x14
} EXTI_RegDef_t;


/*
 * Peripheral Register Definition Structure for SYSCFG
 */
typedef struct{
	volatile uint32_t MEMRMP;			// Memory Remap Register								OFFSET: 0x00
	volatile uint32_t PMC;				// Peripheral Mode Configuration Register				OFFSET: 0x04
	volatile uint32_t EXTICR[4];		// External Interrupt Configuration Registers 1-4		OFFSET: 0x08-0x14
	uint32_t RESERVED1[2];				// Reserved												OFFSET: 0x18-1C
	volatile uint32_t CMPCR;			// Compensation Cell Control Register					OFFSET: 0x20
	uint32_t RESERVED2[2];				// Reserved												OFFSET: 0x24-28
	volatile uint32_t CFGR;				// Configuration Register								OFFSET: 0x2C
} SYSCFG_RegDef_t;

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

#define EXTI		((EXTI_RegDef_t*) EXTI_BASEADDR)

#define SYSCFG		((SYSCFG_RegDef_t*) SYSCFG_BASEADDR)

#define SPI1		((SPI_RegDef_t*) SPI1_BASEADDR)
#define SPI2		((SPI_RegDef_t*) SPI2_BASEADDR)
#define SPI3		((SPI_RegDef_t*) SPI3_BASEADDR)

#define I2C1		((I2C_RegDef_t*) I2C1_BASEADDR)
#define I2C2		((I2C_RegDef_t*) I2C2_BASEADDR)
#define I2C3		((I2C_RegDef_t*) I2C3_BASEADDR)

#define USART1		((USART_RegDef_t*) USART1_BASEADDR)
#define USART2		((USART_RegDef_t*) USART2_BASEADDR)
#define USART3		((USART_RegDef_t*) USART3_BASEADDR)
#define USART6		((USART_RegDef_t*) USART6_BASEADDR)

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


/*
 * Reset GPIOx Peripherals
 */
#define GPIOA_REG_RESET()	do{ (RCC->AHB1RSTR |= (1 << 0)); (RCC->AHB1RSTR &= ~(1 << 0)); }while(0)
#define GPIOB_REG_RESET()	do{ (RCC->AHB1RSTR |= (1 << 1)); (RCC->AHB1RSTR &= ~(1 << 1)); }while(0)
#define GPIOC_REG_RESET()	do{ (RCC->AHB1RSTR |= (1 << 2)); (RCC->AHB1RSTR &= ~(1 << 2)); }while(0)
#define GPIOD_REG_RESET()	do{ (RCC->AHB1RSTR |= (1 << 3)); (RCC->AHB1RSTR &= ~(1 << 3)); }while(0)
#define GPIOE_REG_RESET()	do{ (RCC->AHB1RSTR |= (1 << 4)); (RCC->AHB1RSTR &= ~(1 << 4)); }while(0)
#define GPIOF_REG_RESET()	do{ (RCC->AHB1RSTR |= (1 << 5)); (RCC->AHB1RSTR &= ~(1 << 5)); }while(0)
#define GPIOG_REG_RESET()	do{ (RCC->AHB1RSTR |= (1 << 6)); (RCC->AHB1RSTR &= ~(1 << 6)); }while(0)
#define GPIOH_REG_RESET()	do{ (RCC->AHB1RSTR |= (1 << 7)); (RCC->AHB1RSTR &= ~(1 << 7)); }while(0)


/*
 * Reset SPIx Peripherals
 */
#define SPI1_REG_RESET()	do{ (RCC->APB2RSTR |= (1 << 12)); (RCC->APB2RSTR &= ~(1 << 12)); }while(0)
#define SPI2_REG_RESET()	do{ (RCC->APB1RSTR |= (1 << 14)); (RCC->APB1RSTR &= ~(1 << 14)); }while(0)
#define SPI3_REG_RESET()	do{ (RCC->APB1RSTR |= (1 << 15)); (RCC->APB1RSTR &= ~(1 << 15)); }while(0)


/*
 * Reset I2Cx Peripherals
 */
#define I2C1_REG_RESET()	do{ (RCC->APB1RSTR |= (1 << 21)); (RCC->APB1RSTR &= ~(1 << 21)); }while(0)
#define I2C2_REG_RESET()	do{ (RCC->APB1RSTR |= (1 << 22)); (RCC->APB1RSTR &= ~(1 << 22)); }while(0)
#define I2C3_REG_RESET()	do{ (RCC->APB1RSTR |= (1 << 23)); (RCC->APB1RSTR &= ~(1 << 23)); }while(0)


/*
 * Reset USARTx Peripherals
 */
#define USART1_REG_RESET()	do{ (RCC->APB2RSTR |= (1 << 4)); (RCC->APB2RSTR &= ~(1 << 4)); }while(0)
#define USART2_REG_RESET()	do{ (RCC->APB1RSTR |= (1 << 17)); (RCC->APB1RSTR &= ~(1 << 17)); }while(0)
#define USART3_REG_RESET()	do{ (RCC->APB1RSTR |= (1 << 18)); (RCC->APB1RSTR &= ~(1 << 18)); }while(0)
#define USART6_REG_RESET()	do{ (RCC->APB2RSTR |= (1 << 5)); (RCC->APB2RSTR &= ~(1 << 5)); }while(0)


/*
 * Return Port Code for Given GPIOx Base Address
 */
#define GPIO_BASEADDR_TO_PORTCODE(x)		(   (x == GPIOA) ? 0 :\
											  	(x == GPIOB) ? 1 :\
											  	(x == GPIOC) ? 2 :\
											  	(x == GPIOD) ? 3 :\
											  	(x == GPIOE) ? 4 :\
											  	(x == GPIOF) ? 5 :\
											  	(x == GPIOG) ? 6 : 0)

/*
 * IRQ (Interrupt Request) Numbers of STM32F446xx MCU
 */
#define IRQ_NUM_EXTI0			6
#define IRQ_NUM_EXTI1			7
#define IRQ_NUM_EXTI2			8
#define IRQ_NUM_EXTI3			9
#define IRQ_NUM_EXTI4			10
#define IRQ_NUM_EXTI9_5			23
#define IRQ_NUM_EXTI15_10		40
#define IRQ_NUM_SPI1			35
#define IRQ_NUM_SPI2			36
#define IRQ_NUM_SPI3			51
#define IRQ_NUM_SPI4			84
#define IRQ_NUM_I2C1_EV			31
#define IRQ_NUM_I2C1_ER			32
#define IRQ_NUM_I2C2_EV			33
#define IRQ_NUM_I2C2_ER			34
#define IRQ_NUM_I2C3_EV			72
#define IRQ_NUM_I2C3_ER			73

/*
 * IRQ (Interrupt Request) Priority Numbers of STM32F446xx MCU
 */
#define NVIC_IRQ_PRIO1			1
#define NVIC_IRQ_PRIO2			2
#define NVIC_IRQ_PRIO3			3
#define NVIC_IRQ_PRIO4			4
#define NVIC_IRQ_PRIO5			5
#define NVIC_IRQ_PRIO6			6
#define NVIC_IRQ_PRIO7			7
#define NVIC_IRQ_PRIO8			8
#define NVIC_IRQ_PRIO9			9
#define NVIC_IRQ_PRIO10			10
#define NVIC_IRQ_PRIO11			11
#define NVIC_IRQ_PRIO12			12
#define NVIC_IRQ_PRIO13			13
#define NVIC_IRQ_PRIO14			14
#define NVIC_IRQ_PRIO15			15


/*
 * Bit Positions for  SPI Peripheral Registers
 */
/*
 * SPI Control Register 1
 */
#define SPI_CR1_CPHA			0
#define SPI_CR1_CPOL			1
#define SPI_CR1_MSTR			2
#define SPI_CR1_BR				3
#define SPI_CR1_SPE				6
#define SPI_CR1_LSBFIRST		7
#define SPI_CR1_SSI				8
#define SPI_CR1_SSM				9
#define SPI_CR1_RXONLY			10
#define SPI_CR1_DFF				11
#define SPI_CR1_CRCNEXT			12
#define SPI_CR1_CRCEN			13
#define SPI_CR1_BIDIOE			14
#define SPI_CR1_BIDIMODE		15

/*
 * SPI Control Register 2
 */
#define SPI_CR2_RXDMAEN			0
#define SPI_CR2_TXDMAEN			1
#define SPI_CR2_SSOE			2
#define SPI_CR2_FRF				4
#define SPI_CR2_ERRIE			5
#define SPI_CR2_RXNEIE			6
#define SPI_CR2_TXEIE			7

/*
 * SPI Status Register
 */
#define SPI_SR_RXNE				0
#define SPI_SR_TXE				1
#define SPI_SR_CHSIDE			2
#define SPI_SR_UDR				3
#define SPI_SR_CRCERR			4
#define SPI_SR_MODF				5
#define SPI_SR_OVR				6
#define SPI_SR_BSY				7
#define SPI_SR_FRE				8


/*
 * Bit Positions for I2C Peripheral Registers
 */
/*
 * I2C Control Register 1
 */
#define I2C_CR1_PE				0
#define I2C_CR1_SMBUS			1
#define I2C_CR1_SMBTYPE			3
#define I2C_CR1_ENARP			4
#define I2C_CR1_ENPEC			5
#define I2C_CR1_ENGC			6
#define I2C_CR1_NOSTRETCH		7
#define I2C_CR1_START			8
#define I2C_CR1_STOP			9
#define I2C_CR1_ACK 			10
#define I2C_CR1_POS				11
#define I2C_CR1_PEC				12
#define I2C_CR1_ALERT			13
#define I2C_CR1_SWRST			15

/*
 * I2C Control Register 2
 */
#define I2C_CR2_FREQ			0
#define I2C_CR2_ITERREN			8
#define I2C_CR2_ITEVTEN			9
#define I2C_CR2_ITBUFEN			10
#define I2C_CR2_DMAEN			11
#define I2C_CR2_LAST			12

/*
 * I2C Status Register 1
 */
#define I2C_SR1_SB				0
#define I2C_SR1_ADDR			1
#define I2C_SR1_BTF				2
#define I2C_SR1_ADD10			3
#define I2C_SR1_STOPF			4
#define I2C_SR1_RXNE			6
#define I2C_SR1_TXE				7
#define I2C_SR1_BERR			8
#define I2C_SR1_ARLO			9
#define I2C_SR1_AF				10
#define I2C_SR1_OVR				11
#define I2C_SR1_PECERR			12
#define I2C_SR1_TIMEOUT			14
#define I2C_SR1_SMBALERT		15

/*
 * I2C Status Register 2
 */
#define I2C_SR2_MSL				0
#define I2C_SR2_BUSY			1
#define I2C_SR2_TRA				2
#define I2C_SR2_GENCALL			4
#define I2C_SR2_SMBDEFAULT		5
#define I2C_SR2_SMBHOST			6
#define I2C_SR2_DUALF			7
#define I2C_SR2_PEC				8

/*
 * I2C Clock Control Register
 */
#define I2C_CCR_CCR				0
#define I2C_CCR_DUTY			14
#define I2C_CCR_FS				15


/*
 * Bit Positions for USART Peripheral Registers
 */
/*
 * USART Status Register
 */
#define USART_SR_PE				0
#define USART_SR_FE				1
#define USART_SR_NF				2
#define USART_SR_ORE			3
#define USART_SR_IDLE			4
#define USART_SR_RXNE			5
#define USART_SR_TC				6
#define USART_SR_TXE			7
#define USART_SR_LBD			8
#define USART_SR_CTS			9


/*
 * USART Control Register 1
 */
#define USART_CR1_SBK			0
#define USART_CR1_RWU			1
#define USART_CR1_RE			2
#define USART_CR1_TE			3
#define USART_CR1_IDLEIE		4
#define USART_CR1_RXNEIE		5
#define USART_CR1_TCIE			6
#define USART_CR1_TXEIE			7
#define USART_CR1_PEIE			8
#define USART_CR1_PS			9
#define USART_CR1_PCE			10
#define USART_CR1_WAKE			11
#define USART_CR1_M				12
#define USART_CR1_UE			13
#define USART_CR1_OVER8			15

/*
 * USART Control Register 2
 */
#define USART_CR2_ADD			0
#define USART_CR2_LBDL			5
#define USART_CR2_LBDIE			6
#define USART_CR2_LBCL			8
#define USART_CR2_CPHA			9
#define USART_CR2_CPOL			10
#define USART_CR2_CLKEN			11
#define USART_CR2_STOP			12
#define USART_CR2_LINEN			14


/*
 * USART Control Register 3
 */
#define USART_CR3_EIE			0
#define USART_CR3_IREN			1
#define USART_CR3_IRLP			2
#define USART_CR3_HDSEL			3
#define USART_CR3_NACK			4
#define USART_CR3_SCEN			5
#define USART_CR3_DMAR			6
#define USART_CR3_DMAT			7
#define USART_CR3_RTSE			8
#define USART_CR3_CTSE			9
#define USART_CR3_CTSIE			10
#define USART_CR3_ONEBIT		11


/*
 * USART Control Register 3
 */
#define USART_GTPR_PSC			0
#define USART_GTPR_GT			8



/*
 * Generic Macros
 */
#define ENABLE 					1
#define DISABLE 				0
#define SET 					ENABLE
#define RESET 					DISABLE
#define GPIO_PIN_SET			SET
#define GPIO_PIN_RESET			RESET
#define FLAG_SET				SET
#define FLAG_RESET				RESET



#include "stm32f446xx_gpio_driver.h"
#include "stm32f446xx_spi_driver.h"
#include "stm32f446xx_i2c_driver.h"
#include "stm32f446xx_usart_driver.h"


#endif /* INC_STM32F446XX_H_ */










