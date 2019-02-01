/*
 * GPIO_Driver.h
 *
 *  Created on: Jan 10, 2018
 *      Author: zsolt.balo
 */

#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H

#include "stm32f4xx.h"
#include "StdTypes.h"


#define GPIO_DRIVER_MODE_INPUT								((uint8)0x00)
#define GPIO_DRIVER_MODE_GP_OUT								((uint8)0x01)
#define GPIO_DRIVER_MODE_AF									((uint8)0x02)
#define GPIO_DRIVER_MODE_ANALOG								((uint8)0x03)

#define GPIO_DRIVER_OUT_TYPE_PP								((uint8)0x00)
#define GPIO_DRIVER_OUT_TYPE_OD								((uint8)0x01)

#define GPIO_DRIVER_SPEED_LOW								((uint8)0x00)
#define GPIO_DRIVER_SPEED_MEDIUM							((uint8)0x01)
#define GPIO_DRIVER_SPEED_HIGH								((uint8)0x02)
#define GPIO_DRIVER_SPEED_VERY_HIGH							((uint8)0x03)

#define GPIO_DRIVER_PUPD_NO_PUPD							((uint8)0x00)
#define GPIO_DRIVER_PUPD_PU									((uint8)0x01)
#define GPIO_DRIVER_PUPD_PD									((uint8)0x02)

/*AF0: System*/
#define GPIO_DRIVER_AF_OPT_0								((uint8)0x00)
/*AF1: TIM1/TIM2*/
#define GPIO_DRIVER_AF_OPT_1								((uint8)0x01)
/*AF2: TIM3..5*/
#define GPIO_DRIVER_AF_OPT_2								((uint8)0x02)
/*AF3: TIM8..11*/
#define GPIO_DRIVER_AF_OPT_3								((uint8)0x03)
/*AF4: I2C1..3*/
#define GPIO_DRIVER_AF_OPT_4								((uint8)0x04)
/*AF5: SPI1/2/3/4/5/6*/
#define GPIO_DRIVER_AF_OPT_5								((uint8)0x05)
/*AF6: SPI2/3/SAI1*/
#define GPIO_DRIVER_AF_OPT_6								((uint8)0x06)
/*AF7: USART1..3*/
#define GPIO_DRIVER_AF_OPT_7								((uint8)0x07)
/*AF8: USART4..8*/
#define GPIO_DRIVER_AF_OPT_8								((uint8)0x08)
/*AF9: CAN1/CAN2, LTDC, TIM2..14*/
#define GPIO_DRIVER_AF_OPT_9								((uint8)0x09)
/*AF10: OTG_FS, OTG_HS*/
#define GPIO_DRIVER_AF_OPT_10								((uint8)0x0A)
/*AF11: ETH*/
#define GPIO_DRIVER_AF_OPT_11								((uint8)0x0B)
/*AF12: FMC,SDIO, OTG_HS*/
#define GPIO_DRIVER_AF_OPT_12								((uint8)0x0C)
/*AF13: DCMI*/
#define GPIO_DRIVER_AF_OPT_13								((uint8)0x0D)
/*AF14: LTDC*/
#define GPIO_DRIVER_AF_OPT_14								((uint8)0x0E)
/*AF15:  FPU Eventout*/
#define GPIO_DRIVER_AF_OPT_15								((uint8)0x0F)

typedef struct
{
	GPIO_TypeDef* GPIO_Port;
	uint16 GPIO_Pin_nr;
	uint16 GPIO_Pins[16];
	uint16 GPIO_Pin_Mode[16];
	uint16 GPIO_Pin_OutputType[16];
	uint16 GPIO_Pin_Speed[16];
	uint16 GPIO_Pin_PuPd[16];
	uint16 GPIO_Pin_Alternate_function[16];
}GPIO_Driver_Setup_Type;

extern GPIO_Driver_Setup_Type* GPIO_SETUP;

void GPIO_Driver_Init();
void GPIO_Driver_SetPin(uint8 GPIO_setup_nr,uint16 Pin);
void GPIO_Driver_ClearPin(uint8 GPIO_setup_nr,uint16 Pin);
uint16 GPIO_Driver_ReadInputData(uint8 GPIO_setup_nr);
uint16 GPIO_Driver_ReadOutputData(uint8 GPIO_setup_nr);
uint8 GPIO_Driver_ReadInputDataBit(uint8 GPIO_setup_nr,uint16 Bit_number);
void GPIO_Driver_Lambda_function();

#endif /* GPIO_DRIVER_H_ */

