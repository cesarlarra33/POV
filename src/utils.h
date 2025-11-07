#ifndef UTILS_H  
#define UTILS_H

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

#define F_CPU 13000000UL
#define NB_LEDS 16


// utile pour la configuration de l'interruption
// je passe à 64 car 8 pas assez
#define COEFF_INCR_HALL 64

/// @brief Attend un délai de delay millisecondes
/// @param delay Le délai en millisecondes
void delay_ms(int delay); 

/// @brief Attend un délai de delay microsecondes
/// @param delay Le délai en microsecondes
void delay_us(int delay);

/// @brief attend un nombre de ticks sur le compteur TCNT1
/// @param ticks Le nombre de ticks à attendre
void delay_ticks(uint16_t ticks);

/// @brief attend un nombre de ticks exprimé en microsecondes
/// @param delay_us Le délai en microsecondes
void delay_us_ticks(uint32_t delay_us);

/// @brief Ecris un 1 au pin-ème bit l'adresse DDRx pour qu'il soit un output
/// @param DDRx L'adresse de registre DDRx
/// @param pin Le numéro du pin à configurer
void set_as_output(volatile uint8_t *DDRx, uint8_t pin);

/// @brief Ecris un 0 au pin-ème bit de DDRx pour qu'il soit un input
/// @param DDRx L'adresse de registre DDRx
/// @param pin Le numéro du pin à configurer
void set_as_input(volatile uint8_t *DDRx, uint8_t pin);

/// @brief met value au pin-ème (ex: PB5) bit de PORTx
/// @param PORTx L'adresse de registre PORTx
/// @param pin Le numéro du pin à configurer
/// @param value La valeur à écrire (0 ou 1)
void set_pin(volatile uint8_t *PORTx, uint8_t pin, uint8_t value);

/// @brief lit le pin-ème bit de PINx, qui est la valeur PORTx
/// @param PINx L'adresse de registre PINx
/// @param pin Le numéro du pin à lire
/// @return La valeur du pin (0 ou 1)
uint8_t read_pin(volatile uint8_t *PINx, uint8_t pin);

#endif 