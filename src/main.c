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
	
	Light_Init();    // probleme

	for (;;)
	{
		if (play == 1)
		{
			Buzzer_Sing();
			play = 0;
		}
				
		/*if(flagADC)
		{
			float measured_voltage = (analog_input * 3.3f) / 1023;
			uint8_t parte_zecimala = (uint8_t) measured_voltage;
			uint8_t parte_fractionara1 = ((uint8_t)(measured_voltage * 10)) % 10;
			uint8_t parte_fractionara2 = ((uint8_t)(measured_voltage * 100)) % 10;
	
			UART0_Transmit('V');
			UART0_Transmit('o');
			UART0_Transmit('l');
			UART0_Transmit('t');
			UART0_Transmit('a');
			UART0_Transmit('g');
			UART0_Transmit('e');
			UART0_Transmit(' ');
			UART0_Transmit('=');
			UART0_Transmit(' ');
			UART0_Transmit(parte_zecimala + 0x30);
			UART0_Transmit('.');
			UART0_Transmit(parte_fractionara1 + 0x30);
			UART0_Transmit(parte_fractionara2 + 0x30);
			UART0_Transmit('V');
			UART0_Transmit(0x0A);
			UART0_Transmit(0x0D);
			
			flagADC=0;
		}      */
		
		//UART0_Transmit(Light_Read()+0x30);
	}
}