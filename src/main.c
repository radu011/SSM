#include "Pit.h"
#include "Gpio.h"
#include "Uart.h"

int main(void)
{

	UART0_Init(115200);
	// UART0_Transmit('a');
	PIT_Init();
	RGBLed_Init();

	Buzzer_Init();

	// Buzzer_Sound(3);

	for (;;)
	{
		// read Sound Sensor data
	}
}