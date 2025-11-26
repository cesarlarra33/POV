#ifndef UART_H
#define UART_H

#include <avr/io.h>
#include "utils.h"

#define BAUD 38400
#define MYUBRR (F_CPU / 16 / BAUD - 1)

#define UART_BUF_SIZE 64
extern volatile char uart_received_buffer[UART_BUF_SIZE];
extern volatile uint8_t uart_msg_ready; 
extern volatile uint8_t msg_index; 

void uart_init(unsigned int ubrr);
void uart_transmit(char data);
void uart_putstring(char *str);
char uart_receive();

#endif
