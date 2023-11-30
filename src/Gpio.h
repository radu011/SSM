#include "MKL25Z4.h"

#define RED_LED_PIN 18 // PORT B PIN 18
#define GREEN_LED_PIN 19 // PORT B PIN 19
#define BLUE_LED_PIN 1 // PORT D PIN 1

static uint8_t state = 0;

void RGBLed_Init(void);