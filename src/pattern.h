#ifndef PATTERN_H
#define PATTERN_H

#include <stdint.h>
/*
typedef struct {
    uint16_t angle;
    uint8_t buffer[16];
} pattern_t;
*/

typedef struct {
    uint8_t buffer[2];
    uint16_t angle_start;    // angle de début (en degrés)
    uint16_t angle_end;      // angle de fin (en degrés)
} pattern_t;

extern pattern_t pattern_dict[];
extern const int PATTERN_DICT_SIZE;

#endif