/************************************************************************************************
				This file is the Numpad drivers
				this file include:
					-NUMPAD_init(): initializes pins used by numpad
					-NUMPAD_read(): reads the numpad input
					
				this file is incremental, meaning it is constantly updated based on
				my next project requirements. it is not fully functional for all numpad
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
#include "../Inc/numpad.h"



//===============================================================================================
//	Global variables
//===============================================================================================
static char pad_matrix[4][4] = {{'7','8','9','/'},{'4','5','6','*'},{'1','2','3','-'},{'?','0','=','+'}};


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

static void DELAY(unsigned int x)
{
	int i, j;
	for (i = 0; i < x; i++)
	{
		for (j = 0; j < 255; j++);
	}
}


/**===================================================================================================================================================
* @Fn				- NUMPAD_init
* @brief 			- Initializes pins used by the numpad
* @param [in] 		- none
* @retval 			- none
* Note				- none
*/

void NUMPAD_init(void)
{
	// first 4 pins output, last 4 pins input pull-up
	// NUMPAD_PORT_DIR	= 0x0F;
	GPIO_Pin_Init(NUMPAD_PORT, NP_A, GPIO_MODE_OUT_PP);
	GPIO_Pin_Init(NUMPAD_PORT, NP_B, GPIO_MODE_OUT_PP);
	GPIO_Pin_Init(NUMPAD_PORT, NP_C, GPIO_MODE_OUT_PP);
	GPIO_Pin_Init(NUMPAD_PORT, NP_D, GPIO_MODE_OUT_PP);
	
	GPIO_Pin_Init(NUMPAD_PORT, NP_1, GPIO_MODE_IN_FLOATING);
	GPIO_Pin_Init(NUMPAD_PORT, NP_2, GPIO_MODE_IN_FLOATING);
	GPIO_Pin_Init(NUMPAD_PORT, NP_3, GPIO_MODE_IN_FLOATING);
	GPIO_Pin_Init(NUMPAD_PORT, NP_4, GPIO_MODE_IN_FLOATING);
	// output pins high, input pins pulled high
	// NUMPAD_WRITE = 0xFF;
	GPIO_Pin_Write(NUMPAD_PORT, NP_A, GPIO_HIGH);
	GPIO_Pin_Write(NUMPAD_PORT, NP_B, GPIO_HIGH);
	GPIO_Pin_Write(NUMPAD_PORT, NP_C, GPIO_HIGH);
	GPIO_Pin_Write(NUMPAD_PORT, NP_D, GPIO_HIGH);

}




/**===================================================================================================================================================
* @Fn				- NUMPAD_read
* @brief 			- Reads the pressed button on the numpad
* @param [in] 		- none
* @retval 			- returns a char based on pad_matrix array
* Note				- none
*/

char NUMPAD_read(void)
{
	int i, j;
	for (i = NP_A; i < NP_1; i++)
	{
		// turn off pin i
		// NUMPAD_WRITE &= ~(1 << i);
		GPIO_Pin_Write(NUMPAD_PORT, i, GPIO_LOW);
		
		for (j = NP_1; j < NP_4 + 1; j++)
		{
			if (GPIO_Pin_Read(NUMPAD_PORT, j) == 0)
			{
				while (GPIO_Pin_Read(NUMPAD_PORT, j) == 0);		// stay in loop until button is not pressed
				
				GPIO_Pin_Write(NUMPAD_PORT, i, GPIO_HIGH);
				return pad_matrix[i][j - NP_1];
			}
			DELAY(20);	
		}
		// NUMPAD_WRITE |= 1<<i;
		GPIO_Pin_Write(NUMPAD_PORT, i, GPIO_HIGH);
		DELAY(20);
	}
	return 0;
}