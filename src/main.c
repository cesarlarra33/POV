/*#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

// Tes fichiers existants (Ne les modifie pas)
#include "hall_sensor.h"
#include "MBI5024.h"
#include "utils.h"

// Le fichier qu'on vient de créer
#include "heart_shape.h"

// Buffer en RAM pour construire l'image complète (360 degrés)
pattern_t display_buffer[360];

// --- FONCTION POUR PREPARER LE COEUR ---
void prepare_heart_buffer() {
    // 1. On remplit tout de NOIR d'abord
    for (int i = 0; i < 360; ++i) {
        display_buffer[i].angle = i;
        display_buffer[i].mask = 0x0000;
    }

    // 2. On charge le demi-coeur et on fait le miroir
    for (int i = 0; i < HEART_HALF_SIZE; ++i) {
        uint16_t angle = pgm_read_word(&(heart_half[i].angle));
        uint16_t mask  = pgm_read_word(&(heart_half[i].mask));
        
        // Coté Droit (0 à 180)
        // On décale de +90 pour l'avoir en haut si besoin, sinon laisse +0
        int pos_idx = (angle + 270) % 360; // 270 = -90 degrés (tourné vers le haut)
        display_buffer[pos_idx].mask = mask;

        // Coté Gauche (Miroir : 360 - angle)
        if (angle > 0) {
            int mirror_idx = (360 - angle + 270) % 360;
            display_buffer[mirror_idx].mask = mask;
        }
    }
}

// --- MAIN ---
int main(void) {
    // 1. Initialisation Hardware
    set_HALL_as_input();     // Interruption Hall
    set_all_leds_outputs();  // Driver LED
    
    // 2. Préparation de l'image en RAM
    prepare_heart_buffer();

    // 3. Petit flash de démarrage pour dire "Je suis vivant"
    set_OE(0);
    display_mask(0xFFFF); _delay_ms(200);
    display_mask(0x0000); _delay_ms(200);
    set_OE(1);

    sei(); // Active les interruptions

    while (1) {
        // Attente du passage de l'aimant
        while (!new_rotation) {}

        // Récupération de la vitesse du tour précédent
        uint16_t rotation_ticks = get_rotation_ticks();
        
        // Sécurité si le moteur est arrêté
        if (rotation_ticks < 1000) continue;

        // Calcul du temps par degré
        uint16_t ticks_per_degree = rotation_ticks / 360;

        // --- AFFICHAGE ---
        for (int i = 0; i < 360; ++i) {
            
            // On calcule quand afficher ce degré
            // (Logique simplifiée et robuste de ton code horloge)
            uint32_t target_tick_32 = ((uint32_t)rotation_ticks * i) / 360;
            uint16_t target_tick = (uint16_t)target_tick_32;

            // Attente du bon moment
            delay_us_ticks(target_tick);
            
            // Si on a fini le tour trop tôt (bruit), on sort
            if (new_rotation) break;

            // On charge le masque
            preload_mask(display_buffer[i].mask);

            // --- LE SECRET DE LA NETTETÉ ---
            // On affiche seulement une fraction du temps disponible.
            // ticks_per_degree / 3  => Image très nette
            // ticks_per_degree / 1  => Image baveuse
            uint16_t on_time = ticks_per_degree / 3; 
            if (on_time < 1) on_time = 1;

            display_preloaded_mask_for(on_time);
        }
    }
    return 0;
}*/

#include "utils.h"
#include "hall_sensor.h"
#include "MBI5024.h"
#include "clock.h"
#include "uart.h"
#include <avr/pgmspace.h>

// On inclut ton nouveau fichier
#include "heart_shape.h"

// Variable pour stocker la taille réelle du motif une fois la symétrie faite
uint16_t heart_total_size = 0;

// Cette fonction va remplir le buffer RAM (clock_pattern_buffer)
// avec le cœur complet (droite + gauche)
void load_heart_into_buffer() {
    uint16_t idx = 0;

    // ETAPE 1 : Copier la moitié originale (0 à 130°)
    // On lit depuis la mémoire flash (pgm_read_word) car c'est const PROGMEM
    for (uint8_t i = 0; i < HEART_FULL_SIZE; i++) {
        if (idx >= CLOCK_PATTERN_SIZE) break; // Sécurité débordement

        int16_t angle = (int16_t)pgm_read_word(&heart_full[i].angle);
        uint16_t mask = (uint16_t)pgm_read_word(&heart_full[i].mask);

        clock_pattern_buffer[idx].angle = angle;
        clock_pattern_buffer[idx].mask = mask;
        idx++;
    }

    // ETAPE 2 : Générer la symétrie (360° vers 230°)
    // On parcourt le tableau à l'envers pour que les angles restent croissants
    // dans le buffer (ex: 230, 240, ... 350, 355)
    for (int i = HEART_FULL_SIZE - 1; i >= 0; i--) {
        if (idx >= CLOCK_PATTERN_SIZE) break;

        int16_t angle = (int16_t)pgm_read_word(&heart_full[i].angle);

        // On ne duplique pas l'angle 0 (la pointe du bas) ni 180 (si il existait)
        if (angle == 0 || angle == 180) continue;

        // Calcul du miroir : 360 - angle
        int16_t mirror_angle = 360 - angle;
        uint16_t mask = (uint16_t)pgm_read_word(&heart_full[i].mask);

        clock_pattern_buffer[idx].angle = mirror_angle;
        clock_pattern_buffer[idx].mask = mask;
        idx++;
    }

    // On sauvegarde le nombre total de lignes à afficher
    heart_total_size = idx;
}

int main(void) {
    // Initialisations matérielles
    uart_init(MYUBRR);
    set_all_leds_outputs();
    set_HALL_as_input(); 
    
    // IMPORTANT : On prépare le dessin AVANT la boucle infinie
    // Le buffer clock_pattern_buffer est déclaré dans clock.h/c, on le réutilise ici
    load_heart_into_buffer();

    // On active les interruptions globalement
    sei();

    while (1) {
        // 1. Attendre le signal du capteur Hall (nouveau tour)
        // La fonction display_patterns_from_ram contient déjà le "while (!new_rotation)"
        // Mais pour être sûr de la logique, on peut laisser faire la fonction :
        
        display_patterns_from_ram(clock_pattern_buffer, HEART_FULL_SIZE);
    }

    return 0;
}