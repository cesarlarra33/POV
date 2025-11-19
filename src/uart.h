#ifndef UART_H
#define UART_H

#include <avr/io.h>

#define FOSC 13000000UL
#define BAUD 38400
#define MYUBRR (FOSC / 16 / BAUD - 1)

void USART_Init(unsigned int ubrr);
void USART_Transmit(char data);
void USART_PutString(char *str);
char USART_Receive();

#endif
