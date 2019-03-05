#include "SYSTEM_Driver_Cfg.h"
#include "SYSTICK_Driver_Cfg.h"
#include "GPIO_Driver_Cfg.h"
#include "FMC_Driver_Cfg.h"

#define DUMMY_ADDRESS 0x1234

volatile uint32 counter = 0x00;
volatile uint32 read = 0x00;
volatile uint32 temp;


int main()
{
	SYSTICK_Driver_Init();
	GPIO_Driver_Init();

	FMC_Driver_Init();
	SYSTICK_Driver_Delay_ms(100);
	FMC_DRIVER_WRITE32(0x00, 0xF112);
	FMC_DRIVER_WRITE32(0x04, 0xAB34);
	FMC_DRIVER_WRITE32(0x08, 0xDEADBEEF);
	FMC_DRIVER_WRITE32(0x0C, 0xA5);

	while (1)
	{
		/*Read 16bit*/
		read = (*(volatile uint32*) 0xD0000002);/*0xf112f12f*/
		read = (*(volatile uint32*) 0xD0000006);/*0xab34f12f*/

		read = (*(volatile uint32*) 0xD0000007);/*0xadab34f1*/
		read = (*(volatile uint32*) 0xD0000008);/*0xf12ff12f*/
		read = (*(volatile uint32*) 0xD0000009);/*0xefdeadf1*/

		/*read 32 bit*/
		read = (*(volatile uint32*) 0xD000000A);/*0xbeeff12f*/
		read = (*(volatile uint32*) 0xD000000B);/*0xbeeff1*/
		read = (*(volatile uint32*) 0xD000000C);/*0xf12ff12f*/
		read = (*(volatile uint32*) 0xD000000D);/*0xa50000f1*/
		read = (*(volatile uint32*) 0xD000000E);/*0xa5f12f*/
		read = (*(volatile uint32*) 0xD000000F);/*0xaa00a5f1*/
		read = (*(volatile uint32*) 0xD0000010);/*0xf12ff12f*/


		counter++;
	}
}
