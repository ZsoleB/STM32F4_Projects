#include "SYSTICK_Driver_Cfg.h"
#include "SYSTEM_Driver_Cfg.h"
#include "GPIO_Driver_Cfg.h"
#include "EXTI_Driver_Cfg.h"

uint32 dummy_Cnt = 0x00;

void EXTI0_IRQHandler()
{
	EXTI_Driver_Clear_PendingInterrupt(EXTI_DRIVER_INTERRUPT_PIN_0);
}

int main()
{
	/*SYSTICK_Driver_Init();*/
	GPIO_Driver_Init();

	/*SYSTICK_Driver_Delay_ms(500);*/
	EXTI_Driver_Init(EXTI_DRIVER_INTERRUPT_PIN_0,EXTI_DRIVER_INTERRUPT_PORT_A,EXTI_DRIVER_INTERRUPT_ACTION);
	EXTI_Driver_Rising_Trigger_Select(EXTI_DRIVER_INTERRUPT_PIN_0);
	while (1)
	{
		if(GPIO_Driver_ReadInputDataBit(GPIO_DRIVER_PORTA,GPIO_DRIVER_PORTA_PIN4)!=0x00)
		{
			SYSTEM_Driver_Enter_Sleep_Mode();
		}
		GPIO_Driver_SetPin(GPIO_DRIVER_PORTA,GPIO_DRIVER_PORTA_PIN7);
		for(dummy_Cnt= 0x00;dummy_Cnt<500000;dummy_Cnt++){}
		GPIO_Driver_ClearPin(GPIO_DRIVER_PORTA,GPIO_DRIVER_PORTA_PIN7);
		for(dummy_Cnt= 0x00;dummy_Cnt<500000;dummy_Cnt++){}
	}
}
