#include "SysTick.h"
#include "Uart.h"

void Init_SysTick(void)
{
    // Setarea valorii de inceput/reset pentru numarator
    SysTick->LOAD = (12000000L);
    // Activarea intreruperii si setarea prioritatii in NVIC
    NVIC_SetPriority(SysTick_IRQn, 2);
    // Setarea valorii curente a numaratorului (reset)
    SysTick->VAL = 0;
		// Modificam registrul de control
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk // Selectam clock-ul procesorului
										| SysTick_CTRL_TICKINT_Msk // Activam intreruperea
                    | SysTick_CTRL_ENABLE_Msk; // Activam numaratorul
		// CLOKSOURCE = 0 (Sursa de ceas alternativa)
	
		flagSysTick = 0;
}

// Rutina de tratare a exceptiei generate de SysTick
void SysTick_Handler(void)
{
		flagSysTick = 1;
}
