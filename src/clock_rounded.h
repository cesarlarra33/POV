#ifndef CLOCK_ROUNDED_H
#define CLOCK_ROUNDED_H

#include "pattern.h"

int find_index_by_angle_nearest(const pattern_t *table, int size, int target_angle);



#include "pattern.h"
#include "clock.h"


// tableau de pattern_t de la même taille que le cedran de clock pck ca fonctionnait bien
// stocké en PROGMEM 
extern const pattern_t rounded_clock_base_pattern[CLOCK_PATTERN_SIZE] PROGMEM;

// largeurs des tableaux stocké en progmem pourla fore de chaque chiffre 
#define COLUN_WIDTH 5
#define NUMBER_WIDTH 7


// tableaux de pattern_t correspondant aux chiffres et aux ":"
// tous en progmem
extern const pattern_t colon_pattern[] PROGMEM;
extern const pattern_t number_0[] PROGMEM;
extern const pattern_t number_1[] PROGMEM;
extern const pattern_t number_2[] PROGMEM;
extern const pattern_t number_3[] PROGMEM;
extern const pattern_t number_4[] PROGMEM;
extern const pattern_t number_5[] PROGMEM;
extern const pattern_t number_6[] PROGMEM;
extern const pattern_t number_7[] PROGMEM;
extern const pattern_t number_8[] PROGMEM;
extern const pattern_t number_9[] PROGMEM; 

// enum à utiliser comme index dans le tableau de pointeurs ci dessous. 
enum SYMBOLS {
    ZERO,
    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    COLON
};

#define NUM_SYMBOLS 11

//tableau de pointeurs vers les symboles
extern const pattern_t* symbol_patterns[NUM_SYMBOLS];

// index où doivent se trouver chaque chiffres
#define HOUR_TENS_IDX 93
#define HOUR_UNITS_IDX (HOUR_TENS_IDX + NUMBER_WIDTH)

#define COLON1_IDX (HOUR_UNITS_IDX + NUMBER_WIDTH)

#define MIN_TENS_IDX (COLON1_IDX + COLUN_WIDTH)
#define MIN_UNITS_IDX (MIN_TENS_IDX + NUMBER_WIDTH)

#define COLON2_IDX (MIN_UNITS_IDX + NUMBER_WIDTH)

#define SEC_TENS_IDX (COLON2_IDX + COLUN_WIDTH)
#define SEC_UNITS_IDX (SEC_TENS_IDX + NUMBER_WIDTH)

/// @brief fonction de mise à jour de la clock rounded. 
void update_rounded_d_clock(); 


#endif 