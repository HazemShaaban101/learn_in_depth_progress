/************************************************************************************************
				This file is the LCD drivers
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

//===============================================================================================
//	important includes
//===============================================================================================
#include "../Inc/LCD.h"



//===============================================================================================
//	Global variables
//===============================================================================================

static unsigned int count = 0;

//===============================================================================================
//	Function definitions
//===============================================================================================


/**===================================================================================================================================================
* @Fn				- DELAY
* @brief 			- does a delay by trapping the processor in a loop
* @param [in] 		- x: the number of loops desired, each loop counts from 0 to 255
* @retval 			- none
* Note				- not the best approach, should be replaced with MCU's dedicated delay function
*/

static void DELAY(uint16_t x)
{
	int i, j;
	for (i = 0; i < x; i++)
	{
		for (j = 0; j < 255; j++);
	}
}


/**===================================================================================================================================================
* @Fn				- intToStr
* @brief 			- turns an input number into a string
* @param [in] 		- N: the number user wants to turn into a string
* @param [in]		- str: a pointer to the string we want to format the integer inside
* @retval 			- none
* Note				- not the best approach, but since this is a baremetal application, we cannot use standard functions
*/

void intToStr(int N, char *str) {
	if (N == 0)
	{
		str[0] = '0';
		str[1] = 0;
		return;
	}
    int i = 0;
  
    // Save the copy of the number for sign
    int sign = N;

    // If the number is negative, make it positive
    if (N < 0)
        N = -N;

    // Extract digits from the number and add them to the
    // string
    while (N > 0) {
      
        // Convert integer digit to character and store
      	// it in the str
        str[i++] = N % 10 + '0';
      	N /= 10;
    } 

    // If the number was negative, add a minus sign to the
    // string
    if (sign < 0) {
        str[i++] = '-';
    }

    // Null-terminate the string
    str[i] = '\0';

    // Reverse the string to get the correct order
	int j, k;
    for (j = 0, k = i - 1; j < k; j++, k--) {
        char temp = str[j];
        str[j] = str[k];
        str[k] = temp;
    }
}


/**===================================================================================================================================================
* @Fn				- set_DataPins_Direction
* @brief 			- changes the direction of all data pins
* @param [in] 		- direction: the desired direction of data pins based on GPIO.h:@ref GPIO_PIN_MODE
* @retval 			- none
* Note				- none
*/

void set_DataPins_Direction(uint8_t direction)
{
	GPIO_Pin_Init(PIN_DATA, D0, direction);
	GPIO_Pin_Init(PIN_DATA, D1, direction);
	GPIO_Pin_Init(PIN_DATA, D2, direction);
	GPIO_Pin_Init(PIN_DATA, D3, direction);
	GPIO_Pin_Init(PIN_DATA, D4, direction);
	GPIO_Pin_Init(PIN_DATA, D5, direction);
	GPIO_Pin_Init(PIN_DATA, D6, direction);
	GPIO_Pin_Init(PIN_DATA, D7, direction);
}


/**===================================================================================================================================================
* @Fn				- LCD_init
* @brief 			- initializes pins used by the LCD, then gives the LCD the initialization sequence and commands
* @param [in] 		- none
* @retval 			- none
* Note				- none
*/

