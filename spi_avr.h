#ifndef SPI_AVR_H
#define SPI_AVR_H
#include <stdint.h>
void spi_init(uint8_t mode, uint8_t clk_div); // mode 0..3 ; clk_div: 2,4,8,16,32,64,128
void spi_send_byte(uint8_t v);
#endif
