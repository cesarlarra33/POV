#ifndef IMAGE_H
#define IMAGE_H

#include <avr/pgmspace.h>
#include "pattern.h"

// Déclaration externe du tableau stocké en mémoire programme (PROGMEM)
extern const pattern_t image_pattern[] PROGMEM;

#endif