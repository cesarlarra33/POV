/*
#ifndef PATTERN_H
#define PATTERN_H

#include <stdint.h>
#include <avr/pgmspace.h>

#include "utils.h"

typedef struct {
    int16_t angle;  // angle logique en degrés (peut inclure de petits offsets négatifs)
    uint16_t mask;  // bit i -> LED i (1 = allumé)
} pattern_t;

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

#define PATTERN_DICT_SIZE 10

extern const pattern_t pattern_dict[PATTERN_DICT_SIZE] PROGMEM;

#endif
*/