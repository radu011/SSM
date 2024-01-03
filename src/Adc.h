#include "MKL25Z4.h"

/* PORT C PIN 1 => canalul 15*/
#define ADC_CHANNEL (15) 

/* semnalizare ca s-a citit valoarea si se poate trasmite */
extern volatile uint8_t flagADC;

/* valoarea citita de la senzor */
extern uint16_t analog_input;

/* initializarea ADC-ului */
void ADC0_Init(void);

/* functie de calibrare de la ADC */
int ADC0_Calibrate(void);

/* tratarea intreruperilor pentru perifericul ADC */
void ADC0_IRQHandler(void);