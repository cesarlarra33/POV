#include "utils.h"
#include "hall_sensor.h"
#include "MBI5024.h"
#include "clock.h"
#include "clock_template.h"
#include "uart.h"
#include <avr/io.h>


int main(void) {
    char etat = 0; // 0 = éteint, 1 = allumé

    uart_init(MYUBRR);
    set_all_leds_outputs();

    /* while (1) {
        if (uart_msg_ready) {
            uart_msg_ready = 0;
            uart_putstring("Message reçu : ");
            uart_putstring((char*)uart_received_buffer);
            uart_putstring("\n");
        }
    } */

    set_all_leds_outputs();
    set_HALL_as_input(); 
    start_clock(10,10); 

    return 0;
}
