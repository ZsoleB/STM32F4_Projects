/*
 * CAN_Driver.h
 *
 *  Created on: Apr 19, 2018
 *      Author: zsolt.balo
 */

#ifndef DRIVERS_CAN_DRIVER_CAN_DRIVER_H_
#define DRIVERS_CAN_DRIVER_CAN_DRIVER_H_

#include "stm32f4xx.h"
#include "StdTypes.h"

#define CAN_DRIVER_DEBUG_FREEZE											(0x01<<0x10)
#define CAN_DRIVER_DEBUG_SILENT_MODE									(0x01<<0x1F)
#define CAN_DRIVER_DEBUG_LOOP_BACK_MODE									(0x01<<0x1E)
/*Force a master reset of the bxCAN -> Sleep mode activated after reset (FMP bits and
 CAN_MCR register are initialized to the reset values). This bit is automatically reset to 0.
 */
#define CAN_DRIVER_RESET												(0x01<<0x0F)
#define CAN_DRIVER_INIT_REQUEST											(0x01<<0x00)
#define CAN_DRIVER_SLEEP_MODE_REQUEST									(0x01<<0x01)
#define CAN_DRIVER_INIT_ACKNOWLEDGE										(0x01<<0x00)
#define CAN_DRIVER_SLEEP_ACKNOWLEDGE									(0x01<<0x01)
#define CAN_DRIVER_TRANSMIT_MAILBOX0_EMPTY								(0x01<<0x1A)
#define CAN_DRIVER_TRANSMIT_MAILBOX1_EMPTY								(0x01<<0x1B)
#define CAN_DRIVER_TRANSMIT_MAILBOX2_EMPTY								(0x01<<0x1C)
#define CAN_DRIVER_RX_FIFO_LOCKED_MODE									(0x01<<0x03)
#define CAN_DRIVER_TIME_TRIGGERED_COMMUNICATION_MODE					(0x01<<0x07)
#define CAN_DRIVER_AUTOMATIC_BUS_OFF									(0x01<<0x06)
#define CAN_DRIVER_AUTOMATIC_WAKE_UP									(0x01<<0x05)
/*Clear the TSEG1,TSEG2,SJW=4,CAN time quanta*/
#define CAN_DRIVER_BIT_TIMING_CLEAR_MASK								(~((0x03 << 24) | (0x07 << 20) | (0x0F << 16) | (0x3FF)))
#define CAN_DRIVER_FILTER_BANK_INITIALIZATION_MODE						(0x01<<0x00)
#define CAN_DRIVER_FILTER_BANK_ACTIVE_MODE								(~(0x01<<0x00))
#define CAN_DRIVER_RELEASE_FIFO_MAILBOX									(0x01<<0x05)

/*11bit ID*/
#define CAN_DRIVER_ID_STANDARD 											0x00
/*29bit ID*/
#define CAN_DRIVER_ID_EXTENDED 											0x01
#define CAN_DRIVER_DATA_FRAME 											0x00
#define CAN_DRIVER_REMOTE_FRAME 										0x01

/*

 When more than one transmit mailbox is pending, the transmission order is given by the
 identifier of the message stored in the mailbox. The message with the lowest identifier value
 has the highest priority according to the arbitration of the CAN protocol. If the identifier
 values are equal, the lower mailbox number will be scheduled first.

 */
#define CAN_DRIVER_TRANSMIT_PRIORITY_BY_ID 								(0x00<<0x02)
/*

 The transmit mailboxes can be configured as a transmit FIFO by setting the TXFP bit in the
 CAN_MCR register. In this mode the priority order is given by the transmit request order.
 This mode is very useful for segmented transmission.

 */

#define CAN_DRIVER_TRANSMIT_PRIORITY_BY_TX_REQ_ORDER 					(0x01<<0x02)

#define CAN_DRIVER_AUTOMATIC_TRANSMISSION_MODE							(0x00<<0x04)
/*

 In this mode, each transmission is started only once. If the first attempt fails, due to an
 arbitration loss or an error, the hardware will not automatically restart the message
 transmission.

 */
