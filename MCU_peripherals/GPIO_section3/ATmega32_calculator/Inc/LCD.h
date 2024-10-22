/************************************************************************************************
				This file is the LCD driver header
				this file include:
					
					
				this file is incremental, meaning it is constantly updated based on
				my next project requirements. it is not fully functional for all GPIO
				functions until specified otherwise.
				
				
				*************************************************************
				*				Made by: Hazem Shaaban Bakry				*
				*				github: HazemShaaban101						*
				*				Linkedin: hazemshaaban101					*
				*************************************************************
*************************************************************************************************/


#ifndef _LCD_H_
#define _LCD_H_

//===============================================================================================
//	important includes
//===============================================================================================

#include "ATmega32.h"		// MCU HEADER FILE: contains register addresses
#include "GPIO.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//*****************************************************************************************************************************************
//*****************************************************************************************************************************************

//===============================================================================================
//	// GPIO macro references
//===============================================================================================

// @ref LCD_COMMANDS
#define LCD_MODE_8BIT_1LINE					0x30
#define LCD_MODE_8BIT_2LINES				0x38
#define LCD_MODE_4BIT_1LINE					0x20
#define LCD_MODE_4BIT_2LINES				0x28
#define LCD_ENTRY_MODE						0x06			// called after fully initializing
#define LCD_DISPLAY_OFF_CURSER_OFF			0x08
#define LCD_DISPLAY_ON_CURSOR_ON			0x0E
#define LCD_DISPLAY_ON_CURSOR_OFF			0x0C
#define LCD_DISPLAY_ON_CURSOR_BLINK			0x0F
#define LCD_SHIFT_DISPLAY_LEFT				0x18
#define LCD_SHIFT_DISPLAY_RIGHT				0x1C
#define LCD_MOVE_CURSOR_LEFT				0x10
#define LCD_MOVE_CURSOR_RIGHT				0x14
#define LCD_CLEAR_DISPLAY					0x01
#define LCD_BEGIN_AT_FIRST_ROW				0x80			// to shift cursor to location on first row, add offset to 0x80
#define LCD_BEGIN_AT_SECOND_ROW				0xC0			// to shift cursor to location on second row, add offset to 0xC0




//===============================================================================================
// LCD bit modes, uncomment desired mode
//===============================================================================================

#define LCD_8BIT_MODE
//#define LCD_4BIT_MODE



// define the corresponding bit shift
#ifdef	LCD_4BIT_MODE
#define LCD_SHIFT							4
#endif

#ifdef	LCD_8BIT_MODE
#define LCD_SHIFT							0
#endif


//===============================================================================================
// LCD Pin ports
//===============================================================================================
// define control and data ports
#define PIN_CONTROL							GPIOD
#define PIN_DATA							GPIOC



//===============================================================================================
// LCD Pins
//===============================================================================================
// define individual control pins
#define RS									(0)
#define RW									(1)
#define ENABLE								(2)

#define D0									(0)
#define D1									(1)
#define D2									(2)
#define D3									(3)
#define D4									(4)
#define D5									(5)
#define D6									(6)
#define D7									(7)

//*****************************************************************************************************************************************
//*****************************************************************************************************************************************


// ===============================================================================================
// LCD APIs
// ===============================================================================================

// control function prototypes
void LCD_init(void);
void LCD_kick(void);
void LCD_isbusy(void);
void LCD_send_command(unsigned char command);
void LCD_send_character(unsigned char character);
void LCD_send_string(char * string);
void LCD_clear_display(void);
void LCD_send_number(int number);
void LCD_send_real_number(float number);
void LCD_goto_XY(int line, int digit);


#endif
