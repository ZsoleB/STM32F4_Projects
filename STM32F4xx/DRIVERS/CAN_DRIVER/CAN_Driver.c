/*
 * CAN_Driver.c
 *
 *  Created on: Apr 19, 2018
 *      Author: zsolt.balo
 *
 *
 * Bit Timing for can
 ____________________________________________________________________________________________________
|             |                                          |                                           |
|Sync_Segment |       BIT segment1                       |           BIT segment2                    |
|    	      |       			                         |                 			                 |
 ----------------------------------------------------------------------------------------------------
 1xtq		   TBS1					                       TBS2
			                                             ^					                          ^
						                                 |                                            |
		                                           Sample point                    		      Transmit Point

 	 	            1
 BaudRate = ------------------
 	           NominalBitTime

 NominalBitTime = 1 x tq + tBS1 + tBS2

 with:

 tBS1 = tq x (TS1[3:0] + 1),
 tBS2 = tq x (TS2[2:0] + 1),
 tq = (BRP[9:0] + 1) x tPCLK

 where tq refers to the Time quantum

 tPCLK = time period of the APB clock,

 */
#include "CAN_Driver_Cfg.h"

//CAN_Driver_Tx_Status* CAN_Driver_Tx_global_status = {0x00};
//CAN_Driver_Rx_Status* CAN_Driver_Rx_global_status = {0x00};

static CAN_Driver_Set_State CAN_Driver_StateSetters[] =
{
		CAN_Driver_Enter_InitMode,
		CAN_Driver_Enter_NormalMode,
		CAN_Driver_Enter_SleepMode
};

void CAN_Driver_DebugFreeze(uint8 CAN_setup_nr,uint8 option)
{
	if (option ==NOK)
	{
		CAN_SETUP[CAN_setup_nr].CAN_Driver_instance->MCR &= (~CAN_DRIVER_DEBUG_FREEZE);
	}
	else if(option == OK)
	{
		CAN_SETUP[CAN_setup_nr].CAN_Driver_instance->MCR |= CAN_DRIVER_DEBUG_FREEZE;
	}
	else
	{
		/*Nothing to do*/
	}
}

void CAN_Driver_Enter_NormalMode(uint8 CAN_setup_nr)
{
	/*Exit from Initialization mode, and enter normal mode*/
	CAN_SETUP[CAN_setup_nr].CAN_Driver_instance->MCR &= (~CAN_DRIVER_INIT_REQUEST);

	/*Wait until change confirmed, 11 recessive bits are detected and the line is idle*/
	while (!(CAN_SETUP[CAN_setup_nr].CAN_Driver_instance->MSR & CAN_DRIVER_INIT_ACKNOWLEDGE) != 0x00)
	{
	}
}

void CAN_Driver_Enter_SleepMode(uint8 CAN_setup_nr)
{
	/*Exit from Initialization mode*/
	CAN_SETUP[CAN_setup_nr].CAN_Driver_instance->MCR &= (~CAN_DRIVER_INIT_REQUEST);

	/*Enter into Sleep mode*/
	CAN_SETUP[CAN_setup_nr].CAN_Driver_instance->MCR |= CAN_DRIVER_SLEEP_MODE_REQUEST;

	/*Wait until change confirmed*/
	while (!((CAN_SETUP[CAN_setup_nr].CAN_Driver_instance->MSR & CAN_DRIVER_SLEEP_ACKNOWLEDGE) != 0x00) &&
			((CAN_SETUP[CAN_setup_nr].CAN_Driver_instance->MSR & CAN_DRIVER_INIT_ACKNOWLEDGE) == 0x00))
	{
	}
}

