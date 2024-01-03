#include "Pit.h"
#include "Uart.h"
#include "Gpio.h"

void PIT_Init(void)
{
	/* activarea semnalului de ceas pentru perifericul PIT */
	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;
	/* utilizarea semnalului de ceas pentru tabloul de timere */
	PIT_MCR &= ~PIT_MCR_MDIS_MASK;
	/* oprirea decrementarii valorilor numaratoarelor in modul debug */
	PIT->MCR |= PIT_MCR_FRZ_MASK;
	/* setarea valorii numaratorului de pe canalul 0 la o perioada de 1677 milisecunde */
	PIT->CHANNEL[0].LDVAL = 0x10C51EA;

	/* activarea intreruperilor pe canalul 0 */
	PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TIE_MASK;
	/* activarea timerului de pe canalul 0 */
	PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TEN_MASK;

	/* activarea intreruperii mascabile si setarea prioritatii */
	NVIC_ClearPendingIRQ(PIT_IRQn);
	NVIC_SetPriority(PIT_IRQn, 5);
	NVIC_EnableIRQ(PIT_IRQn);

	order = 0;
	state = 0;
}

void PIT_IRQHandler(void)
{
	if (PIT->CHANNEL[0].TFLG & PIT_TFLG_TIF_MASK)
	{
		GPIOB->PCOR |= (1 << RED_LED_PIN);
		GPIOB->PCOR |= (1 << GREEN_LED_PIN);
		GPIOD->PCOR |= (1 << BLUE_LED_PIN);
		
		if (state == 1)
		{
			GPIOB->PSOR |= (1 << RED_LED_PIN);
			GPIOB->PSOR |= (1 << GREEN_LED_PIN);
		}
		else if (state == 2)
		{
			GPIOB->PSOR |= (1 << RED_LED_PIN);
			GPIOB->PCOR |= (1 << GREEN_LED_PIN);
		}
		else if (state == 3)
		{
			GPIOB->PSOR |= (1 << RED_LED_PIN);
			GPIOB->PSOR |= (1 << GREEN_LED_PIN);
			GPIOD->PSOR |= (1 << BLUE_LED_PIN);
		}
		
		if (order == 0)
		{
			state++;
		}
		else
		{
			if(state == 0)
			{
				state = 3;
			}
			else 
			{
				state--;
			}
		}
		state = state % 4;
		PIT->CHANNEL[0].TFLG &= PIT_TFLG_TIF_MASK; // resetare
	}
}

void PIT_LED_Change_Order(void)
{
	order = (order + 1) % 2;
}