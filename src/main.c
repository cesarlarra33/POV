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

    while (1) {
        if (uart_msg_ready) {
            uart_msg_ready = 0;
            uart_putstring("Message reçu : ");
            uart_putstring((char*)uart_received_buffer);
            uart_putstring("\n");
        }
    }
    return 0;
}
