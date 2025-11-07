#ifndef PATTERN_H
#define PATTERN_H

#include <stdint.h>

typedef struct {
    uint16_t angle;
    uint8_t buffer[16];
} pattern_t;

extern pattern_t pattern_dict[];
extern const int PATTERN_DICT_SIZE;

#endif