/*
 * DAC_Driver_Cfg.c
 *
 *  Created on: Apr 15, 2019
 *      Author: zsolt.balo
 */

#ifndef DRIVERS_DAC_DRIVER_DAC_DRIVER_CFG_C_
#define DRIVERS_DAC_DRIVER_DAC_DRIVER_CFG_C_

#include "DAC_Driver_Cfg.h"

DAC_Driver_Setup_Type DAC_CONF_SETUP =
{
		DAC_DRIVER_SINGLE_CHANNEL,
		{DAC_Driver_Output_LFSR},
		{0x0B},
		{OK},
		{DAC_Driver_TS_Software_Trigger},
		{OK},
		{DAC_Driver_12Bit_Right_Alignment},
		NOK
};

uint16 DAC_Driver_Output_Data_1[DAC_DRIVER_SAMPLE_SIZE_CH1] =
{
		2048, 3251, 3995, 3996, 3253, 2051, 847, 101, 98, 839
};

uint16 DAC_Driver_Output_Data_2[DAC_DRIVER_SAMPLE_SIZE_CH2] =
{

};

DAC_Driver_Setup_Type* DAC_SETUP = &DAC_CONF_SETUP;
uint16* DAC_Driver_Data_Buffer_CH1 = DAC_Driver_Output_Data_1;
uint16* DAC_Driver_Data_Buffer_CH2 = DAC_Driver_Output_Data_2;

#endif /* DRIVERS_DAC_DRIVER_DAC_DRIVER_CFG_C_ */
