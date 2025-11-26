#include "MBI5024.h"
#include "hall_sensor.h"
#include "pattern.h"

int main(void) {
    // Initialisation des LEDs et du capteur Hall
    set_all_leds_outputs();
    set_HALL_as_input();
    
    // Boucle principale : afficher les patterns en fonction de l'angle
    while(1) {
        display_patterns(pattern_dict, 16);
    }

    return 0; // jamais atteint
}