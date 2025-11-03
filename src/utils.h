#ifndef UTILS_H  
#define UTILS_H

#include <avr/io.h>
#include <util/delay.h>



// attend un delai de delay ms
void delay(int delay); 

// Ecris un 1 au pin-ème bit l'adresse DDRx pour qu'il soit un output 
void set_as_output(volatile uint8_t *DDRx, uint8_t pin);

// Ecris un 0 au pin-ème bit de DDRx pour qu'il soit un output 
void set_as_input(volatile uint8_t *DDRx, uint8_t pin) ; 

// met value au pin-ème (ex: PB5) bit de PORTx  
void set_pin(volatile uint8_t *PORTx, uint8_t pin, uint8_t value); 

// lit le pin-ème bit de PINx, qui est la valeur PORTx
uint8_t read_pin(volatile uint8_t *PINx, uint8_t pin); 

#endif 

