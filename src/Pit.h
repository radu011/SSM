#include "MKL25Z4.h"

static uint8_t order;
static uint8_t state;

// Functie de initializare a modulului periferic
void PIT_Init(void);

// Functia de tratare a intreruperilor pentru perifericul PIT
void PIT_IRQHandler(void);

// Functia care schimba ordinea de aprindere a culorilor(schimbare valoare variabila order)
void PIT_LED_Change_Order();