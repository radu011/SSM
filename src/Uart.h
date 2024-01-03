#include "MKL25Z4.h"

/* functie folostia pentru a trimite un octet pe interfata UART */
void UART0_Transmit(uint8_t data);

/* functie ce citeste un octet de pe interfata UART */
uint8_t UART0_Receive(void);

/* initializare a modulului UART pentru trasmiterea datelor, ce primeste ca parametru baud rate-ul */
void UART0_Init(uint32_t baud_rate);

/* functie de tratare a intreruperii pentru perifericul UART (receptie) */
void UART0_IRQHandler(void);
