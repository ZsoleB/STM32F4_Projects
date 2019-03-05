/*
 * FMC_Driver.c
 *
 *  Created on: Feb 26, 2019
 *      Author: zsolt.balo
 */

#include "FMC_Driver_Cfg.h"

void FMC_Driver_Init()
{

	RCC->AHB3ENR|=RCC_AHB3ENR_FMCEN;

#if((FMC_DRIVER_MEMMORY_SOURCE & FMC_DRIVER_MEMMORY_SOURCE_SDRAM)!=0x00)

	/*Step 1 Initialize FMC controller according to the attached memory's data sheet*/

#if (FMC_DRIVER_SELECTED_BANK == FMC_DRIVER_BANK1_SELECTION)

	FMC_Bank5_6->SDCR[FMC_DRIVER_BANK1_SELECTION] = FMC_DRIVER_8_BIT_COLUMN|FMC_DRIVER_12_BITS_ROWS|FMC_DRIVER_16_BITS_BUS_WIDTH|FMC_DRIVER_FOUR_INTERNAL_BANKS|
													FMC_DRIVER_3_CYCLES_CAS_LATENCY|FMC_DRIVER_WRITE_ACCESSES_ALLOWED|FMC_DRIVER_SDCLK_2X_HCLK_PERIODS|
													FMC_DRIVER_SINGLE_READ_REQUESTS_NOT_AS_BURSTS|FMC_DRIVER_ONE_HCLK_DELAY;

#elif (FMC_DRIVER_SELECTED_BANK == FMC_DRIVER_BANK2_SELECTION)

	FMC_Bank5_6->SDCR[FMC_DRIVER_BANK1_SELECTION] = FMC_DRIVER_SDCLK_2X_HCLK_PERIODS|FMC_DRIVER_SINGLE_READ_REQUESTS_NOT_AS_BURSTS|FMC_DRIVER_ONE_HCLK_DELAY;
	FMC_Bank5_6->SDCR[FMC_DRIVER_BANK2_SELECTION] = FMC_DRIVER_8_BIT_COLUMN|FMC_DRIVER_12_BITS_ROWS|FMC_DRIVER_16_BITS_BUS_WIDTH|FMC_DRIVER_FOUR_INTERNAL_BANKS|
													FMC_DRIVER_3_CYCLES_CAS_LATENCY|FMC_DRIVER_WRITE_ACCESSES_ALLOWED|FMC_DRIVER_SDCLK_2X_HCLK_PERIODS|
													FMC_DRIVER_SINGLE_READ_REQUESTS_NOT_AS_BURSTS|FMC_DRIVER_ONE_HCLK_DELAY;

#else

#error "The selected FMC_DRIVER_SELECTED_BANK is not correct, choose one from the available ones !"
#endif


#if (FMC_DRIVER_SELECTED_BANK == FMC_DRIVER_BANK1_SELECTION)

	FMC_Bank5_6->SDTR[FMC_DRIVER_BANK1_SELECTION] = FMC_DRIVER_TRCD|FMC_DRIVER_TRP|FMC_DRIVER_TWR|FMC_DRIVER_TRC|FMC_DRIVER_TRAS|FMC_DRIVER_TXSR|FMC_DRIVER_TMRD;

#elif (FMC_DRIVER_SELECTED_BANK == FMC_DRIVER_BANK2_SELECTION)

	FMC_Bank5_6->SDTR[FMC_DRIVER_BANK1_SELECTION] = FMC_DRIVER_TRP |FMC_DRIVER_TRC;
	FMC_Bank5_6->SDTR[FMC_DRIVER_BANK2_SELECTION] = FMC_DRIVER_TRCD|FMC_DRIVER_TWR|FMC_DRIVER_TRAS|FMC_DRIVER_TXSR|FMC_DRIVER_TMRD;

#else

#error "The selected FMC_DRIVER_SELECTED_BANK is not correct, choose one from the available ones !"
#endif

	/*Step 2 send the commands for the memory's initialization sequence*/
	/*1.Clock configuration enable.*/
	FMC_Driver_SendCommand(FMC_DRIVER_DRIVER_CLOCK_CONFIGURATION_ENABLE_CMD_CONFIG);
	FMC_DRIVER_WAIT(FMC_DRIVER_WAIT_PERIOD);

	/*2.PALL (Precharge/set to idle all the rows).*/
	FMC_Driver_SendCommand(FMC_DRIVER_PALL_CMD_CONFIG);

	/*3.Set the Auto-Refresh functionality, so the memory will use an internal counter for row counting,
	otherwise it has to be counted by the application.*/
	FMC_Driver_SendCommand(FMC_DRIVER_AUTO_REFRESH_CMD_CONFIG);

	/*4.Configure the load mode register*/
	FMC_Driver_SendCommand(FMC_DRIVER_LOAD_MODE_CMD_CONFIG);

	/*step 3 Set the refresh rate counter*/
	/* Set the refresh rate counter */
	/* (15.625 us x Freq) - 20 = (15.625 * 90MHz) - 20 = 1386 */
	/* Set the device refresh counter */

	FMC_Bank5_6->SDRTR|=((FMC_DRIVER_REFRESH_COUNT)<<1);

	while ((FMC_Driver_GetStatus(FMC_DRIVER_BUSY_STATUS)) != FAILED)
	{
		/* Wait until the SDRAM controller is ready */
	}

#elif((FMC_DRIVER_MEMMORY_SOURCE & FMC_DRIVER_MEMMORY_SOURCE_NAND_PC_CARD)!=0x00)
	/*Not implemented*/
#elif((FMC_DRIVER_MEMMORY_SOURCE & FMC_DRIVER_MEMMORY_SOURCE_NOR_PSRAM)!=0x00)
	/*Not implemented*/
#else
#error "The selected FMC_DRIVER_MEMMORY_SOURCE is not correct, choose one from the available ones !"
#endif

}
void FMC_Driver_SendCommand(uint32 FMC_Command)
{
#if((FMC_DRIVER_MEMMORY_SOURCE & FMC_DRIVER_MEMMORY_SOURCE_SDRAM)!=0x00)

	while ((FMC_Driver_GetStatus(FMC_DRIVER_BUSY_STATUS)) != FAILED)
	{
		/* Wait until the SDRAM controller is ready */
	}

	FMC_Bank5_6->SDCMR |= FMC_Command;

#elif((FMC_DRIVER_MEMMORY_SOURCE & FMC_DRIVER_MEMMORY_SOURCE_NAND_PC_CARD)!=0x00)
	/*Not implemented*/
#elif((FMC_DRIVER_MEMMORY_SOURCE & FMC_DRIVER_MEMMORY_SOURCE_NOR_PSRAM)!=0x00)
	/*Not implemented*/
#else
#error "The selected FMC_DRIVER_MEMMORY_SOURCE is not correct, choose one from the available ones !"
#endif
}

uint8 FMC_Driver_GetStatus(uint8 Event)
{
	uint8 ResultCode = 0x00;
#if((FMC_DRIVER_MEMMORY_SOURCE & FMC_DRIVER_MEMMORY_SOURCE_SDRAM)!=0x00)

	if ((FMC_Bank5_6->SDSR & Event) != FALSE)
	{
		ResultCode = SUCCES;
	}
	else
	{
		ResultCode = FAILED;
	}

#elif((FMC_DRIVER_MEMMORY_SOURCE & FMC_DRIVER_MEMMORY_SOURCE_NAND_PC_CARD)!=0x00)
	/*Not implemented*/
#elif((FMC_DRIVER_MEMMORY_SOURCE & FMC_DRIVER_MEMMORY_SOURCE_NOR_PSRAM)!=0x00)
	/*Not implemented*/
#else
#error "The selected FMC_DRIVER_MEMMORY_SOURCE is not correct, choose one from the available ones !"
#endif
	return ResultCode;
}
