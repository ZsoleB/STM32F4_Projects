/*
 * FMC_Driver_Cfg.h
 *
 *  Created on: Feb 26, 2019
 *      Author: zsolt.balo
 */

/* Timing configuration for 90 Mhz of SD clock frequency (180Mhz/2) */
/* 1 clock cycle = 1 / 90MHz = 11.1ns */

/*
 The parameters taken from, the STM32F429ZIT development boards, IS42S16400J SDRAMs datasheet:

 Row Addresses A0-A11
 Column Addresses A0-A7
 memory width 32 bits (to be mappable for the MCU)

 TRCD = 15ns
 TRP = 15ns
 TWR = 2clk
 TRC = 63ns
 TRAS = [42;100,000] ns
 TXSR = 70ns
 TMRD = 2clk

 the timing values start at 0x00 so their values was reduced by 1
 */

#ifndef DRIVERS_FMC_DRIVER_FMC_DRIVER_CFG_H_
#define DRIVERS_FMC_DRIVER_FMC_DRIVER_CFG_H_

#include "FMC_Driver.h"

/*FMC memmory used*/
#define FMC_DRIVER_MEMMORY_SOURCE									FMC_DRIVER_MEMMORY_SOURCE_SDRAM

/*Row to column delay*/

#define FMC_DRIVER_TRCD												((0x01)<<0x18)

/*Row precharge delay*/

#define FMC_DRIVER_TRP 												((0x01)<<0x14)

/*Recovery delay*/

#define FMC_DRIVER_TWR 												((0x01)<<0x10)

/*Row cycle delay*/

#define FMC_DRIVER_TRC 												((0x06)<<0x0C)

/*Self refresh time*/

#define FMC_DRIVER_TRAS												((0x03)<<0x08)

/*Exit Self-refresh delay*/

#define FMC_DRIVER_TXSR												((0x06)<<0x04)

/*Load Mode Register to Active*/

#define FMC_DRIVER_TMRD												(0x01)

/*Refresh Timer Count*/
/*Refresh rate SDRAM refresh rate SDRAM clock frequency = ( ) × – 20*/
/* (7.81 us x Freq) - 20 = (7.81 * 90MHz) - 20 = 683 */

#define FMC_DRIVER_REFRESH_COUNT									(1386)

#define FMC_DRIVER_SELECTED_BANK									FMC_DRIVER_BANK2_SELECTION
#define FMC_DRIVER_COLUMNBITSNUMBER									FMC_DRIVER_8_BIT_COLUMN
#define FMC_DRIVER_ROWBITSNUMBER									FMC_DRIVER_12_BITS_ROWS
#define FMC_DRIVER_MEMORYDATAWIDTH									FMC_DRIVER_16_BITS_BUS_WIDTH
#define FMC_DRIVER_INTERNALBANKNUMBER								FMC_DRIVER_FOUR_INTERNAL_BANKS
#define FMC_DRIVER_CASLATENCY										FMC_DRIVER_3_CYCLES_CAS_LATENCY
#define FMC_DRIVER_WRITEPROTECTION									FMC_DRIVER_WRITE_ACCESSES_ALLOWED
#define FMC_DRIVER_SDCLOCKPERIOD									FMC_DRIVER_SDCLK_2X_HCLK_PERIODS
#define FMC_DRIVER_READBURST										FMC_DRIVER_SINGLE_READ_REQUESTS_NOT_AS_BURSTS
#define FMC_DRIVER_READPIPEDELAY									FMC_DRIVER_ONE_HCLK_DELAY

#if(FMC_DRIVER_SELECTED_BANK == FMC_DRIVER_BANK1_SELECTION)

	#define FMC_DRIVER_SELECTED_TARGET_BANK								FMC_DRIVER_TARGET_BANK_1
	#define FMC_SDRAM_START_ADDRESS										0xC000 0000

#elif(FMC_DRIVER_SELECTED_BANK == FMC_DRIVER_BANK2_SELECTION)

	#define FMC_DRIVER_SELECTED_TARGET_BANK								FMC_DRIVER_TARGET_BANK_2
	#define FMC_SDRAM_START_ADDRESS										0xD0000000

#else
#error "The selected FMC_DRIVER_SELECTED_BANK is not correct, choose one from the available ones !"
#endif
/*
 Burst length: 0x01
 Burst type: Sequential
 CAS latency: 0x03
 Operating mode: Standard Operation
 Write Burst Mode: Single Location Access
 */
#define FMC_DRIVER_MODE_REGISTER_DEFINITION							((0x0231)<<0x09)

#define FMC_DRIVER_DRIVER_CLOCK_CONFIGURATION_ENABLE_CMD_CONFIG		(FMC_DRIVER_CLOCK_CONFIGURATION_ENABLE)|(FMC_DRIVER_SELECTED_TARGET_BANK)|((0x01)<<0x05)
#define FMC_DRIVER_PALL_CMD_CONFIG									(FMC_DRIVER_PALL_CMD)|(FMC_DRIVER_SELECTED_TARGET_BANK)|((0x01)<<0x05)
#define FMC_DRIVER_AUTO_REFRESH_CMD_CONFIG							(FMC_DRIVER_AUTO_REFRESH_CMD)|(FMC_DRIVER_SELECTED_TARGET_BANK)|((0x08)<<0x05)
#define FMC_DRIVER_LOAD_MODE_CMD_CONFIG								(FMC_DRIVER_LOAD_MODE_REGISTER)|(FMC_DRIVER_SELECTED_TARGET_BANK)|((0x01)<<0x05)|(FMC_DRIVER_MODE_REGISTER_DEFINITION)


/*
 These bits define the SDRAM clock period for both SDRAM banks and allow disabling the clock
 before changing the frequency. In this case the SDRAM must be re-initialized.
*/

#endif /* DRIVERS_FMC_DRIVER_FMC_DRIVER_CFG_H_ */
