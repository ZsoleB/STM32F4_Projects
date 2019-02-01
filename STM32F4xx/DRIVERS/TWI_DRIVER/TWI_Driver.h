/*
 * TWI_Driver.h
 *
 *  Created on: Jul 17, 2018
 *      Author: zsolt.balo
 */

#ifndef DRIVERS_TWI_DRIVER_TWI_DRIVER_H_
#define DRIVERS_TWI_DRIVER_TWI_DRIVER_H_

#include "stm32f4xx.h"
#include "StdTypes.h"

#define TWI_DRIVER_INTERRUPT_FUNCTIONALITY					0x00
#define TWI_DRIVER_POLLING_FUNCTIONALITY					0x01
#define TWI_DRIVER_STANDARD_SPEED_100KHz					0x00 /*Maximum value is 100KHz*/
#define TWI_DRIVER_FAST_SPEED_400KHZ						0x01 /*Maximum value is 400KHz*/
#define TWI_DRIVER_FAST_SPEED_DUTY_CYCLE_2					0x00
#define TWI_DRIVER_FAST_SPEED_DUTY_CYCLE_16_9				0x01
#define TWI_DRIVER_7_BIT_ADDRESSING							0x00
#define TWI_DRIVER_10_BIT_ADDRESSING						0x01
/*Implement config. in system driver*/
#define TWI_DRIVER_PCLK_VALUE								((uint32)(36000000))
#define TWI_DRIVER_PCLOCK_MHZ								((uint8)((TWI_DRIVER_PCLK_VALUE)/1000000))

/*TWI status flags*/

/*Dual flag (Slave mode), is set when receiving second address in dual addressing*/
#define TWI_DRIVER_DUAL_FLAG2							((uint16)(0x01<<0x07))
/*General call address (Slave mode)*/
#define TWI_DRIVER_GENRAL_CALL_FLAG2					((uint16)(0x01<<0x04))
/*Transmitter/receive, This bit is set depending on the R/W bit of the address byte,
at the end of total address phase.It is also cleared by hardware after detection
of Stop condition (STOPF=1), repeated Start condition, loss of bus arbitration
(ARLO=1), or when PE=0.*/
#define TWI_DRIVER_TX_RX_DIR_SELECTED_FLAG2				((uint16)(0x01<<0x02))
/*Bus busy, It indicates a communication in progress on the bus.*/
#define TWI_DRIVER_BUS_BUSY_FLAG2						((uint16)(0x01<<0x01))
/*Master/slave, indicates the I2c mode*/
#define TWI_DRIVER_MASTER_SALVE_SELECTED_FLAG2			((uint16)(0x01))
/*Timeout detected*/
#define TWI_DRIVER_TIMEOUT_FLAG							((uint16)(0x01<<0x0E))
/*Overrun detected*/
#define TWI_DRIVER_OVERRUN_FLAG							((uint16)(0x01<<0x0B))
/*Acknowledge failure*/
#define TWI_DRIVER_ACK_FAILURE_FLAG						((uint16)(0x01<<0x0A))
/*Arbitration lost*/
#define TWI_DRIVER_ARB_LOST_FLAG						((uint16)(0x01<<0x09))
/*Bus error*/
#define TWI_DRIVER_BUS_ERROR_FLAG						((uint16)(0x01<<0x08))
/*Data register empty (transmitters)*/
#define TWI_DRIVER_DR_EMPTY_FLAG						((uint16)(0x01<<0x07))
/*Data register not empty (receivers)*/
#define TWI_DRIVER_DR_NOT_EMPTY_FLAG					((uint16)(0x01<<0x06))
/*Stop detection (slave mode)*/
#define TWI_DRIVER_STOP_DETECTED_FLAG					((uint16)(0x01<<0x04))
/*10-bit header sent (Master mode)*/
#define TWI_DRIVER_10_HEADER_SENT						((uint16)(0x01<<0x03))
/*Byte transfer finished*/
#define TWI_DRIVER_BYTE_TX_FINISHED						((uint16)(0x01<<0x02))
/*Address sent (master mode)/matched (slave mode)*/
#define TWI_DRIVER_ADDRESS_SENT_MATCHED					((uint16)(0x01<<0x01))
/*Start bit (Master mode)*/
#define TWI_DRIVER_START_FLAG							((uint16)(0x01))
/*EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address*/
#define TWI_DRIVER_EV5									(uint32)(((TWI_DRIVER_MASTER_SALVE_SELECTED_FLAG2|TWI_DRIVER_BUS_BUSY_FLAG2)<<16)|(TWI_DRIVER_START_FLAG))
#define TWI_DRIVER_EV6									(uint32)(((TWI_DRIVER_MASTER_SALVE_SELECTED_FLAG2|TWI_DRIVER_BUS_BUSY_FLAG2|TWI_DRIVER_TX_RX_DIR_SELECTED_FLAG2)<<16)|(TWI_DRIVER_ADDRESS_SENT_MATCHED|TWI_DRIVER_DR_EMPTY_FLAG))
#define TWI_DRIVER_EV8_2								(uint32)(((TWI_DRIVER_MASTER_SALVE_SELECTED_FLAG2|TWI_DRIVER_BUS_BUSY_FLAG2|TWI_DRIVER_TX_RX_DIR_SELECTED_FLAG2)<<16)|(TWI_DRIVER_BYTE_TX_FINISHED|TWI_DRIVER_DR_EMPTY_FLAG))

typedef struct
{
	uint8_t payloadLenght;
	uint8_t* message_buffer;
	uint8_t* address_buffer;
}TWI_DRIVER_Messagebuffer_Type;

uint32 TWI_Driver_Get_Status(I2C_TypeDef* TWIx,uint32 StatusCode);
void TWI_Driver_Init(I2C_TypeDef* TWIx);
uint8 TWI_Driver_ReceiveData(I2C_TypeDef* TWIx);
void TWI_Driver_Reset(I2C_TypeDef* TWIx);
void TWI_Driver_SetAddress(I2C_TypeDef* TWIx);
void TWI_Driver_SetClock(I2C_TypeDef* TWIx);
void TWI_Driver_SendData(I2C_TypeDef* TWIx,uint8 Payload);
void TWI_Driver_SendAddress(I2C_TypeDef* TWIx,uint8 Address);
void TWI_Driver_SendStart(I2C_TypeDef* TWIx);
void TWI_Driver_SendStop(I2C_TypeDef* TWIx);
void TWI_Driver_Start(I2C_TypeDef* TWIx);
void TWI_Driver_Stop(I2C_TypeDef* TWIx);
void TWI_Driver_PollingOneByteTx(I2C_TypeDef* TWIx,uint8 message, uint8 Address);
void TWI_Driver_PollingTx(I2C_TypeDef* TWIx,TWI_DRIVER_Messagebuffer_Type* payload);
void TWI_Driver_InterruptOneByteTx(I2C_TypeDef* TWIx,uint8 message, uint8 Address);
void TWI_Driver_InterruptTx(I2C_TypeDef* TWIx,TWI_DRIVER_Messagebuffer_Type* payload);


#endif /* DRIVERS_TWI_DRIVER_TWI_DRIVER_H_ */
