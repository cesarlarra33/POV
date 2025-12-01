#include "clock_digital.h"
#include "clock.h"
#include <stdint.h>
#include "digits.h"


#if (THETA_RESOLUTION % 4) != 0
# error "THETA_RESOLUTION doit être un multiple de 4"
#endif

#define QUART_SIZE (THETA_RESOLUTION / 4)

// pattern_t de l'affichage digital courant dans lequel on viendra coller
// les digits en fonction de leur position.
pattern_t digital_clock_pattern[THETA_RESOLUTION] = {0};


void update_digital_clock(void) {
    static uint8_t last_minute = 255;// valeur impossible comme ca on force le 1er update

    uint8_t hour   = current_time.hours;
    uint8_t minute = current_time.minutes;

    // on recalcuule que si les min ont changé car on affiche pas les secondes icit
    if (minute == last_minute) {
        return;
    }
    last_minute = minute;

    uint8_t h_tens  = hour   / 10;
    uint8_t h_units = hour   % 10;
    uint8_t m_tens  = minute / 10;
    uint8_t m_units = minute % 10;

    // tableaux de pointeurs pour chaque quart du tour
    const pattern_t* digit_quart_HG[10] = {
        number_0_Q1, number_1_Q1, number_2_Q1, number_3_Q1, number_4_Q1,
        number_5_Q1, number_6_Q1, number_7_Q1, number_8_Q1, number_9_Q1
    };
    const pattern_t* digit_quart_BG[10] = {
        number_0_Q2, number_1_Q2, number_2_Q2, number_3_Q2, number_4_Q2,
        number_5_Q2, number_6_Q2, number_7_Q2, number_8_Q2, number_9_Q2
    };
    const pattern_t* digit_quart_BD[10] = {
        number_0_Q3, number_1_Q3, number_2_Q3, number_3_Q3, number_4_Q3,
        number_5_Q3, number_6_Q3, number_7_Q3, number_8_Q3, number_9_Q3
    };
    const pattern_t* digit_quart_HD[10] = {
        number_0_Q4, number_1_Q4, number_2_Q4, number_3_Q4, number_4_Q4,
        number_5_Q4, number_6_Q4, number_7_Q4, number_8_Q4, number_9_Q4
    };

    

    // on va copier les bon tableaux de patterns dans digital_clock_pattern, aux bon indices correspondant aux quarts. 
    memcpy_P(&digital_clock_pattern[0 * QUART_SIZE],
             digit_quart_HG[h_tens],
             QUART_SIZE * sizeof(pattern_t)); // Nord→Ouest

    memcpy_P(&digital_clock_pattern[1 * QUART_SIZE],
             digit_quart_BG[m_tens],
             QUART_SIZE * sizeof(pattern_t)); // Ouest→Sud

    memcpy_P(&digital_clock_pattern[2 * QUART_SIZE],
             digit_quart_BD[m_units],
             QUART_SIZE * sizeof(pattern_t)); // Sud→Est

    memcpy_P(&digital_clock_pattern[3 * QUART_SIZE],
             digit_quart_HD[h_units],
             QUART_SIZE * sizeof(pattern_t)); // Est→Nord

}
