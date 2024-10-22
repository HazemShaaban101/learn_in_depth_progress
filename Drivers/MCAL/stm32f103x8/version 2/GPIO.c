/************************************************************************************************
				This file is the GPIO drivers for stm32f103x8 devices
				this file include:
					- get_CRHL_shift():calculates the shift for CRH or CRL based on pin number
					- GPIO_Pin_Init():initializes a selected pin based on selected port and pin number and pin configurations
					- GPIO_Port_DeInit(): resets a port using RCC APB2RSTR register
					- GPIO_Pin_Read(): reads the value on one pin on the desired port
					- GPIO_Port_Read(): reads the value on the desired port
					- GPIO_Pin_Write(): writes the  desired value to specified pin
					- GPIO_Port_Write(): writes the value to the desired port
					- GPIO_Pin_Output_Speed(): Changes output operation speed of a specific pin
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

#include "./Inc/GPIO.h"


//*****************************************************************************************************************************************
//*****************************************************************************************************************************************



//===============================================================================================
//	Function definitions
//===============================================================================================


/**===================================================================================================================================================
* @Fn				- get_CRHL_shift
* @brief 			- calculates the shift for CRH or CRL based on pin number
* @param [in] 		- PinNumber: the number of desired pin on the port
* @retval 			- the shift to reach the desired pin on CRH and CRL registers as an 8-bit unsigned int
* Note				- none
*/
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
* @param [in] 		- PinNumber: the number of desired pin on the port
* @param [in] 		- PinMode: the desired operation mode for the selected pin
* @retval 			- none
* Note				- none
*/
void GPIO_Pin_Init(volatile GPIO_t * GPIOx, uint8_t PinNumber, uint8_t PinMode)
{
	// decide which mode register to use (CRH/CRL) based on pin number
	volatile uint32_t *config_reg = (PinNumber < GPIO_PIN8)? &(GPIOx->CRL):&(GPIOx->CRH);
	// put zero in MODE and CNF bits corresponding to the desired pin
	*config_reg &= ~(0xF << get_CRHL_shift(PinNumber));
	// check if user wants to set pin to output
	if ((PinMode == GPIO_MODE_OUT_PP) || (PinMode == GPIO_MODE_OUT_OD) || (PinMode == GPIO_MODE_AFOUT_PP) || (PinMode == GPIO_MODE_AFOUT_OD))
	{
		
		*config_reg |= ((PinMode - 4) << 2 | 0x0001) << get_CRHL_shift(PinNumber);		//default speed is 10Mhz, changing speed can be done using GPIO_Pin_Output_Speed function
	}
	// if code reaches here, user definitely wants to set the pins to input
	else
	{
		switch (PinMode)
		{
			case GPIO_MODE_ANALOG:
				*config_reg |= 0b0000 << get_CRHL_shift(PinNumber);  		// CNF = 00		MODE = 00
				break;
			case GPIO_MODE_IN_FLOATING:
				*config_reg |= 0b0100 << get_CRHL_shift(PinNumber);  		// CNF = 01		MODE = 00
				break;
			case GPIO_MODE_IN_PU:
				*config_reg |= 0b1000 << get_CRHL_shift(PinNumber);  		// CNF = 10		MODE = 00
				GPIOx->ODR |= 1 << PinNumber;								// ODR for the desired pin is set to HIGH to enable internal Pull-up resistance
				break;
			case GPIO_MODE_IN_PD:
				*config_reg |= 0b1000 << get_CRHL_shift(PinNumber);  		// CNF = 10		MODE = 00
				GPIOx->ODR &= ~(1 << PinNumber);							// ODR for the desired pin is set to LOW to enable internal Pull-down resistance
				break;
			case GPIO_MODE_AFI:
				*config_reg |= 0b0100 << get_CRHL_shift(PinNumber);  		// CNF = 01		MODE = 00   (Floating input)
				break;
			default:
				*config_reg |= 0b0000 << get_CRHL_shift(PinNumber);  		// CNF = 00		MODE = 00	(Reset value)
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
	return ((GPIOx->IDR & (1 << PinNumber)) >> PinNumber);
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
* @retval 			- none
* Note				- none
*/
void GPIO_Pin_Write(volatile GPIO_t * GPIOx, uint16_t PinNumber, uint8_t value)
{
	if (value == GPIO_LOW)
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
* @retval 			- none
* Note				- none
*/

void GPIO_Port_Write(volatile GPIO_t * GPIOx, uint16_t value)
{
	GPIOx->ODR |= (uint32_t) value;
}






/**===================================================================================================================================================
* @Fn				- GPIO_Pin_Output_Speed
* @brief 			- Changes output operation speed of a specific pin
* @param [in] 		- GPIOx: pointer to the desired GPIO port, the pointer is casted to GPIO_t which is a structure that contains all GPIO registers
* @param [in] 		- PinNumber: number of desired pin based on GPIO.h:@ref GPIO_PIN_NUMBER
* @param [in] 		- PinSpeed: Speed of selected pin based on GPIO.h:@ref GPIO_PIN_NUMBER
* @retval 			- None
* Note				- Pin has to be in output for the speed to change. function will ignore attempts to change the speed of input operating pin
*/
void GPIO_Pin_Output_Speed(volatile GPIO_t * GPIOx, uint8_t PinNumber, uint8_t PinSpeed)
{
	// decide which mode register to use (CRH/CRL) based on pin number
	volatile uint32_t *config_reg = (PinNumber < GPIO_PIN8)? &(GPIOx->CRL):&(GPIOx->CRH);
	// check if pin is in output mode
	if (0x00000003UL << get_CRHL_shift(PinNumber) & *config_reg)
	{
		// clear mode bits for desired pin, then write the new speed to it
		*config_reg &= ~(0x00000003UL << get_CRHL_shift(PinNumber));
		*config_reg |= (PinSpeed << get_CRHL_shift(PinNumber));
	}
}



/**===================================================================================================================================================
* @Fn				- GPIO_Pin_Toggle
* @brief 			- Toggles pin between GPIO_HIGH and GPIO_LOW define in GPIO.h:@ref GPIO_PIN_VALUE
* @param [in] 		- GPIOx: pointer to the desired GPIO port, the pointer is casted to GPIO_t which is a structure that contains all GPIO registers
* @param [in] 		- PinNumber: number of desired pin based on GPIO.h:@ref GPIO_PIN_NUMBER
* @retval 			- None
* Note				- Pin has to be in output for the speed to change. function will ignore attempts to change the speed of input operating pin
*/

void GPIO_Pin_Toggle(volatile GPIO_t * GPIOx, uint16_t PinNumber)
{
	GPIOx->ODR ^= 1 << PinNumber;
}