void CAN_Driver_Init()
{
	uint8 CAN_Driver_index= 0x00;

#if(CAN_DRIVER_CAN1 == OK)
	RCC->APB1ENR |= RCC_APB1ENR_CAN1EN;
#elif(CAN_DRIVER_CAN2 == OK)
	RCC->APB1ENR |= RCC_APB1ENR_CAN2EN;
#endif
	/*Enter into initialization mode.
	 Erroneous access to certain configuration registers can cause the hardware to temporarily
	 disturb the whole CAN network. Therefore the CAN_BTR register can be modified by
	 software only while the CAN hardware is in initialization mode.

	 */
	for (CAN_Driver_index = 0x00; CAN_Driver_index < CAN_DRIVER_INSTANCE_NUM; CAN_Driver_index++)
	{
		CAN_Driver_ModeChange(CAN_Driver_index, CAN_DRIVER_OPERATING_MODE_INIT);

		/*Set up the CAN option registers*/

		/*Can-debug configuration*/
		if (CAN_SETUP[CAN_Driver_index].CAN_Driver_run_on_debug_mode == OK)
		{

			CAN_Driver_DebugFreeze(CAN_Driver_index, NOK);
		}
		else if(CAN_SETUP[CAN_Driver_index].CAN_Driver_run_on_debug_mode == NOK)
		{
			CAN_Driver_DebugFreeze(CAN_Driver_index, OK);
		}
		else
		{
			/*Do nothing*/
		}

		/*Can Transmit priority*/
		if (CAN_SETUP[CAN_Driver_index].CAN_Driver_transmit_priority == CAN_DRIVER_TRANSMIT_PRIORITY_BY_ID)
		{
			CAN_SETUP[CAN_Driver_index].CAN_Driver_instance->MCR |= CAN_DRIVER_TRANSMIT_PRIORITY_BY_ID;
		}
		else if (CAN_SETUP[CAN_Driver_index].CAN_Driver_transmit_priority == CAN_DRIVER_TRANSMIT_PRIORITY_BY_TX_REQ_ORDER)
		{
			CAN_SETUP[CAN_Driver_index].CAN_Driver_instance->MCR |= CAN_DRIVER_TRANSMIT_PRIORITY_BY_TX_REQ_ORDER;
		}
		else
		{
			/*Do nothing*/
		}

		/*Can Transmission mode*/
		if (CAN_SETUP[CAN_Driver_index].CAN_Driver_transmission_mode == CAN_DRIVER_NON_AUTOMATIC_TRANSMISSION_MODE)
		{
			CAN_SETUP[CAN_Driver_index].CAN_Driver_instance->MCR |= CAN_DRIVER_NON_AUTOMATIC_TRANSMISSION_MODE;
		}
		else if (CAN_SETUP[CAN_Driver_index].CAN_Driver_transmission_mode == CAN_DRIVER_AUTOMATIC_TRANSMISSION_MODE)
		{
			CAN_SETUP[CAN_Driver_index].CAN_Driver_instance->MCR |= CAN_DRIVER_NON_AUTOMATIC_TRANSMISSION_MODE;
		}
		else
		{
			/*Do nothing*/
		}

		/*Can Rx overwrite or retain the old values*/
		if (CAN_SETUP[CAN_Driver_index].CAN_Driver_rx_overwrite_enable == OK)
		{

			/*Receive FIFO not locked on overrun. Once a receive FIFO is full the next incoming
			 message will overwrite the previous one */
			CAN_SETUP[CAN_Driver_index].CAN_Driver_instance->MCR &= (~CAN_DRIVER_RX_FIFO_LOCKED_MODE);
		}
		else if (CAN_SETUP[CAN_Driver_index].CAN_Driver_rx_overwrite_enable == NOK)
		{
			/*Receive FIFO locked against overrun. Once a receive FIFO is full the next incoming
			 message will be discarded */
			CAN_SETUP[CAN_Driver_index].CAN_Driver_instance->MCR |= CAN_DRIVER_RX_FIFO_LOCKED_MODE;
		}
		else
		{
			/*Do nothing*/
		}

		/*Can Time-Triggered transmission*/
		if (CAN_SETUP[CAN_Driver_index].CAN_Driver_time_triggered_transmission == OK)
		{
			CAN_SETUP[CAN_Driver_index].CAN_Driver_instance->MCR |= CAN_DRIVER_TIME_TRIGGERED_COMMUNICATION_MODE;
		}
		else if (CAN_SETUP[CAN_Driver_index].CAN_Driver_time_triggered_transmission == NOK)
		{
			CAN_SETUP[CAN_Driver_index].CAN_Driver_instance->MCR &= (~CAN_DRIVER_TIME_TRIGGERED_COMMUNICATION_MODE);
		}
		else
		{
			/*Do nothing*/
		}

		/*Can auto bus off management*/
		if (CAN_SETUP[CAN_Driver_index].CAN_Driver_automatic_bus_off_management == OK)
		{
			CAN_SETUP[CAN_Driver_index].CAN_Driver_instance->MCR |= CAN_DRIVER_AUTOMATIC_BUS_OFF;
		}
		else if (CAN_SETUP[CAN_Driver_index].CAN_Driver_automatic_bus_off_management == NOK)
		{
			CAN_SETUP[CAN_Driver_index].CAN_Driver_instance->MCR &= (~CAN_DRIVER_AUTOMATIC_BUS_OFF);
		}
		else
		{
			/*Do nothing*/
		}

		/*Can automatic wake-up mode*/
		if (CAN_SETUP[CAN_Driver_index].CAN_Driver_automatic_wake_up_mode == OK)
		{
			/*The Bus-Off state is left automatically by hardware once 128 occurrences of 11 recessive
			 bits have been monitored. */
			CAN_SETUP[CAN_Driver_index].CAN_Driver_instance->MCR |= CAN_DRIVER_AUTOMATIC_WAKE_UP;
		}
		else if (CAN_SETUP[CAN_Driver_index].CAN_Driver_automatic_wake_up_mode == NOK)
		{
			/*The Bus-Off state is left on software request, once 128 occurrences of 11 recessive bits
			 have been monitored and the software has first set and cleared the INRQ bit of the
			 CAN_MCR register.  */
			CAN_SETUP[CAN_Driver_index].CAN_Driver_instance->MCR &= (~CAN_DRIVER_AUTOMATIC_WAKE_UP);
		}
		else
		{
			/*Do nothing*/
		}

		/*Set up the CAN bit timing registers*/
		CAN_SETUP[CAN_Driver_index].CAN_Driver_instance->BTR &= CAN_DRIVER_BIT_TIMING_CLEAR_MASK;
		/*set TSEG1*/
		CAN_SETUP[CAN_Driver_index].CAN_Driver_instance->BTR |= ((((CAN_SETUP[CAN_Driver_index].CAN_Driver_bit_segment1 - 1) & 0x0F) << 16));
		/*set TSEG2*/
		CAN_SETUP[CAN_Driver_index].CAN_Driver_instance->BTR |= ((((CAN_SETUP[CAN_Driver_index].CAN_Driver_bit_segment2 - 1) & 0x07) << 20));
		/*set SJW*/
		CAN_SETUP[CAN_Driver_index].CAN_Driver_instance->BTR |= ((((CAN_SETUP[CAN_Driver_index].CAN_Driver_resynchronization_jump_width - 1) & 0x03) << 24));
		/*set CAN pescaler*/
		CAN_SETUP[CAN_Driver_index].CAN_Driver_instance->BTR |= (((CAN_BAUD_RATE_PRESCALER(CAN_SETUP[CAN_Driver_index].CAN_Driver_bit_segment1,
				CAN_SETUP[CAN_Driver_index].CAN_Driver_bit_segment2,
				CAN_SETUP[CAN_Driver_index].CAN_Driver_frequency) - 1) & 0x3FF));

		/*Set up additional functionalities, ex. TestModes*/
		if (CAN_SETUP[CAN_Driver_index].CAN_Driver_test_mode_enable == OK)
		{
			CAN_Driver_SetTestMode(CAN_Driver_index);
		}
	}
}

