#include <util/delay.h>
#include "mbi5024.h"

#define DELAY_MS 300

int main(void){
    mbi5024_init();
    while(1){
        mbi5024_write16(0xFFFF); // toutes ON
        _delay_ms(DELAY_MS);
        mbi5024_write16(0x0000); // toutes OFF
        _delay_ms(DELAY_MS);
    }
}
