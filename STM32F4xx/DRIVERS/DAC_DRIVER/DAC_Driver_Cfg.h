/*
 * DAC_Driver_Cfg.h
 *
 *  Created on: Apr 15, 2019
 *      Author: zsolt.balo
 */

#ifndef DRIVERS_DAC_DRIVER_DAC_DRIVER_CFG_H_
#define DRIVERS_DAC_DRIVER_DAC_DRIVER_CFG_H_

#include "DAC_Driver.h"

#define DAC_DRIVER_SELECTED_SINGLE_CHANNEL						DAC_DRIVER_CHANNEL1
#define DAC_DRIVER_SAMPLE_SIZE_CH1								0x0A
#define DAC_DRIVER_SAMPLE_SIZE_CH2								0x00

extern uint16* DAC_Driver_Data_Buffer_CH1;
extern uint16* DAC_Driver_Data_Buffer_CH2;

#endif /* DRIVERS_DAC_DRIVER_DAC_DRIVER_CFG_H_ */