#define CAN_DRIVER_NON_AUTOMATIC_TRANSMISSION_MODE						(0x01<<0x04)
/*

 In mask mode the identifier registers are associated with mask registers specifying which
 bits of the identifier are handled as �must match� or as �don�t care�. Can be used when frame
 groups are used not single frames.

 */
#define CAN_DRIVER_FILTER_MASK_MODE										0x00
/*

 In identifier list mode, the mask registers are used as identifier registers. Thus instead of
 defining an identifier and a mask, two identifiers are specified, doubling the number of single
 identifiers. All bits of the incoming identifier must match the bits specified in the filter
 registers.

 */
#define CAN_DRIVER_FILTER_ID_LIST_MODE											0x01
#define CAN_DRIVER_FILTER_SCALE_16_BIT											0x00
#define CAN_DRIVER_FILTER_SCALE_32_BIT											0x01

/*The peripheral clock frequency from the system clock source (in our case PLL) divided by the configured division factor*/
#define CAN_DRIVER_PERIPHERAL_FREQUENCY 							((168000000)/4)
#define CAN_BAUD_RATE_PRESCALER(BS1,BS2,CF)						((CAN_DRIVER_PERIPHERAL_FREQUENCY/(BS1+BS2+1))/CF)

typedef void (*CAN_Driver_Set_State)(uint8 CAN_setup_nr);

typedef enum
{
	CAN_DRIVER_OPERATING_MODE_INIT = 0,
	CAN_DRIVER_OPERATING_MODE_NORMAL = 1,
	CAN_DRIVER_OPERATING_MODE_SLEEP = 2,
} CAN_Driver_Operating_Modes;

typedef enum
{
	CAN_Driver_FIFO_0, CAN_Driver_FIFO_1
} CAN_Driver_FIFO_Number;

typedef enum
{
	CAN_Driver_MailBox_0, CAN_Driver_MailBox_1, CAN_Driver_MailBox_2
} CAN_Driver_MailBox_Number;

typedef enum
{
	/*The CAN can receive messages, but can't send any because, Tx is redirected to Rx*/
	CAN_Driver_test_mode_silent= 0,
	/*The CAN Rx channel is connected directly to the Tx, and disconnected from the exterior*/
	CAN_Driver_test_mode_loop_back = 1,
	/*Both Tx and Rx are disconnected from the exterior*/
	CAN_Driver_test_mode_silent_and_loopback = 2,
} CAN_Driver_Test_Modes;

typedef struct
{
	uint32 ID; /*ID of the CAN message*/
	uint8 Payload[8]; /*Payload to be transmitted*/
	uint8 Length; /*Length of the payload*/
	uint8 Payload_Type; /*Data Frame or Remote Frame*/
	uint8 Format; /*Extended or Standard (11bit or 29bit ID)*/
} CAN_Driver_Message;

typedef struct
{
	uint8 CAN_Driver_Tx0_Ready;
	uint8 CAN_Driver_Tx1_Ready;
	uint8 CAN_Driver_Tx2_Ready;
} CAN_Driver_Tx_Status;

typedef struct
{
	uint8 CAN_Driver_Rx0_Ready;
	uint8 CAN_Driver_Rx1_Ready;
	uint8 CAN_Driver_Rx2_Ready;
} CAN_Driver_Rx_Status;

