/************************************************************************************************
				This file is the GPIO drivers for stm32f103x8 devices
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

#include "./Inc/GPIO.h"


//*****************************************************************************************************************************************
//*****************************************************************************************************************************************



//===============================================================================================
//	Function definitions
//===============================================================================================

uint8_t get_CRHL_shift(uint16_t pin_number)
{
	switch (pin_number)
	{
		case GPIO_PIN0:
			return 0;
		case GPIO_PIN1:
			return 4;
		case GPIO_PIN2:
			return 8;
		case GPIO_PIN3:
			return 12;
		case GPIO_PIN4:
			return 16;
		case GPIO_PIN5:
			return 20;
		case GPIO_PIN6:
			return 24;
		case GPIO_PIN7:
			return 28;
		case GPIO_PIN8:
			return 0;
		case GPIO_PIN9:
			return 4;
		case GPIO_PIN10:
			return 8;
		case GPIO_PIN11:
			return 12;
		case GPIO_PIN12:
			return 16;
		case GPIO_PIN13:
			return 20;
		case GPIO_PIN14:
			return 24;
		case GPIO_PIN15:
			return 28;
	}
}

/**===================================================================================================================================================
* @Fn				- GPIO_Pin_Init
* @brief 			- initializes a selected pin based on selected port and pin number and pin configurations
* @param [in] 		- GPIOx: pointer to the desired GPIO port, the pointer is casted to GPIO_t which is a structure that contains all GPIO registers
* @param [in] 		- PinConfig: pointer to a struct that contains pin number, desired pin mode, and pin speed in case of output
* @retval 			- none
* Note				- none
*/
void GPIO_Pin_Init(volatile GPIO_t * GPIOx, GPIO_PIN_CONFIG_t * PinConfig)
{
	// decide which mode register to use (CRH/CRL) based on pin number
	volatile uint32_t *config_reg = (PinConfig->PinNumber < GPIO_PIN8)? &(GPIOx->CRL):&(GPIOx->CRH);
	// put zero in MODE and CNF bits corresponding to the desired pin
	*config_reg &= ~(0xF << get_CRHL_shift(PinConfig->PinNumber));
	// check if user wants to set pin to output
	if ((PinConfig->PinMode == GPIO_MODE_OUT_PP) || (PinConfig->PinMode == GPIO_MODE_OUT_OD) || (PinConfig->PinMode == GPIO_MODE_AFOUT_PP) || (PinConfig->PinMode == GPIO_MODE_AFOUT_OD))
	{
		
		*config_reg |= ((PinConfig->PinMode - 4) << 2 | PinConfig->PinSpeed) << get_CRHL_shift(PinConfig->PinNumber);
	}
	// if code reaches here, user definitely wants to set the pins to input
	else
	{
		switch (PinConfig->PinMode)
		{
			case GPIO_MODE_ANALOG:
				*config_reg |= 0b0000 << get_CRHL_shift(PinConfig->PinNumber);  // CNF = 00		MODE = 00
				break;
			case GPIO_MODE_IN_FLOATING:
				*config_reg |= 0b0100 << get_CRHL_shift(PinConfig->PinNumber);  // CNF = 01		MODE = 00
				break;
			case GPIO_MODE_IN_PU:
				*config_reg |= 0b1000 << get_CRHL_shift(PinConfig->PinNumber);  // CNF = 10		MODE = 00
				GPIOx->ODR |= PinConfig->PinNumber;								// ODR for the desired pin is set to HIGH to enable internal Pull-up resistance
				break;
			case GPIO_MODE_IN_PD:
				*config_reg |= 0b1000 << get_CRHL_shift(PinConfig->PinNumber);  // CNF = 10		MODE = 00
				GPIOx->ODR &= ~(PinConfig->PinNumber);							// ODR for the desired pin is set to LOW to enable internal Pull-down resistance
				break;
			case GPIO_MODE_AFI:
				*config_reg |= 0b0100 << get_CRHL_shift(PinConfig->PinNumber);  // CNF = 01		MODE = 00   (Floating input)
				break;
			default:
				*config_reg |= 0b0000 << get_CRHL_shift(PinConfig->PinNumber);  // CNF = 00		MODE = 00	(Reset value)
				break;
		}
	}
}