void CAN_Driver_InitBuffer(CAN_Driver_Message *CAN_MSG)
{
	uint8_t index = 0x00;

	for (index = 0x00; index < 8; index++)
	{
		CAN_MSG->Payload[index] = 0x00;
	}
}

void CAN_Driver_SetBuffer(CAN_Driver_Message* arg, uint8 len, uint8* message)
{
	uint8_t ind = 0x00;
	arg->Length = len;

	for (ind = 0x00; ind < len; ind++)
	{
		arg->Payload[ind] = message[ind];
	}
}

void CAN_Driver_Enter_InitMode(uint8 CAN_setup_nr)
{
	/*Exit from Sleep mode*/
	CAN_SETUP[CAN_setup_nr].CAN_Driver_instance->MCR &= (~CAN_DRIVER_SLEEP_MODE_REQUEST);

	/*Enter into Initialization mode*/
	CAN_SETUP[CAN_setup_nr].CAN_Driver_instance->MCR |= CAN_DRIVER_INIT_REQUEST;

	/*Wait until change confirmed, INAK is set and SLAK is cleared*/
	while (!((CAN_SETUP[CAN_setup_nr].CAN_Driver_instance->MSR & CAN_DRIVER_INIT_ACKNOWLEDGE) != 0x00) &&
			((CAN_SETUP[CAN_setup_nr].CAN_Driver_instance->MSR & CAN_DRIVER_SLEEP_ACKNOWLEDGE) == 0x00))
	{
		/*Do nothing*/
	}
}

