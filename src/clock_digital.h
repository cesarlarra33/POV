#ifndef CLOCK_DIGITAL_H
#define CLOCK_DIGITAL_H

#include "pattern.h"

#define THETA_RESOLUTION 120 // nombre de pattenr_t pour faire un tour complet (360°)

#define CARTESIAN_DIGIT_HEIGHT 12
#define CARTESIAN_DIGIT_WIDTH 10

// struct qui sert à décrire une position cartésienne
typedef struct {
    uint8_t x;
    int8_t y;
} cartesian_point_t;

extern const cartesian_point_t hour_tens_pos;
extern const cartesian_point_t hour_units_pos;
extern const cartesian_point_t min_hour_pos;
extern const cartesian_point_t min_units_pos;

#define MATRIX_SIZE 2 * NB_LEDS
// Matrice de pixels pour l'affichage digital (0 = éteint, 1 = allumé)
extern const uint8_t cartesian_pixel_matrix[MATRIX_SIZE][MATRIX_SIZE] PROGMEM;

// matrices de bits pour la réprésentation cartésienne des digits 0-9
extern const uint8_t digit_0[CARTESIAN_DIGIT_HEIGHT][CARTESIAN_DIGIT_WIDTH]; 
extern const uint8_t digit_1[CARTESIAN_DIGIT_HEIGHT][CARTESIAN_DIGIT_WIDTH]; 
extern const uint8_t digit_2[CARTESIAN_DIGIT_HEIGHT][CARTESIAN_DIGIT_WIDTH]; 
extern const uint8_t digit_3[CARTESIAN_DIGIT_HEIGHT][CARTESIAN_DIGIT_WIDTH]; 
extern const uint8_t digit_4[CARTESIAN_DIGIT_HEIGHT][CARTESIAN_DIGIT_WIDTH]; 
extern const uint8_t digit_5[CARTESIAN_DIGIT_HEIGHT][CARTESIAN_DIGIT_WIDTH]; 
extern const uint8_t digit_6[CARTESIAN_DIGIT_HEIGHT][CARTESIAN_DIGIT_WIDTH]; 
extern const uint8_t digit_7[CARTESIAN_DIGIT_HEIGHT][CARTESIAN_DIGIT_WIDTH]; 
extern const uint8_t digit_8[CARTESIAN_DIGIT_HEIGHT][CARTESIAN_DIGIT_WIDTH]; 
extern const uint8_t digit_9[CARTESIAN_DIGIT_HEIGHT][CARTESIAN_DIGIT_WIDTH]; 
// tableau de pointeurs vers les digits cartésiens
extern const uint8_t* cartesian_digits[10];

// pattern_t de l'affichage digital courant dans lequel on viendra coller la conversion cartésienne / polaire 
// de la matrice de pixels, elle en PROGMEM
pattern_t digital_clock_pattern[THETA_RESOLUTION];

/// @brief fonction de maj de l'affichage digital
void update_digital_clock();

#endif