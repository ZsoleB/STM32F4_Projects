#include "SYSTEM_Driver_Cfg.h"
#include "SYSTICK_Driver_Cfg.h"
#include "GPIO_Driver_Cfg.h"
#include "FMC_Driver_Cfg.h"

#define DUMMY_ADDRESS 0x1234

volatile uint32 counter = 0x00;
volatile uint16 read = 0x00;
volatile uint32 temp;

int main()
{
	SYSTICK_Driver_Init();
	GPIO_Driver_Init();

	FMC_Driver_Init();

	FMC_DRIVER_WRITE16(0x00, 0xAB12);
	FMC_DRIVER_WRITE8(0x02, 0xCD);
	FMC_DRIVER_WRITE32(0x1234,0xEF23A311);


	while (1)
	{
		read = FMC_DRIVER_READ16(0x00);
		read = FMC_DRIVER_READ8(0x02);
		read = FMC_DRIVER_READ16(0x1234);
		read = FMC_DRIVER_READ16(0x1236);
		temp = FMC_DRIVER_READ32(0x1234);

		counter++;
	}
}
