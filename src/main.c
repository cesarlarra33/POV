#include "utils.h"
#include "hall_sensor.h"
#include "MBI5024.h"
#include "clock.h"
#include "clock_template.h"
#include "uart.h"
#include "heart_pattern.h"
#include <avr/io.h>


void start_heart_animation(){
    // Initialisation basique (LEDs en sortie, interruption Hall)
    set_all_leds_outputs();
    set_HALL_as_input();
    
    // On active les interruptions globalement
    sei();

    while(1){
        // 1. Attendre le signal de nouvelle rotation (capteur Hall)
        // La variable 'new_rotation' est mise à 1 par l'ISR(HALL_INT)
        while(!new_rotation) {}
        
        // 2. Afficher le motif
        // Cette fonction (déjà présente dans ton code) gère le timing angulaire
        display_patterns(heart_pattern, HEART_PATTERN_SIZE);
    }
}

int main(void) {
    

    uart_init(MYUBRR);
    /*
    set_all_leds_outputs();

    

    set_all_leds_outputs();
    set_HALL_as_input(); 
    start_clock(); 
    */
    start_heart_animation();

    return 0;
}