#include <avr/io.h>
#include <string.h>

#define FOSC 13000000  
#define BAUD 38400
#define MYUBRR (FOSC / 16 / BAUD - 1) 

// Initialisation de l'UART en mode asynchrone normal
void USART_Init(unsigned int ubrr) {
    
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;

    // Activer le mode asynchrone normal
    UCSR0A = 0;  // Désactiver le mode double vitesse

    // Activer le récepteur et l'émetteur
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);

    // Configurer le format du trame : 8 bits de données, 2 bits d'arrêt
    UCSR0C = (1 << USBS0) | (3 << UCSZ00);
}

// Envoi d'un caractère
void USART_Transmit(char data) {
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = data;
}

// Envoi d'une chaîne de caractères
void USART_PutString(char *str) {
    while (*str) {
        USART_Transmit(*str++);
    }
}

// Lecture d'un caractère
char USART_Receive() {
    while (!(UCSR0A & (1 << RXC0)));  // Attendre qu'un caractère soit reçu
    return UDR0;
}


int main(void) {
    char receivedChar;
    char messageReceived = 0;  // Indicateur pour savoir si un message a été reçu

    // Initialiser l'UART en mode asynchrone normal avec la valeur de UBRR calculée
    USART_Init(MYUBRR);

    while (1) {
        receivedChar = USART_Receive();

        if (receivedChar == '\n' || receivedChar == '\r') {
            if (messageReceived) {
                // Répondre "OK Bouchra" seulement après avoir reçu une nouvelle ligne
                USART_PutString("OK Bouchra\n");
                messageReceived = 0;  // Réinitialiser l'indicateur
            }
        } else {
            messageReceived = 1;  // Indiquer qu'un message est en cours de réception
        }
    }

    return 0;
}