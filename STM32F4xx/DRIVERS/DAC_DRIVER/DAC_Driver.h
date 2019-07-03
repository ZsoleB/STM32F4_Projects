/*
 * DAC_Driver.h
 *
 *  Created on: Apr 15, 2019
 *      Author: zsolt.balo
 */

#ifndef DRIVERS_DAC_DRIVER_DAC_DRIVER_H_
#define DRIVERS_DAC_DRIVER_DAC_DRIVER_H_

#include "stm32f4xx.h"
#include "StdTypes.h"

#define DAC_DRIVER_CH1_TRIGGER_SELECT(arg)						(arg<<0x03)
#define DAC_DRIVER_CH2_TRIGGER_SELECT(arg)						(arg<<0x13)
#define DAC_DRIVER_CH1_WAVE_SELECT(arg)							(arg<<0x06)
#define DAC_DRIVER_CH2_WAVE_SELECT(arg)							(arg<<0x16)
#define DAC_DRIVER_CH1_SET_AMPLITUDE(arg)						(arg<<0x08)
#define DAC_DRIVER_CH2_SET_AMPLITUDE(arg)						(arg<<0x18)
#define DAC_DRIVER_SINGLE_CHANNEL								(0x00)
#define DAC_DRIVER_TWO_CHANNELS									(0x01)
#define DAC_DRIVER_CHANNEL1										(0x00)
#define DAC_DRIVER_CHANNEL2										(0x01)
#define DAC_DRIVER_CH1_ON										(0x01)
#define DAC_DRIVER_CH1_OFF										(~(0x01))
#define DAC_DRIVER_CH2_ON										(0x01<<0x10)
#define DAC_DRIVER_CH2_OFF										(~(0x01<<0x10))
#define DAC_DRIVER_CH1_TRIGGER_ENABLE							(0x01<<0x02)
#define DAC_DRIVER_CH2_TRIGGER_ENABLE							(0x01<<0x12)
#define DAC_DRIVER_CH1_TRIGGER_DISABLE							(~(0x01<<0x02))
#define DAC_DRIVER_CH2_TRIGGER_DISABLE							(~(0x01<<0x12))
#define DAC_DRIVER_OUTPUT_BUFFER1_ON							(~(0x01<<0x01))
#define DAC_DRIVER_OUTPUT_BUFFER1_OFF							(0x01<<0x01)
#define DAC_DRIVER_OUTPUT_BUFFER2_ON							(~(0x01<<0x11))
#define DAC_DRIVER_OUTPUT_BUFFER2_OFF							(0x01<<0x11)
#define DAC_DRIVER_SW_TRIGGER_CH1								(0x01)
#define DAC_DRIVER_SW_TRIGGER_CH2								(0x01<<0x01)
#define DAC_DRIVER_CH2_DMA_UNDERRUN_FLAG						(0x01<<0x1D)
#define DAC_DRIVER_CH1_DMA_UNDERRUN_FLAG						(0x01<<0x0D)

typedef enum
{
	/*Each time a DAC interface detects a rising edge on the selected timer TRGO output, or on
	the selected external interrupt line 9, the last data stored into the DAC_DHRx register are
	transferred into the DAC_DORx register. The DAC_DORx register is updated three APB1
	cycles after the trigger occurs.*/
	DAC_Driver_TS_TIMER6_EVENT 		= 0x00,
	DAC_Driver_TS_TIMER8_EVENT 		= 0x01,
	DAC_Driver_TS_TIMER7_EVENT 		= 0x02,
	DAC_Driver_TS_TIMER5_EVENT 		= 0x03,
	DAC_Driver_TS_TIMER2_EVENT 		= 0x04,
	DAC_Driver_TS_TIMER4_EVENT 		= 0x05,
	DAC_Driver_TS_EXTI9 			= 0x06,
	/*When software trigger is selected, the transfer from the DAC_DHRx register to the
	DAC_DOR1 register takes only one APB1 clock cycle.*/
	DAC_Driver_TS_Software_Trigger 	= 0x07,
}DAC_Driver_Trigger_Source;

typedef enum
{
	/*Output changes according the DOR register*/
	DAC_Driver_Output_DEFAULT 	= 0x00,
	/*Output will be noise.
	The noise produced by this generator has a flat spectral distribution and can be considered
	white noise. However, instead of having a Gaussian output characteristics, it is uniformly
	distributed. */
	DAC_Driver_Output_LFSR		= 0x01,
	/*Output will be a triangle signal*/
	DAC_Driver_Output_TRIANGLE 	= 0x02,
}DAC_Driver_Output_Signal_Types;

typedef enum
{
	/*
	– 8-bit right alignment: data for DAC channel1 to be loaded into the DAC_DHR8RD
	[7:0] bits (stored into the DHR1[11:4] bits) and data for DAC channel2 to be loaded
	into the DAC_DHR8RD [15:8] bits (stored into the DHR2[11:4] bits)
	*/
	DAC_Driver_8Bit_Right_Alignment  = 0x00,
	/*
	– 12-bit left alignment: data for DAC channel1 to be loaded into the DAC_DHR12LD
	[15:4] bits (stored into the DHR1[11:0] bits) and data for DAC channel2 to be
	loaded into the DAC_DHR12LD [31:20] bits (stored into the DHR2[11:0] bits)
	*/
	DAC_Driver_12Bit_Left_Alignment  = 0x01,
	/*
	– 12-bit right alignment: data for DAC channel1 to be loaded into the
	DAC_DHR12RD [11:0] bits (stored into the DHR1[11:0] bits) and data for DAC
	channel2 to be loaded into the DAC_DHR12LD [27:16] bits (stored into the
	DHR2[11:0] bits)
	*/
	DAC_Driver_12Bit_Right_Alignment = 0x02,
}DAC_Driver_Alignment_Types;

typedef struct
{
	uint16 DAC_Channel_Count;
	uint16 DAC_Output_Signal_Type[2];
	/*This option can be set in the case when triangle or LFSR(noise) is used*/
	uint16 DAC_Output_Signal_Amplitude[2];
	uint16 DAC_Trigger_Enable[2];
	uint16 DAC_Trigger_Source[2];
	uint16 DAC_Output_Buffer_Enable[2];
	uint16 DAC_Data_Alignment[2];
	/*Simultaneous write can be used only, in the case when, both channels have the same output*/
	uint16 DAC_Simultaneous_Write;
}DAC_Driver_Setup_Type;

extern DAC_Driver_Setup_Type* DAC_SETUP;

void DAC_Driver_Init();
uint8 DAC_Driver_GetStatus(uint8 DAC_Channel_Number);
uint16 DAC_Driver_Read_Data_Output(uint8 DAC_Channel_Number);
void DAC_Driver_Write_Buffer(uint8 DAC_Channel_Number);
void DAC_Driver_Write_Data(uint8 DAC_Channel_Number,uint16 DAC_Output_value);
void DAC_Driver_Simultaneous_Write_Data(uint8 DAC_Channel_Number,uint16 DAC_Output_value1,uint16 DAC_Output_value2);
void DAC_Driver_SW_Start(uint8 DAC_Channel_Number);

#endif /* DRIVERS_DAC_DRIVER_DAC_DRIVER_H_ */