void LCD_init(void)
{
	DELAY(1000);
	// setting all pins connected to LCD to output
	GPIO_Pin_Init(PIN_CONTROL, RS, GPIO_MODE_OUT_PP);
	GPIO_Pin_Init(PIN_CONTROL, RW, GPIO_MODE_OUT_PP);
	GPIO_Pin_Init(PIN_CONTROL, ENABLE, GPIO_MODE_OUT_PP);
	set_DataPins_Direction(GPIO_MODE_OUT_PP);

	
	// control pins output control
	GPIO_Pin_Write(PIN_CONTROL, RS, GPIO_LOW);
	GPIO_Pin_Write(PIN_CONTROL, RW, GPIO_LOW);
	GPIO_Pin_Write(PIN_CONTROL, ENABLE, GPIO_LOW);
	DELAY(300);
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


/**===================================================================================================================================================
* @Fn				- LCD_isbusy
* @brief 			- checks if LCD is busy
* @param [in] 		- none
* @retval 			- none
* Note				- none
*/

void LCD_isbusy(void)
{
	// set data lines to input
	set_DataPins_Direction(GPIO_MODE_IN_FLOATING);
	// put LCD in read mode
	GPIO_Pin_Write(PIN_CONTROL, RW, GPIO_HIGH);
	// put LCD in command mode
	GPIO_Pin_Write(PIN_CONTROL, RS, GPIO_LOW);
	// kick to initialize read/write
	LCD_kick();
	
	// set data lines to output
	set_DataPins_Direction(GPIO_MODE_OUT_PP);
	
}


/**===================================================================================================================================================
* @Fn				- LCD_kick
* @brief 			- gives the LCD a kick, the kick is turning off enable pin, then a small delay, then turning it back on. this gives the LCD an indicator to read/write
* @param [in] 		- none
* @retval 			- none
* Note				- none
*/

void LCD_kick(void)
{
	// to initialize read or write, a kick has to be performed on the enable pin, we simply pull it low, wait a few ms, and then pull it back high
	GPIO_Pin_Write(PIN_CONTROL, ENABLE, GPIO_LOW);
	DELAY(50);
	GPIO_Pin_Write(PIN_CONTROL, ENABLE, GPIO_HIGH);
}


/**===================================================================================================================================================
* @Fn				- LCD_send_command
* @brief 			- sends a command to LCD
* @param [in] 		- command: the command user wants to send to LCD according to LCD.h:@ref LCD_COMMANDS
* @retval 			- none
* Note				- none
*/

void LCD_send_command(unsigned char command)
{
	// check if LCD is busy
	LCD_isbusy();
	
	GPIO_Pin_Write(PIN_CONTROL, RW, GPIO_LOW);
	GPIO_Pin_Write(PIN_CONTROL, RS, GPIO_LOW);
	
	#ifdef LCD_8BIT_MODE
	// write data to output pins and then give the LCD a kick
	//OUTPUT_DATA = command;
	GPIO_Port_Write(PIN_DATA, (((uint16_t) command << LCD_SHIFT) | (GPIO_Port_Read(PIN_DATA) & 0x00FFu))) ;
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


/**===================================================================================================================================================
* @Fn				- LCD_send_character
* @brief 			- sends a character to LCD
* @param [in] 		- character: the character user wants to send to LCD
* @retval 			- none
* Note				- none
*/

void LCD_send_character(unsigned char character)
{
	// check if LCD is busy
	LCD_isbusy();
	
	// OUTPUT_CONTROL &= ~(1<<RW);
	// OUTPUT_CONTROL |= 1<<RS;
	GPIO_Pin_Write(PIN_CONTROL, RW, GPIO_LOW);
	GPIO_Pin_Write(PIN_CONTROL, RS, GPIO_HIGH);
	
	#ifdef LCD_8BIT_MODE
	// write data to output pins and then give the LCD a kick
	// OUTPUT_DATA = character;
	GPIO_Port_Write(PIN_DATA, (((uint16_t) character << LCD_SHIFT) | (GPIO_Port_Read(PIN_DATA) & 0x00FFu)));
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



/**===================================================================================================================================================
* @Fn				- LCD_send_string
* @brief 			- sends a string to LCD character by character
* @param [in] 		- string: the string user wants to send to LCD
* @retval 			- none
* Note				- none
*/

void LCD_send_string(char * string)
{
	// checks if pointer points to anything other than null character
	while (*string)
	{
		// sends the character and increments pointer and counter
		LCD_send_character(*string++);
	}
}


/**===================================================================================================================================================
* @Fn				- LCD_clear_display
* @brief 			- sends the clear screen command to LCD
* @param [in] 		- none
* @retval 			- none
* Note				- none
*/

void LCD_clear_display(void)
{
	LCD_send_command(LCD_CLEAR_DISPLAY);
	count = 0;
}


/**===================================================================================================================================================
* @Fn				- LCD_send_number
* @brief 			- uses intToStr function to parse a number into a string, then uses LCD_send_string fucntion to print the string
* @param [in] 		- number: the number user wants to print to LCD
* @retval 			- none
* Note				- none
*/

void LCD_send_number(int number)
{
	//format number as a string
	char buffer[50];
	intToStr(number, buffer);
	LCD_send_string(buffer);
}



// void LCD_send_real_number(float number)
// {
	// // split number into two parts, the integer part and the real part
	// char Lbuffer[10];
	// char Rbuffer[10];
	// int leftside = number;
	// number -= (float) leftside;
	// number *= 1000;
	// intToStr((int) leftside, Lbuffer);
	// intToStr(number, Rbuffer);
	// LCD_send_string(Lbuffer);
	// LCD_send_string(Rbuffer);
// }


/**===================================================================================================================================================
* @Fn				- LCD_goto_XY
* @brief 			- sends a command to LCD containing cursor coordinates
* @param [in] 		- line: the desired line on LCD
* @param [in] 		- digit: the desired digit on LCD
* @retval 			- none
* Note				- none
*/

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




