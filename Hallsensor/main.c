#include <avr/io.h>
#include <avr/interrupt.h>

#define HALL_PIN PD2
#define LED_PIN  PD6

void HallSensor_Init() {
    DDRD &= ~(1 << HALL_PIN);      // PD2 en entrée
    PORTD |= (1 << HALL_PIN);      // Pull-up interne activée
    EICRA |= (1 << ISC01);         // Front descendant
    EIMSK |= (1 << INT0);          // Active INT0
    DDRD |= (1 << LED_PIN);        // LED en sortie
}

ISR(INT0_vect) {
    PORTD ^= (1 << LED_PIN);       // Toggle LED à chaque détection
}

int main() {
    HallSensor_Init();
    sei();                         // Active les interruptions globales
    while (1) {}                   // Boucle vide
}
