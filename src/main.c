#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "utils.h"
#include "hall_sensor.h"
#include "MBI5024.h"
#include "pattern.h"

extern const pattern_t heart_pattern[];
extern const int HEART_PATTERN_SIZE;

int main(void) {
    // --- 1. INITIALISATION ---
    
    // Configurer le capteur Hall (Interruption INT0)
    set_HALL_as_input();
    
    // Configurer les pins vers le driver LED
    set_all_leds_outputs();

    // --- 2. SÉQUENCE DE DÉMARRAGE (FEEDBACK VISUEL) ---
    // Cela permet de vérifier que le driver et les LEDs fonctionnent
    // sans avoir besoin de faire tourner le système.
    
    set_OE(0); // Activer la sortie
    
    // Clignote 3 fois rapidement
    for(int i=0; i<3; i++) {
        display_mask(0xFFFF); // Tout Blanc
        _delay_ms(100);
        display_mask(0x0000); // Tout Noir
        _delay_ms(100);
    }
    
    set_OE(1); // Désactiver la sortie en attendant la rotation

    // --- 3. ACTIVATION DES INTERRUPTIONS ---
    // Crucial : Sans ça, ISR(HALL_INT) ne se lancera jamais
    sei(); 

    // --- 4. BOUCLE INFINIE ---
    while (1) {
        // Cette fonction contient sa propre attente "while(!new_rotation)"
        // Elle va attendre le passage de l'aimant, puis afficher toute la liste
        // définie dans pattern.c
        //display_patterns(pattern_dict, PATTERN_DICT_SIZE);
        display_patterns(heart_pattern, HEART_PATTERN_SIZE);
    }

    return 0;
}