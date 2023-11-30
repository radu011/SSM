#include "Pit.h"
#include "Uart.h"
#include "Gpio.h"

void PIT_Init(void)
{
	// Activarea semnalului de ceas pentru perifericul PIT
	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;
	// Utilizarea semnalului de ceas pentru tabloul de timere
	PIT_MCR &= ~PIT_MCR_MDIS_MASK;
	// Oprirea decrementarii valorilor numaratoarelor in modul debug
	PIT->MCR |= PIT_MCR_FRZ_MASK;
	// Setarea valoarea numaratorului de pe canalul 0 la o perioada de 1 secunda
	PIT->CHANNEL[0].LDVAL = 0x10C51EA; 
	
  // Activarea intreruperilor pe canalul 0
	PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TIE_MASK;
	// Activarea timerului de pe canalul 0
	PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TEN_MASK;
	
	// Activarea intreruperii mascabile si setarea prioritatiis
	NVIC_ClearPendingIRQ(PIT_IRQn);
	NVIC_SetPriority(PIT_IRQn,5);
	NVIC_EnableIRQ(PIT_IRQn);
}


void PIT_IRQHandler(void)
{
	if(PIT->CHANNEL[0].TFLG & PIT_TFLG_TIF_MASK)
	{
		if(state == 0)
		{
			GPIOB->PCOR |= (1 << RED_LED_PIN);
			GPIOB->PCOR |= (1 << GREEN_LED_PIN);
			GPIOD->PCOR |= (1 << BLUE_LED_PIN);
		}
		else if(state == 1)
		{
			GPIOD->PCOR |= (1 << BLUE_LED_PIN);
			GPIOB->PSOR |= (1 << RED_LED_PIN);
			GPIOB->PSOR |= (1 << GREEN_LED_PIN);
		}
		else if(state == 2)
		{
			GPIOD->PCOR |= (1 << BLUE_LED_PIN);
			GPIOB->PSOR |= (1 << RED_LED_PIN);
			GPIOB->PCOR |= (1 << GREEN_LED_PIN);
		}
		else if(state == 3)
		{
			GPIOB->PSOR |= (1 << RED_LED_PIN);
			GPIOB->PSOR |= (1 << GREEN_LED_PIN);
			GPIOD->PSOR |= (1 << BLUE_LED_PIN);
		}
		state += 1;
		state = state % 4;
		PIT->CHANNEL[0].TFLG &= PIT_TFLG_TIF_MASK;
	}
}
	