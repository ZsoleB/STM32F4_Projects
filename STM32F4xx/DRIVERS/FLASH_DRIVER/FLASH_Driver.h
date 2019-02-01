/*
 * FLASH_Driver.h
 *
 *  Created on: Jan 21, 2019
 *      Author: zsolt.balo
 */

#ifndef FLASH_DRIVER_H_
#define FLASH_DRIVER_H_

#include "stm32f4xx.h"
#include "StdTypes.h"

#define FLASH_DRIVER_KEY1					 				((uint32)0x45670123)
#define FLASH_DRIVER_KEY2					 				((uint32)0xCDEF89AB)
#define FLASH_DRIVER_SECTOR_MASK							((uint32)(0xFFFFFF07))
#define FLASH_DRIVER_PGSIZE_MASK							((uint32)(0xFFFFFCFF))
#define FLASH_DRIVER_LOCK					 				((uint32)(0x01<<0x1F))
#define FLASH_DRIVER_START_OP					 			((uint32)(0x01<<0x10))
#define FLASH_DRIVER_SECTOR_ERASE_OP					 	((uint32)(0x01<<0x01))
#define FLASH_DRIVER_MASS_ERASE_OP					 		((uint32)(0x01<<0x02))
#define FLASH_DRIVER_MASS1_ERASE_OP					 		((uint32)(0x01<<0x0F))
#define FLASH_DRIVER_PROGRAM_OP					 			((uint32)(0x01<<0x00))
#define FLASH_DRIVER_BUSY_FLAG					 			((uint32)(0x01<<0x10))
#define FLASH_DRIVER_END_OF_OPERATION_FLAG					((uint32)(0x01))
#define FLASH_DRIVER_VOLTAGE_RANGE_2_7_3_6_V				(0x00)
#define FLASH_DRIVER_VOLTAGE_RANGE_2_4_2_7_V                (0x01)
#define FLASH_DRIVER_VOLTAGE_RANGE_2_1_2_4_V                (0x02)
#define FLASH_DRIVER_VOLTAGE_RANGE_1_8_2_1_V				(0x03)
#define FLASH_DRIVER_PROGRAM_SIZE_BYTE						((uint32)(0x00<<0x08))
#define FLASH_DRIVER_PROGRAM_SIZE_HALF_WORD					((uint32)(0x01<<0x08))
#define FLASH_DRIVER_PROGRAM_SIZE_WORD						((uint32)(0x02<<0x08))
#define FLASH_DRIVER_PROGRAM_SIZE_DOUBLE_WORD				((uint32)(0x03<<0x08))
#define FLASH_DRIVER_SNB_0									((uint32)(0x00<<0x03))
#define FLASH_DRIVER_SNB_1									((uint32)(0x01<<0x03))
#define FLASH_DRIVER_SNB_2									((uint32)(0x02<<0x03))
#define FLASH_DRIVER_SNB_3									((uint32)(0x03<<0x03))
#define FLASH_DRIVER_SNB_4									((uint32)(0x04<<0x03))
#define FLASH_DRIVER_SNB_5									((uint32)(0x05<<0x03))
#define FLASH_DRIVER_SNB_6									((uint32)(0x06<<0x03))
#define FLASH_DRIVER_SNB_7									((uint32)(0x07<<0x03))
#define FLASH_DRIVER_SNB_8									((uint32)(0x08<<0x03))
#define FLASH_DRIVER_SNB_9									((uint32)(0x09<<0x03))
#define FLASH_DRIVER_SNB_10									((uint32)(0x0A<<0x03))
#define FLASH_DRIVER_SNB_11									((uint32)(0x0B<<0x03))
#define FLASH_DRIVER_FLASH_SIZE_SINGLE_BANK					(0x00)
#define FLASH_DRIVER_FLASH_SIZE_DOUBLE_BANK					(0x01)
#define FLASH_DRIVER_FLASH_BANK1							(0x00)
#define FLASH_DRIVER_FLASH_BANK2							(0x01)

typedef void(*FLASH_Driver_Program_Type)(uint32 SectorNumber,uint32 Adress,uint64 Payload);

typedef enum
{
	FLASH_Driver_program_size_byte,
	FLASH_Driver_program_size_half_word,
	FLASH_Driver_program_size_word,
	FLASH_Driver_program_size_double_word
}FLASH_Driver_Program_options;

void FLASH_Driver_Lock();
void FLASH_Driver_UnLock();
void FLASH_Driver_Bank_Erease(uint8 BankNumber);
void FLASH_Driver_Program_Byte(uint32 SectorNumber,uint32 Address,uint64 Payload);
void FLASH_Driver_Program_Half_Word(uint32 SectorNumber,uint32 Address,uint64 Payload);
void FLASH_Driver_Program_Word(uint32 SectorNumber,uint32 Address,uint64 Payload);
void FLASH_Driver_Program_Double_Word(uint32 SectorNumber,uint32 Address,uint64 Payload);
void FLASH_Driver_Erease_Sector(uint32 SectorNumber);
void FLASH_Driver_Mass_Erease();
uint64 FLASH_Driver_Read(uint32 Address);

extern FLASH_Driver_Program_Type FLASH_Driver_Write[4];

#endif /* FLASH_DRIVER_H_ */
