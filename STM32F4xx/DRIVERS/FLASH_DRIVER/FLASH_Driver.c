/*
 * FLASH_Driver.c
 *
 *  Created on: Jan 21, 2019
 *      Author: zsolt.balo
 */

#include "FLASH_Driver_Cfg.h"

/*Lock the Flash memory, to protect it from unwanted modifications*/
void FLASH_Driver_Lock()
{
	/*Write 1 to the Lock bit to block the access to the flash memory*/
	FLASH->CR|=FLASH_DRIVER_LOCK;
}

/*Unlock the flash memory in order to perform operations on it */
void FLASH_Driver_UnLock()
{
	/*Write the first key to the key register*/
	FLASH->KEYR = FLASH_DRIVER_KEY1;
	/*Write the second key to the key register*/
	FLASH->KEYR = FLASH_DRIVER_KEY2;
}

/*Program a byte length payload to the given address, in the selected sector  */
void FLASH_Driver_Program_Byte(uint32 SectorNumber,uint32 Address,uint64 Payload)
{
	uint8 Data_To_Write = 0x00;
	Data_To_Write = ((uint8)(Payload & 0x00000000000000FF));

	/*Clear previous sector size*/
	FLASH->CR &= FLASH_DRIVER_SECTOR_MASK;

	/*Select the program parallelism size*/
	FLASH->CR|=FLASH_DRIVER_PROGRAM_SIZE_BYTE;

	/*Erase the sector before writing*/
	FLASH_Driver_Erease_Sector(SectorNumber);

	/*Wait for the last operation*/
	while((FLASH->SR & (FLASH_DRIVER_BUSY_FLAG))!=0x00)
	{/*No operation, wait until the busy bit is set*/}

	/*Set the program operation*/
	FLASH->CR |= FLASH_DRIVER_PROGRAM_OP;

	/*Perform program operation to the desired address*/
	*(volatile uint8*)Address = Data_To_Write;

	/*Wait for the last operation*/
	while((FLASH->SR & (FLASH_DRIVER_BUSY_FLAG))!=0x00)
	{/*No operation, wait until the busy bit is set*/}

	/*Clear the program operation*/
	FLASH->CR &= (~FLASH_DRIVER_PROGRAM_OP);

}

/*Program a half word length payload to the given address, in the selected sector  */
void FLASH_Driver_Program_Half_Word(uint32 SectorNumber,uint32 Address,uint64 Payload)
{
	uint16 Data_To_Write = 0x00;
	Data_To_Write = ((uint16)(Payload & 0x000000000000FFFF));

	/*Clear previous sector size*/
	FLASH->CR &= FLASH_DRIVER_SECTOR_MASK;

	/*Select the program parallelism size*/
	FLASH->CR|=FLASH_DRIVER_PROGRAM_SIZE_HALF_WORD;

	/*Erase the sector before writing*/
	FLASH_Driver_Erease_Sector(SectorNumber);

	/*Wait for the last operation*/
	while((FLASH->SR & (FLASH_DRIVER_BUSY_FLAG))!=0x00)
	{/*No operation, wait until the busy bit is set*/}

	/*Set the program operation*/
	FLASH->CR |= FLASH_DRIVER_PROGRAM_OP;

	/*Perform program operation to the desired address*/
	*(volatile uint16*)Address = Data_To_Write;

	/*Wait for the last operation*/
	while((FLASH->SR & (FLASH_DRIVER_BUSY_FLAG))!=0x00)
	{/*No operation, wait until the busy bit is set*/}

	/*Clear the program operation*/
	FLASH->CR &= (~FLASH_DRIVER_PROGRAM_OP);
}

/*Program a word length payload to the given address, in the selected sector  */
void FLASH_Driver_Program_Word(uint32 SectorNumber,uint32 Address,uint64 Payload)
{
	uint32 Data_To_Write = 0x00;
	Data_To_Write = ((uint32)(Payload & 0x00000000FFFFFFFF));

	/*Clear previous sector size*/
	FLASH->CR &= FLASH_DRIVER_SECTOR_MASK;

	/*Select the program parallelism size*/
	FLASH->CR|=FLASH_DRIVER_PROGRAM_SIZE_WORD;

	/*Erase the sector before writing*/
	FLASH_Driver_Erease_Sector(SectorNumber);

	/*Wait for the last operation*/
	while((FLASH->SR & (FLASH_DRIVER_BUSY_FLAG))!=0x00)
	{/*No operation, wait until the busy bit is set*/}

	/*Set the program operation*/
	FLASH->CR |= FLASH_DRIVER_PROGRAM_OP;

	/*Perform program operation to the desired address*/
	*(volatile uint32*)Address = Data_To_Write;

	/*Wait for the last operation*/
	while((FLASH->SR & (FLASH_DRIVER_BUSY_FLAG))!=0x00)
	{/*No operation, wait until the busy bit is set*/}

	/*Clear the program operation*/
	FLASH->CR &= (~FLASH_DRIVER_PROGRAM_OP);
}

