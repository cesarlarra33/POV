#include <avr/io.h>
#include <util/delay.h>
#include "spi_avr.h"
#include "mbi5024.h"

// Broches de contrôle sur PORTC
#define MBI_LE_PORT   PORTC
#define MBI_LE_DDR    DDRC
#define MBI_LE_PIN    PC2

#define MBI_OE_PORT   PORTC
#define MBI_OE_DDR    DDRC
#define MBI_OE_PIN    PC1  // actif bas

static inline void le_high(void){ MBI_LE_PORT |=  (1<<MBI_LE_PIN); }
static inline void le_low(void) { MBI_LE_PORT &= ~(1<<MBI_LE_PIN); }
static inline void oe_high(void){ MBI_OE_PORT |=  (1<<MBI_OE_PIN); }
static inline void oe_low(void) { MBI_OE_PORT &= ~(1<<MBI_OE_PIN); }

void mbi5024_init(void){
    // LE, OE en sortie
    MBI_LE_DDR |= (1<<MBI_LE_PIN);
    MBI_OE_DDR |= (1<<MBI_OE_PIN);
    le_low();
    oe_high(); // masquer au démarrage

    // SPI mode 0, F_CPU/4 ≈ 3.25 MHz (F_CPU=13 MHz)
    spi_init(0, 4);

    // Tout éteint au départ
    mbi5024_write16(0x0000);
    mbi5024_display_enable(true);
}

void mbi5024_display_enable(bool on){
    if(on) oe_low(); else oe_high();
}

void mbi5024_write16(uint16_t bits){
    oe_high(); // masquer pendant la mise à jour
    uint8_t hi = (uint8_t)(bits >> 8);
    uint8_t lo = (uint8_t)(bits & 0xFF);

    // MBI5024 attend MSB d'abord → hi puis lo
    spi_send_byte(hi);
    spi_send_byte(lo);

    // Latch
    le_high();
    _delay_us(1);
    le_low();

    oe_low();  // afficher
}
