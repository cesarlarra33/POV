#ifndef MBI5024_H
#define MBI5024_H
#include <stdint.h>
#include <stdbool.h>
void mbi5024_init(void);                // configure OE, LE + SPI
void mbi5024_display_enable(bool on);   // on=true -> OE=0 (affiche)
void mbi5024_write16(uint16_t bits);    // shift 16 bits + latch
#endif
