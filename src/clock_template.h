
#ifndef CLOCK_TEMPLATE_H
#define CLOCK_TEMPLATE_H

#include "clock.h"
#include <avr/pgmspace.h>
#include "pattern.h"


extern const pattern_t hour_aiguille[] PROGMEM;
extern const pattern_t min_aiguille[] PROGMEM;
extern const pattern_t second_aiguille[] PROGMEM;

extern const uint8_t HOUR_AIGUILLE_LENGTH;
extern const uint8_t HOUR_AIGUILLE_THICKNESS;
extern const uint8_t MINUTE_AIGUILLE_LENGTH;
extern const uint8_t MINUTE_AIGUILLE_THICKNESS;
extern const uint8_t SECOND_AIGUILLE_LENGTH;
extern const uint8_t SECOND_AIGUILLE_THICKNESS;

extern const pattern_t analog_clock_base_pattern[CLOCK_PATTERN_SIZE] PROGMEM;


#endif
