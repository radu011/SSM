#include "Pit.h"
#include "Gpio.h"
#include "Uart.h"

uint8_t play;

int main(void)
{

	UART0_Init(115200);
	PIT_Init();
	RGBLed_Init();
	Buzzer_Init();

	// Buzzer_Sound(3);

	// Buzzer_Sing();

	for (;;)
	{
		if (play == 1)
		{
			Buzzer_Sing();
			play = 0;
		}
		// read Sound Sensor data
	}
}