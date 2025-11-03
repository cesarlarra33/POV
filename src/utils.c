#include "utils.h"

// pratique car on peut pas passer de délai non constant à la compilaton à _delay_ms()
void delay(int delay){
    for(int i = 0; i<delay; i++){
        _delay_ms(1); 
    }
}

//////// 
/// volatile dit au compilateur de ne pas faire d'optilisations sur la variable
////////


// Ecris un 1 au pin-ème bit l'adresse DDRx pour qu'il soit un output 
void set_as_output(volatile uint8_t *DDRx, uint8_t pin) {
    *DDRx |= (1 << pin);
}

// Ecris un 0 au pin-ème bit de DDRx pour qu'il soit un output 
void set_as_input(volatile uint8_t *DDRx, uint8_t pin) {
    *DDRx &= ~(1 << pin);
}

// met value au pin-ème (ex: PB5) bit de PORTx  
void set_pin(volatile uint8_t *PORTx, uint8_t pin, uint8_t value) {
    if (value)
        *PORTx |= (1 << pin);
    else
        *PORTx &= ~(1 << pin);
}

// lit le pin-ème bit de PINx, qui est la valeur PORTx
uint8_t read_pin(volatile uint8_t *PINx, uint8_t pin) {
    return ((*PINx & (1 << pin)) != 0);
}
