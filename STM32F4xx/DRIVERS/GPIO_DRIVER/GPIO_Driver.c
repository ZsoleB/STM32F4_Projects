/*

 * GPIO_Driver.c
 *
 *  Created on: Jan 10, 2018
 *      Author: zsolt.balo

*/

#include "GPIO_Driver_Cfg.h"

/*Initialize the selected GPIO modules*/
void GPIO_Driver_Init()
{
	uint16 index = 0x00;
	uint16 index1 = 0x00;

	/*Enable the selected peripheral's clock signal*/

	#if GPIO_DRIVER_GPIOA!=NOK
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN;
	#endif
	#if GPIO_DRIVER_GPIOB!=NOK
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIOBEN;
	#endif
	#if GPIO_DRIVER_GPIOC!=NOK
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIOCEN;
	#endif
	#if GPIO_DRIVER_GPIOD!=NOK
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIODEN;
	#endif
	#if GPIO_DRIVER_GPIOE!=NOK
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIOEEN;
	#endif
	#if GPIO_DRIVER_GPIOF!=NOK
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIOFEN;
	#endif
	#if GPIO_DRIVER_GPIOG!=NOK
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIOGEN;
	#endif
	#if GPIO_DRIVER_GPIOH!=NOK
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIOHEN;
	#endif
	#if GPIO_DRIVER_GPIOI!=NOK
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIOIEN;
	#endif
	#if GPIO_DRIVER_GPIOJ!=NOK
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIOJEN;
	#endif
	#if GPIO_DRIVER_GPIOK!=NOK
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIOKEN;
	#endif

	for(index=0x00;index<GPIO_DRIVER_INSTANCE_NUM;index++)
	{
		for(index1=0x00;index1<GPIO_SETUP[index].GPIO_Pin_nr;index1++)
		{
				/*The first step is to clear the default setting*/

				GPIO_SETUP[index].GPIO_Port->MODER     &= (~((uint32)(0x03 <<(2*(GPIO_SETUP[index].GPIO_Pins[index1])))));
				GPIO_SETUP[index].GPIO_Port->OTYPER    &= (~((uint16)(0x01 <<(GPIO_SETUP[index].GPIO_Pins[index1]))));
				GPIO_SETUP[index].GPIO_Port->OSPEEDR   &= (~((uint32)(0x03 <<(2*(GPIO_SETUP[index].GPIO_Pins[index1])))));
				GPIO_SETUP[index].GPIO_Port->PUPDR     &= (~((uint32)(0x03 <<(2*(GPIO_SETUP[index].GPIO_Pins[index1])))));

				if(GPIO_SETUP[index].GPIO_Pins[index1]<0x08)
				{
					/*clear the default alternate function and set the new one*/

					GPIO_SETUP[index].GPIO_Port->AFR[0]    &= (~((uint32)(0x0F <<(4*(GPIO_SETUP[index].GPIO_Pins[index1])))));
					GPIO_SETUP[index].GPIO_Port->AFR[0]    |= ((uint32)((GPIO_SETUP[index].GPIO_Pin_Alternate_function[index1]) <<(4*(GPIO_SETUP[index].GPIO_Pins[index1]))));

				}
				else
				{
					GPIO_SETUP[index].GPIO_Port->AFR[1]    &= (~((uint32)(0x0F <<(4*(GPIO_SETUP[index].GPIO_Pins[index1])))));
					GPIO_SETUP[index].GPIO_Port->AFR[1]    |= ((uint32)((GPIO_SETUP[index].GPIO_Pin_Alternate_function[index1]) <<(4*((GPIO_SETUP[index].GPIO_Pins[index1])-8))));
				}

				/*Set the GPIO configuration*/

				GPIO_SETUP[index].GPIO_Port->MODER     |= ((uint32)((GPIO_SETUP[index].GPIO_Pin_Mode[index1]) <<(2*(GPIO_SETUP[index].GPIO_Pins[index1]))));
				GPIO_SETUP[index].GPIO_Port->OTYPER    |= ((uint16)((GPIO_SETUP[index].GPIO_Pin_OutputType[index1]) <<(GPIO_SETUP[index].GPIO_Pins[index1])));
				GPIO_SETUP[index].GPIO_Port->OSPEEDR   |= ((uint32)((GPIO_SETUP[index].GPIO_Pin_Speed[index1]) <<(2*(GPIO_SETUP[index].GPIO_Pins[index1]))));
				GPIO_SETUP[index].GPIO_Port->PUPDR     |= ((uint32)((GPIO_SETUP[index].GPIO_Pin_PuPd[index1]) <<(2*(GPIO_SETUP[index].GPIO_Pins[index1]))));
		}
	}
}

/*Set the selected pin to 1*/
void GPIO_Driver_SetPin(uint8 GPIO_setup_nr,uint16 Pin)
{
		GPIO_SETUP[GPIO_setup_nr].GPIO_Port->BSRRL|=(1<<(GPIO_SETUP[GPIO_setup_nr].GPIO_Pins[Pin]));
}

/*Clear the selected pin*/
void GPIO_Driver_ClearPin(uint8 GPIO_setup_nr,uint16 Pin)
{
	GPIO_SETUP[GPIO_setup_nr].GPIO_Port->BSRRH|=(1<<(GPIO_SETUP[GPIO_setup_nr].GPIO_Pins[Pin]));
}

/*Read the value of the input data (the value of all the bits)*/
uint16 GPIO_Driver_ReadInputData(uint8 GPIO_setup_nr)
{
	uint16 result = 0x00;
	result = ((uint16)(GPIO_SETUP[GPIO_setup_nr].GPIO_Port->IDR));
	return result;
}

/*Read the value of the input data (the value of only one bit)*/
uint8 GPIO_Driver_ReadInputDataBit(uint8 GPIO_setup_nr,uint16 Bit_number)
{
	uint16 input = 0x00;
	uint8 result = 0x00;

	input  = ((uint16)(GPIO_SETUP[GPIO_setup_nr].GPIO_Port->IDR));
	result = ((input & ((0x01)<<(GPIO_SETUP[GPIO_setup_nr].GPIO_Pins[Bit_number])))!=0x00) ? 1 : 0;
	return result;
}

/*Read the value of the output data register(the value of all the bits)*/
uint16 GPIO_Driver_ReadOutputData(uint8 GPIO_setup_nr)
{
	uint16 result = 0x00;
	result = ((uint16)(GPIO_SETUP[GPIO_setup_nr].GPIO_Port->ODR));
	return result;
}

