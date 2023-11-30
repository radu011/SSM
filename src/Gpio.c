#include "Gpio.h"

void RGBLed_Init(void)
{
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;

	PORTB->PCR[RED_LED_PIN] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[GREEN_LED_PIN] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[BLUE_LED_PIN] &= ~PORT_PCR_MUX_MASK;

	PORTB->PCR[RED_LED_PIN] |= PORT_PCR_MUX(1);
	PORTB->PCR[GREEN_LED_PIN] |= PORT_PCR_MUX(1);
	PORTD->PCR[BLUE_LED_PIN] |= PORT_PCR_MUX(1);

	GPIOB->PDDR |= (1 << RED_LED_PIN);
	GPIOB->PDDR |= (1 << GREEN_LED_PIN);
	GPIOD->PDDR |= (1 << BLUE_LED_PIN);

	GPIOB->PCOR |= (1 << RED_LED_PIN);
	GPIOD->PCOR |= (1 << BLUE_LED_PIN);
	GPIOB->PCOR |= (1 << GREEN_LED_PIN);
}

void Buzzer_Init(void)
{
	// Activarea semnalului de ceas pentru portul D (conexiune pe PTD4)
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;

	// Utilizare GPIO ca varianta de multiplexare
	PORTD->PCR[BUZZER_PIN] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[BUZZER_PIN] |= PORT_PCR_MUX(1); // GPIO

	// Configurare pin pe post de output
	GPIOD_PDDR |= (1 << BUZZER_PIN);

	// Stingerea buzzer-ului / punerea pe 0 logic
	GPIOD_PCOR |= (1 << BUZZER_PIN);
}

void Buzzer_Sound(uint8_t noBip)
{
	uint32_t timer = 200000;
	uint32_t timerCount;

	// Numarul de bip-uri
	uint8_t i = 0;
	for (i = 0; i < noBip; i++)
	{
		// Activarea buzzer-ului (1 logic)
		GPIOD_PSOR |= (1 << BUZZER_PIN);

		// Durata sunetului
		timerCount = 0;
		while (timerCount < timer)
			timerCount++;

		// Dezactivarea buzzer-ului (1 logic)
		GPIOD_PCOR |= (1 << BUZZER_PIN);

		// Durata pauzei dintre sunete
		timerCount = 0;
		while (timerCount < timer)
			timerCount++;
	}
}
