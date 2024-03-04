/*
 * lcd.c
 *
 *  Created on: Mar 2, 2024
 *      Author: wyatt
 */




#include "lcd.h"


/*
 * Private Helper Functions
 */
static void write_4_bits(uint8_t value);
static void lcd_enable(void);
static void mdelay(uint32_t cnt);
static void udelay(uint32_t cnt);


void lcd_send_command(uint8_t cmd){
	/* RS=0 for LCD Command
	 * R/^W=0 for write
	 */
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RS, GPIO_PIN_RESET);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RW, GPIO_PIN_RESET);

	// Send the higher nibble
	write_4_bits(((cmd >> 4) & 0x0F));

	// Send the Lower Nibble
	write_4_bits((cmd & 0x0F));

}


void lcd_print_char(uint8_t data){
	/* RS=1 for Data
	 * R/^W=0 for write
	 */
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RS, GPIO_PIN_SET);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RW, GPIO_PIN_RESET);

	// Send the higher nibble
	write_4_bits((data >> 4));

	// Send the Lower Nibble
	write_4_bits((data & 0x0F));



}


void lcd_print_string(char *message){
	do{
		lcd_print_char((uint8_t)*message);
		message++;
	}while(*message != '\0');
}


/*
 * Row can be 1 or 2
 * Column can be 1 to 16
 */
void lcd_set_cursor(uint8_t row, uint8_t column){
	column--;
	switch(row){
	case 1:
		// Set Cursor to 1st Row Address and add index
		lcd_send_command((column |= 0x80));
		break;
	case 2:
		// Set Cursor to 2nd Row Address and add index
		lcd_send_command((column |= 0xC0));
		break;
	default:
		break;
	}
}


void lcd_init(void){

	// 1. Configure LCD GPIO Pins
	GPIO_Handle_t lcd_signal;

	// Common Configurations of pins
	lcd_signal.pGPIOx = LCD_GPIO_PORT;
	lcd_signal.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT;
	lcd_signal.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	lcd_signal.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	lcd_signal.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	// Initialize Each Pin
	lcd_signal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_RS;
	GPIO_Init(&lcd_signal);
	lcd_signal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_RW;
	GPIO_Init(&lcd_signal);
	lcd_signal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_EN;
	GPIO_Init(&lcd_signal);
	lcd_signal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_D4;
	GPIO_Init(&lcd_signal);
	lcd_signal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_D5;
	GPIO_Init(&lcd_signal);
	lcd_signal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_D6;
	GPIO_Init(&lcd_signal);
	lcd_signal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_D7;
	GPIO_Init(&lcd_signal);

	// Clear all the pins
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RS, GPIO_PIN_RESET);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RW, GPIO_PIN_RESET);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_EN, GPIO_PIN_RESET);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D4, GPIO_PIN_RESET);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D5, GPIO_PIN_RESET);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D6, GPIO_PIN_RESET);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D7, GPIO_PIN_RESET);



	// 2. Initialize the LCD

	// Wait 40milliseconds
	mdelay(40);

	// Write 000011 to RS, R/^W, DB7, DB6, DB5, DB4
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RS, GPIO_PIN_RESET);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RW, GPIO_PIN_RESET);
	write_4_bits(0x3); // 0011

	// Wait for more than 4.1ms
	mdelay(5);
	udelay(150);

	// Write 000011 to RS, R/^W, DB7, DB6, DB5, DB4
	write_4_bits(0x3); // 0011

	// Wait for more than 1us
//	mdelay(1);

	// Write 000011 to RS, R/^W, DB7, DB6, DB5, DB4
	write_4_bits(0x3); // 0011

	// Write the following into DB7, DB6, DB5, DB4
	write_4_bits(0x2); // 0010
	lcd_send_command(LCD_CMD_4DL_2N_5X8F); // Function Set
	lcd_send_command(LCD_CMD_DON_CURON); // Display On Cursor On
	lcd_display_clear(); // Display Clear
	lcd_send_command(LCD_CMD_INCADD); // Entry Mode Set


}


void lcd_display_clear(void){
	lcd_send_command(LCD_CMD_DIS_CLEAR);
	mdelay(5);
}

void lcd_display_return_home(void){
	lcd_send_command(LCD_CMD_DIS_RETURN_HOME);
	mdelay(5);
}


// Writes 4 bits of Data to DB7, DB6, DB5, DB4
static void write_4_bits(uint8_t value){
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D4, (value & 0x1));
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D5, ((value >> 1) & 0x1));
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D6, ((value >> 2) & 0x1));
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D7, ((value >> 3) & 0x1));

	lcd_enable();
}


// Transitions the Enable line to make the LCD Read
static void lcd_enable(void){

	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_EN, GPIO_PIN_SET);
	udelay(10); // Wait 10us
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_EN, GPIO_PIN_RESET);
	udelay(100); // Wait >37us
}


static void mdelay(uint32_t cnt){
	for(uint32_t i=0; i < (cnt * 1000); i++);
}

static void udelay(uint32_t cnt){
	for(uint32_t i=0; i < (cnt * 1); i++);
}












