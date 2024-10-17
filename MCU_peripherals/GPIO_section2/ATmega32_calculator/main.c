/*==================================================================================*
 *                  		code is made by hazem shaaban                   		*
 * it is submitted to Learn in depth:Mastering embedded systems as an assignment 	*
 *                                                                					*
 *     								Calculator app	    					   		*
 * 			  																		*
 *                                                                  				*
 * 			this might not be the best way to do it, but it does the job     		*
 *                     				for a beginner                             		*
/*==================================================================================*/


#include "./LCD_drivers/LCD.h"
#include "./numpad_drivers/numpad.h"

// function prototypes
void calculator(void);
void is_number(char character);
void is_operation(char character);
void is_clr_scrn(void);
void is_equal(void);

// useful global values
int first_value = 0, second_value = 0;
int *value_ptr = &first_value;
unsigned char sign = 0;



int main(void)
{
	LCD_init();
	NUMPAD_init();
	LCD_send_string("hello to my calculator app!");
	_delay_ms(2000);
	LCD_clear_display();
	
	while(1)
	{
		calculator();
	}
	return 0;
}




// calculator app, gets input and buffers it to decide action
void calculator(void)
{
	// read character
	char buffer = NUMPAD_read();
	// analyze character
	if (buffer == '?')		// clear screen character
	{
		is_clr_scrn();
	}
	
	else if (buffer == '=')
	{
		is_equal();
	}
	
	else if (buffer == '+' || buffer == '-' || buffer == '*' || buffer == '/')
	{
		is_operation(buffer);
	}
	
	else if (buffer >= '0' && buffer <= '9')
	{
		is_number(buffer);
	}
}

/*steps of the program
1- get input from numpad
2- analyze input then call corresponding function
*/

void is_number(char character)
{
	// if character is a number, display it on LCD , then concatenate it to the variable pointed to by value pointer
	LCD_send_character(character);
	*value_ptr = (*value_ptr * 10) + (int) (character - '0');
}

void is_operation(char character)
{
	// if characte is an operation, display it on LCD, then save it in sign char
	LCD_send_character(character);
	sign = character;
	value_ptr = &second_value;
}

void is_clr_scrn(void)
{
	// if character is '?', clear screen and variables as if the calculator just restarted
	first_value = 0; second_value = 0; sign = 0; value_ptr = &first_value;
	LCD_clear_display();
}

void is_equal(void)
{
	// if a user presses equal without specifying operation, display the value user entered as answer
	if (value_ptr == &first_value)
	{
		LCD_goto_XY(2, 0);
		LCD_send_string("Answer= ");
		LCD_send_number(first_value);
	}
	// if user did specify operation, switch to the case depending on the operation saved in char sign
	// for any operation, go to second line on lCD, then print the answer depending on operation 
	else
	{
		switch (sign)
		{
			case '+':
				LCD_goto_XY(2, 0);
				LCD_send_string("Answer= ");
				LCD_send_number(first_value + second_value);
				break;
			case '-':
				LCD_goto_XY(2, 0);
				LCD_send_string("Answer= ");
				LCD_send_number(first_value - second_value);
				break;
			case '*':
				LCD_goto_XY(2, 0);
				LCD_send_string("Answer= ");
				LCD_send_number(first_value * second_value);
				break;
			case '/':
				LCD_goto_XY(2, 0);
				LCD_send_string("Answer= ");
				if (second_value == 0)
				{
					// check if denominator is equal to zero, then answer is infinite
					LCD_send_string("infinite");
					break;
				}
				LCD_send_number(first_value / second_value);
				break;
			default:
				LCD_goto_XY(2, 0);
				LCD_send_string("ERROR");
		}
	}
}