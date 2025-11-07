#include <avr/io.h>
#include "spi_avr.h"

static void spi_set_clk_div(uint8_t div){
    uint8_t spcr = SPCR & ~((1<<SPR1)|(1<<SPR0));
    uint8_t spsr = SPSR & ~(1<<SPI2X);
    switch(div){
        case 2:   spsr |= (1<<SPI2X); break;
        case 4:   break;
        case 8:   spsr |= (1<<SPI2X); spcr |= (1<<SPR0); break;
        case 16:  spcr |= (1<<SPR0); break;
        case 32:  spsr |= (1<<SPI2X); spcr |= (1<<SPR1); break;
        case 64:  spcr |= (1<<SPR1); break;
        case 128: spcr |= (1<<SPR1)|(1<<SPR0); break;
        default:  spcr |= (1<<SPR0); break; // /16
    }
    SPCR = (SPCR & ~((1<<SPR1)|(1<<SPR0))) | (spcr & ((1<<SPR1)|(1<<SPR0)));
    SPSR = (SPSR & ~(1<<SPI2X)) | (spsr & (1<<SPI2X));
}

void spi_init(uint8_t mode, uint8_t clk_div){
    DDRB |= (1<<PB3) | (1<<PB5) | (1<<PB2); // MOSI, SCK, SS en sortie
    PORTB |= (1<<PB2);                      // garder SS à 1

    uint8_t cpol = (mode==2 || mode==3) ? 1 : 0;
    uint8_t cpha = (mode==1 || mode==3) ? 1 : 0;

    SPCR = (1<<SPE) | (1<<MSTR) |
           (cpol ? (1<<CPOL):0) |
           (cpha ? (1<<CPHA):0);

    spi_set_clk_div(clk_div);
}

void spi_send_byte(uint8_t v){
    SPDR = v;
    while(!(SPSR & (1<<SPIF))) {;}
    (void)SPDR; // clear SPIF
}
