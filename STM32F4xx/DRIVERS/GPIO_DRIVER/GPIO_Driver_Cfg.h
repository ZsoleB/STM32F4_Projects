/*
 * GPIO_Driver_Cfg.h
 *
 *  Created on: Jan 23, 2018
 *      Author: zsolt.balo
 */
#ifndef GPIO_DRIVER_CFG_H_
#define GPIO_DRIVER_CFG_H_

#include "GPIO_Driver.h"

#define GPIO_DRIVER_GPIOA 				  			OK
#define GPIO_DRIVER_GPIOB 				  			NOK
#define GPIO_DRIVER_GPIOC 				  			NOK
#define GPIO_DRIVER_GPIOD 				  			NOK
#define GPIO_DRIVER_GPIOE 				  			NOK
#define GPIO_DRIVER_GPIOF 				  			NOK
#define GPIO_DRIVER_GPIOG 				  			NOK
#define GPIO_DRIVER_GPIOH 				  			NOK
#define GPIO_DRIVER_GPIOI 				  			NOK
#define GPIO_DRIVER_GPIOJ 				  			NOK
#define GPIO_DRIVER_GPIOK 				  			NOK
#define GPIO_DRIVER_INSTANCE_NUM 					((uint32)0x01)

typedef enum
{
	GPIO_DRIVER_PORTA
}GPIO_Driver_Port_Instances;

typedef enum
{
	/*PORT B Pins*/
	GPIO_DRIVER_PORTA_PIN4,
	GPIO_DRIVER_PORTA_PIN5,
}GPIO_Driver_Pin_Instances;

#endif /* GPIO_DRIVER_CFG_STM32F103_H_ */
