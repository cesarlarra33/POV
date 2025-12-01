#ifndef CLOCK_H
#define CLOCK_H

#include "utils.h"
#include "hall_sensor.h"
#include "MBI5024.h"
#include "speedometer.h"
#include "image.h"

#include <avr/pgmspace.h>
#include <avr/io.h>

// Vecteur d'interruption utilisé pour cadencer la mise à jour de l'heure
#define CLOCK_INT TIMER2_OVF_vect

// Le timer 2 va s'incrémenter à F_CPU/ 1024
#define TIMER2_PRESCALER 1024UL

// Calcule la durée en cycles d'un overflow du Timer2
#define CYCLE_PAR_OVF   (TIMER2_PRESCALER * 256UL)
// nombre d'overflow du timer2 par seconde. 
// le fait qu'on a ovf_per_s = (f_cpu + c_per_ovf / 2) / cycle_per_ovf,
// en ajoutant la moitié du diviseur avant de diviser on force l'arrondi fait par 
// le cast en uint16_t à l'entier el plus proche
#define OVF_PER_S        ((uint16_t)((F_CPU + (CYCLE_PAR_OVF / 2UL)) / CYCLE_PAR_OVF))

// nombre de pattern_t qu'il y a dans le tableau template du cadran
#define CLOCK_PATTERN_SIZE 120 

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
	DIGITAL, 
	SPEEDOMETER, 
	IMAGE
}; 

// variable qui indique quel style de clock on affiche 
// volatile car sera modifée par l'interrupt uart quand elle appelle le handler 
extern volatile int current_clock_style; 

// pointeur vers le pattern_t de l'affichage courant, initialisé dans le .c à &analog_clock_pattern_buffer[CLOCK_PATTERN_SIZE];
// c.a.d le pattern de la clock digitale volatile car là ou il pointe sera changé dans le handler uart
// en fonction de la commande recue 
extern volatile pattern_t *current_pattern; 


// Volatiles car toutes ces variables sont modifiées par l'interruption
extern volatile time_t current_time;
extern volatile uint8_t second_elapsed;
extern volatile uint8_t clock_dirty;
// pattern courant en ram dans lequel onviendra copier les templates de PROGMEM
extern pattern_t display_pattern_buffer[CLOCK_PATTERN_SIZE];

// Templates en PROGMEM
extern const pattern_t analog_clock_base_pattern[CLOCK_PATTERN_SIZE] PROGMEM;
extern const pattern_t rounded_clock_base_pattern[CLOCK_PATTERN_SIZE] PROGMEM;

/// @brief charge dans le buffer d'affichage le template stocké en PROGMEM
/// @param template_progmem le template à charger
void load_template(const pattern_t *template_progmem);

/// @brief initialise le timer et les variables de l'horloge
void init_clock();

/// @brief met à jour l'affichage de l'horloge en fonction du style courant
void update_clock(int clock_style);

/// @brief démarre la boucle principale de l'horloge
void start_clock();

/// @brief règle l'heure de l'horloge
/// @param hour l'heure (0-23)
/// @param minute la minute (0-59)
void set_clock_time(uint8_t hour, uint8_t minute); 

/// @brief renvoie l'index du pattern dont l'angle est le plus proche de target_angle (0..359)
/// @param table le tableau de pattern_t à chercher
/// @param size la taille du tableau
/// @param target_angle l'angle cible
int find_index_by_angle_nearest(const pattern_t *table, int size, int target_angle);

#endif