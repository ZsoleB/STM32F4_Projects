///*
// * SYSTEM_Driver.h
// *
// *  Created on: Oct 1, 2018
// *      Author: zsolt.balo
// */
//
//#ifndef DRIVERS_SYSTEM_DRIVER_SYSTEM_DRIVER_H_
//#define DRIVERS_SYSTEM_DRIVER_SYSTEM_DRIVER_H_
//
//#include "stm32f4xx.h"
//#include "StdTypes.h"
//#include "RTC_Driver_Cfg.h"
//
//#define  SYSTEM_DRIVER_HSE_ON									((0x01)<<0x10)
//#define  SYSTEM_DRIVER_HSE_OFF									(~((0x01)<<0x10))
//#define  SYSTEM_DRIVER_HSE_CLOCK_READY							((0x01)<<0x11)
//#define  SYSTEM_DRIVER_HSI_ON									(0x01)
//#define  SYSTEM_DRIVER_HSI_OFF									(0x00)
//#define  SYSTEM_DRIVER_HSI_CLOCK_READY							((0x01)<<0x01)
//#define  SYSTEM_DRIVER_PLL_ON									((0x01)<<0x18)
//#define  SYSTEM_DRIVER_PLL_OFF									(~((0x01)<<0x18))
//#define  SYSTEM_DRIVER_PLL_CLOCK_READY							((0x01)<<0x19)
//#define  SYSTEM_DRIVER_MCO_DISABLE								((0x00)<<0x18)
//#define  SYSTEM_DRIVER_MCO_SYSCLK								((0x04)<<0x18)
//#define  SYSTEM_DRIVER_MCO_HSI									((0x05)<<0x18)
//#define  SYSTEM_DRIVER_MCO_HSE									((0x06)<<0x18)
//#define  SYSTEM_DRIVER_MCO_PLL									((0x07)<<0x18)
//#define  SYSTEM_DRIVER_USB_NO_DIV								((0x01)<<0x16)
//#define  SYSTEM_DRIVER_USB_DIV_1_5								((0x00)<<0x16)
//#define  SYSTEM_DRIVER_PLLMUL_2									((0x00)<<0x12)
//#define  SYSTEM_DRIVER_PLLMUL_3									((0x01)<<0x12)
//#define  SYSTEM_DRIVER_PLLMUL_4									((0x02)<<0x12)
//#define  SYSTEM_DRIVER_PLLMUL_5									((0x03)<<0x12)
//#define  SYSTEM_DRIVER_PLLMUL_6									((0x04)<<0x12)
//#define  SYSTEM_DRIVER_PLLMUL_7									((0x05)<<0x12)
//#define  SYSTEM_DRIVER_PLLMUL_8									((0x06)<<0x12)
//#define  SYSTEM_DRIVER_PLLMUL_9									((0x07)<<0x12)
//#define  SYSTEM_DRIVER_PLLMUL_10								((0x08)<<0x12)
//#define  SYSTEM_DRIVER_PLLMUL_11								((0x09)<<0x12)
//#define  SYSTEM_DRIVER_PLLMUL_12								((0x0a)<<0x12)
//#define  SYSTEM_DRIVER_PLLMUL_13								((0x0b)<<0x12)
//#define  SYSTEM_DRIVER_PLLMUL_14								((0x0c)<<0x12)
//#define  SYSTEM_DRIVER_PLLMUL_15								((0x0d)<<0x12)
//#define  SYSTEM_DRIVER_PLLMUL_16								((0x0e)<<0x12)
//#define  SYSTEM_DRIVER_PLL_CLOCK_NDIV							((0x00)<<0x11)
//#define  SYSTEM_DRIVER_PLL_CLOCK_DIV2							((0x01)<<0x11)
//#define  SYSTEM_DRIVER_PLL_CLOCK_SRC_HSI_DIV2					((0x00)<<0x10)
//#define  SYSTEM_DRIVER_PLL_CLOCK_SRC_HSE						((0x01)<<0x10)
//#define  SYSTEM_DRIVER_ADC_PRE_2								((0x00)<<0x0E)
//#define  SYSTEM_DRIVER_ADC_PRE_4								((0x01)<<0x0E)
//#define  SYSTEM_DRIVER_ADC_PRE_6								((0x02)<<0x0E)
//#define  SYSTEM_DRIVER_ADC_PRE_8								((0x03)<<0x0E)
///*The APB1 and APB2 prescalers are multiplied by 2 for the timers,
//  when the selected prescaler value is greater than 0x01 */
//#define  SYSTEM_DRIVER_APB2_NDIV								((0x00)<<0x0B)
//#define  SYSTEM_DRIVER_APB2_DIV2								((0x04)<<0x0B)
//#define  SYSTEM_DRIVER_APB2_DIV4								((0x05)<<0x0B)
//#define  SYSTEM_DRIVER_APB2_DIV8								((0x06)<<0x0B)
//#define  SYSTEM_DRIVER_APB2_DIV16								((0x07)<<0x0B)
//#define  SYSTEM_DRIVER_APB1_NDIV								((0x00)<<0x08)
//#define  SYSTEM_DRIVER_APB1_DIV2								((0x04)<<0x08)
//#define  SYSTEM_DRIVER_APB1_DIV4								((0x05)<<0x08)
//#define  SYSTEM_DRIVER_APB1_DIV8								((0x06)<<0x08)
//#define  SYSTEM_DRIVER_APB1_DIV16								((0x07)<<0x08)
//#define  SYSTEM_DRIVER_AHB_NDIV									((0x00)<<0x04)
//#define  SYSTEM_DRIVER_AHB_DIV2									((0x08)<<0x04)
//#define  SYSTEM_DRIVER_AHB_DIV4									((0x09)<<0x04)
//#define  SYSTEM_DRIVER_AHB_DIV8									((0x0a)<<0x04)
//#define  SYSTEM_DRIVER_AHB_DIV16								((0x0b)<<0x04)
//#define  SYSTEM_DRIVER_AHB_DIV64								((0x0c)<<0x04)
//#define  SYSTEM_DRIVER_AHB_DIV128								((0x0d)<<0x04)
//#define  SYSTEM_DRIVER_AHB_DIV256								((0x0e)<<0x04)
//#define  SYSTEM_DRIVER_AHB_DIV512								((0x0f)<<0x04)
//#define  SYSTEM_DRIVER_SWITCH_TO_HSI							(0x00)
//#define  SYSTEM_DRIVER_SWITCH_TO_HSE							(0x01)
//#define  SYSTEM_DRIVER_SWITCH_TO_PLL							(0x02)
//
//#define SYSTEM_DRIVER_AIRCR_VECTORKEY_CLEAR_MASK				((uint32)0xFFFF0000)
//#define SYSTEM_DRIVER_AIRCR_VECTORKEY_MASK						((uint32)0x05FA0000)
//
//void SYSTEM_Driver_Software_Reset();
//void SYSTEM_Driver_Set_System_Clock();
//
//#endif /* DRIVERS_SYSTEM_DRIVER_SYSTEM_DRIVER_H_ */
