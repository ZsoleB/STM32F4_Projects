/*
 * GPIO_Driver_Cfg.c
 *
 *  Created on: Aug 21, 2018
 *      Author: zsolt.balo
 */

#include "GPIO_Driver_Cfg.h"

GPIO_Driver_Setup_Type GPIO_CONF_SETUP[GPIO_DRIVER_INSTANCE_NUM]=
{
	{
			GPIOA,
			0x01,
			{0x00},
			{GPIO_DRIVER_MODE_INPUT},
			{DEFAULT},
			{DEFAULT},
			{GPIO_DRIVER_PUPD_NO_PUPD},
			{DEFAULT}
	},
	{
			GPIOG,
			0x01,
			{0x0E},
			{GPIO_DRIVER_MODE_GP_OUT},
			{GPIO_DRIVER_OUT_TYPE_PP},
			{GPIO_DRIVER_SPEED_VERY_HIGH},
			{GPIO_DRIVER_PUPD_NO_PUPD},
			{DEFAULT}
	}
};

GPIO_Driver_Setup_Type* GPIO_SETUP = GPIO_CONF_SETUP;

void GPIO_Driver_Lambda_function()
{
/*	static uint8 status = 0x00;

	if(status == 0x00)
	{
		GPIO_Driver_ClearPin(GPIO_DRIVER_PORTG,GPIO_DRIVER_PORTG_PIN13);
	}
	else
	{
		GPIO_Driver_SetPin(GPIO_DRIVER_PORTG,GPIO_DRIVER_PORTG_PIN13);
	}

	status = !status;*/
}
