/*==================================================================================*
 *                  		code is made by hazem shaaban                   		*
 * it is submitted to Learn in depth:Mastering embedded systems as an assignment 	*
 *                                                                					*
 *  			this file contain LCD control functions for LCD driver  			*
 *                                                                  				*
 * 			this might not be the best way to do it, but it does the job     		*
 *                     				for a beginner                             		*
/*==================================================================================*/


#include "LCD.h"

static unsigned int count = 0;

void LCD_init(void)
{
	_delay_ms(50);
	// setting all pins connected to LCD to output
	PINDIR_CONTROL |= (1<<RS | 1<< RW | 1<<ENABLE);
	PINDIR_DATA |= 0xFF << LCD_SHIFT;
	
	// control pins output control
	OUTPUT_CONTROL &= ~(1<<RS | 1<<RW);
	OUTPUT_CONTROL |= 1<<ENABLE;
	_delay_ms(15);
	//----------------------------------------------------------->> ready to send commands
	
	// mode select
	#ifdef LCD_8BIT_MODE
	LCD_send_command(LCD_MODE_8BIT_2LINES);
	#endif
	
	#ifdef LCD_4BIT_MODE
	LCD_send_command(0x02);
	LCD_send_command(LCD_MODE_4BIT_2LINES);
	#endif
	
	// initialization prucedure
	LCD_send_command(LCD_ENTRY_MODE);
	LCD_send_command(LCD_DISPLAY_ON_CURSOR_BLINK);
	LCD_send_command(LCD_BEGIN_AT_FIRST_ROW);
}

void LCD_isbusy(void)
{
	// set data lines to input
	PINDIR_DATA &= ~(0xFF << LCD_SHIFT);
	// put LCD in read mode
	OUTPUT_CONTROL |= 1<<RW;
	// put LCD in command mode
	OUTPUT_CONTROL &= ~(1<<RS);
	// kick to initialize read/write
	LCD_kick();
	
	// set data lines to output
	PINDIR_DATA |= 0xFF << LCD_SHIFT;
	
}

void LCD_kick(void)
{
	// to initialize read or write, a kick has to be performed on the enable pin, we simply pull it low, wait a few ms, and then pull it back high
	OUTPUT_CONTROL &= ~(1<<ENABLE);
	_delay_ms(10);
	OUTPUT_CONTROL |= 1<<ENABLE;
}

void LCD_send_command(unsigned char command)
{
	// check if LCD is busy
	LCD_isbusy();
	
	OUTPUT_CONTROL &= ~(1<<RW | 1<<RS);
	
	#ifdef LCD_8BIT_MODE
	// write data to output pins and then give the LCD a kick
	OUTPUT_DATA = command;
	LCD_kick();
	#endif
	
	#ifdef LCD_4BIT_MODE
	// write first half of data to output pins and then give the LCD a kick
	OUTPUT_DATA = (OUTPUT_DATA & 0x0F) | (command & 0xF0);
	LCD_kick();
	// write second half of data to output pins and then give the LCD a kick
	OUTPUT_DATA = (OUTPUT_DATA & 0x0F) | (command << 4);
	LCD_kick();
	#endif
}

void LCD_send_character(unsigned char character)
{
	// check if LCD is busy
	LCD_isbusy();
	
	OUTPUT_CONTROL &= ~(1<<RW);
	OUTPUT_CONTROL |= 1<<RS;
	
	#ifdef LCD_8BIT_MODE
	// write data to output pins and then give the LCD a kick
	OUTPUT_DATA = character;
	LCD_kick();
	#endif
	
	#ifdef LCD_4BIT_MODE
	// write first half of data to output pins and then give the LCD a kick
	OUTPUT_DATA = (OUTPUT_DATA & 0x0F) | (character & 0xF0);
	LCD_kick();
	// write second half of data to output pins and then give the LCD a kick
	OUTPUT_DATA = (OUTPUT_DATA & 0x0F) | (character << 4);
	LCD_kick();
	#endif
	
	count++;
	// condition to prevent losing characters, when the display character limit is passed, go to next line or clear screen if the two lines are full
		if (count == 16)
		{
			LCD_send_command(LCD_BEGIN_AT_SECOND_ROW);
		}
		else if (count == 33)
		{
			count = 0;
			LCD_clear_display();
		}
}

void LCD_send_string(char * string)
{
	// checks if pointer points to anything other than null character
	while (*string)
	{
		// sends the character and increments pointer and counter
		LCD_send_character(*string++);
	}
}

void LCD_clear_display(void)
{
	LCD_send_command(LCD_CLEAR_DISPLAY);
	count = 0;
}

void LCD_send_number(int number)
{
	// format number as a string
	char buffer[50];
	sprintf(buffer, "%d", number);
	LCD_send_string(buffer);
}

void LCD_send_real_number(float number)
{
	// split number into two parts, the integer part and the real part
	char buffer[50];
	int leftside = number;
	number -= leftside;
	number *= 1000;
	sprintf(buffer, "%d.%d", leftside, (int) number);
	LCD_send_string(buffer);
}

void LCD_goto_XY(int line, int digit)
{
	if (line == 1)
	{
		LCD_send_command(LCD_BEGIN_AT_FIRST_ROW + digit);
	}
	else if (line == 2)
	{
		LCD_send_command(LCD_BEGIN_AT_SECOND_ROW + digit);
	}
	count = ((line - 1) * 16) + digit;
}