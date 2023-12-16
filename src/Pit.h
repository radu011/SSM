#include "MKL25Z4.h"

static uint8_t order;
static uint8_t state;

// Functie de initializare a modulului periferic (PIT[0])
void PIT_Init(void);

// Functie de initializare a modulului periferic (PIT[1])
void PIT_Init2(void);

// Functia de tratare a intreruperilor pentru perifericul PIT
void PIT_IRQHandler(void);

// Functia care schimba ordinea de aprindere a culorilor(schimbare valoare variabila order)
void PIT_LED_Change_Order(void);