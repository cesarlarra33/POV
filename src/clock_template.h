#ifndef CLOCK_TEMPLATE_H
#define CLOCK_TEMPLATE_H

#include <avr/pgmspace.h>
#include "pattern.h"

// macro qui convertit 16 bits individuels en un masque 16 bits
// se fait a la compilation donc coute pas + cher à l'exec 
// comment ca marche :
// !! convertit en booléen (0 ou 1) 
// puis les 16 bits sont castés en uint16_t et décalés à leur position respective
#ifndef MASK16
#define MASK16(b0,b1,b2,b3,b4,b5,b6,b7,b8,b9,b10,b11,b12,b13,b14,b15) \
    (uint16_t)( \
        ((uint16_t)(!!(b0))  << 0)  | ((uint16_t)(!!(b1))  << 1)  | \
        ((uint16_t)(!!(b2))  << 2)  | ((uint16_t)(!!(b3))  << 3)  | \
        ((uint16_t)(!!(b4))  << 4)  | ((uint16_t)(!!(b5))  << 5)  | \
        ((uint16_t)(!!(b6))  << 6)  | ((uint16_t)(!!(b7))  << 7)  | \
        ((uint16_t)(!!(b8))  << 8)  | ((uint16_t)(!!(b9))  << 9)  | \
        ((uint16_t)(!!(b10)) << 10) | ((uint16_t)(!!(b11)) << 11) | \
        ((uint16_t)(!!(b12)) << 12) | ((uint16_t)(!!(b13)) << 13) | \
        ((uint16_t)(!!(b14)) << 14) | ((uint16_t)(!!(b15)) << 15))
#endif

extern const pattern_t hour_aiguille[] PROGMEM;
extern const pattern_t min_aiguille[] PROGMEM;
extern const pattern_t second_aiguille[] PROGMEM;

extern const uint8_t HOUR_AIGUILLE_LENGTH;
extern const uint8_t HOUR_AIGUILLE_THICKNESS;
extern const uint8_t MINUTE_AIGUILLE_LENGTH;
extern const uint8_t MINUTE_AIGUILLE_THICKNESS;
extern const uint8_t SECOND_AIGUILLE_LENGTH;
extern const uint8_t SECOND_AIGUILLE_THICKNESS;

extern const pattern_t clock_base_pattern[] PROGMEM;
extern const int CLOCK_PATTERN_SIZE;

#endif