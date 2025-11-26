#include <avr/pgmspace.h>

#include "pattern.h"

#define FULL_ON_MASK 0xFFFFU
#define FULL_ON_ANGLE_DEG 90U


const pattern_t pattern_dict[PATTERN_DICT_SIZE] PROGMEM = {
// FOND NOIR (On n'affiche rien)
    { .angle = 0, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0) },

    // DEBUT DU DIAMANT (Pointe)
    // On allume juste le bit tout à la fin (le plus au centre)
    { .angle = 10, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1) },
    
    // ON ELARGIT (3 pixels au centre)
    { .angle = 15, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1) },
    
    // LE PLUS LARGE (5 pixels au centre)
    { .angle = 20, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1) },
    
    // ON REFERME (3 pixels)
    { .angle = 25, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1) },
    
    // FIN DU DIAMANT (Pointe)
    { .angle = 30, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1) },

    // FOND NOIR
    { .angle = 40, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0) }
};
