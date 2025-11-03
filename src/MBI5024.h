#ifndef MBI5024_H
#define MBO5024_H

#include <avr/io.h>
#include "utils.h"

#define CLOCK PB5
#define SDI PB3
#define OE PC1
#define LE PC2

// configure l'horloge comme une sortie 
void set_CLOCK_as_output(); 

// configure SDI (serial data input) comme une sortie 
void set_SDI_as_output(); 

// configure OE (output terminal) comme une sortie 
void set_OE_as_output(); 

// configure LE comme une sortie 
void set_LE_as_ouput(); 

// configure tous les outputs necessaires d'un coup : 
void set_all_leds_outputs(); 

// front montant sur l'horloge 
void CLOCK_UP(); 

// front descendant sur l'horloge
void CLOCK_DOWN(); 

void set_SDI(int on_off); 

void set_OE(int on_off); 

void set_LE(int on_off);

void display_buffer(int *buffer); 



#endif 