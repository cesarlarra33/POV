#include "clock_digital.h"
#include "clock.h"

// on initialise la matrice comme 32 lignes de 32 '0'
const uint8_t cartesian_pixel_matrix[MATRIX_SIZE][MATRIX_SIZE] PROGMEM = { {0} };

const uint8_t digit_0[CARTESIAN_DIGIT_HEIGHT][CARTESIAN_DIGIT_WIDTH] PROGMEM = {
    {0,0,1,1,1,1,1,1,0,0},
    {0,1,1,0,0,0,0,1,1,0},
    {1,1,0,0,0,0,0,0,1,1},
    {1,1,0,0,0,0,0,0,1,1},
    {1,1,0,0,0,0,0,0,1,1},
    {1,1,0,0,0,0,0,0,1,1},
    {1,1,0,0,0,0,0,0,1,1},
    {1,1,0,0,0,0,0,0,1,1},
    {1,1,0,0,0,0,0,0,1,1},
    {0,1,1,0,0,0,0,1,1,0},
    {0,0,1,1,1,1,1,1,0,0},
    {0,0,0,0,0,0,0,0,0,0}
};

const uint8_t digit_1[CARTESIAN_DIGIT_HEIGHT][CARTESIAN_DIGIT_WIDTH] PROGMEM = {
    {0,0,0,1,1,1,0,0,0,0},
    {0,0,1,1,1,1,0,0,0,0},
    {0,1,1,0,1,1,0,0,0,0},
    {1,1,0,0,1,1,0,0,0,0},
    {0,0,0,0,1,1,0,0,0,0},
    {0,0,0,0,1,1,0,0,0,0},
    {0,0,0,0,1,1,0,0,0,0},
    {0,0,0,0,1,1,0,0,0,0},
    {0,0,0,0,1,1,0,0,0,0},
    {0,0,0,0,1,1,0,0,0,0},
    {0,0,0,1,1,1,1,0,0,0},
    {0,1,1,1,1,1,1,1,1,0},
};

const uint8_t digit_2[CARTESIAN_DIGIT_HEIGHT][CARTESIAN_DIGIT_WIDTH] PROGMEM = {
    {0,0,1,1,1,1,1,1,0,0},
    {0,1,1,0,0,0,0,1,1,0},
    {1,1,0,0,0,0,0,0,1,1},
    {1,1,0,0,0,0,0,0,1,1},
    {0,0,0,0,0,0,0,1,1,0},
    {0,0,0,0,0,0,1,1,0,0},
    {0,0,0,0,0,1,1,0,0,0},
    {0,0,0,0,1,1,0,0,0,0},
    {0,0,0,1,1,0,0,0,0,0},
    {0,0,1,1,0,0,0,0,0,0},
    {0,1,1,1,1,1,1,1,1,0},
    {0,1,1,1,1,1,1,1,1,0},
};

const uint8_t digit_3[CARTESIAN_DIGIT_HEIGHT][CARTESIAN_DIGIT_WIDTH] PROGMEM = {
    {0,0,1,1,1,1,1,1,0,0},
    {0,1,1,0,0,0,0,1,1,0},
    {1,1,0,0,0,0,0,0,1,1},
    {0,0,0,0,0,0,0,0,1,1},
    {0,0,0,0,0,0,0,1,1,0},
    {0,0,0,0,0,1,1,1,0,0},
    {0,0,0,0,0,0,0,1,1,0},
    {0,0,0,0,0,0,0,0,1,1},
    {1,1,0,0,0,0,0,0,1,1},
    {0,1,1,0,0,0,0,1,1,0},
    {0,0,1,1,1,1,1,1,0,0},
    {0,0,0,0,0,0,0,0,0,0}
};

const uint8_t digit_4[CARTESIAN_DIGIT_HEIGHT][CARTESIAN_DIGIT_WIDTH] PROGMEM = {
    {0,0,0,0,0,1,1,1,0,0},
    {0,0,0,0,1,1,1,1,0,0},
    {0,0,0,1,1,1,1,1,0,0},
    {0,0,1,1,1,0,1,1,0,0},
    {0,1,1,1,0,0,1,1,0,0},
    {1,1,1,0,0,0,1,1,0,0},
    {1,1,0,0,0,0,1,1,0,0},
    {1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1},
    {0,0,0,0,0,0,1,1,0,0},
    {0,0,0,0,0,0,1,1,0,0},
    {0,0,0,0,0,0,1,1,0,0}
};


const uint8_t digit_5[CARTESIAN_DIGIT_HEIGHT][CARTESIAN_DIGIT_WIDTH] PROGMEM = {
    {1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1},
    {1,1,0,0,0,0,0,0,0,0},
    {1,1,0,0,0,0,0,0,0,0},
    {1,1,1,1,1,1,1,1,0,0},
    {1,1,1,1,1,1,1,1,1,0},
    {0,0,0,0,0,0,0,1,1,1},
    {0,0,0,0,0,0,0,0,1,1},
    {0,0,0,0,0,0,0,0,1,1},
    {1,1,0,0,0,0,0,1,1,1},
    {1,1,1,1,1,1,1,1,1,1},
    {0,0,1,1,1,1,1,1,0,0}
};

