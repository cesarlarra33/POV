#include "utils.h"

void delay_ms(int delay){
    for(int i = 0; i<delay; i++){
        _delay_ms(1); // on fait ca car _delay_ms() ne prend qu'une constante à la compilation
    }
}

void delay_us(int delay){
    for(int i = 0; i<delay; i++){
        _delay_us(1); 
    }
}
    
void delay_ticks(uint16_t ticks){
    if (ticks == 0) {
        return;
    }
    // Time countercontient la valeur du timer
    uint16_t start = TCNT1;
    while ((uint16_t)(TCNT1 - start) < ticks) {
    }
}

void delay_us_ticks(uint32_t delay_us){
    if (delay_us == 0) {
        return;
    }

    // on convertit delay_us en ticks 
    uint64_t numerator = (uint64_t)delay_us * (uint64_t)F_CPU;
    uint64_t denom = (uint64_t)COEFF_INCR_HALL * 1000000ULL;
    uint64_t ticks64 = numerator / denom;

    //si les us font 0 ticks on force quand même a 1 tick minimum
    if (ticks64 == 0) {
        ticks64 = 1;
    }
    // on limite à 0xFFFF pour éviter overflow
    if (ticks64 > 0xFFFF) {
        ticks64 = 0xFFFF;
    }

    uint16_t ticks = (uint16_t)ticks64;
    uint16_t start = TCNT1;
    while ((uint16_t)(TCNT1 - start) < ticks) {
    }
}

void set_as_output(volatile uint8_t *DDRx, uint8_t pin) {
    *DDRx |= (1 << pin);
}

void set_as_input(volatile uint8_t *DDRx, uint8_t pin) {
    *DDRx &= ~(1 << pin);
}

void set_pin(volatile uint8_t *PORTx, uint8_t pin, uint8_t value) {
    if (value)
        *PORTx |= (1 << pin); // pour mettre 1
    else
        *PORTx &= ~(1 << pin); // pour mettre zéro
}

uint8_t read_pin(volatile uint8_t *PINx, uint8_t pin) {
    return ((*PINx & (1 << pin)) != 0);
}