void CAN_Driver_ModeChange(uint8 CAN_setup_nr,CAN_Driver_Operating_Modes Mode)
{
	CAN_Driver_StateSetters[Mode](CAN_setup_nr);
}

void CAN_Driver_ReceiveMessage(uint8 CAN_setup_nr,CAN_Driver_Message *msg, uint8 MailBox_Number,
uint8 FIFO_Number)
{
	/*Read the message identifiers*/
	if ((CAN_SETUP[CAN_setup_nr].CAN_Driver_instance->sFIFOMailBox[FIFO_Number].RIR & (CAN_DRIVER_ID_STANDARD << 2)) == 0x00)
	{
		msg->Format = CAN_DRIVER_ID_STANDARD;
		msg->ID = (uint32_t) (0x000007FF) & (CAN1->sFIFOMailBox[FIFO_Number].RIR >> 21);
	}
	else if ((CAN_SETUP[CAN_setup_nr].CAN_Driver_instance->sFIFOMailBox[FIFO_Number].RIR & (CAN_DRIVER_ID_EXTENDED << 2)) != 0x00)
	{
		msg->Format = CAN_DRIVER_ID_EXTENDED;
		msg->ID = (uint32_t) (0x0003FFFF) & (CAN1->sFIFOMailBox[FIFO_Number].RIR >> 3);
	}

	/*Read the message format*/
	if ((CAN_SETUP[CAN_setup_nr].CAN_Driver_instance->sFIFOMailBox[FIFO_Number].RIR & (CAN_DRIVER_DATA_FRAME << 1)) == 0x00)
	{
		msg->Payload_Type = CAN_DRIVER_DATA_FRAME;
	}
	else if ((CAN_SETUP[CAN_setup_nr].CAN_Driver_instance->sFIFOMailBox[FIFO_Number].RIR & (CAN_DRIVER_REMOTE_FRAME << 1)) != 0x00)
	{
		msg->Payload_Type = CAN_DRIVER_REMOTE_FRAME;
	}

	/*Get message length*/
	msg->Length = (uint8_t) ((0x0000000F) & (CAN_SETUP[CAN_setup_nr].CAN_Driver_instance->sFIFOMailBox[FIFO_Number].RDTR));

	/*Get message lower part*/
	msg->Payload[0] = (uint8_t) (0x000000FF & (CAN_SETUP[CAN_setup_nr].CAN_Driver_instance->sFIFOMailBox[FIFO_Number].RDLR));
	msg->Payload[1] = (uint8_t) (0x000000FF & (CAN_SETUP[CAN_setup_nr].CAN_Driver_instance->sFIFOMailBox[FIFO_Number].RDLR >> 8));
	msg->Payload[2] = (uint8_t) (0x000000FF & (CAN_SETUP[CAN_setup_nr].CAN_Driver_instance->sFIFOMailBox[FIFO_Number].RDLR >> 16));
	msg->Payload[3] = (uint8_t) (0x000000FF & (CAN_SETUP[CAN_setup_nr].CAN_Driver_instance->sFIFOMailBox[FIFO_Number].RDLR >> 24));

	/*Get message higher part*/
	msg->Payload[4] = (uint8_t) (0x000000FF & (CAN_SETUP[CAN_setup_nr].CAN_Driver_instance->sFIFOMailBox[FIFO_Number].RDHR));
	msg->Payload[5] = (uint8_t) (0x000000FF & (CAN_SETUP[CAN_setup_nr].CAN_Driver_instance->sFIFOMailBox[FIFO_Number].RDHR >> 8));
	msg->Payload[6] = (uint8_t) (0x000000FF & (CAN_SETUP[CAN_setup_nr].CAN_Driver_instance->sFIFOMailBox[FIFO_Number].RDHR >> 16));
	msg->Payload[7] = (uint8_t) (0x000000FF & (CAN_SETUP[CAN_setup_nr].CAN_Driver_instance->sFIFOMailBox[FIFO_Number].RDHR >> 24));

	CAN_Driver_Release_Rx_MailBox(CAN_setup_nr,FIFO_Number);

	CAN_Driver_Clear_Request_Completed_Flag(CAN_setup_nr,MailBox_Number);
}

