#include "MBI5024.h"
#include "utils.h"

// configure l'horloge comme une sortie 
void set_CLOCK_as_output(){
    set_as_output(&DDRB, CLOCK); 
    set_pin(&PORTB, CLOCK, 0); //on force l'horloge à zéro 
}

// configure SDI (serial data input) comme une sortie 
void set_SDI_as_output(){
    set_as_output(&DDRB, SDI); 
}

// configure OE (output terminal) comme une sortie 
void set_OE_as_output(){
    set_as_output(&DDRC, OE); 
    set_OE(0); // on l'active par défaut, et il est activé quand à zéro d'après la doc 
}

// configure LE comme une sortie 
void set_LE_as_ouput(){
    DDRC |= (1<<PC2); // Met le pin 2 de DDRC en sorti
    set_LE(0); // au cas ou on desactive la sortie
}

// configure tous les outputs necessaires d'un coup : 
void set_all_leds_outputs(){
    set_CLOCK_as_output(); 
    set_SDI_as_output(); 
    set_OE_as_output(); 
    set_LE_as_ouput(); 
}

// front montant sur l'horloge 
void CLOCK_UP(){
    set_pin(&PORTB,CLOCK, 1); 
}

// front descendant sur l'horloge
void CLOCK_DOWN(){
    set_pin(&PORTB, CLOCK, 0); 
}

// met sdi en haut (1) ou en bas (0) pour dire si on allume cette led ou pas 
void set_SDI(int up_down){
    if(up_down){
        set_pin(&PORTB,SDI,1);
    }
    else {
        set_pin(&PORTB,SDI,0);
    }
}

// met OE en haut (1) ou en bas (0)
void set_OE(int up_down){
    if(up_down){
        set_pin(&PORTC,OE,1);
    }
    else {
        set_pin(&PORTC,OE,0);
    }
}

// met LE en haut (1) ou en bas (0)
void set_LE(int up_down){
    if(up_down){
        set_pin(&PORTC,LE,1);
    }
    else {
        set_pin(&PORTC,LE,0);
    }
}

// eclaire les leds selon un pattern buffer. ex : {1,1,1,1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0 ,0 ,0}
void display_buffer(int *buffer){
    set_OE(1); // on coupe temporairement la sortie (OE actif à 0)
    for(int i = 0; i < 16; i++){
        set_SDI(buffer[i]);
        CLOCK_UP(); 
        CLOCK_DOWN(); 
    }
    set_LE(1);
    delay(1);
    set_LE(0);
    set_OE(0);
}
 