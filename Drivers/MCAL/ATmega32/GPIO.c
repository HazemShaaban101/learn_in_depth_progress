/************************************************************************************************
				This file is the GPIO drivers for ATmega32 devices
				this file include:
					- GPIO_Pin_Init():initializes a selected pin based on selected port and pin number and pin configurations
					- GPIO_Port_DeInit(): resets a port to reset values
					- GPIO_Pin_Read(): reads the value on one pin on the desired port
					- GPIO_Port_Read(): reads the value on the desired port
					- GPIO_Pin_Write(): writes the  desired value to specified pin
					- GPIO_Port_Write(): writes the value to the desired port
					- GPIO_Pin_Toggle(): Toggles pin between GPIO_HIGH and GPIO_LOW define in GPIO.h:@ref GPIO_PIN_VALUE
					
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

#include "../Inc/GPIO.h"

//===============================================================================================
//	Function definitions
//===============================================================================================


/**===================================================================================================================================================
* @Fn				- GPIO_Pin_Init
* @brief 			- initializes a selected pin based on selected port and pin number and pin configurations
* @param [in] 		- GPIOx: pointer to the desired GPIO port, the pointer is casted to GPIO_t which is a structure that contains all GPIO registers
* @param [in] 		- PinNumber: the number of desired pin on the port
* @param [in] 		- PinMode: the desired operation mode for the selected pin
* @retval 			- none
* Note				- none
*/
void GPIO_Pin_Init(volatile GPIO_t * GPIOx, uint8_t PinNumber, uint8_t PinMode)
{
	switch (PinMode)
	{
		case GPIO_MODE_IN_FLOATING:
			GPIOx->DDR &= ~(1 << PinNumber);
			GPIOx->PORT &= ~(1 << PinNumber);
			break;
		case GPIO_MODE_IN_PU:
			GPIOx->DDR &= ~(1 << PinNumber);
			GPIOx->PORT |= (1 << PinNumber);
		case GPIO_MODE_OUT_PP:
			GPIOx->DDR |= (1 << PinNumber);
	}
}

/**===================================================================================================================================================
* @Fn				- GPIO_Port_DeInit
* @brief 			- Resets a selected port
* @param [in] 		- GPIOx: pointer to the desired GPIO port, the pointer is casted to GPIO_t which is a structure that contains all GPIO registers
* @retval 			- none
* Note				- none
*/
void GPIO_Port_DeInit(volatile GPIO_t * GPIOx)
{
	GPIOx->DDR = 0;
	GPIOx->PORT = 0;
}


/**===================================================================================================================================================
* @Fn				- GPIO_Pin_Read
* @brief 			- Reads a selected pin on a selected port
* @param [in] 		- GPIOx: pointer to the desired GPIO port, the pointer is casted to GPIO_t which is a structure that contains all GPIO registers
* @param [in] 		- PinNumber: number of pin user wants to read from
* @retval 			- Pin reading based on values from GPIO-h:@ref GPIO_PIN_VALUE
* Note				- none
*/
uint8_t GPIO_Pin_Read(volatile GPIO_t * GPIOx, uint8_t PinNumber)
{
	return ((GPIOx->PIN & (1 << PinNumber)) >> PinNumber);
}


/**===================================================================================================================================================
* @Fn				- GPIO_Port_Read
* @brief 			- Reads a selected port
* @param [in] 		- GPIOx: pointer to the desired GPIO port, the pointer is casted to GPIO_t which is a structure that contains all GPIO registers
* @retval 			- the values on all pins of port in the form of an unsigned 8 bit integer
* Note				- none
*/
uint8_t GPIO_Port_Read(volatile GPIO_t * GPIOx)
{
	return GPIOx->PIN;
}


/**===================================================================================================================================================
* @Fn				- GPIO_Pin_Write
* @brief 			- writes to a selected pin in a selected port
* @param [in] 		- GPIOx: pointer to the desired GPIO port, the pointer is casted to GPIO_t which is a structure that contains all GPIO registers
* @param [in] 		- PinNumber: the number of pin user wants to write to
* @param [in] 		- value: the value user wants to write to pin
* @retval 			- none
* Note				- none
*/
void GPIO_Pin_Write(volatile GPIO_t * GPIOx, uint8_t PinNumber, uint8_t value)
{
	if (value == GPIO_LOW)
	{
		GPIOx->PORT &= ~(1 << PinNumber);
	}
	else
	{
		GPIOx->PORT |= 1 << PinNumber;
	}
}


/**===================================================================================================================================================
* @Fn				- GPIO_Port_Write
* @brief 			- writes to a selected port
* @param [in] 		- GPIOx: pointer to the desired GPIO port, the pointer is casted to GPIO_t which is a structure that contains all GPIO registers
* @param [in] 		- value: the value user wants to write to Port
* @retval 			- none
* Note				- none
*/
void GPIO_Port_Write(volatile GPIO_t * GPIOx, uint8_t value)
{
	GPIOx->PORT = value;
}


/**===================================================================================================================================================
* @Fn				- GPIO_Pin_Toggle
* @brief 			- toggles a selected pin on a selected port
* @param [in] 		- GPIOx: pointer to the desired GPIO port, the pointer is casted to GPIO_t which is a structure that contains all GPIO registers
* @param [in] 		- PinNumber: the pin user wants to toggle
* @retval 			- none
* Note				- none
*/
void GPIO_Pin_Toggle(volatile GPIO_t * GPIOx, uint8_t PinNumber)
{
	GPIOx->PORT ^= 1 << PinNumber;
}



