#include <avr/io.h>
#include "clock.h"
#include <stddef.h>


volatile time_t current_time = {0, 0, 0};
volatile uint8_t second_elapsed = 0;
volatile uint8_t clock_dirty = 0;
pattern_t clock_pattern_buffer[CLOCK_PATTERN_SIZE];

ISR(CLOCK_INT){
    static uint32_t cycle_acc = 0;
    cycle_acc += TIMER2_OVF_DEN;
    if (cycle_acc >= F_CPU){
        cycle_acc -= F_CPU;
        second_elapsed = 1;
    }
}

void configure_clock_interrupt(){
    // pour comprendre cf. : 
    // https://passionelectronique.fr/introduction-timer-arduino/#introduction-aux-timer-de-latmega328

    // TIMSK2 est le registre qui configure l'interruption du timer 2
    // TOEI2 c'est le bit qui dit déclenche l'interruption en cas d'égalité avec la valeur du bit 
    // donc si on met 1 on aura une interruption à chaque overflow du timer 2
    set_pin(&TIMSK2, TOIE2, 1); 

    // Timer2 prescaler (CS22..CS20): 111 => /1024 (spécifique à Timer2: 101 serait /128)
    // comme ca on compte assez lentement pour pas avoir d'overflow trop rapide
    set_pin(&TCCR2B, CS20, 1);
    set_pin(&TCCR2B, CS21, 1);
    set_pin(&TCCR2B, CS22, 1); // diviseur par 1024
    sei(); 
}

void set_clock_time(uint8_t hour, uint8_t minute){
    // verif si un temps valide 
    if (hour >= 24 || minute >= 60){
        return; 
    }
    // set les variables globales et update()
    current_time.hours = hour;
    current_time.minutes = minute;
    current_time.seconds = 0;
    clock_dirty = 1; 
}

static void load_clock_base_template(){
    for (int i = 0; i < CLOCK_PATTERN_SIZE; ++i){
        clock_pattern_buffer[i].angle = pgm_read_word(&(clock_base_pattern[i].angle));
        clock_pattern_buffer[i].mask = pgm_read_word(&(clock_base_pattern[i].mask));
    }
}

void init_clock(){
    load_clock_base_template();
}

// renvoie l'index du pattern dont l'angle est le plus proche de target_angle (0..359)
// va servir à superposer de manièren exacte les patterns des aiguilles sur la base de l'horloge
static int find_index_by_angle_nearest(const pattern_t *table, int size, int target_angle){
    int best_i = 0;
    int best_diff = 361;
    for (int i = 0; i < size; ++i){
        // Normalisation de l'angle (au cas où une valeur >360 a été injectée par erreur)
        int a = (int)(table[i].angle % 360);
        int d = a - target_angle;
        if (d < 0) d = -d;
        if (d > 180) d = 360 - d; // distance circulaire
        if (d < best_diff){
            best_diff = d;
            best_i = i;
            if (best_diff == 0) break;
        }
    }
    return best_i;
}

void superpose_aiguille(const pattern_t *aiguille_pattern, uint8_t aiguille_length, uint8_t aiguille_thickness, int base_index){
    // verif de la validité des paramêtres jsp si c'est utile, on pourra les retirer
    // si on réduire le glitch à chaque seconde qui passe. 
    if (aiguille_pattern == NULL || aiguille_thickness == 0){
        return;
    }
    if (aiguille_length == 0){
        return;
    }
    if (aiguille_length > NB_LEDS){
        aiguille_length = NB_LEDS;
    }

    // on prépare un masque plein de 16 bits à 1
    uint16_t length_mask = 0xFFFFU;
    // qu'on va tronquer en fonction de la taille de l'aiguille
    if (aiguille_length < NB_LEDS){
        uint8_t shift = (uint8_t)(NB_LEDS - aiguille_length);
        length_mask = (uint16_t)((0xFFFFU << shift) & 0xFFFFU);
    }

    // Centrage de l'aiguille sur base_index
    // Centrage géométrique de l'aiguille sur base_index
    int center = (aiguille_thickness - 1) / 2;
    for (uint8_t t = 0; t < aiguille_thickness; ++t){
        uint16_t raw_mask = pgm_read_word(&(aiguille_pattern[t].mask));
        uint16_t mask = raw_mask & length_mask;

        int target_index = base_index + ((int)t - center); // centre sur base_index
        while (target_index < 0){
            target_index += CLOCK_PATTERN_SIZE;
        }
        target_index %= CLOCK_PATTERN_SIZE;

        clock_pattern_buffer[target_index].mask |= mask;
    }
}

// met à jour l'affichage des aiguilles en fonction de l'heure courante
void update_clock(){
    load_clock_base_template();

    // index minute / hour, sec on inverse car les angles augmentent dans le sens antihoraire 
    int minute_angle = 360 - ((current_time.minutes % 60) * 6);
    int hour_angle   = 360 - (((current_time.hours % 12) * 60 + current_time.minutes) / 2);
    int second_angle = 360 - ((current_time.seconds % 60) * 6);

    int minute_index = find_index_by_angle_nearest(clock_pattern_buffer, CLOCK_PATTERN_SIZE, minute_angle);
    int hour_index = find_index_by_angle_nearest(clock_pattern_buffer, CLOCK_PATTERN_SIZE, hour_angle);
    int second_index = find_index_by_angle_nearest(clock_pattern_buffer, CLOCK_PATTERN_SIZE, second_angle);

    superpose_aiguille(min_aiguille, MINUTE_AIGUILLE_LENGTH, MINUTE_AIGUILLE_THICKNESS, minute_index);
    superpose_aiguille(hour_aiguille, HOUR_AIGUILLE_LENGTH, HOUR_AIGUILLE_THICKNESS, hour_index);
    superpose_aiguille(second_aiguille, SECOND_AIGUILLE_LENGTH, SECOND_AIGUILLE_THICKNESS, second_index);
}

void start_clock(){
    init_clock();
    /* current_time.hours = hour % 24;
    current_time.minutes = minute % 60;
    current_time.seconds = 0;
    clock_dirty = 1; */
    configure_clock_interrupt();
    while(1){
        // on met a jour les variables globales de l'heure ici, pas dans l'ISR
        // pour tenter de gratter du temps
        if (second_elapsed){
            second_elapsed = 0;
            current_time.seconds++;
            if (current_time.seconds >= 60){
                current_time.seconds = 0;
                current_time.minutes++;
                if (current_time.minutes >= 60){
                    current_time.minutes = 0;
                    current_time.hours = (current_time.hours + 1) % 24;
                }
            }
            clock_dirty = 1;
        }
        // Tant que c'est pas un nouveau tour, on attend
        while(!new_rotation) {}
            // si la clock est dirty (c.a.d, doit être updatée), on le fait 
            if (clock_dirty){
                clock_dirty = 0;
                update_clock();
            }

            display_patterns_from_ram(clock_pattern_buffer, CLOCK_PATTERN_SIZE);
        }
}
    