#include "MKL25Z4.h"

#define RED_LED_PIN 18   /* PORT B PIN 18 */
#define GREEN_LED_PIN 19 /* PORT B PIN 19 */
#define BLUE_LED_PIN 1   /* PORT D PIN 1 */

#define LIGHT_PIN 4 /* PORT A PIN 4 */

#define BUZZER_PIN (4) /* PORT D PIN 4 */

/* variabila pentru declansarea buzzerului cu o melodie */
extern volatile uint8_t play;

/* initializarea led-urilor */
void RGBLed_Init(void);

/* initializarea buzzerului */
void Buzzer_Init(void);

/* initializarea senzorului de lumina */
void Light_Init(void);

/* functie pentru citirea datelor de la senzor de lumina */
uint8_t Light_Read(void);

/* activarea buzzerului pentru declansarea semnalelor sonore pentru cele 3 intervale */
void Buzzer_Sound(uint8_t noBip);

/* pornirea melodiei */
void Buzzer_Sing(void);
