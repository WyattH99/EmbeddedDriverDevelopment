/*
 * stm32f446xx_gpio_driver.h
 *
 *  Created on: Feb 10, 2024
 *      Author: wyatt
 */

#ifndef INC_STM32F446XX_GPIO_DRIVER_H_
#define INC_STM32F446XX_GPIO_DRIVER_H_


#include "stm32f446xx.h"


/*
 * GPIO Pin Configuration Structure
 */
typedef struct{
	uint8_t GPIO_PinNumber;			/*!< Possible Values from @GPIO_PIN_NUMBER >*/
	uint8_t GPIO_PinMode;			/*!< Possible Values from @GPIO_PIN_MODES >*/
	uint8_t GPIO_PinSpeed;			/*!< Possible Values from @GPIO_PIN_SPEED >*/
	uint8_t GPIO_PinPuPdControl;	/*!< Possible Values from @GPIO_PIN_PUPD >*/
	uint8_t GPIO_PinOPType;			/*!< Possible Values from @GPIO_PIN_OPType >*/
	uint8_t GPIO_PinAltFunMode;		/*!< Possible Values from @GPIO_PIN_ALTFUN >*/

}GPIO_PinConfig_t;


/*
 * GPIO Pin Handle Structure
 */
typedef struct{
	GPIO_RegDef_t *pGPIOx; 					// Base Address of the GPIO Port to which the pin belongs
	GPIO_PinConfig_t GPIO_PinConfig;		// GPIO Pin Configuration Settings

}GPIO_Handle_t;


/*
 * @GPIO_PIN_NUMBER
 * GPIO Pin Possible Numbers
 */
#define GPIO_PIN_NO_0		0
#define GPIO_PIN_NO_1		1
#define GPIO_PIN_NO_2		2
#define GPIO_PIN_NO_3		3
#define GPIO_PIN_NO_4		4
#define GPIO_PIN_NO_5		5
#define GPIO_PIN_NO_6		6
#define GPIO_PIN_NO_7		7
#define GPIO_PIN_NO_8		8
#define GPIO_PIN_NO_9		9
#define GPIO_PIN_NO_10		10
#define GPIO_PIN_NO_11		11
#define GPIO_PIN_NO_12		12
#define GPIO_PIN_NO_13		13
#define GPIO_PIN_NO_14		14
#define GPIO_PIN_NO_15		15


/*
 * @GPIO_PIN_MODES
 * GPIO Pin Possible Modes
 */
#define GPIO_MODE_INPUT 	0
#define GPIO_MODE_OUTPUt 	1
#define GPIO_MODE_ALTFUN	2
#define GPIO_MODE_ANALOG	3
#define GPIO_MODE_IT_FT		4	// Interrupt Falling Edge Trigger
#define GPIO_MODE_IT_RT		5	// Interrupt Rising Edge Trigger
#define GPIO_MODE_IT_RFT	6	// Interrupt Rising Falling Edge Trigger

/*
 * @GPIO_PIN_OPType
 * GPIO Pin Possible Output Types
 */
#define GPIO_OP_TYPE_PP		0	// Push-Pull
#define GPIO_OP_TYPE_OD		1	// Open-Drain

/*
 * @GPIO_PIN_SPEED
 * GPIO Pin Possible Output Speed
 */
#define GPIO_SPEED_LOW		0
#define GPIO_SPEED_MEDIUM	1
#define	GPIO_SPEED_FAST		2
#define	GPIO_SPEED_HIGH		3

/*
 * @GPIO_PIN_PUPD
 * GPIO Pin Pull Up or Pull Down
 */
#define GPIO_NO_PUPD		0
#define GPIO_PIN_PU			1
#define	GPIO_PIN_PD			2

/*
 *
 */



/*
 * API Prototypes
 */

// Peripheral Clock Control
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnOrDi); // Pointer to Base Address and Enable or Disable Variable

// Initialize and De-Initialize
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);

// Data Read and Write
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value);
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value);
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);

// IRQ Configuration and ISR Handling
void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnOrDi);
void GPIO_IRQHandling(uint8_t PinNumber);





#endif /* INC_STM32F446XX_GPIO_DRIVER_H_ */








