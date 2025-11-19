#include "utils.h"
#include "hall_sensor.h"
#include "MBI5024.h"
#include "clock.h"
#include "clock_template.h"
#include "uart.h"
#include <avr/io.h>


int main(void) {
    /* char etat = 0; // 0 = éteint, 1 = allumé

    USART_Init(MYUBRR);
    set_all_leds_outputs();

    while (1) {
        // Affiche en continu l'état courant
        if (etat == 0) {
            display_mask(0x0000); // LEDs éteintes
        } else {
            display_mask(0xFFFF); // LEDs allumées
        }
        // Vérifie s'il y a un message reçu (bloquant)
        if (USART_Receive()) {
            etat = !etat; // Inverse l'état à chaque message
        }
    } */

    set_all_leds_outputs();
    set_HALL_as_input(); 
    start_clock(10,10); 

    return 0;
}