/**===================================================================================================================================================
* @Fn				- GPIO_Port_DeInit
* @brief 			- resets the selected port to reset values
* @param [in] 		- GPIOx: pointer to the desired GPIO port, the pointer is casted to GPIO_t which is a structure that contains all GPIO registers
* @retval 			- none
* Note				- none
*/
void GPIO_Port_DeInit(volatile GPIO_t * GPIOx)
{
	// GPIOx->CRL = 0x44444444;
	// GPIOx->CRH = 0x44444444;
	// //GPIOx->IDR = (READ ONLY)
	// GPIOx->ODR = 0x00000000;
	// GPIOx->BSRR = 0x00000000;
	// GPIOx->BRR = 0x00000000;
	// GPIOx->LCK = 0x00000000;
	
	uint8_t GPIO_NUMBER = 0;
	
	switch ((uint32_t) GPIOx)
	{
		case (uint32_t) GPIOA:
			GPIO_NUMBER = 2;
			break;
		case (uint32_t) GPIOB:
			GPIO_NUMBER = 3;
			break;
		case (uint32_t) GPIOC:
			GPIO_NUMBER = 4;
			break;
		case (uint32_t) GPIOD:
			GPIO_NUMBER = 5;
			break;
		case (uint32_t) GPIOE:
			GPIO_NUMBER = 6;
			break;
		default:
			return;
	}
	// employs RCC APB2 reset register
	// IOPxRST: IO port x reset
	// Set and cleared by software.
	// 0: No effect
	// 1: Reset IO port x
	// reset port
	((RCC_t *) RCC)->APB2RSTR |= 1 << GPIO_NUMBER;
	// small delay
	for (int i = 0; i < 10; i++);
	// return reset bit to zero
	((RCC_t *) RCC)->APB2RSTR &= ~(1 << GPIO_NUMBER);
}


/**===================================================================================================================================================
* @Fn				- GPIO_Pin_Read
* @brief 			- reads the value on one pin on the desired port
* @param [in] 		- GPIOx: pointer to the desired GPIO port, the pointer is casted to GPIO_t which is a structure that contains all GPIO registers
* @param [in] 		- PinNumber: desired pin number
* @retval 			- returns 0 if pin is LOW, and 1 if pin is HIGH
* Note				- none
*/

uint8_t GPIO_Pin_Read(volatile GPIO_t * GPIOx, uint16_t PinNumber)
{
	return ((GPIOx->IDR & (1<<PinNumber)) >> PinNumber);
}


/**===================================================================================================================================================
* @Fn				- GPIO_Port_Read
* @brief 			- reads the value on the desired port
* @param [in] 		- GPIOx: pointer to the desired GPIO port, the pointer is casted to GPIO_t which is a structure that contains all GPIO registers
* @retval 			- returns the value on the entire port's pins
* Note				- none
*/

uint16_t GPIO_Port_Read(volatile GPIO_t * GPIOx)
{
	return ((uint16_t) GPIOx->IDR);
}

/**===================================================================================================================================================
* @Fn				- GPIO_Pin_Write
* @brief 			- writes the  desired value to specified pin
* @param [in] 		- GPIOx: pointer to the desired GPIO port, the pointer is casted to GPIO_t which is a structure that contains all GPIO registers
* @param [in] 		- PinNumber: pointer to the desired GPIO port, the pointer is casted to GPIO_t which is a structure that contains all GPIO registers
* @param [in] 		- value: the value user wants to set the pin to
* @retval 			- returns the value on the entire port's pins
* Note				- none
*/
void GPIO_Pin_Write(volatile GPIO_t * GPIOx, uint16_t PinNumber, uint8_t value)
{
	if (value == 0)
	{
		GPIOx->ODR &= ~(1 << PinNumber);
	}
	else
	{
		GPIOx->ODR |= (1 << PinNumber);
	}
}


/**===================================================================================================================================================
* @Fn				- GPIO_Port_Write
* @brief 			- writes the value to the desired port
* @param [in] 		- GPIOx: pointer to the desired GPIO port, the pointer is casted to GPIO_t which is a structure that contains all GPIO registers
* @param [in] 		- value: the value user wants to set the port pins to
* @retval 			- returns the value on the entire port's pins
* Note				- none
*/

void GPIO_Port_Write(volatile GPIO_t * GPIOx, uint16_t value)
{
	GPIOx->ODR |= (uint32_t) value;
}


/**===================================================================================================================================================
* @Fn				- GPIO_Pin_toggle
* @brief 			- toggles a specific pin on the desired port
* @param [in] 		- GPIOx: pointer to the desired GPIO port, the pointer is casted to GPIO_t which is a structure that contains all GPIO registers
* @param [in] 		- PinNumber: number of pin on port
* @retval 			- none
* Note				- none
*/

void GPIO_Pin_toggle(volatile GPIO_t * GPIOx, uint16_t PinNumber)
{
	GPIOx->ODR ^= 1 << PinNumber;
}

