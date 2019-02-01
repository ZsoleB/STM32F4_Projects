/*
 * HWCRC_Driver.c
 *
 *  Created on: May 7, 2018
 *      Author: zsolt.balo
 */
#include "HWCRC_Driver_Cfg.h"


uint32 HWCRC_Driver_Calculate_CRC(uint32 data)
{
	CRC->DR = data;
	return (uint32)(CRC->DR);
}

void HWCRC_Driver_Init()
{
	#if (HWCRC_DRIVER_ENABLE == OK)
		RCC->AHB1ENR|=RCC_AHB1ENR_CRCEN;
	#endif

	HWCRC_Driver_Reset();
}

void HWCRC_Driver_Reset()
{
	CRC->CR = 0x01;
}
