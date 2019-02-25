#include "SYSTICK_Driver_Cfg.h"
#include "SYSTEM_Driver_Cfg.h"
#include "GPIO_Driver_Cfg.h"
#include "EXTI_Driver_Cfg.h"

uint32 dummy_Cnt = 0x00;

int main()
{
	/*SYSTICK_Driver_Init();*/
	GPIO_Driver_Init();

	/*SYSTICK_Driver_Delay_ms(500);*/

	while (1)
	{
		if(GPIO_Driver_ReadInputDataBit(GPIO_DRIVER_PORTA,GPIO_DRIVER_PORTA_PIN4)!=0x00)
		{
			/*SYSTEM_Driver_Enter_Standby_Mode();*/
		}
		if((SYSTEM_Driver_Enter_Standby_Mode_Check())==SYSTEM_DRIVER_STANDBY_FLAG_SET)
		{
			GPIO_Driver_SetPin(GPIO_DRIVER_PORTA,GPIO_DRIVER_PORTA_PIN7);
			for(dummy_Cnt= 0x00;dummy_Cnt<5000000;dummy_Cnt++){}
			GPIO_Driver_ClearPin(GPIO_DRIVER_PORTA,GPIO_DRIVER_PORTA_PIN7);
			for(dummy_Cnt= 0x00;dummy_Cnt<5000000;dummy_Cnt++){}
			GPIO_Driver_SetPin(GPIO_DRIVER_PORTA,GPIO_DRIVER_PORTA_PIN7);
			for(dummy_Cnt= 0x00;dummy_Cnt<5000000;dummy_Cnt++){}
			GPIO_Driver_ClearPin(GPIO_DRIVER_PORTA,GPIO_DRIVER_PORTA_PIN7);
			for(dummy_Cnt= 0x00;dummy_Cnt<5000000;dummy_Cnt++){}
			GPIO_Driver_SetPin(GPIO_DRIVER_PORTA,GPIO_DRIVER_PORTA_PIN7);
			for(dummy_Cnt= 0x00;dummy_Cnt<5000000;dummy_Cnt++){}
			GPIO_Driver_ClearPin(GPIO_DRIVER_PORTA,GPIO_DRIVER_PORTA_PIN7);
			for(dummy_Cnt= 0x00;dummy_Cnt<5000000;dummy_Cnt++){}
		}
		else
		{
			GPIO_Driver_SetPin(GPIO_DRIVER_PORTA,GPIO_DRIVER_PORTA_PIN7);
		}
	}
}
