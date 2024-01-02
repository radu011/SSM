#include "Pit.h"
#include "Gpio.h"
#include "Uart.h"
#include "SysTick.h"
#include "Adc.h"

uint8_t play;

int main(void)
{

	UART0_Init(115200);
	Buzzer_Init();
	ADC0_Init();
	
	PIT_Init();
	Init_SysTick();
	RGBLed_Init();
	
	Light_Init();    /* probleme */

	float prev = 0;
	
	for (;;)
	{
		if (play == 1)
		{
			Buzzer_Sing();
			play = 0;
		}
				
		if(flagADC)
		{
			float measured_voltage = 3.3f - (analog_input * 3.3f) / 1023;
			
			uint8_t parte_zecimala = (uint8_t) measured_voltage;
			uint8_t parte_fractionara1 = ((uint8_t)(measured_voltage * 10)) % 10;
			uint8_t parte_fractionara2 = ((uint8_t)(measured_voltage * 100)) % 10;
			
			uint8_t lightData = Light_Read() + 0x30;
				
			UART0_Transmit(parte_zecimala + 0x30);
			UART0_Transmit(parte_fractionara1 + 0x30);
			UART0_Transmit(parte_fractionara2 + 0x30);
			UART0_Transmit(lightData);
			
			if(prev < 0.2 && measured_voltage > 0.4)
				Buzzer_Sound(2);
			else if(prev < 0.2 && measured_voltage > 0.2)
				Buzzer_Sound(1);
			/*else if(prev > 0.4 && measured_voltage > 0.2 && measured_voltage < 0.4)
				Buzzer_Sound(2);
			else if(prev > 0.2 && measured_voltage < 0.2)
				Buzzer_Sound(1);*/
			
			flagADC=0;
		} 

	}
}