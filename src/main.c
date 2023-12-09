#include "Pit.h"
#include "Gpio.h"
#include "Uart.h"
#include "SysTick.h"

uint8_t play;
uint8_t flagSysTick;

int main(void)
{

	UART0_Init(115200);
	// PIT_Init();
	// RGBLed_Init();
	// Buzzer_Init();
	Init_SysTick();

	// Buzzer_Sound(3);

	// Buzzer_Sing();

	for (;;)
	{
		if (play == 1)
		{
			// Buzzer_Sing();
			play = 0;
		}
		
		if(flagSysTick == 1)
		{
			
			// read Sound Sensor data
			UART0_Transmit('c'); // just for test
			
			flagSysTick = 0;
		}
	}
}