void CAN_Driver_Reset(uint8 CAN_setup_nr)
{
	/*Reset master, enter to sleep mode. Bit is reseted to 0 by hardware*/
	CAN_SETUP[CAN_setup_nr].CAN_Driver_instance->MCR |= CAN_DRIVER_RESET;
}

void CAN_Driver_SendMessage(uint8 CAN_setup_nr,CAN_Driver_Message *msg, uint8 MailBox_Number)
{
	/*Reset the transmission identifier register*/
	CAN_SETUP[CAN_setup_nr].CAN_Driver_instance->sTxMailBox[MailBox_Number].TIR = (uint32_t) 0x00;

	/*Set message ID and the IDE (identifier extension)*/
	if (msg->Format == CAN_DRIVER_ID_STANDARD)
	{
		CAN_SETUP[CAN_setup_nr].CAN_Driver_instance->sTxMailBox[MailBox_Number].TIR |= (uint32_t) ((msg->ID << 21));
	}
	else if (msg->Format == CAN_DRIVER_ID_EXTENDED)
	{
		CAN_SETUP[CAN_setup_nr].CAN_Driver_instance->sTxMailBox[MailBox_Number].TIR |= (uint32_t) ((msg->ID << 3) | (CAN_DRIVER_ID_EXTENDED << 2));
	}else
	{
		/*Do nothing*/
	}

	/*Set message type (Data or Remote frame)*/
	if (msg->Payload_Type == CAN_DRIVER_DATA_FRAME)
	{
		CAN_SETUP[CAN_setup_nr].CAN_Driver_instance->sTxMailBox[MailBox_Number].TIR |= (CAN_DRIVER_DATA_FRAME << 1);
	}
	else if (msg->Payload_Type == CAN_DRIVER_REMOTE_FRAME)
	{
		CAN_SETUP[CAN_setup_nr].CAN_Driver_instance->sTxMailBox[MailBox_Number].TIR |= (CAN_DRIVER_REMOTE_FRAME << 1);
	}
	else
	{
		/*Do nothing*/
	}

	/*Set the payload (lower part)*/

	CAN_SETUP[CAN_setup_nr].CAN_Driver_instance->sTxMailBox[MailBox_Number].TDLR = (((uint32_t) msg->Payload[3] << 24) | ((uint32_t) msg->Payload[2] << 16) | ((uint32_t) msg->Payload[1] << 8)
			| (uint32_t) msg->Payload[0]);

	/*Set the payload (upper part)*/

	CAN_SETUP[CAN_setup_nr].CAN_Driver_instance->sTxMailBox[MailBox_Number].TDHR = (((uint32_t) msg->Payload[7] << 24) | ((uint32_t) msg->Payload[6] << 16) | ((uint32_t) msg->Payload[5] << 8)
			| (uint32_t) msg->Payload[4]);

	/*Clear the message Length*/
	CAN_SETUP[CAN_setup_nr].CAN_Driver_instance->sTxMailBox[MailBox_Number].TDTR &= ~((uint32) 0x0F);

	/*Set the message Length*/
	CAN_SETUP[CAN_setup_nr].CAN_Driver_instance->sTxMailBox[MailBox_Number].TDTR |= (msg->Length & ((uint32) 0x0F));

	/*Set the Transmit Mailbox Empty interrupt*/
	/*CANx->IER|=(CAN_IER_TMEIE);*/

	/*Request the transmission of the data*/
	CAN_SETUP[CAN_setup_nr].CAN_Driver_instance->sTxMailBox[MailBox_Number].TIR |= CAN_TI0R_TXRQ;
}

