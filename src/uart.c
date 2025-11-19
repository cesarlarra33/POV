#include "uart.h"
#include <string.h>

void USART_Init(unsigned int ubrr) {
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;
    UCSR0A = 0;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    UCSR0C = (1 << USBS0) | (3 << UCSZ00);
}

void USART_Transmit(char data) {
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = data;
}

void USART_PutString(char *str) {
    while (*str) {
        USART_Transmit(*str++);
    }
}

char USART_Receive() {
    while (!(UCSR0A & (1 << RXC0)));
    return UDR0;
}