const uint8_t digit_6[CARTESIAN_DIGIT_HEIGHT][CARTESIAN_DIGIT_WIDTH] PROGMEM = {
    {0,0,0,0,0,1,1,0,0,0},
    {0,0,0,0,1,1,0,0,0,0},
    {0,0,0,1,1,0,0,0,0,0},
    {0,0,1,1,0,0,0,0,0,0},
    {0,1,1,0,0,0,0,0,0,0},
    {0,1,1,1,1,1,1,1,0,0},
    {1,1,1,0,0,0,0,1,1,0},
    {1,1,0,0,0,0,0,0,1,1},
    {1,1,0,0,0,0,0,0,1,1},
    {1,1,0,0,0,0,0,0,1,1},
    {1,1,1,0,0,0,0,1,1,1},
    {0,0,1,1,1,1,1,1,0,0}
};

const uint8_t digit_7[CARTESIAN_DIGIT_HEIGHT][CARTESIAN_DIGIT_WIDTH] PROGMEM = {
    {0,1,1,1,1,1,1,1,1,1},
    {0,1,1,1,1,1,1,1,1,1},
    {0,0,0,0,0,0,0,0,1,1},
    {0,0,0,0,0,0,0,0,1,1},
    {0,0,1,1,1,1,1,1,1,0},
    {0,0,1,1,1,1,1,1,0,0},
    {0,0,0,0,0,1,1,0,0,0},
    {0,0,0,0,1,1,0,0,0,0},
    {0,0,0,1,1,0,0,0,0,0},
    {0,0,0,1,1,0,0,0,0,0},
    {0,0,1,1,0,0,0,0,0,0},
    {0,0,1,1,0,0,0,0,0,0},
};

const uint8_t digit_8[CARTESIAN_DIGIT_HEIGHT][CARTESIAN_DIGIT_WIDTH] PROGMEM = {
    {0,0,1,1,1,1,1,1,0,0},
    {0,1,1,0,0,0,0,1,1,0},
    {1,1,0,0,0,0,0,0,1,1},
    {1,1,0,0,0,0,0,0,1,1},
    {0,1,1,0,0,0,0,1,1,0},
    {0,0,1,1,1,1,1,1,0,0},
    {0,1,1,0,0,0,0,1,1,0},
    {1,1,0,0,0,0,0,0,1,1},
    {1,1,0,0,0,0,0,0,1,1},
    {0,1,1,0,0,0,0,1,1,0},
    {0,0,1,1,1,1,1,1,0,0},
    {0,0,0,0,0,0,0,0,0,0}
};

const uint8_t digit_9[CARTESIAN_DIGIT_HEIGHT][CARTESIAN_DIGIT_WIDTH] PROGMEM = {
    {0,0,1,1,1,1,1,1,0,0},
    {0,1,1,0,0,0,0,1,1,0},
    {1,1,0,0,0,0,0,0,1,1},
    {1,1,0,0,0,0,0,0,1,1},
    {0,1,1,0,0,0,0,1,1,1},
    {0,0,1,1,1,1,1,1,1,1},
    {0,0,0,0,0,0,0,0,1,1},
    {0,0,0,0,0,0,0,0,1,1},
    {0,0,0,0,0,0,0,0,1,1},
    {1,0,0,0,0,0,0,1,1,1},
    {1,1,1,1,1,1,1,1,1,0},
    {0,0,1,1,1,1,1,0,0,0}
};

const uint8_t* cartesian_digits[10] = {
    (const uint8_t*)digit_0,
    (const uint8_t*)digit_1,
    (const uint8_t*)digit_2,
    (const uint8_t*)digit_3,
    (const uint8_t*)digit_4,
    (const uint8_t*)digit_5,
    (const uint8_t*)digit_6,
    (const uint8_t*)digit_7,
    (const uint8_t*)digit_8,
    (const uint8_t*)digit_9
};

const cartesian_point_t hour_tens_pos = {.x = -12, .y = 14};
const cartesian_point_t hour_units_pos = {.x = 2, .y = 14};
const cartesian_point_t min_hour_pos = {.x = -12, .y = -2};
const cartesian_point_t min_units_pos = {.x = 2, .y = -2};


// pattern_t de l'affichage digital courant dans lequel on viendra coller la conversion cartésienne / polaire 
// de la matrice de pixels, elle en PROGMEM
pattern_t digital_clock_pattern[THETA_RESOLUTION] = {0};

