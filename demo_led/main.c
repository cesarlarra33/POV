// led.c
#include <avr/io.h>

int main(void)
{
    DDRB |= (1 << PB5); // PB5 en sortie
    PORTB |= (1 << PB5); // PB5 à 1
    while (1);
}