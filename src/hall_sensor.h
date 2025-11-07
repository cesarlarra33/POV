#ifndef HALL_SENSOR_H
#define HALL_SENSOR_H

#include <avr/interrupt.h>
#include "utils.h"

#define HALL PD2

// Macro pour l'interruption liée à un changement de PD2 
// on va utiliser une interruption ca c'est beaucoup plus rapide que d''avoir une fonction read_HALL()
#define HALL_INT INT0_vect

// durée d'un tour en tick de la clock du microcontroleur 
extern volatile uint16_t rotation_time;   
// permet de gérer si on dépasse une rotation le temps d'afficher le pattern
extern volatile uint8_t new_rotation; 
// volatile c'est pour dire au compilateur que cette variable ne doit pas être optimisée
// car elle peut changer en dehors du flux normal du programme (dans une interruption par ex)

/// @brief Gestionnaire d'interruption pour le capteur Hall 
/// cette fonction est automatiquement appelée lors d'un front descendant sur le pin HALL 
/// ca va beaucoup plus vite que de tester à chaque tour de boucle si on a une réponde du capteur
/// quand appélée va juste actualiser rotation_time et new_rotation
ISR(HALL_INT); 

/// @brief Retourne le nombre de ticks mesurés sur TCNT1 pour faire un tour
/// @return Le nombre de ticks pour un tour complet sur TCNT1 dans 16 bits
uint16_t get_rotation_ticks(); 

/// @brief Convertit un angle en degrés en nombre de ticks du timer en fonction du temps de rotation mesuré
/// @param angle_deg L'angle en degrés à convertir
/// @return Le nombre de ticks correspondant à l'angle donné 
uint16_t convert_angle_to_ticks(uint32_t angle_deg);

/// @brief Configure le pin HALL comme une entrée avec interruption sur front descendant
void set_HALL_as_input();

/// @brief Retourne la valeur lue sur le pin HALL de PIND : on utilise plus
uint8_t read_HALL();


#endif 