void CAN_Driver_SetFilter(uint8 CAN_setup_nr,uint32 ID,uint8 ID_type)
{
	static uint8 CAN_ID_index = 0x00;
	uint32_t CAN_Msg_ID = 0x00;

	/*Bits 27:14 are available in connectivity line devices only and are reserved otherwise.*/
	/*Because the MCU is not a connectivity line device if a greater value then 13 is requested the function will stop
	 the configuration here.*/
	if (CAN_ID_index > 13)
	{
		return;
	}

	/*Set the ID's after the  mailbox identifier registers format*/
	if (ID_type == CAN_DRIVER_ID_STANDARD)
	{
		CAN_Msg_ID |= (uint32_t) (ID << 21);
	}
	else if (ID_type == CAN_DRIVER_ID_EXTENDED)
	{
		/*Append the EXTENDED IDE after the ID, for STANDARD it is 0*/
		CAN_Msg_ID |= (uint32_t) ((ID << 3) | (0x01 << 2));
	}
	else
	{
		/*Do nothing*/
	}

	/*Set Filter banks in Initialization mode*/
	CAN_SETUP[CAN_setup_nr].CAN_Driver_instance->FMR |= CAN_DRIVER_FILTER_BANK_INITIALIZATION_MODE;

	/*Deactivate filter bank*/
	CAN_SETUP[CAN_setup_nr].CAN_Driver_instance->FA1R &= (~((uint32_t) (1 << CAN_ID_index)));

	/*Set filter bank in list mode (each bit must match)*/
	CAN_SETUP[CAN_setup_nr].CAN_Driver_instance->FM1R |= (uint32_t) (1 << CAN_ID_index);

	/*Set the filter bank to single 32-bit scale configuration*/
	CAN_SETUP[CAN_setup_nr].CAN_Driver_instance->FS1R |= (uint32_t) (1 << CAN_ID_index);

	/*Set the ID in the filter bank and in the mask to (in list mode the mask register can be used to)*/
	CAN_SETUP[CAN_setup_nr].CAN_Driver_instance->sFilterRegister[CAN_ID_index].FR1 = CAN_Msg_ID;
	CAN_SETUP[CAN_setup_nr].CAN_Driver_instance->sFilterRegister[CAN_ID_index].FR2 = 0x00;

	/*Assign to FIFO0-0, FIFO1-1 (FIFO0 in our case) */
	CAN_SETUP[CAN_setup_nr].CAN_Driver_instance->FFA1R &= ~(uint32_t) (1 << CAN_ID_index);

	/*Activate Filter Bank*/
	CAN_SETUP[CAN_setup_nr].CAN_Driver_instance->FA1R |= ((uint32_t) (1 << CAN_ID_index));

	/*Set Filter banks in Active mode*/
	CAN_SETUP[CAN_setup_nr].CAN_Driver_instance->FMR &= CAN_DRIVER_FILTER_BANK_ACTIVE_MODE;

	/*Increase filter index*/
	CAN_ID_index++;
}

void CAN_Driver_SetTestMode(uint8 CAN_setup_nr)
{
	CAN_SETUP[CAN_setup_nr].CAN_Driver_instance->BTR &= ~(CAN_DRIVER_DEBUG_SILENT_MODE | CAN_DRIVER_DEBUG_LOOP_BACK_MODE);

	if (CAN_SETUP[CAN_setup_nr].CAN_Driver_test_mode_type == CAN_Driver_test_mode_silent)
	{
		CAN_SETUP[CAN_setup_nr].CAN_Driver_instance->BTR |= CAN_DRIVER_DEBUG_SILENT_MODE;
	}

	else if (CAN_SETUP[CAN_setup_nr].CAN_Driver_test_mode_type == CAN_Driver_test_mode_loop_back)
	{
		CAN_SETUP[CAN_setup_nr].CAN_Driver_instance->BTR |= CAN_DRIVER_DEBUG_LOOP_BACK_MODE;
	}

	else if (CAN_SETUP[CAN_setup_nr].CAN_Driver_test_mode_type == CAN_Driver_test_mode_silent_and_loopback)
	{
		CAN_SETUP[CAN_setup_nr].CAN_Driver_instance->BTR |= (CAN_DRIVER_DEBUG_SILENT_MODE | CAN_DRIVER_DEBUG_LOOP_BACK_MODE);
	}
	else
	{
		/*Do nothing*/
	}
}

void CAN_Driver_Start(uint8 CAN_setup_nr)
{
	CAN_Driver_StateSetters[CAN_DRIVER_OPERATING_MODE_NORMAL](CAN_setup_nr);
}

