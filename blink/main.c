// led.c
#include <avr/io.h>
#include <util/delay.h>

void delay(int delay){
    for(int i = 0; i<delay; i++){
        _delay_ms(1); 
    }
}


int main(void)
{
    DDRB |= (1 << PB5); // PB5 en sortie 
    while (1) {
        PORTB &= ~(1 << PB5); // PB5 à 1 
        delay(200);
        PORTB |= (1 << PB5);
        delay(200);
    }
}