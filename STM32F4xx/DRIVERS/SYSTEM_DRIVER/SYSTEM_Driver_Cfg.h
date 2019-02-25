/*
 * SYSTEM_Driver_Cfg.h
 *
 *  Created on: Oct 1, 2018
 *      Author: zsolt.balo
 */

#ifndef DRIVERS_SYSTEM_DRIVER_SYSTEM_DRIVER_CFG_H_
#define DRIVERS_SYSTEM_DRIVER_SYSTEM_DRIVER_CFG_H_

#include "SYSTEM_Driver.h"

/*Regulator voltage scaling output selection*/
#define SYSTEM_DRIVER_REGULATOR_SCALE 						SYSTEM_DRIVER_REGULATOR_SCALE_1

/*System clock configuration*/
#define SYSTEM_DRIVER_CLK_SOURCE 							SYSTEM_DRIVER_SWITCH_TO_PLL
#define SYSTEM_DRIVER_PLL_SOURCE 							SYSTEM_DRIVER_PLLSRC_HSE
#define SYSTEM_DRIVER_HCLK_DIV 	 							SYSTEM_DRIVER_AHB_NDIV
#define SYSTEM_DRIVER_PCLK1_DIV 							SYSTEM_DRIVER_APB1_DIV4
#define SYSTEM_DRIVER_PCLK2_DIV 							SYSTEM_DRIVER_APB2_DIV2
#define SYSTEM_DRIVER_PLLQ 									((0x07)<<0x18)
#define SYSTEM_DRIVER_PLLP 									((((0x02)>>1)-1)<<0x10)
#define SYSTEM_DRIVER_PLLN 									((SYSTEM_Driver_Frequency_180MHz)<<0x06)
#define SYSTEM_DRIVER_PLLM 									0x04

/*Select the low power mode(s), which can be used by the application*/
#define SYSTEM_DRIVER_SLEEP_ENABLE 							NOK
#define SYSTEM_DRIVER_STOP_ENABLE 							NOK
#define SYSTEM_DRIVER_STANDBY_ENABLE 						NOK

/*Select the how should the sleep mode behave, before entering in the sleep state*/
#define SYSTEM_DRIVER_SLEEP_MODE 							SYSTEM_DRIVER_SLEEP_NOW

/*Select the how should the low-power mode(s) be entered*/
#define SYSTEM_DRIVER_SLEEP_ENTER 							SYSTEM_DRIVER_USE_WFI
#define SYSTEM_DRIVER_STOP_ENTER 							SYSTEM_DRIVER_USE_WFI
#define SYSTEM_DRIVER_STANDBY_ENTER 						SYSTEM_DRIVER_USE_WFI

/*The event wake-up can't be used, when SLEEP-ON-EXIT is used*/
#if((SYSTEM_DRIVER_SLEEP_MODE == SYSTEM_DRIVER_SLEEP_ON_EXIT)&&\
(SYSTEM_DRIVER_SLEEP_ENTER  != SYSTEM_DRIVER_USE_WFI))

#error "The sleep mode can't be entered and/or woken up, when SLEEP-ON-EXIT is used"

#endif

#define SYSTEM_DRIVER_WKUP_PIN_ENABLE 						OK

/*When the voltage regulator operates in low-power mode, an additional startup delay is
incurred when waking up from Stop mode. By keeping the internal regulator ON during Stop
mode, the consumption is higher although the startup time is reduced.*/
#define SYSTEM_DRIVER_STOP_MODE_LP_ENABLE 					OK

/*When the voltage regulator operates in low-power mode, an additional startup delay is
incurred when waking up from Stop mode. By keeping the internal regulator ON during Stop
mode, the consumption is higher although the startup time is reduced.*/
#define SYSTEM_DRIVER_UNDER_DRIVE_MODE 						OK

/*By setting the FPDS bit in the PWR_CR register, the Flash memory also enters power-down
mode when the device enters Stop mode. When the Flash memory is in power-down mode,
an additional startup delay is incurred when waking up from Stop mode

Note: Its not needed in case, the under-drive mode is used.
*/
#define SYSTEM_DRIVER_FLASH_POWER_DOWN_ENABLE 				NOK

#define SYSTEM_DRIVER_PVD_ENABLE 							NOK
#define SYSTEM_DRIVER_PVD_THRESHOLD 						SYSTEM_DRIVER_PVD_LEVEL_6

#endif /* DRIVERS_SYSTEM_DRIVER_SYSTEM_DRIVER_CFG_H_ */
