#include "CAN_Driver_Cfg.h"

CAN_Driver_Setup_Type CAN_CONF_SETUP[CAN_DRIVER_INSTANCE_NUM]=
{
	{
			CAN1,
			500000,
			12,
			5,
			4,
			OK,
			CAN_Driver_test_mode_loop_back,
			OK,
			OK,
			NOK,
			NOK,
			CAN_DRIVER_TRANSMIT_PRIORITY_BY_ID,
			CAN_DRIVER_NON_AUTOMATIC_TRANSMISSION_MODE,
			OK,
			CAN_DRIVER_FILTER_SCALE_32_BIT,
			NOK,
			NOK,
			NOK
	}
};

CAN_Driver_Setup_Type* CAN_SETUP = CAN_CONF_SETUP;

