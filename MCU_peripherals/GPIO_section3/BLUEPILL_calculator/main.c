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


#include "./Inc/LCD.h"
#include "./Inc/numpad.h"

#define SEG_ZERO           0x40
#define SEG_ONE            0x79
#define SEG_TWO            0x24
#define SEG_THREE          0x30
#define SEG_FOUR           0x19
#define SEG_FIVE           0x12
#define SEG_SIX            0x02
#define SEG_SEVEN          0x58
#define SEG_EIGHT          0x00
#define SEG_NINE           0x10

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

void wait_ms(int x)
{
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < 255; j++);
    }
}

int main(void)
{
    unsigned char seg[] = {SEG_ZERO, SEG_ONE, SEG_TWO, SEG_THREE, SEG_FOUR, SEG_FIVE, SEG_SIX, SEG_SEVEN, SEG_EIGHT, SEG_NINE, SEG_ZERO};
    unsigned char disp[] = {'0','1','2','3','4','5','6','7','8','9','0'};
    GPIOA_CLK_EN();
    GPIOB_CLK_EN();
    LCD_init();
    NUMPAD_init();
    GPIO_Pin_Init(GPIOB, 9, GPIO_MODE_OUT_PP);
    GPIO_Pin_Init(GPIOB, 10, GPIO_MODE_OUT_PP);
    GPIO_Pin_Init(GPIOB, 11, GPIO_MODE_OUT_PP);
    GPIO_Pin_Init(GPIOB, 12, GPIO_MODE_OUT_PP);
    GPIO_Pin_Init(GPIOB, 13, GPIO_MODE_OUT_PP);
    GPIO_Pin_Init(GPIOB, 14, GPIO_MODE_OUT_PP);
    GPIO_Pin_Init(GPIOB, 15, GPIO_MODE_OUT_PP);
    LCD_send_string("hello to my calculator app!");
    wait_ms(100);
    LCD_clear_display();
    LCD_send_string("don't mind the 7 seg");
    wait_ms(100);
    LCD_clear_display();
    for (int i = 0; i < 11; i++)
    {
        GPIO_Port_Write(GPIOB, seg[i] << 9);
        LCD_send_character(disp[i]);
        wait_ms(1000);
    }
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
    first_value = 0;
    second_value = 0;
    sign = 0;
    value_ptr = &first_value;
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