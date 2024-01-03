#include "SysTick.h"
#include "Uart.h"

volatile uint8_t flagSysTick;

void Init_SysTick(void)
{
    /* setarea valorii de inceput/reset pentru numarator */
    SysTick->LOAD = (4800000L); /* 100ms */
    /* activarea intreruperii si setarea prioritatii in NVIC */
    NVIC_SetPriority(SysTick_IRQn, 2);
    /* setarea valorii curente a numaratorului (reset) */
    SysTick->VAL = 0;
		/* modificam registrul de control */
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk /* selectam clock-ul procesorului */
										| SysTick_CTRL_TICKINT_Msk /* activam intreruperea */
                    | SysTick_CTRL_ENABLE_Msk; /* activam numaratorul */
		/* CLOKSOURCE = 0 (Sursa de ceas alternativa) */
	
		flagSysTick = 0;
}

/* rutina de tratare a exceptiei generate de SysTick */
void SysTick_Handler(void)
{
		flagSysTick = 1;
	
		/* activate intrerupere pentru ADC */
		ADC0->SC1[0] |= ADC_SC1_AIEN_MASK;
}
