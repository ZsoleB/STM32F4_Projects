#include "SYSTICK_Driver_Cfg.h"
#include "GPIO_Driver_Cfg.h"
#include "DAC_Driver_Cfg.h"

uint16 counter  = 0x00;
uint8  sign     = 0x00;

int main()
{

	SYSTICK_Driver_Init();
	GPIO_Driver_Init();
	DAC_Driver_Init();

	while (1)
	{
		DAC_Driver_SW_Start(DAC_DRIVER_CHANNEL1);
		SYSTICK_Driver_Delay_ms(50);
	}
}
