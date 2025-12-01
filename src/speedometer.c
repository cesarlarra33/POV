#include "speedometer.h"
#include <stdlib.h>

#define PRESCALER_HALL 64U

void update_speedometer() {
    uint16_t rotation_tick = get_rotation_ticks();

    // on a le nmbre de ticks d'un tour 
    float tours_par_seconde = ((float)F_CPU / PRESCALER_HALL) / (float)rotation_tick;
    char buf[50];
    snprintf(buf, sizeof(buf), "Tours/s: %d\r\n", (int)tours_par_seconde);
    uart_putstring(buf);

}