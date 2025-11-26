#include "uart.h"
#include <string.h>

#include <avr/interrupt.h>

#define UART_BUF_SIZE 64
volatile char uart_received_buffer[UART_BUF_SIZE];
volatile uint8_t uart_msg_ready = 0;
volatile uint8_t msg_index = 0;

void uart_enable_rx_interrupt() {
    UCSR0B |= (1 << RXCIE0);
    sei();
}

void uart_init(unsigned int ubrr) {
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;
    UCSR0A = 0;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    uart_enable_rx_interrupt();
    UCSR0C = (1 << USBS0) | (3 << UCSZ00);
}

/// Interruption liée au chgt du registre RX de l'uart
ISR(USART_RX_vect) {
    // recup le msg recu caractère par caractère
    char c = UDR0;
    if (c == '\n' || msg_index >= UART_BUF_SIZE - 1) {
        uart_received_buffer[msg_index] = '\0';
        // si on arrive à a fin de la string, on met le flag msg ready à 1
        uart_msg_ready = 1;
        msg_index = 0;
    } else {
        uart_received_buffer[msg_index++] = c;
    }
}

void uart_transmit(char data) {
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = data;
}

void uart_putstring(char *str) {
    while (*str) {
        uart_transmit(*str++);
    }
}

char uart_receive() {
    while (!(UCSR0A & (1 << RXC0)));
    return UDR0;
}
