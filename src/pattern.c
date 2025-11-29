#include <avr/pgmspace.h>

#include "pattern.h"

#define FULL_ON_MASK 0xFFFFU
#define FULL_ON_ANGLE_DEG 90U

const pattern_t pattern_dict[PATTERN_DICT_SIZE] PROGMEM = {
    { FULL_ON_ANGLE_DEG, FULL_ON_MASK }
};