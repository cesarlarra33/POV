//make -f Makefile.windows


// led.c
/*
#include <avr/io.h>
#include <util/delay.h>

void delay(int delay){
    for(int i = 0; i<delay; i++){
        _delay_ms(1); 
    }
}


int main(void)
{
    DDRD |= (1 << PD6); 
    while (1) {
        PORTD &= ~(1 << PD6); 
        delay(200);
        PORTD |= (1 << PD6);
        delay(200);
    }
}



#include <avr/io.h>

int main(void)
{
    DDRB = 0xFF;   
    DDRD = 0xFF;   

    PORTB = 0xFF; 
    PORTD = 0xFF;  

    while (1) {
        
    }

    return 0;
}
    


#include <avr/io.h>
#include <util/delay.h>

// Broches utilisées
#define SDI   PB3
#define CLK    PB5
#define LE     PC2
#define OE     PC1

void init_pins(void){
    DDRC |= (1<<SDI)|(1<<CLK);
    DDRB |= (1<<LE)|(1<<OE);
    PORTB &= ~((1<<SDI)|(1<<CLK));  // initial LOW
    PORTC &= ~(1<<OE);  // OE LOW = LEDs activées
    PORTC &= ~(1<<LE);
}

int buffer[16] = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]

// Envoie 16 bits au MBI5024
void send16(uint16_t value){
    for(int i=15; i>=0; i--){ // MSB first
        if(value & (1<<i))
            PORTB |= (1<<SDI);
        else
            PORTB &= ~(1<<SDI);

        // Pulse CLK
        PORTB |= (1<<CLK);
        _delay_us(1);
        PORTB &= ~(1<<CLK);
    }

    // Latch
    PORTC |= (1<<LE);
}

int main(void){
    init_pins();

    while(1){
        for(int i=15; i>=0; i--){ // MSB first
                PORTB |= (1<<SDI);

                // Pulse CLK
                PORTB |= (1<<CLK);
                _delay_us(1);
                PORTB &= ~(1<<CLK);
                PORTB &= ~(1<<SDI);
            }

        
        // Latch
        PORTC |= (1<<LE);
        _delay_us(1);
        PORTC &= ~(1<<LE);
    }
}

*/

#include <avr/io.h>
#include <util/delay.h>

uint16_t led_buffer = 0;  // 16 bits pour les 16 LEDs

#define SDI   PB3
#define CLK   PB5
#define LE    PC2
#define OE    PC1

void init_pins(void){
    DDRB |= (1<<SDI)|(1<<CLK);
    DDRC |= (1<<LE)|(1<<OE);

    PORTB &= ~((1<<SDI)|(1<<CLK));
    PORTC &= ~(1<<OE);  // OE HIGH = LEDs activées
    PORTC &= ~(1<<LE);
}

// envoie le buffer au MBI5024
void send16(uint16_t buffer){
    for(int i=15; i>=0; i--){
        if(buffer & (1<<i))
            PORTB |= (1<<SDI);
        else
            PORTB &= ~(1<<SDI);

        PORTB |= (1<<CLK);
        _delay_us(10);
        PORTB &= ~(1<<CLK);
    }
    // latch
    PORTC |= (1<<LE);
    _delay_us(1);
    PORTC &= ~(1<<LE);
}

int main(void){
    init_pins();

    while(1){
        led_buffer = 1; // allume toutes les LED paires
        send16(led_buffer);

    }
}
