#ifndef UART_H
#define UART_H

#include <avr/io.h>
#include "utils.h"

#define BAUD 38400
#define MYUBRR (F_CPU / 16 / BAUD - 1)

void uart_init(unsigned int ubrr);
void uart_transmit(char data);
void uart_putstring(char *str);
char uart_receive();

#endif
