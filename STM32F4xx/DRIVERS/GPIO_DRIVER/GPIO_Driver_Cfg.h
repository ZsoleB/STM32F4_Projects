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
#define GPIO_DRIVER_GPIOB 				  			OK
#define GPIO_DRIVER_GPIOC 				  			NOK
#define GPIO_DRIVER_GPIOD 				  			NOK
#define GPIO_DRIVER_GPIOE 				  			NOK
#define GPIO_DRIVER_GPIOF 				  			NOK
#define GPIO_DRIVER_GPIOG 				  			NOK
#define GPIO_DRIVER_GPIOH 				  			NOK
#define GPIO_DRIVER_GPIOI 				  			NOK
#define GPIO_DRIVER_GPIOJ 				  			NOK
#define GPIO_DRIVER_GPIOK 				  			NOK
#define GPIO_DRIVER_INSTANCE_NUM 					((uint32)0x02)

typedef enum
{
	GPIO_DRIVER_PORTA,
	GPIO_DRIVER_PORTB
}GPIO_Driver_Instances;

typedef enum
{
	GPIO_DRIVER_PORTA_PIN5,
	GPIO_DRIVER_PORTA_PIN6,
	GPIO_DRIVER_PORTA_PIN7
}GPIO_Driver_A_Pin_Instances;

typedef enum
{
	GPIO_DRIVER_PORTB_PIN1,
}GPIO_Driver_B_Pin_Instances;

#endif /* GPIO_DRIVER_CFG_STM32F103_H_ */
