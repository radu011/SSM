#include "MKL25Z4.h"

/* variabila de control pentru ordinea secventei led-urilor */
static uint8_t order;

/* variabila pentru memorarea starii curente a led-ului */
static uint8_t state;

/* functie de initializare a modulului periferic (PIT[0]) */
void PIT_Init(void);

/* functia de tratare a intreruperilor pentru perifericul PIT */
void PIT_IRQHandler(void);

/* functia care schimba ordinea de aprindere a culorilor(schimbare valoare variabila order) */
void PIT_LED_Change_Order(void);