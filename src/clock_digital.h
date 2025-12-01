#ifndef CLOCK_DIGITAL_H
#define CLOCK_DIGITAL_H

#include "pattern.h"

#define THETA_RESOLUTION 120// nombre de pattenr_t pour faire un tour complet (360°)

#define CARTESIAN_DIGIT_HEIGHT 16
#define CARTESIAN_DIGIT_WIDTH 16

// struct qui sert à décrire une position cartésienne
typedef struct {
    int8_t x;
    int8_t y;
} cartesian_point_t;

// positionsn des digits réprésentants les unités/dizaines des heures/minutes
extern const cartesian_point_t hour_tens_pos;
extern const cartesian_point_t hour_units_pos;
extern const cartesian_point_t min_hour_pos;
extern const cartesian_point_t min_units_pos;



// pattern_t de l'affichage digital courant dans lequel on viendra coller la conversion cartésienne / polaire 
// des digits dessinés en cartésien 
extern pattern_t digital_clock_pattern[THETA_RESOLUTION];

/// @brief fonction de maj de l'affichage digital
void update_digital_clock();

#endif