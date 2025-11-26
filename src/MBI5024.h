#ifndef MBI5024_H
#define MBI5024_H

#include "utils.h"
#include "hall_sensor.h"
#include "pattern.h"

#define CLOCK PB5
#define SDI PB3
#define OE PC1
#define LE PC2

// ca fonctionne 1 tick pour l'instant, je laisse même si ca colle pas avec les calculs
#define LEDS_BRIGHTNESS_TICKS 1

// nombre de ticks à anticiper pour précharger un buffer avant son allumage 
#define PRELOAD_TICKS 6

/// @brief configure l'horloge comme une sortie
void set_CLOCK_as_output(); 

/// @brief configure SDI (serial data input) comme une sortie
void set_SDI_as_output(); 

/// @brief configure OE (output terminal) comme une sortie
void set_OE_as_output(); 

/// @brief configure LE (latch enable) comme une sortie
void set_LE_as_output(); 

/// @brief configure tous les outputs necessaires pour les leds d'un coup
void set_all_leds_outputs(); 

/// @brief front montant sur l'horloge
void CLOCK_UP(); 

/// @brief front descendant sur l'horloge
void CLOCK_DOWN(); 

/// @brief Allume SDI (serial data input) le registre si on allume la led courante
/// @param on_off si on alume ou pas la led courante
void set_SDI(int on_off); 

/// @brief change l'état de OE, l'output, activé à 0. 
/// @param on_off si on active (0) ou désactive (1) l'output
void set_OE(int on_off); 

/// @brief change l'état de LE, le truc pour envoyer le buffer aux leds. 
void set_LE(int on_off);

/// @brief affiche le motif (masque binaire) envoyé au driver
/// @param mask Masque 16 bits, 1 = LED allumée
void display_mask(uint16_t mask);

/// @brief Affiche le motif pendant us microsecondes ensuite noir
/// @param mask Masque 16 bits, 1 = LED allumée
/// @param us Le nombre de microsecondes à afficher
void display_mask_during_us(uint16_t mask, uint16_t us);

/// @brief Affiche le motif à l'angle souhaité angle_deg
/// appeler comme ca : while(1){ display_mask_at_angle(mask, ANGLE); }
/// cette fonction gère le timing toute seule
/// @param mask Masque 16 bits, 1 = LED allumée
/// @param angle_deg L'angle à afficher
void display_mask_at_angle(uint16_t mask, uint32_t angle_deg);

/// @brief affiche chaque buffer du disctionnaire pattern à son angle associé. 
/// cette fonction aussi gère le timing toute seule
/// @param pattern_dict Le dictionnaire de patterns à afficher
void display_patterns(const pattern_t pattern_dict[], uint16_t pattern_count);

/// @brief Affiche un buffer de patterns stocké en RAM (pas en PROGMEM)
void display_patterns_from_ram(const pattern_t *pattern_dict, uint16_t pattern_count);

#endif 