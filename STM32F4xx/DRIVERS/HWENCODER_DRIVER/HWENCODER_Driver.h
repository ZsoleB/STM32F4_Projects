/*
 * HWENCODER_Driver.h
 *
 *  Created on: 19 feb. 2018
 *      Author: Zsole
 */

#ifndef HWENCODER_DRIVER_H_
#define HWENCODER_DRIVER_H_

#include "stm32f4xx.h"
#include "StdTypes.h"
#include "TCNT_Driver_Cfg.h"

#define HWENCODER_DRIVER_COUNT_ON_TIMER_INPUT_1												(0x01)
#define HWENCODER_DRIVER_COUNT_ON_TIMER_INPUT_2												(0x02)
#define HWENCODER_DRIVER_COUNT_ON_TIMER_INPUT_1_AND_2										(0x03)
#define HWENCODER_DRIVER_CAPTURE_COMPARE_SELECTION_PRIMARY_ON_TI1							(0x01)
#define HWENCODER_DRIVER_CAPTURE_COMPARE_SELECTION_PRIMARY_ON_TI2							(0x02)
#define HWENCODER_DRIVER_CAPTURE_COMPARE_SELECTION_SECONDARY_ON_TI1							(0x02<<0x08)
#define HWENCODER_DRIVER_CAPTURE_COMPARE_SELECTION_SECONDARY_ON_TI2							(0x01<<0x08)
#define HWENCODER_DRIVER_CAPTURE_COMPARE_OUTPUT_ENABLE_PRIMARY								(0x01)
#define HWENCODER_DRIVER_CAPTURE_COMPARE_OUTPUT_ENABLE_SECONDARY							(0x01<<0x04)
#define HWENCODER_DRIVER_CAPTURE_COMPARE_OUTPUT_ENABLE_THIRD								(0x01<<0x08)
#define HWENCODER_DRIVER_CAPTURE_COMPARE_OUTPUT_ENABLE_FOURTH								(0x01<<0x0C)
#define HWENCODER_DRIVER_CAPTURE_COMPARE_OUTPUT_DISABLE_PRIMARY								(0x00)
#define HWENCODER_DRIVER_CAPTURE_COMPARE_OUTPUT_DISABLE_SECONDARY							(0x00<<0x04)
#define HWENCODER_DRIVER_CAPTURE_COMPARE_OUTPUT_DISABLE_THIRD								(0x00<<0x08)
#define HWENCODER_DRIVER_CAPTURE_COMPARE_OUTPUT_DISABLE_FOURTH								(0x00<<0x0C)
#define HWENCODER_DRIVER_CHANNEL_1_AND_2													(0x00)
#define HWENCODER_DRIVER_CHANNEL_3_AND_4													(0x01)

typedef struct
{
	TIM_TypeDef* Timer_Source;
	uint8 HWENCODER_Driver_selected_timer_input;
	uint8 HWENCODER_Driver_Channel_pair;
	uint8 HWENCODER_Driver_Capture_Compare_outputs;
	uint8 HWENCODER_Driver_Capture_Compare_selection_primary;
	uint16 HWENCODER_Driver_Capture_Compare_selection_secondary;
}HWENCODER_Driver_Setup_Type;

extern HWENCODER_Driver_Setup_Type* HWENCODER_SETUP;

void HWENCODER_Driver_Init();
uint32 HWENCODER_Driver_Get_Count_Value(uint8 HWENCODER_setup_nr);

#endif /* HWENCODER_DRIVER_H_ */
