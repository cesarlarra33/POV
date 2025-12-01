#ifndef CLOCK_ROUNDED_H
#define CLOCK_ROUNDED_H

#include "pattern.h"
#include "pattern.h"
#include "clock.h"

// tableau de pattern_t de la même taille que le cedran de clock pck ca fonctionnait bien
// stocké en PROGMEM 
extern const pattern_t rounded_clock_base_pattern[CLOCK_PATTERN_SIZE] PROGMEM;

// largeurs des tableaux stocké en progmem pourla fore de chaque chiffre 
#define COLUN_WIDTH 5
#define NUMBER_WIDTH 7

// largeur des lettres (l sera plus etroit que w)
#define LETTER_WIDTH 4
#define THIN_LETTER_WIDTH 3
#define WIDE_LETTER_WIDTH 5

// plage d'angles sur laquelle on peut placer des lettres [83°-> 0°] u [0°->276°]
#define LETTER_START_ANGLE 83 
#define LETTER_END_ANGLE 276


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

// enum pour accéder aux lettres de l'alphabet
typedef enum {
    CHAR_A = 0,
    CHAR_B,
    CHAR_C,
    CHAR_D,
    CHAR_E,
    CHAR_F,
    CHAR_G,
    CHAR_H,
    CHAR_I,
    CHAR_J,
    CHAR_K,
    CHAR_L,
    CHAR_M,
    CHAR_N,
    CHAR_O,
    CHAR_P,
    CHAR_Q,
    CHAR_R,
    CHAR_S,
    CHAR_T,
    CHAR_U,
    CHAR_V,
    CHAR_W,
    CHAR_X,
    CHAR_Y,
    CHAR_Z,

    ALPHABET_SIZE
} alphabet_index_t;

// structure pour stocker un pointeur vers un pattern_t et sa largeur
// servira à acceder plus facilement aux patterns des lettres. 
typedef struct {
    const pattern_t* pattern;   
    uint8_t width;              
} letter_entry_t;

// paramètres du message à afficher
#define MAX_MESSAGE_LENGTH 9
extern volatile char message_buffer[MAX_MESSAGE_LENGTH]; // buffer du message courant
extern volatile uint8_t new_message; // sert à indiquer qu'un nouveau message est dispo
extern volatile uint8_t current_message_active; // sert à que le current_msg ne disparaisse à chaque refresh

#define NUM_SYMBOLS 11 // 10 chiffres + ":"

//tableau de pointeurs vers les symboles
extern const pattern_t* symbol_patterns[NUM_SYMBOLS];

// indexs où doivent se trouver chaque chiffres
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