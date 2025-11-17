#ifndef PATTERN_H
#define PATTERN_H

#include <stdint.h>
#include "utils.h"

typedef struct {
    uint16_t angle; // angle logique en degrés
    uint16_t mask;  // bit i -> LED i (1 = allumé)
} pattern_t;

#define PATTERN_DICT_SIZE 1

extern const pattern_t pattern_dict[PATTERN_DICT_SIZE];

#endif
