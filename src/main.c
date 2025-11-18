#include "utils.h"
#include "hall_sensor.h"
#include "MBI5024.h"
#include "clock.h"
#include "clock_template.h"


int main(void) {
    set_all_leds_outputs();
    set_HALL_as_input();

    

    start_clock(14,4); 

    return 0;
}
