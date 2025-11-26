#include "utils.h"
#include "hall_sensor.h"
#include "MBI5024.h"
#include "clock.h"
#include "clock_template.h"
#include "uart.h"
#include <avr/io.h>


int main(void) {
    

    uart_init(MYUBRR);
    set_all_leds_outputs();

    

    set_all_leds_outputs();
    set_HALL_as_input(); 
    start_clock(); 

    return 0;
}
