#ifndef CLOCK_H
#define CLOCK_H

#include "utils.h"
#include "hall_sensor.h"
#include "MBI5024.h"
#include "clock_template.h"
#include "clock_rounded.h"
#include <avr/pgmspace.h>
#include <avr/io.h>

// Vecteur d'interruption utilisé pour cadencer la mise à jour de l'heure
#define CLOCK_INT TIMER2_OVF_vect

// Paramétrage du Timer2 pour générer une base de temps lente (~1 seconde)
#define TIMER2_PRESCALER 1024UL

// Calcule la durée en cycles d'un overflow du Timer2
#define TIMER2_OVF_DEN   (TIMER2_PRESCALER * 256UL)
#define OVF_PER_S        ((uint16_t)((F_CPU + (TIMER2_OVF_DEN / 2UL)) / TIMER2_OVF_DEN))


// struct qui sert à stocker le temps actuel, initialisé à h0, m0, s0
typedef struct {
	uint8_t hours;
	uint8_t minutes;
	uint8_t seconds;
} time_t;

// enum qui sert à indiquer quelle type de clock on veut afficher
enum clocks {
	ANALOG, 
	ROUNDED_D,
	DIGITAL
}; 

// variable qui indique quel style de clock on affiche 
// volatile car sera modifée par l'interrupt uart quand elle appelle le handler 
extern volatile int current_clock_style; 


// Volatiles car toutes ces variables sont modifiées par l'interruption
extern volatile time_t current_time;
extern volatile uint8_t second_elapsed;
extern volatile uint8_t clock_dirty;
#define CLOCK_PATTERN_SIZE 120 // (ou la vraie taille de ton template, à ajuster)
extern pattern_t clock_pattern_buffer[CLOCK_PATTERN_SIZE];

void init_clock();
void update_clock();
void superpose_aiguille(const pattern_t *aiguille_pattern, uint8_t aiguille_length, uint8_t aiguille_thickness, int target_index);
void start_clock();
void set_clock_time(uint8_t hour, uint8_t minute); 

#endif