typedef struct
{
	CAN_TypeDef* CAN_Driver_instance;
	uint32 CAN_Driver_frequency;
	/*CAN bit timing parameters (the values can be selected from a standard value table) */
	uint8 CAN_Driver_bit_segment1;
	uint8 CAN_Driver_bit_segment2;
	uint8 CAN_Driver_resynchronization_jump_width;
	/*Enable the CAN Driver to change its configuration from normal communication mode to a selected test mode*/
	uint8 CAN_Driver_test_mode_enable;
	uint8 CAN_Driver_test_mode_type;
	/*CAN driver will run or the reception/transmission will be frozen while in debug*/
	uint8 CAN_Driver_run_on_debug_mode;
	/*Check transmit mailbox 0*/
	uint8 CAN_Driver_use_mailbox_0;
	/*Check transmit mailbox 1*/
	uint8 CAN_Driver_use_mailbox_1;
	/*Check transmit mailbox 2*/
	uint8 CAN_Driver_use_mailbox_2;
	/*Select the desired transmit priority (ID based or by the transmission order)*/
	uint8 CAN_Driver_transmit_priority;
	/*Select the desired transmission mode (automatic or non-automatic)*/
	uint8 CAN_Driver_transmission_mode;
	/*

		Check if the RX FIFO can be overwritten by the new values,else
	the three oldest frames will be retained, ignoring the new ones

	*/
	uint8 CAN_Driver_rx_overwrite_enable;
	uint8 CAN_Driver_rx_filter_scale;
	/*

		In this mode, the internal counter of the CAN hardware is activated and used to generate the
	Time Stamp value. The internal counter is incremented each CAN bit time. The internal counter
	is captured on the sample point of the Start Of Frame bit in both reception and transmission.

	 */
	uint8 CAN_Driver_time_triggered_transmission;
	/*This controls the behavior of the CAN hardware on leaving the Bus-Off state.

	NOK - State is left on software request, once 128 occurrences of 11 recessive bits
	have been monitored and the software has first set and cleared the INRQ bit of the
	CAN_MCR register.

	OK - The Bus-Off state is left automatically by hardware once 128 occurrences of 11 recessive
	bits have been monitored.

	*/
	uint8 CAN_Driver_automatic_bus_off_management;
	/*

	 This bit controls the behavior of the CAN hardware on message reception during Sleep
	mode.

	NOK - The Sleep mode is left on software request by clearing the SLEEP bit of the CAN_MCR
	register.

	OK - The Sleep mode is left automatically by hardware on CAN message detection.
	The SLEEP bit of the CAN_MCR register and the SLAK bit of the CAN_MSR register are
	cleared by hardware.

	 */
	uint8 CAN_Driver_automatic_wake_up_mode;

}CAN_Driver_Setup_Type;

extern CAN_Driver_Setup_Type* CAN_SETUP;

void CAN_Driver_Clear_Request_Completed_Flag(uint8 CAN_setup_nr,uint8 MailBox_Number);
uint8 CAN_Driver_Check_Message_Pending(uint8 CAN_setup_nr,uint8 FIFO_Number);
void CAN_Driver_DebugFreeze(uint8 CAN_setup_nr,uint8 option);
void CAN_Driver_Enter_NormalMode(uint8 CAN_setup_nr);
void CAN_Driver_Enter_SleepMode(uint8 CAN_setup_nr);
void CAN_Driver_Init();
void CAN_Driver_InitBuffer(CAN_Driver_Message *CAN_MSG);
void CAN_Driver_Enter_InitMode(uint8 CAN_setup_nr);
void CAN_Driver_ModeChange(uint8 CAN_setup_nr,CAN_Driver_Operating_Modes Mode);
void CAN_Driver_ReceiveMessage(uint8 CAN_setup_nr,CAN_Driver_Message *msg, uint8 MailBox_Number, uint8 FIFO_Number);
void CAN_Driver_Reset(uint8 CAN_setup_nr);
void CAN_Driver_Release_Rx_MailBox(uint8 CAN_setup_nr,uint8 FIFO_Number);
void CAN_Driver_SendMessage(uint8 CAN_setup_nr,CAN_Driver_Message *msg,uint8 MailBox_Number);
void CAN_Driver_SetFilter(uint8 CAN_setup_nr,uint32 ID,uint8 ID_type);
void CAN_Driver_SetTestMode(uint8 CAN_setup_nr);
void CAN_Driver_SetBuffer(CAN_Driver_Message* arg, uint8 len, uint8* message);
void CAN_Driver_Start(uint8 CAN_setup_nr);
void CAN_Driver_Wait_for_Ready(uint8 CAN_setup_nr);

#endif /* DRIVERS_CAN_DRIVER_CAN_DRIVER_H_ */
