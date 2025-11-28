/*
#include <avr/pgmspace.h>

#include "pattern.h"

#define FULL_ON_MASK 0xFFFFU
#define FULL_ON_ANGLE_DEG 90U


const pattern_t pattern_dict[PATTERN_DICT_SIZE] PROGMEM = {
// Pointe du coeur (Angle 0)
    { .angle = 0,   .mask = MASK16(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1) },
    
    // Coté droit
    { .angle = 5,   .mask = MASK16(0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0) },
    { .angle = 10,  .mask = MASK16(0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0) },
    { .angle = 20,  .mask = MASK16(0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0) },
    { .angle = 30,  .mask = MASK16(0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0) },
    { .angle = 40,  .mask = MASK16(0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0) },
    
    // Le haut (les deux bosses)
    { .angle = 60,  .mask = MASK16(0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0) },
    { .angle = 70,  .mask = MASK16(0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0) },
    { .angle = 80,  .mask = MASK16(0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0) },
    
    // Le creux du haut
    { .angle = 90,  .mask = MASK16(0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0) },
    
    // Symétrie (Coté gauche) - Je simplifie, on va juste afficher un demi-coeur
    // pour voir si ça marche déjà. Si tu vois une moitié de coeur, c'est gagné.
};
*/