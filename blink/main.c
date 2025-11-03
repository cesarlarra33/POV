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
    int cpt = 1; 
    for(long i =1; i<1000000; i++) {
        PORTB &= ~(1 << PB5); // PB5 à 1 
        delay(i);
        PORTB |= (1 << PB5);
        delay(i);
    }
}