/*Program a double word length payload to the given address, in the selected sector */
void FLASH_Driver_Program_Double_Word(uint32 SectorNumber,uint32 Address,uint64 Payload)
{
	uint64 Data_To_Write = 0x00;
	Data_To_Write = Payload;

	/*Clear previous sector size*/
	FLASH->CR &= FLASH_DRIVER_SECTOR_MASK;

	/*Select the program parallelism size*/
	FLASH->CR|=FLASH_DRIVER_PROGRAM_SIZE_DOUBLE_WORD;

	/*Erase the sector before writing*/
	FLASH_Driver_Erease_Sector(SectorNumber);

	/*Wait for the last operation*/
	while((FLASH->SR & (FLASH_DRIVER_BUSY_FLAG))!=0x00)
	{/*No operation, wait until the busy bit is set*/}

	/*Set the program operation*/
	FLASH->CR |= FLASH_DRIVER_PROGRAM_OP;

	/*Perform program operation to the desired address*/
	*(volatile uint64*)Address = Data_To_Write;

	/*Wait for the last operation*/
	while((FLASH->SR & (FLASH_DRIVER_BUSY_FLAG))!=0x00)
	{/*No operation, wait until the busy bit is set*/}

	/*Clear the program operation*/
	FLASH->CR &= (~FLASH_DRIVER_PROGRAM_OP);
}

/*Erase the selected sector */
void FLASH_Driver_Erease_Sector(uint32 SectorNumber)
{
	while((FLASH->SR & (FLASH_DRIVER_BUSY_FLAG))!=0x00)
	{/*No operation, wait until the busy bit is set*/}

	/*Set new sector*/
	FLASH->CR |= SectorNumber;
	/*Set the sector erase operation*/
	FLASH->CR |= FLASH_DRIVER_SECTOR_ERASE_OP;
	/*Start the sector erase operation*/
	FLASH->CR |= FLASH_DRIVER_START_OP;

	/*Wait for the last operation*/
	while((FLASH->SR & (FLASH_DRIVER_BUSY_FLAG))!=0x00)
	{/*No operation, wait until the busy bit is set*/}

	/* If the erase operation is completed, disable the SER Bit */
	FLASH->CR &= (~FLASH_DRIVER_SECTOR_ERASE_OP);
	/*Clear mask*/
	FLASH->CR &= FLASH_DRIVER_SECTOR_MASK;
}

/*Erase all the memory from the selected bank */
void FLASH_Driver_Bank_Erease(uint8 BankNumber)
{
#if(FLASH_DRIVER_FLASH_SIZE == FLASH_DRIVER_FLASH_SIZE_DOUBLE_BANK)
	while((FLASH->SR & (FLASH_DRIVER_BUSY_FLAG))!=0x00)
	{/*No operation, wait until the busy bit is set*/}

	/*Set the mass erase operation for the selected bank*/
	if(BankNumber == FLASH_DRIVER_FLASH_BANK1)
	{
		FLASH->CR |= FLASH_DRIVER_MASS_ERASE_OP;
	}
	else
	{
		FLASH->CR |= FLASH_DRIVER_MASS1_ERASE_OP;
	}

	/*Start the mass erase operation*/
	FLASH->CR |= FLASH_DRIVER_START_OP;

	/*Wait for the last operation*/
	while((FLASH->SR & (FLASH_DRIVER_BUSY_FLAG))!=0x00)
	{/*No operation, wait until the busy bit is set*/}

	/* If the erase operation is completed, disable the slected MER Bit */

	if(BankNumber == FLASH_DRIVER_FLASH_BANK1)
	{
		FLASH->CR &= (~FLASH_DRIVER_MASS_ERASE_OP);
	}
	else
	{
		FLASH->CR &= (~FLASH_DRIVER_MASS1_ERASE_OP);
	}
#else

	/*Function is used only by devices, with 2MB of Flash*/

#endif
}

/*Erase all the Flash memory */
void FLASH_Driver_Mass_Erease()
{
	while((FLASH->SR & (FLASH_DRIVER_BUSY_FLAG))!=0x00)
	{/*No operation, wait until the busy bit is set*/}

#if(FLASH_DRIVER_FLASH_SIZE == FLASH_DRIVER_FLASH_SIZE_DOUBLE_BANK)
	/*Set the mass erase operation for Bank 1 and Bank 2*/
	FLASH->CR |= FLASH_DRIVER_MASS_ERASE_OP;
	FLASH->CR |= FLASH_DRIVER_MASS1_ERASE_OP;
#else
	/*Set the mass erase operation*/
	FLASH->CR |= FLASH_DRIVER_MASS_ERASE_OP;
#endif
	/*Start the mass erase operation*/
	FLASH->CR |= FLASH_DRIVER_START_OP;

	/*Wait for the last operation*/
	while((FLASH->SR & (FLASH_DRIVER_BUSY_FLAG))!=0x00)
	{/*No operation, wait until the busy bit is set*/}

#if(FLASH_DRIVER_FLASH_SIZE == FLASH_DRIVER_FLASH_SIZE_DOUBLE_BANK)
	/*If the erase operation is completed, disable the MER1 and the MER Bit*/
	FLASH->CR &= (~FLASH_DRIVER_MASS_ERASE_OP);
	FLASH->CR &= (~FLASH_DRIVER_MASS1_ERASE_OP);
#else
	/* If the erase operation is completed, disable the MER Bit */
	FLASH->CR &= (~FLASH_DRIVER_MASS_ERASE_OP);
#endif
}

/*Read from the flash driver, using the given address */
uint64 FLASH_Driver_Read(uint32 Address)
{
	uint64 Result = 0x00;

	while((FLASH->SR & (FLASH_DRIVER_BUSY_FLAG))!=0x00)
	{/*No operation, wait until the busy bit is set*/}

	Result = (*(volatile uint64*)Address);

	return Result;
}

/*Function pointer array for the different programming functions */
FLASH_Driver_Program_Type FLASH_Driver_Write[4] =
{
		FLASH_Driver_Program_Byte,
		FLASH_Driver_Program_Half_Word,
		FLASH_Driver_Program_Word,
		FLASH_Driver_Program_Double_Word
};
