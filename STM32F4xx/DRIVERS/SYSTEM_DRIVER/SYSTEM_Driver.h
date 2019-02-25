/*
 * SYSTEM_Driver.h
 *
 *  Created on: Oct 1, 2018
 *      Author: zsolt.balo
 */

#ifndef DRIVERS_SYSTEM_DRIVER_SYSTEM_DRIVER_H_
#define DRIVERS_SYSTEM_DRIVER_SYSTEM_DRIVER_H_

#include "stm32f4xx.h"
#include "StdTypes.h"
#include "RTC_Driver_Cfg.h"

/*Regulator voltage scaling options*/
#define SYSTEM_DRIVER_REGULATOR_SCALE_3 						((0x01)<<0x0E)
#define SYSTEM_DRIVER_REGULATOR_SCALE_2 						((0x02)<<0x0E)
#define SYSTEM_DRIVER_REGULATOR_SCALE_1 						((0x03)<<0x0E)

/*Enable/Disable MCU clock sources */
#define  SYSTEM_DRIVER_HSE_ON									((0x01)<<0x10)
#define  SYSTEM_DRIVER_HSE_OFF									(~((0x01)<<0x10))
#define  SYSTEM_DRIVER_HSE_CLOCK_READY							((0x01)<<0x11)
#define  SYSTEM_DRIVER_HSI_ON									(0x01)
#define  SYSTEM_DRIVER_HSI_OFF									(~(0x01))
#define  SYSTEM_DRIVER_HSI_CLOCK_READY							((0x01)<<0x01)
#define  SYSTEM_DRIVER_PLL_ON									((0x01)<<0x18)
#define  SYSTEM_DRIVER_PLL_OFF									(~((0x01)<<0x18))
#define  SYSTEM_DRIVER_PLL_CLOCK_READY							((0x01)<<0x19)

/*PLL source selector*/
#define  SYSTEM_DRIVER_PLLSRC_HSI								((0x00)<<0x16)
#define  SYSTEM_DRIVER_PLLSRC_HSE								((0x01)<<0x16)

/*Select MCO source and the prescale value*/
#define  SYSTEM_DRIVER_MCO2_SYSCLK								((0x00)<<0x1E)
#define  SYSTEM_DRIVER_MCO2_PLLI2S								((0x01)<<0x1E)
#define  SYSTEM_DRIVER_MCO2_HSE									((0x02)<<0x1E)
#define  SYSTEM_DRIVER_MCO2_PLL									((0x03)<<0x1E)
#define  SYSTEM_DRIVER_MCO2_PRE_NDIV							((0x00)<<0x1B)
#define  SYSTEM_DRIVER_MCO2_PRE_2								((0x04)<<0x1B)
#define  SYSTEM_DRIVER_MCO2_PRE_3								((0x05)<<0x1B)
#define  SYSTEM_DRIVER_MCO2_PRE_4								((0x06)<<0x1B)
#define  SYSTEM_DRIVER_MCO2_PRE_5								((0x07)<<0x1B)
#define  SYSTEM_DRIVER_MCO1_HSI									((0x00)<<0x15)
#define  SYSTEM_DRIVER_MCO1_LSE									((0x01)<<0x15)
#define  SYSTEM_DRIVER_MCO1_HSE									((0x02)<<0x15)
#define  SYSTEM_DRIVER_MCO1_PLL									((0x03)<<0x15)
#define  SYSTEM_DRIVER_MCO1_PRE_NDIV							((0x00)<<0x18)
#define  SYSTEM_DRIVER_MCO1_PRE_2								((0x04)<<0x18)
#define  SYSTEM_DRIVER_MCO1_PRE_3								((0x05)<<0x18)
#define  SYSTEM_DRIVER_MCO1_PRE_4								((0x06)<<0x18)
#define  SYSTEM_DRIVER_MCO1_PRE_5								((0x07)<<0x18)

/*The APB1 and APB2 prescalers are multiplied by 2 for the timers,
  when the selected prescaler value is greater than 0x01 */
