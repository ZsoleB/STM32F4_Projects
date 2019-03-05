/*
 * FMC_Driver.h
 *
 *  Created on: Feb 26, 2019
 *      Author: zsolt.balo
 */

#ifndef DRIVERS_FMC_DRIVER_FMC_DRIVER_H_
#define DRIVERS_FMC_DRIVER_FMC_DRIVER_H_

#include "stm32f4xx.h"
#include "StdTypes.h"

/*FMC read/write functions

 Taken the fact that the used SDRAM has a 16bit memory width, the main
 read and write functions are based on the 16bit read/write functions.
 In the case of 8/32 bits, the FMC will adapt the data, making the
 operations complicated to handle. So, by using the 16 methods, the
 8 and 32 bit operations can be derived, creating a much more manageable
 interfaces.
 */

#define FMC_DRIVER_WRITE16(address, value)									(*(volatile uint16*) (FMC_SDRAM_START_ADDRESS + (address)) = (value))
#define FMC_DRIVER_WRITE8(address, value)									(FMC_DRIVER_WRITE16(address, value))
#define FMC_DRIVER_WRITE32(address, value)({\
		do{\
			FMC_DRIVER_WRITE16(address, (uint16)((value & 0xFFFF0000)>>0x10));\
			FMC_DRIVER_WRITE16((address+2), (uint16)(value & 0x0000FFFF));\
			}while(0);\
		})


#define FMC_DRIVER_READ16(arg) ({\
		uint32 payload = 0x00;\
		do{\
			if(((arg/2)%2)==0x00)\
			{\
				payload = (*(volatile uint32*) (FMC_SDRAM_START_ADDRESS+(arg+2)));\
			}\
			else\
			{\
				payload = (((*(volatile uint32*) (FMC_SDRAM_START_ADDRESS+(arg-1)))<<0x08)& 0xFFFF0000);\
			}\
			}while(0);\
			payload = (payload >> 0x10);\
			payload;\
	})

#define FMC_DRIVER_READ8(arg)({\
		uint8 payload = 0x00;\
		do{\
			payload = FMC_DRIVER_READ16(arg);\
			}while(0);\
			payload;\
})

#define FMC_DRIVER_READ32(arg)({\
		uint32 payload = 0x00;\
		do{\
			payload = (((FMC_DRIVER_READ16(arg))<<0x10)|(FMC_DRIVER_READ16(arg+2)));\
			}while(0);\
			payload;\
		})

/*Wait function macro for the initialization time, and an arbitrary delay time, long enough for the needed setup time*/
#define FMC_DRIVER_WAIT_PERIOD												0xFFFF
#define FMC_DRIVER_WAIT(arg)\
	do{\
		uint32 counter = arg;\
		while(counter)\
		{counter--;}\
	}while(0)

#define FMC_DRIVER_MEMMORY_SOURCE_NOR_PSRAM									(0x01)
#define FMC_DRIVER_MEMMORY_SOURCE_NAND_PC_CARD								(0x02)
#define FMC_DRIVER_MEMMORY_SOURCE_SDRAM										(0x04)

#define FMC_DRIVER_BANK1_SELECTION											(0x00)
#define FMC_DRIVER_BANK2_SELECTION											(0x01)

/*Read pipe
 These bits define the delay, in HCLK clock cycles, for reading data after CAS latency*/

#define FMC_DRIVER_NO_HCLK_DELAY 											((0x00)<<0x0D)
#define FMC_DRIVER_ONE_HCLK_DELAY 											((0x01)<<0x0D)
#define FMC_DRIVER_TWO_HCLK_DELAY 											((0x02)<<0x0D)

/*This bit enables burst read mode. The SDRAM controller anticipates the next read commands
during the CAS latency and stores data in the Read FIFO.*/

#define FMC_DRIVER_SINGLE_READ_REQUESTS_NOT_AS_BURSTS						((0x00)<<0x0B)
#define FMC_DRIVER_SINGLE_READ_REQUESTS_AS_BURSTS							((0x01)<<0x0B)

/*These bits define the SDRAM clock period for both SDRAM banks and allow disabling the clock
before changing the frequency. In this case the SDRAM must be re-initialized.*/

#define FMC_DRIVER_SDCLK_CLOCK_DISABLED										((0x00)<<0x0A)
#define FMC_DRIVER_SDCLK_2X_HCLK_PERIODS									((0x01)<<0x0A)
#define FMC_DRIVER_SDCLK_3X_HCLK_PERIODS									((0x02)<<0x0A)

/*Write protection*/

#define FMC_DRIVER_WRITE_ACCESSES_ALLOWED									((0x00)<<0x09)
#define FMC_DRIVER_WRITE_ACCESSES_IGNORED									((0x01)<<0x09)

/*CAS Latency*/

#define FMC_DRIVER_1_CYCLE_CAS_LATENCY										((0x01)<<0x07)
#define FMC_DRIVER_2_CYCLES_CAS_LATENCY										((0x02)<<0x07)
#define FMC_DRIVER_3_CYCLES_CAS_LATENCY										((0x03)<<0x07)

/* Number of internal banks*/

#define FMC_DRIVER_TWO_INTERNAL_BANKS										((0x00)<<0x06)
#define FMC_DRIVER_FOUR_INTERNAL_BANKS										((0x01)<<0x06)

/* Memory data bus width*/

#define FMC_DRIVER_8_BITS_BUS_WIDTH											((0x00)<<0x04)
#define FMC_DRIVER_16_BITS_BUS_WIDTH										((0x01)<<0x04)
#define FMC_DRIVER_32_BITS_BUS_WIDTH										((0x02)<<0x04)

/* Number of row address bits*/

#define FMC_DRIVER_11_BIT_ROWS												((0x00)<<0x02)
#define FMC_DRIVER_12_BITS_ROWS												((0x01)<<0x02)
#define FMC_DRIVER_13_BITS_ROWS												((0x02)<<0x02)

/* Number of column address bits*/

#define FMC_DRIVER_8_BIT_COLUMN												(0x00)
#define FMC_DRIVER_9_BIT_COLUMN												(0x01)
#define FMC_DRIVER_10_BIT_COLUMN											(0x02)
#define FMC_DRIVER_11_BIT_COLUMN											(0x03)

/* Command Target Banks*/

#define FMC_DRIVER_TARGET_BANK_1											((0x01)<<0x04)
#define FMC_DRIVER_TARGET_BANK_2											((0x01)<<0x03)

/* Command modes*/

#define FMC_DRIVER_NORMAL_MODE												(0x00)
#define FMC_DRIVER_CLOCK_CONFIGURATION_ENABLE          						(0x01)
#define FMC_DRIVER_PALL_CMD 												(0x02)
#define FMC_DRIVER_AUTO_REFRESH_CMD                							(0x03)
#define FMC_DRIVER_LOAD_MODE_REGISTER                  						(0x04)
#define FMC_DRIVER_SELF_REFRESH_CMD                							(0x05)
#define FMC_DRIVER_POWER_DOWN_CMD                  							(0x06)

/*Busy status flag*/
/*
 0: SDRAM Controller is ready to accept a new request
 1: SDRAM Controller is not ready to accept a new request
 */
#define FMC_DRIVER_BUSY_STATUS												((0x01)<<0x05)

void FMC_Driver_Init();
void FMC_Driver_SendCommand(uint32 FMC_Command);
uint8 FMC_Driver_GetStatus(uint8 Event);


#endif /* DRIVERS_FMC_DRIVER_FMC_DRIVER_H_ */
