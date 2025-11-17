#include "utils.h"
#include "hall_sensor.h"

void set_all_leds_outputs(void);
void display_buffer_at_angle(uint8_t *buffer, uint32_t angle_deg);

int main(void) {
    set_all_leds_outputs();
    set_HALL_as_input();

    static uint8_t full_on_buffer[NB_LEDS];
    for (uint8_t i = 0; i < NB_LEDS; ++i) {
        full_on_buffer[i] = 1U;
    }
    while (1) {
        display_buffer_at_angle(full_on_buffer, 90U); // refresh the image at 90 degrees
    }

    return 0;
}