#define  SYSTEM_DRIVER_APB2_NDIV								((0x00)<<0x0D)
#define  SYSTEM_DRIVER_APB2_DIV2								((0x04)<<0x0D)
#define  SYSTEM_DRIVER_APB2_DIV4								((0x05)<<0x0D)
#define  SYSTEM_DRIVER_APB2_DIV8								((0x06)<<0x0D)
#define  SYSTEM_DRIVER_APB2_DIV16								((0x07)<<0x0D)
#define  SYSTEM_DRIVER_APB1_NDIV								((0x00)<<0x0A)
#define  SYSTEM_DRIVER_APB1_DIV2								((0x04)<<0x0A)
#define  SYSTEM_DRIVER_APB1_DIV4								((0x05)<<0x0A)
#define  SYSTEM_DRIVER_APB1_DIV8								((0x06)<<0x0A)
#define  SYSTEM_DRIVER_APB1_DIV16								((0x07)<<0x0A)
#define  SYSTEM_DRIVER_AHB_NDIV									((0x00)<<0x04)
#define  SYSTEM_DRIVER_AHB_DIV2									((0x08)<<0x04)
#define  SYSTEM_DRIVER_AHB_DIV4									((0x09)<<0x04)
#define  SYSTEM_DRIVER_AHB_DIV8									((0x0a)<<0x04)
#define  SYSTEM_DRIVER_AHB_DIV16								((0x0b)<<0x04)
#define  SYSTEM_DRIVER_AHB_DIV64								((0x0c)<<0x04)
#define  SYSTEM_DRIVER_AHB_DIV128								((0x0d)<<0x04)
#define  SYSTEM_DRIVER_AHB_DIV256								((0x0e)<<0x04)
#define  SYSTEM_DRIVER_AHB_DIV512								((0x0f)<<0x04)
#define  SYSTEM_DRIVER_SWITCH_TO_HSI							(0x00)
#define  SYSTEM_DRIVER_SWITCH_TO_HSE							(0x01)
#define  SYSTEM_DRIVER_SWITCH_TO_PLL							(0x02)

/*Select the instruction, which should start the selected low-power mode:

  __WFE: wait for event
  __WFI: wait for interrupt
*/
#define  SYSTEM_DRIVER_USE_WFI									(0x00)
#define  SYSTEM_DRIVER_USE_WFE									(0x01)

/*The STOP mode can be leaved, by setting an EXTI interrupt or event*/
/*SLEEP mode can be leaved by any kind of interrupt*/
#define  SYSTEM_DRIVER_INTERRUPT								(0x00)
#define  SYSTEM_DRIVER_EVENT									(0x01)

/*If the SLEEPONEXIT bit is cleared, the MCU enters Sleep mode as soon
as WFI or WFE instruction is executed*/
#define  SYSTEM_DRIVER_SLEEP_NOW 								((0x00)<<0x01)

/*If the SLEEPONEXIT bit of the SCR is set to 1, when the processor completes the execution
of an exception handler it returns to Thread mode and immediately enters sleep mode. Use
this mechanism in applications that only require the processor to run when an exception
occurs.*/
#define  SYSTEM_DRIVER_SLEEP_ON_EXIT 							((0x01)<<0x01)

/*WKUP pin is used for wakeup from Standby mode and forced in input pull down
configuration*/
#define  SYSTEM_DRIVER_WKUP_PIN 								((0x01)<<0x08)
#define  SYSTEM_DRIVER_DEEP_SLEEP 								((0x01)<<0x02)
#define  SYSTEM_DRIVER_STOP_MODE_MR_UNDER_DRIVE					(0x01<<0x0B)
#define  SYSTEM_DRIVER_STOP_MODE_LP_UNDER_DRIVE					(0x01<<0x0A)
#define  SYSTEM_DRIVER_STOP_MODE_LOW_POWER 						(0x01)
#define  SYSTEM_DRIVER_STOP_MODE_UNDER_DRIVE 					((0x03<<0x12)|SYSTEM_DRIVER_STOP_MODE_MR_UNDER_DRIVE)
#define  SYSTEM_DRIVER_STOP_MODE_UNDER_DRIVE_LP 				((0x03<<0x12)|SYSTEM_DRIVER_STOP_MODE_LP_UNDER_DRIVE|SYSTEM_DRIVER_STOP_MODE_LOW_POWER)
#define  SYSTEM_DRIVER_STOP_MODE_FLASH_POWER_DOWN 				(0x01<<0x09)

