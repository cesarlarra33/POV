#include <avr/io.h>
#include <util/delay.h>

#define LED PD6      
#define DELAY_MS 500  

int main(void) {
    
    DDRD |= (1 << LED);

    while (1) {
        
        PORTD |= (1 << LED);
        _delay_ms(DELAY_MS);

        
        PORTD &= ~(1 << LED);
        _delay_ms(DELAY_MS);
    }

    return 0;
}