void cartesian_copy_digit_on_matrix(
    uint8_t dest_matrix[MATRIX_SIZE][MATRIX_SIZE], // dest_matrix : matrice globale 32x32
    const uint8_t digit_matrix[CARTESIAN_DIGIT_HEIGHT][CARTESIAN_DIGIT_WIDTH],// digit_matrix : matrice du chiffre à copier (hauteur x largeur)
    cartesian_point_t pos // pos_x, pos_y : position du coin supérieur gauche du chiffre dans la matrice globale
) 
{
    int pos_x = pos.x;
    int pos_y = pos.y;
    for (int dy = 0; dy < CARTESIAN_DIGIT_HEIGHT; dy++) {
        for (int dx = 0; dx < CARTESIAN_DIGIT_WIDTH; dx++) {
            int x = pos_x + dx;
            int y = pos_y - dy; // avancer dans le digit = descendre sur la matrice globale
            if (x >= 0 && x < MATRIX_SIZE && y >= 0 && y < MATRIX_SIZE) {
                dest_matrix[x][y] = pgm_read_byte(&(digit_matrix[dy][dx]));
            }
        }
    }
}

// Conversion directe d'un digit cartésien (PROGMEM) vers pattern_t polaire
void convert_digit_cartesian_to_polar_pattern(const uint8_t digit_matrix[CARTESIAN_DIGIT_HEIGHT][CARTESIAN_DIGIT_WIDTH], cartesian_point_t pos, pattern_t *polar_buffer) {
    uint8_t angle_step = 360 / THETA_RESOLUTION;
    for (int i = 0; i < THETA_RESOLUTION; i++) {
        uint16_t angle = i * angle_step;
        polar_buffer[i].angle = angle;
        uint16_t mask = 0;
        double theta = angle * M_PI / 180.0;
        for (int r = 0; r < NB_LEDS; r++) {
            int x = pos.x + (int)(r * cos(theta));
            int y = pos.y - (int)(r * sin(theta));
            if (x >= 0 && x < MATRIX_SIZE && y >= 0 && y < MATRIX_SIZE) {
                if (pgm_read_byte(&(digit_matrix[y][x-pos.x]))) {
                    mask |= (1 << r);
                }
            }
        }
        polar_buffer[i].mask = mask;
    }
}

// retourne les 16 bits allumés ou éteints pour un angle donné dans la matrice cartésienne
uint16_t get_pattern_t_at_angle_from_matrix(uint16_t angle_deg){
    // converti angle en radians
    double theta = angle_deg * M_PI / 180.0;
    // init du mask qu'on va retourner
    uint16_t mask = 0;
    // à cet angle on va cherhcer les positions x,y de chaque led polaire dans la matrice cartésienne
    for (int r = 0; r < NB_LEDS; r++) {
        // on prend leur partie entière
        int x = (int)(r * cos(theta));
        int y = (int)(r * sin(theta));

        // si la led est allumée à cette position dans la matrice cartésienne, on met le bit correspondant dans le mask à 1 
        if (pgm_read_byte(&(cartesian_pixel_matrix[x][y]))) {
            mask |= (1 << r);
        }
        
    }
    return mask;
}

// cette fonction construit le pattern_t polaire à partir de la matrice cartésienne
void cartesian_matrix_to_polar_pattern(){
    // écart angle entre chaque pattern_t
    uint8_t angle_step = 360 / THETA_RESOLUTION;
    for (int i = 0; i < THETA_RESOLUTION; i++) {
        uint16_t angle = i * angle_step;
        digital_clock_pattern[i].angle = angle;
        digital_clock_pattern[i].mask = get_pattern_t_at_angle_from_matrix(angle);
    }
}


void update_digital_clock() {
    // 1. Efface le buffer polaire
    for (int i = 0; i < THETA_RESOLUTION; i++) {
        digital_clock_pattern[i].mask = 0;
    }
    // 2. Récupère l'heure courante
    int h_tens = current_time.hours / 10;
    int h_units = current_time.hours % 10;
    int m_tens = current_time.minutes / 10;
    int m_units = current_time.minutes % 10;
    // 3. Colle chaque digit directement dans le buffer polaire
    convert_digit_cartesian_to_polar_pattern((const uint8_t (*)[CARTESIAN_DIGIT_WIDTH])cartesian_digits[h_tens], hour_tens_pos, digital_clock_pattern);
    convert_digit_cartesian_to_polar_pattern((const uint8_t (*)[CARTESIAN_DIGIT_WIDTH])cartesian_digits[h_units], hour_units_pos, digital_clock_pattern);
    convert_digit_cartesian_to_polar_pattern((const uint8_t (*)[CARTESIAN_DIGIT_WIDTH])cartesian_digits[m_tens], min_hour_pos, digital_clock_pattern);
    convert_digit_cartesian_to_polar_pattern((const uint8_t (*)[CARTESIAN_DIGIT_WIDTH])cartesian_digits[m_units], min_units_pos, digital_clock_pattern);
}