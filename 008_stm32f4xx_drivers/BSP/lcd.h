/*
 * lcd.h
 *
 *  Created on: Mar 2, 2024
 *      Author: wyatt
 */

#ifndef LCD_H_
#define LCD_H_


#include "stm32f446xx.h"

/*
 * Application Configurable Items
 */
/*
 * LCD Pins
 * RS --> PC13
 * R/^W --> PC14
 * EN --> PC15
 * D4 --> PC9
 * D5 --> PC8
 * D6 --> PC6
 * D7 --> PC5
 *
 */
#define LCD_GPIO_PORT		GPIOC
#define LCD_GPIO_RS			GPIO_PIN_NO_0
#define LCD_GPIO_RW			GPIO_PIN_NO_7
#define LCD_GPIO_EN			GPIO_PIN_NO_8
#define LCD_GPIO_D4			GPIO_PIN_NO_9
#define LCD_GPIO_D5			GPIO_PIN_NO_4
#define LCD_GPIO_D6			GPIO_PIN_NO_5
#define LCD_GPIO_D7			GPIO_PIN_NO_6

/* LCD Commands */
#define LCD_CMD_4DL_2N_5X8F			0x28		// Function Set. 4 Data Length, 2 Lines, Font Size 5x8
#define LCD_CMD_DON_CURON			0x0E		// Display On, Cursor On
#define	LCD_CMD_INCADD				0x06		// Increment DDRAM Address
#define LCD_CMD_DIS_CLEAR			0x01		// Display Clear
#define LCD_CMD_DIS_RETURN_HOME		0x02		// Display Return Home




/* API Prototypes */
void lcd_init(void);
void lcd_send_command(uint8_t cmd);
void lcd_print_char(uint8_t data);
void lcd_print_string(char *message);
void lcd_display_clear(void);
void lcd_display_return_home(void);
void lcd_set_cursor(uint8_t row, uint8_t column);


#endif /* LCD_H_ */










