#include "MKL25Z4.h"

#define RED_LED_PIN 18   // PORT B PIN 18
#define GREEN_LED_PIN 19 // PORT B PIN 19
#define BLUE_LED_PIN 1   // PORT D PIN 1

#define BUZZER_PIN (4) // PORT D PIN 4

void RGBLed_Init(void);
void Buzzer_Init(void);

void Buzzer_Sound(uint8_t noBip);
void Buzzer_Sing(void);
