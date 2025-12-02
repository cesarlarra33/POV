#ifndef THETA_RESOLUTION
#define THETA_RESOLUTION 120
#endif
#define QUART_SIZE (THETA_RESOLUTION / 4)
#include "speedometer.h"
#include <stdlib.h>
#include <avr/pgmspace.h>

#define PRESCALER_HALL 64U

// On suppose THETA_RESOLUTION et QUART_SIZE définis comme dans clock_digital.c
#include "clock_digital.h"
#include "digits.h"
#include <string.h>
#include "clock_rounded.h"


// Version dédiée pour écrire dans digital_clock_pattern
void superpose_symbol_digital(const pattern_t *symbol_pattern, uint8_t pattern_width, int pattern_index) {
    for (uint8_t i = 0; i < pattern_width; i++) {
        int target_index = pattern_index + i;
        if (target_index < 0 || target_index >= THETA_RESOLUTION) continue;
        uint16_t mask = pgm_read_word(&(symbol_pattern[i].mask));
        digital_clock_pattern[target_index].mask |= mask;
    }
}

uint16_t reverse_mask_digital(uint16_t mask) {
    uint16_t result = 0;
    for (int i = 0; i < 16; i++) {
        if (mask & (1 << i)) {
            result |= (1 << (15 - i));
        }
    }
    return result;
}

void superpose_symbol_reversed_digital(const pattern_t *symbol_pattern, uint8_t pattern_width, int pattern_index) {
    for (uint8_t i = 0; i < pattern_width; i++) {
        int target_index = pattern_index + i;
        if (target_index < 0 || target_index >= THETA_RESOLUTION) continue;
        uint16_t mask = pgm_read_word(&(symbol_pattern[pattern_width - 1 - i].mask));
        mask = reverse_mask_digital(mask);
        digital_clock_pattern[target_index].mask |= mask;
    }
}

void superpose_message_digital_buf(const char *message_buffer) {
    char clean_buffer[MAX_MESSAGE_LENGTH];
    uint8_t clean_length = 0;
    for (uint8_t i = 0; i < strlen(message_buffer); ++i) {
        char c = message_buffer[i];
        if ((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) {
            clean_buffer[clean_length++] = c;
        }
    }
    clean_buffer[clean_length] = '\0';

    int angles[clean_length];
    int center_angle = 0;
    int letter_spacing = 20;
    for (int i = 0; i < clean_length; ++i) {
        double offset = ((clean_length - 1) / 2.0 - i) * letter_spacing;
        int angle = (int)(center_angle + offset + 360) % 360;
        angles[i] = angle;
    }

    int idx[clean_length];
    for (int i = 0; i < clean_length; ++i) {
        idx[i] = find_index_by_angle_nearest(digital_clock_pattern, THETA_RESOLUTION, angles[i]);
    }

    for(int i = 0; i < clean_length; ++i){
        char c = clean_buffer[i];
        if (c >= 'a' && c <= 'z') {
            superpose_symbol_digital(
                pgm_read_ptr(&(alphabet[(uint8_t)c - 'a'].pattern)),
                pgm_read_byte(&(alphabet[(uint8_t)c - 'a'].width)),
                idx[i]);
        }
        else if (c >= '0' && c <= '9') {
            extern const pattern_t* symbol_patterns[NUM_SYMBOLS];
            superpose_symbol_reversed_digital(
                symbol_patterns[(uint8_t)c - '0'],
                NUMBER_WIDTH,
                idx[i]);
        }
    }
}


void update_speedometer() {

    
    // réinitialise les bons angles et des masques vides 
    for (int i = 0; i < THETA_RESOLUTION; ++i) {
        digital_clock_pattern[i].angle = (360 * i) / THETA_RESOLUTION;
        digital_clock_pattern[i].mask = 0;
    }

    // calcul de la vitesse en tours par minute
    uint16_t rotation_tick = get_rotation_ticks();
    float tours_par_seconde = ((float)F_CPU / PRESCALER_HALL) / (float)rotation_tick;
    uint8_t tours_par_seconde_int = (uint8_t)(tours_par_seconde);

    // recup les 2 chiffres à afficher
    uint8_t dizaines = tours_par_seconde_int / 10;
    uint8_t unites = tours_par_seconde_int % 10;


    // patterns de digits polaires pour chaque chiffre 
    const pattern_t* digit_quart_BG[10] = { // dizaines en bas à gauche (Ouest→Sud)
        number_0_Q2, number_1_Q2, number_2_Q2, number_3_Q2, number_4_Q2,
        number_5_Q2, number_6_Q2, number_7_Q2, number_8_Q2, number_9_Q2
    };
    const pattern_t* digit_quart_BD[10] = { // unités en bas à droite (Sud→Est)
        number_0_Q3, number_1_Q3, number_2_Q3, number_3_Q3, number_4_Q3,
        number_5_Q3, number_6_Q3, number_7_Q3, number_8_Q3, number_9_Q3
    };

    // Copie les patterns dans le buffer digital
    memcpy_P(&digital_clock_pattern[1 * QUART_SIZE],
             digit_quart_BG[dizaines],
             QUART_SIZE * sizeof(pattern_t)); // Ouest→Sud

    memcpy_P(&digital_clock_pattern[2 * QUART_SIZE],
             digit_quart_BD[unites],
             QUART_SIZE * sizeof(pattern_t)); // Sud→Est

    superpose_message_digital_buf("spe ed"); 
    

    // retour uart pour débug
    char buf[50];
    snprintf(buf, sizeof(buf), "Tours/s: %u\r\n", tours_par_seconde_int);
    uart_putstring(buf);
}