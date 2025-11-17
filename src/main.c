#include "utils.h"
#include "hall_sensor.h"
#include "MBI5024.h"
#include "clock_template.h"


int main(void) {
    set_all_leds_outputs();
    set_HALL_as_input();

    while (1) {
        display_patterns(clock_base_pattern, (uint16_t)CLOCK_PATTERN_SIZE);
    }

    return 0;
}
