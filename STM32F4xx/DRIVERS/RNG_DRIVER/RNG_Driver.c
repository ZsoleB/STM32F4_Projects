/*
 * HWCRC_Driver.c
 *
 *  Created on: Nov 26, 2018
 *      Author: zsolt.balo
 */

#include "RNG_Driver_Cfg.h"

void RNG_Driver_Init()
{
	#if(RNG_DRIVER_ENABLE == OK)
		RCC->AHB2ENR |= RCC_AHB2ENR_RNGEN;
	#endif

	#if(RNG_DRIVER_ENABLE_DURING_SLEEP_MODE == OK)
		RCC->AHB2LPENR |= RCC_AHB2LPENR_RNGLPEN;
	#endif

		RNG->CR |= RNG_DRIVER_SET_ENABLE;

	#if(RNG_DRIVER_ENABLE_INTERRUPT == OK)
		RNG->CR |= RNG_DRIVER_ENABLE_INTERRUPT;
	#endif
}

uint8 RNG_Driver_Check_Random_number()
{
	uint32 RNG_Driver_New_Value = 0x00, RNG_Driver_Old_Value = 0x00;

	RNG_Driver_Old_Value = RNG_Driver_Get_Random_number();
	RNG_Driver_New_Value = RNG_Driver_Get_Random_number();

	if(RNG_Driver_New_Value == RNG_Driver_Old_Value)
	{
		return 0x01;
	}
	else
	{
		return 0x00;
	}
}

void RNG_Driver_Clear_Staus(uint32 Status)
{
	RNG->SR &= (~(Status));
}

uint8 RNG_Driver_Check_Staus(uint32 Status)
{
	uint8 result;

	if((RNG->SR & Status) != 0x00)
	{
		result = SUCCES;
	}
	else
	{
		result = FAILED;
	}

	return result;
}

uint32 RNG_Driver_Get_Random_number()
{
	return (uint32)(RNG->DR);
}