#define  SYSTEM_DRIVER_STANDY_BY_MODE_POWER_DOWN 				((0x01)<<0x01)

/*Flag used to indicate if Standby mode was entered*/
#define  SYSTEM_DRIVER_STANDBY_FLAG								((0x01)<<0x01)
/*Flag used to indicate if wake-up pin was used*/
#define  SYSTEM_DRIVER_WAKE_UP_FLAG								(0x01)
/*Clear Standby and Wake-up flags*/
#define  SYSTEM_DRIVER_WAKE_UP_FLAG_CLEAR						((0x01)<<0x02)
#define  SYSTEM_DRIVER_STANDBY_FLAG_CLEAR						((0x01)<<0x03)
#define  SYSTEM_DRIVER_STANDBY_FLAG_SET							(0x01)
#define  SYSTEM_DRIVER_STANDBY_FLAG_NOT_SET						(0x00)

/*Enable the Programable voltage detector*/
#define  SYSTEM_DRIVER_PVD_ON									((0x01)<<0x04)

/*Disable the Programable voltage detector*/
#define  SYSTEM_DRIVER_PVD_OFF									(~((0x01)<<0x04))

/*Set the threshold, from witch the PVD will signal the state of the supply volatge*/
#define  SYSTEM_DRIVER_PVD_THRESHOLD_FLAG						((0x01)<<0x02)

/*Voltage threshold detected by the Programmable Voltage Detector*/
/*2.2V*/
#define  SYSTEM_DRIVER_PVD_LEVEL_0								((0x00)<<0x05)
/*2.3V*/
#define  SYSTEM_DRIVER_PVD_LEVEL_1								((0x01)<<0x05)
/*2.4V*/
#define  SYSTEM_DRIVER_PVD_LEVEL_2								((0x02)<<0x05)
/*2.5V*/
#define  SYSTEM_DRIVER_PVD_LEVEL_3								((0x03)<<0x05)
/*2.6V*/
#define  SYSTEM_DRIVER_PVD_LEVEL_4								((0x04)<<0x05)
/*2.7V*/
#define  SYSTEM_DRIVER_PVD_LEVEL_5								((0x05)<<0x05)
/*2.8V*/
#define  SYSTEM_DRIVER_PVD_LEVEL_6								((0x06)<<0x05)
/*2.9V*/
#define  SYSTEM_DRIVER_PVD_LEVEL_7								((0x07)<<0x05)

#define SYSTEM_DRIVER_AIRCR_VECTORKEY_CLEAR_MASK				((uint32)0xFFFF0000)
#define SYSTEM_DRIVER_AIRCR_VECTORKEY_MASK						((uint32)0x05FA0000)

typedef enum
{
	  SYSTEM_Driver_Frequency_120MHz = 120,
	  SYSTEM_Driver_Frequency_144MHz = 144,
	  SYSTEM_Driver_Frequency_168MHz = 168,
	  /*This frequency can be achieved by over-clocking or
	    by setting the PWR to over-drive mode*/
	  SYSTEM_Driver_Frequency_180MHz = 180
}
SYSTEM_Driver_selectable_frequencies;

void SYSTEM_Driver_Software_Reset();
void SYSTEM_Driver_Set_System_Clock();
void SYSTEM_Driver_PVD_Init();
void SYSTEM_Driver_PVD_Enable();
void SYSTEM_Driver_PVD_Disable();
uint8 SYSTEM_Driver_PVD_Get_Power_Status();
void SYSTEM_Driver_Enter_Sleep_Mode();
void SYSTEM_Driver_Enter_Stop_Mode();
void SYSTEM_Driver_Enter_Standby_Mode();
uint8 SYSTEM_Driver_Enter_Standby_Mode_Check();
#endif /* DRIVERS_SYSTEM_DRIVER_SYSTEM_DRIVER_H_ */
