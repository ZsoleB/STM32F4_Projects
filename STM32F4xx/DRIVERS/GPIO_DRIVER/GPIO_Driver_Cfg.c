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
			GPIOD,
			0x02,
			{0x0C,0x0D},
			{GPIO_DRIVER_MODE_AF,GPIO_DRIVER_MODE_AF},
			{DEFAULT,DEFAULT},
			{GPIO_DRIVER_SPEED_HIGH,GPIO_DRIVER_SPEED_HIGH},
			{GPIO_DRIVER_PUPD_NO_PUPD,GPIO_DRIVER_PUPD_NO_PUPD},
			{GPIO_DRIVER_AF_OPT_2,GPIO_DRIVER_AF_OPT_2}
	},
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
