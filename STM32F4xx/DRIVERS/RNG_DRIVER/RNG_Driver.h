/*
 * HWCRC_Driver.h
 *
 *  Created on: Nov 26, 2018
 *      Author: zsolt.balo
 */

#ifndef DRIVERS_RNG_DRIVER_RNG_DRIVER_H_
#define DRIVERS_RNG_DRIVER_RNG_DRIVER_H_

#include "stm32f4xx.h"
#include "StdTypes.h"

#define RNG_DRIVER_SET_ENABLE											((uint32)0x01<<0x02)
#define RNG_DRIVER_INTERRUPT_ENABLE										((uint32)0x01<<0x03)
#define RNG_DRIVER_SEED_ERROR_INTERRUPT									((uint32)0x01<<0x06)
#define RNG_DRIVER_CLOCK_ERROR_INTERRUPT								((uint32)0x01<<0x05)
#define RNG_DRIVER_SEED_ERROR_STATUS									((uint32)0x01<<0x02)
#define RNG_DRIVER_CLOCK_ERROR_STATUS									((uint32)0x01<<0x01)
#define RNG_DRIVER_DATA_READY											((uint32)0x01)

void RNG_Driver_Init();
uint8 RNG_Driver_Check_Random_number();
void RNG_Driver_Clear_Staus(uint32 Status);
uint8 RNG_Driver_Check_Staus(uint32 Status);
uint32 RNG_Driver_Get_Random_number();

#endif /* DRIVERS_RNG_DRIVER_RNG_DRIVER_H_ */
