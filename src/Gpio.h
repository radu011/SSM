#include "MKL25Z4.h"

#define RED_LED_PIN 18   // PORT B PIN 18
#define GREEN_LED_PIN 19 // PORT B PIN 19
#define BLUE_LED_PIN 1   // PORT D PIN 1

#define LIGHT_PIN 4			// PORT A PIN 4

#define BUZZER_PIN (4) // PORT D PIN 4

extern uint8_t play;

void RGBLed_Init(void);
void Buzzer_Init(void);
void Light_Init(void);

uint8_t Light_Read(void);

void Buzzer_Sound(uint8_t noBip);
void Buzzer_Sing(void);
