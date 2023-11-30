#include "Pit.h"
#include "Gpio.h"
#include "Uart.h"
#include "ClockSettings.h"
#include "Adc.h"

extern uint16_t temperature_read;

int main(void)
{

	SystemClock_Configure();
	SystemClockTick_Configure();
	UART0_Init(115200);
	//PIT_Init();
	ADC0_Init();

	for (;;)
	{
		if (flag_50ms)
		{
			Temperature_Read();
			flag_50ms = 0U;
		} 
	}
}