#include "utils.h"
#include "hall_sensor.h"
#include "MBI5024.h"


int main(void) {
    set_all_leds_outputs();
    set_HALL_as_input();

    uint16_t full_on_mask = 0;
    for (uint8_t i = 0; i < NB_LEDS; ++i) {
        full_on_mask |= (uint16_t)(1U << i);
    }

    while (1) {
        display_mask_at_angle(full_on_mask, 90U); // refresh the image at 90 degrees
    }

    return 0;
}