void CAN_Driver_Release_Rx_MailBox(uint8 CAN_setup_nr,uint8 FIFO_Number)
{
	if (FIFO_Number == CAN_Driver_FIFO_0)
	{
		/*Release FIFO 0 output mailbox*/
		CAN_SETUP[CAN_setup_nr].CAN_Driver_instance->RF0R |= CAN_DRIVER_RELEASE_FIFO_MAILBOX;
	}
	else
	{
		/*Release FIFO 1 output mailbox*/
		CAN_SETUP[CAN_setup_nr].CAN_Driver_instance->RF1R |= CAN_DRIVER_RELEASE_FIFO_MAILBOX;
	}
}

void CAN_Driver_Clear_Request_Completed_Flag(uint8 CAN_setup_nr,uint8 MailBox_Number)
{
	if (MailBox_Number == CAN_Driver_MailBox_0)
	{
		/*Clear Request completed flag in MailBox 0*/
		CAN_SETUP[CAN_setup_nr].CAN_Driver_instance->TSR |= CAN_TSR_RQCP0;
	}
	else if (MailBox_Number == CAN_Driver_MailBox_1)
	{
		/*Clear Request completed flag in MailBox 1*/
		CAN_SETUP[CAN_setup_nr].CAN_Driver_instance->TSR |= CAN_TSR_RQCP1;
	}
	else
	{
		/*Clear Request completed flag in MailBox 2*/
		CAN_SETUP[CAN_setup_nr].CAN_Driver_instance->TSR |= CAN_TSR_RQCP2;
	}

}

uint8 CAN_Driver_Check_Message_Pending(uint8 CAN_setup_nr,uint8 FIFO_Number)
{
	uint8 result = 0x00;

	switch (FIFO_Number)
	{
	case CAN_Driver_FIFO_0:
		if ((CAN_SETUP[CAN_setup_nr].CAN_Driver_instance->RF0R & 0x03) != NOK)
		{
			result = SUCCES;
		}
		else
		{
			result = FAILED;
		}
		break;
	case CAN_Driver_FIFO_1:
		if ((CAN_SETUP[CAN_setup_nr].CAN_Driver_instance->RF1R & 0x03) != NOK)
		{
			result = SUCCES;
		}
		else
		{
			result = FAILED;
		}
		break;
	default:
		result = FAILED;
		break;
	}

	return result;
}

void CAN_Driver_Wait_for_Ready(uint8 CAN_setup_nr)
{

	if (CAN_SETUP[CAN_setup_nr].CAN_Driver_use_mailbox_0 == OK)
	{
		/*This bit is set by hardware when no transmit request is pending for mailbox */
		while ((CAN_SETUP[CAN_setup_nr].CAN_Driver_instance->TSR & CAN_DRIVER_TRANSMIT_MAILBOX0_EMPTY) == 0x00)
		{
			/*Do nothing*/
		}
		/*CAN_Driver_Tx_global_status->CAN_Driver_Tx0_Ready = 0x01;*/
	}
	else if (CAN_SETUP[CAN_setup_nr].CAN_Driver_use_mailbox_1 == OK)
	{
		while ((CAN_SETUP[CAN_setup_nr].CAN_Driver_instance->TSR & CAN_DRIVER_TRANSMIT_MAILBOX1_EMPTY) == 0x00)
		{
			/*Do nothing*/
		}
		/*CAN_Driver_Tx_global_status->CAN_Driver_Tx1_Ready = 0x01;*/
	}
	else if (CAN_SETUP[CAN_setup_nr].CAN_Driver_use_mailbox_2 == OK)
	{
		while ((CAN_SETUP[CAN_setup_nr].CAN_Driver_instance->TSR & CAN_DRIVER_TRANSMIT_MAILBOX2_EMPTY) == 0x00)
		{
			/*Do nothing*/
		}
		/*CAN_Driver_Tx_global_status->CAN_Driver_Tx2_Ready = 0x01;*/
	}
	else
	{
		/*Do nothing*/
	}
}

void CAN_Driver_Wake_Up(uint8 CAN_setup_nr)
{
	/*Exit from Sleep mode*/
	CAN_SETUP[CAN_setup_nr].CAN_Driver_instance->MCR &= (~CAN_DRIVER_SLEEP_MODE_REQUEST);

	/*Wait until change confirmed*/
	while ((CAN_SETUP[CAN_setup_nr].CAN_Driver_instance->MSR & CAN_DRIVER_SLEEP_ACKNOWLEDGE) != 0x00)
	{
		/*Do nothing*/
	}
}
