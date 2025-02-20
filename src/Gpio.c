#include "Gpio.h"

volatile uint8_t play;

void RGBLed_Init(void)
{
	/* activarea sursei de ceas pentru portul B */
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	/* activarea sursei de ceas pentru portul D */
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;

	/* resetam valoarea pentru alternativa selectata pentru pini */
	PORTB->PCR[RED_LED_PIN] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[GREEN_LED_PIN] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[BLUE_LED_PIN] &= ~PORT_PCR_MUX_MASK;

	/* selectarea alternativei pentru pinii folositi pentru led-uri */
	PORTB->PCR[RED_LED_PIN] |= PORT_PCR_MUX(1);	  /* PTB18 */
	PORTB->PCR[GREEN_LED_PIN] |= PORT_PCR_MUX(1); /* PTB19 */
	PORTD->PCR[BLUE_LED_PIN] |= PORT_PCR_MUX(1);  /* PTD1 */

	/* setam pinii ca fiind pentru output */
	GPIOB->PDDR |= (1 << RED_LED_PIN);
	GPIOB->PDDR |= (1 << GREEN_LED_PIN);
	GPIOD->PDDR |= (1 << BLUE_LED_PIN);

	/* resetam valoarea transmisa pe pini (punem valoarea 0) pentru a stinge led-urile */
	GPIOB->PCOR |= (1 << RED_LED_PIN);
	GPIOD->PCOR |= (1 << BLUE_LED_PIN);
	GPIOB->PCOR |= (1 << GREEN_LED_PIN);
}

void Light_Init(void)
{
	/* activam sursa de ceas (chiar daca este deja activa, poate folosim separat de restul acest modul)*/
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;

	/* selectarea alternativei pentru pinul pe care am conectat senzorul de lumina */
	PORTA->PCR[LIGHT_PIN] &= ~PORT_PCR_MUX_MASK;
	PORTA->PCR[LIGHT_PIN] |= PORT_PCR_MUX(1);

	/* Setam pentru input pinu-ul desi el default este pe input dar sa fim siguri */
	GPIOA->PDDR |= (0 << LIGHT_PIN);
}

uint8_t Light_Read(void)
{
	/* activ pe 0 */
	if (GPIOA->PDIR & (1 << LIGHT_PIN))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void Buzzer_Init(void)
{
	/* activarea semnalului de ceas pentru portul D (conexiune pe PTD4) */
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;

	/* utilizare GPIO ca varianta de multiplexare */
	PORTD->PCR[BUZZER_PIN] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[BUZZER_PIN] |= PORT_PCR_MUX(1); /* GPIO */

	/* configurare pin pe post de output */
	GPIOD_PDDR |= (1 << BUZZER_PIN);

	/* stingerea buzzer-ului / punerea pe 0 logic */
	GPIOD_PCOR |= (1 << BUZZER_PIN);

	play = 0;
}

void Buzzer_Sound(uint8_t noBip)
{
	uint32_t timer = 20000;
	uint32_t timerCount;

	/* Numarul de bip-uri */
	uint8_t i = 0;
	for (i = 0; i < noBip; i++)
	{
		/* Activarea buzzer-ului (1 logic) */
		GPIOD_PSOR |= (1 << BUZZER_PIN);

		/* Durata sunetului */
		timerCount = 0;
		while (timerCount < timer)
			timerCount++;

		/* Dezactivarea buzzer-ului (1 logic) */
		GPIOD_PCOR |= (1 << BUZZER_PIN);

		/* Durata pauzei dintre sunete */
		timerCount = 0;
		while (timerCount < timer * 10)
			timerCount++;
	}
}

static void delay(int value)
{
	while (value > 0)
		value--;
}

static void playTone(int tone, int duration)
{
	long i;
	for (i = 0; i < duration * 1000; i += tone * 2)
	{
		GPIOD_PSOR |= (1 << BUZZER_PIN);
		delay(tone / 4);
		/* delay(tone / 2); */
		GPIOD_PCOR |= (1 << BUZZER_PIN);
		delay(tone * 2.5);
		/* delay(tone * 2); */
	}
	GPIOD_PCOR |= (1 << BUZZER_PIN);
}

static void playNote(char note, int duration)
{
	char names[] = {'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C'};
	int tones[] = {1915, 1700, 1519, 1432, 1275, 1136, 1014, 956};

	int i;
	for (i = 0; i < 8; i++)
	{
		if (names[i] == note)
		{
			playTone(tones[i], duration);
		}
	}
}

void Buzzer_Sing(void)
{
	int length = 26;
	char notes[] = "eeeeeeegcde fffffeeeeddedg";
	int beats[] = {1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2};
	int tempo = 300;

	int i;
	for (i = 0; i < length; i++)
	{
		if (notes[i] == ' ')
		{
			delay(beats[i] * tempo);
		}
		else
		{
			playNote(notes[i], beats[i] * tempo);
		}
		delay(tempo / 2);
	}
}
