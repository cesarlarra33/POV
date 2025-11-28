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

// macro qui convertit 16 bits individuels en un masque 16 bits
// se fait a la compilation donc coute pas + cher à l'exec 
// comment ca marche :
// !! convertit en booléen (0 ou 1) 
// puis les 16 bits sont castés en uint16_t et décalés à leur position respective
#ifndef MASK16
#define MASK16(b0,b1,b2,b3,b4,b5,b6,b7,b8,b9,b10,b11,b12,b13,b14,b15) \
    (uint16_t)( \
        ((uint16_t)(!!(b0))  << 0)  | ((uint16_t)(!!(b1))  << 1)  | \
        ((uint16_t)(!!(b2))  << 2)  | ((uint16_t)(!!(b3))  << 3)  | \
        ((uint16_t)(!!(b4))  << 4)  | ((uint16_t)(!!(b5))  << 5)  | \
        ((uint16_t)(!!(b6))  << 6)  | ((uint16_t)(!!(b7))  << 7)  | \
        ((uint16_t)(!!(b8))  << 8)  | ((uint16_t)(!!(b9))  << 9)  | \
        ((uint16_t)(!!(b10)) << 10) | ((uint16_t)(!!(b11)) << 11) | \
        ((uint16_t)(!!(b12)) << 12) | ((uint16_t)(!!(b13)) << 13) | \
        ((uint16_t)(!!(b14)) << 14) | ((uint16_t)(!!(b15)) << 15))
#endif

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

