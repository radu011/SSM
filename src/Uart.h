#include "MKL25Z4.h"

// Functie folostia pentru a trimite un octet catre interfata UART
void UART0_Transmit(uint8_t data);

// Functie ce returneaza un octet de pe interfata UART, atunci cand acesta exista un buffer
uint8_t UART0_Receive(void);

// Initializare a modulului UART pentru trasmiterea datelor, ce primeste ca parametru baud rate-ul dorit
void UART0_Init(uint32_t baud_rate);

void UART0_IRQHandler(void);
