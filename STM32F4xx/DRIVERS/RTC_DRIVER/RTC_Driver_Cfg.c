/*
 * RTC_Driver_Cfg.c
 *
 *  Created on: Nov 7, 2018
 *      Author: zsolt.balo
 */

#include "RTC_Driver_Cfg.h"
#include "GPIO_Driver_Cfg.h"

volatile static uint8 counter = 0x00;

void RTC_Driver_Callback_Function()
{
/*	if(counter % 2 == 0x00)
	{
		GPIO_Driver_SetPin(GPIO_DRIVER_PORTA,GPIO_DRIVER_PORTA_PIN3);
	}else
	{
		GPIO_Driver_ClearPin(GPIO_DRIVER_PORTA,GPIO_DRIVER_PORTA_PIN3);
	}

	counter++;*/
}


