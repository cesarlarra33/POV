#include <avr/pgmspace.h>

#include "MBI5024.h"

static inline void preload_mask(uint16_t mask);
static inline uint16_t wrap_angle(int16_t angle);

void set_CLOCK_as_output(){
    set_as_output(&DDRB, CLOCK); 
    set_pin(&PORTB, CLOCK, 0); //on force l'horloge à zéro 
}

void set_SDI_as_output(){
    set_as_output(&DDRB, SDI); 
}

void set_OE_as_output(){
    set_as_output(&DDRC, OE); 
    set_OE(0); // on l'active par défaut, et il est activé quand à zéro d'après la doc 
}

void set_LE_as_output(){
    set_as_output(&DDRC, LE);  // Met le pin 2 de DDRC en sorti
    set_LE(0); // au cas ou on desactive la sortie
}

void set_all_leds_outputs(){
    set_CLOCK_as_output(); 
    set_SDI_as_output(); 
    set_OE_as_output(); 
    set_LE_as_output(); 
    set_OE(0);
}

void delay_until_tick(uint16_t target){
    // TCNT1 est sur 16 bits donc reboucle de 0xFFFF à 0, donc on regarde d'abord si la cible 
    // est devant ou derrière comparant la delta_t courant à la cible avec la moitié, d'un uint_16t
    // soit 0x8000 
    // si c'est deriière on boucle pas
    // si c'est devant on attend sauf si c'est un nouveau tour alors delay pas 
    while ((uint16_t)(target - TCNT1) < 0x8000) {
        if (new_rotation) {
            
            return;
        }
    }
}

void CLOCK_UP(){
    set_pin(&PORTB,CLOCK, 1); 
}

void CLOCK_DOWN(){
    set_pin(&PORTB, CLOCK, 0); 
}

void set_SDI(int up_down){
    if(up_down){
        set_pin(&PORTB,SDI,1);
    }
    else {
        set_pin(&PORTB,SDI,0);
    }
}

void set_OE(int up_down){
    if(up_down){
        set_pin(&PORTC,OE,1);
    }
    else {
        set_pin(&PORTC,OE,0);
    }
}

void set_LE(int up_down){
    if(up_down){
        set_pin(&PORTC,LE,1);
    }
    else {
        set_pin(&PORTC,LE,0);
    }
}


static inline void preload_mask(uint16_t mask){
    for (uint8_t i = 0; i < NB_LEDS; ++i) {
        set_SDI((mask >> i) & 0x1U);
        CLOCK_UP();
        CLOCK_DOWN();
    }
}


// fais en sorte que si jamais par exemple il est midi, 
// on va vouloir affichée l'aiguille des heures à 0 deg
// mais avec les offsets d'angle sur le mask aguille on peut avoir
// des angles négatifs ou > 360, cette fonction remet tout dans [0, 360[
static inline uint16_t wrap_angle(int16_t angle){
    int16_t normalized = angle % 360;
    if (normalized < 0) {
        normalized += 360;
    }
    return (uint16_t)normalized;
}

void display_mask(uint16_t mask){
    // lire la doc du MBI5024 pour comprendre le fonctionnement
    set_OE(1); // on coupe temporairement la sortie (OE actif à 0)
    preload_mask(mask);
    // envoie l'output
    set_LE(1);
    set_LE(0);
    set_OE(0); 
}

void display_mask_during_us(uint16_t mask, uint16_t delay_us){
    // ==> Pas assez précise avec _delay_us maintenant on va delay directement en ticks
    display_mask(mask); 
    delay_us_ticks(delay_us); 
    set_OE(1); // on coupe la sortie après l'affichage
}

void display_mask_during_ticks(uint16_t mask, uint16_t time_ticks){
    // ==> toujours pas top niveau nombre de buffers qu'on peut afficher au tour 
    // ==> parce que en gros sur le temps disponible dans 1 tour pour afficher 1 buffer 
    // on perd du temps a charger le buffer dans les leds avec display_mask()
    display_mask(mask); 
    delay_ticks(time_ticks); 
    set_OE(1); // on coupe la sortie après l'affichage
}

void display_preloaded_mask_for(uint16_t time_ticks){
    // ensuite au moment venu on activte le latch pour valider le masque préchargé
    // et on met OE à 0 pour affiché le masque durant time_ticks ticks
    set_LE(1);
    set_LE(0);
    set_OE(0);
    delay_ticks(time_ticks);
    set_OE(1);
}

