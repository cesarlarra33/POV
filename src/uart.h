#ifndef UART_H
#define UART_H

#include <avr/io.h>
#include <stdio.h>
#include "clock.h"
#include "utils.h"
#include <string.h>
#include <avr/interrupt.h>

// la baudrate de l'uart sur atmega328p 
#define BAUD 38400 

// UBRR = USART Baud Rate Register
// c'est la fréquence de communication uart à rentrer dans les registres UBRRH et UBRRL du atmega328p 
// elle se calcule par cette formule :
#define MYUBRR (F_CPU / 16 / BAUD - 1)

// taille max de la commande uart qu'on peut envoyer. 
#define UART_BUF_SIZE 64

// buffer dans lequel on va stocker char par char la commande recue
extern volatile char uart_received_buffer[UART_BUF_SIZE];

// flags relatifs à si le msg est stocké en entier et à quel char du msg on en est. 
extern volatile uint8_t uart_msg_ready; 
extern volatile uint8_t msg_index; 

/// @brief interruption qui se déclenche à chaque chgt de RX soit à chaque char recu
/// @param USART_RX_vect le registre correspondant à RX
ISR(USART_RX_vect); 

/// @brief initialise la communication uart en mettant les registres en question aux bonnes valeurs
/// et intialise l'interrupt liée à l'uart
/// @param ubrr 
void uart_init(unsigned int ubrr);

/// @brief permet d'envoyer un caractère via uart
/// @param data le caractère en question à envoyer 
void uart_transmit(char data);

/// @brief permet d'envoyer une string entière par uart en itérant sur chaque char 
/// @param str la string à envoyer
void uart_putstring(char *str);

/// @brief permettait de recevoir un char en uart, mais dépréciée car écoute active bloquante
/// @return le char recu. 
char uart_receive();

#endif