void display_mask_at_angle(uint16_t mask, uint32_t angle_deg){
    // affiche un buffer à l'angle souhaité en fonction du temps de rotation mesuré
    // appeler comme ca
    // while(1){ display_mask_at_angle(mask, ANGLE); }
    // cette fonction gère le timing toute seule
    // ==> juste en faisant boucler cette fonction sur un {.angle = 90, .buffer = {..}},
    // ca fonctionne bien mais si on veut augmenter le nombre de buffers affichés par tour
    // il faut une autre approche : cf display_patterns()

    // attendre la nouvelle rotation
    while (!new_rotation) {}
    // nb de ticks du tour 
    uint16_t rotation_ticks = get_rotation_ticks();

    // ticks à attendre pour atteindre l'angle demandé (calcul en 32 bits pour éviter l'overflow)
    uint32_t angle_ticks32 = ((uint32_t)rotation_ticks * (uint32_t)angle_deg) / 360U;
    // si jamais l'angle est trop grand on met au dernier tick, sinon on cast 32 dans 16 
    uint16_t angle_ticks = (angle_ticks32 > 0xFFFF) ? 0xFFFF : (uint16_t)angle_ticks32;

    // attendre jusqu'à l'angle 
    delay_until_tick(angle_ticks);

    // temps d'allumage 1deg de rotation, mais au - un tick 
    uint16_t ticks_on = rotation_ticks / 360U;
    if (ticks_on == 0) ticks_on = 1;
    display_mask_during_ticks(mask, LEDS_BRIGHTNESS_TICKS * ticks_on);
}

void display_patterns(const pattern_t pattern_dict[], uint16_t pattern_count){
    if (pattern_count == 0U) {
        return;
    }

    while (!new_rotation) {}

    uint16_t rotation_ticks = get_rotation_ticks();
    if (rotation_ticks == 0U) {
        return;
    }

    uint16_t ticks_on = rotation_ticks / 360U;
    if (ticks_on < 1U) {
        ticks_on = 1U;
    }

    for (uint16_t i = 0; i < pattern_count; ++i) {
        int16_t raw_angle = (int16_t)pgm_read_word(&(pattern_dict[i].angle));
        uint16_t current_angle = wrap_angle(raw_angle);
        uint16_t mask = pgm_read_word(&(pattern_dict[i].mask));

        uint32_t target32 = ((uint32_t)rotation_ticks * (uint32_t)current_angle) / 360U;
        uint16_t target = (target32 > 0xFFFFU) ? 0xFFFFU : (uint16_t)target32;

        uint16_t preload_target = (target > PRELOAD_TICKS) ? (uint16_t)(target - PRELOAD_TICKS) : 0U;

        delay_until_tick(preload_target);
        if (new_rotation) {
            break;
        }

        preload_mask(mask);

        delay_until_tick(target);
        if (new_rotation) {
            break;
        }

        display_preloaded_mask_for((uint16_t)(ticks_on * LEDS_BRIGHTNESS_TICKS));
    }
}

// Affiche un buffer de patterns stocké en RAM (pas en PROGMEM)
void display_patterns_from_ram(const pattern_t *pattern_dict, uint16_t pattern_count) {
    uint16_t rotation_ticks = get_rotation_ticks();
    

    uint16_t ticks_on = rotation_ticks / 360U;

    for (uint16_t i = 0; i < pattern_count; ++i) {
        int16_t raw_angle = pattern_dict[i].angle;
        uint16_t current_angle = wrap_angle(raw_angle);
        uint16_t mask = pattern_dict[i].mask;

        uint32_t target32 = ((uint32_t)rotation_ticks * (uint32_t)current_angle) / 360U;
        uint16_t target = (target32 > 0xFFFFU) ? 0xFFFFU : (uint16_t)target32;

        uint16_t preload_target = (target > PRELOAD_TICKS) ? (uint16_t)(target - PRELOAD_TICKS) : 0U;

        delay_until_tick(preload_target);
        

        preload_mask(mask);

        delay_until_tick(target);
        if (new_rotation) {
            break;
        }

        display_preloaded_mask_for((uint16_t)(ticks_on * LEDS_BRIGHTNESS_TICKS));
    }
}