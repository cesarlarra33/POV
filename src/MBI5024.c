#include "MBI5024.h"

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

void display_buffer(uint8_t *buffer){
    set_OE(1);
    for(int i = 0; i < NB_LEDS; i++){
        int bit_value = (buffer[i/8] >> (7 - (i%8))) & 1; // bit par bit
        set_SDI(bit_value);
        CLOCK_UP();
        CLOCK_DOWN();
    }
    set_LE(1);
    set_LE(0);
    set_OE(0);
}

void display_buffer_during_us(uint8_t *buffer, uint16_t delay_us){
    // ==> Pas assez précise avec _delay_us maintenant on va delay directement en ticks
    display_buffer(buffer); 
    delay_us_ticks(delay_us); 
    set_OE(1); // on coupe la sortie après l'affichage
}

void display_buffer_during_ticks(uint8_t *buffer, uint16_t time_ticks){
    // ==> toujours pas top niveau nombre de buffers qu'on peut afficher au tour 
    // ==> parce que en gros sur le temps disponible dans 1 tour pour afficher 1 buffer 
    // on perd du temps a charger le buffer dans les leds avec display_buffer()
    display_buffer(buffer); 
    delay_ticks(time_ticks); 
    set_OE(1); // on coupe la sortie après l'affichage
}

void preload_buffer(uint8_t *buffer){
    // précharge le buffer dans SDI 
    // ==> la solution c'est d'exploiter le temps de noir avant le temps d'éclairage du tour
    // en chargeant le buffer pendant ce temps de noir quand OE = 1
    for(int i = 0; i < NB_LEDS; i++){
        set_SDI(buffer[i]);
        CLOCK_UP();
        CLOCK_DOWN();
    }
}

void display_preloaded_buffer_for(uint16_t time_ticks){
    // ensuite au moment venu on activte le latch pour valider le buffer préchargé
    // et on met OE à 0 pour affiché le buffer durant time_ticks ticks
    set_LE(1);
    set_LE(0);
    set_OE(0);
    delay_ticks(time_ticks);
    set_OE(1);
}

void display_buffer_at_angle(uint8_t *buffer, uint32_t angle_deg){
    // affiche un buffer à l'angle souhaité en fonction du temps de rotation mesuré
    // appeler comme ca
    // while(1){ display_buffer_at_angle(buf, ANGLE); }
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
    display_buffer_during_ticks(buffer, LEDS_BRIGHTNESS_TICKS * ticks_on);
}

void display_patterns(pattern_t pattern_dict[], uint8_t pattern_count) {
    // Attend un nouveau tour complet
    while (!new_rotation) {}

    uint16_t rotation_ticks = get_rotation_ticks();

    for (int i = 0; i < pattern_count; i++) {
        // Calcul des ticks correspondant à l'angle de début et de fin
        uint32_t start_ticks32 = ((uint32_t)rotation_ticks * (uint32_t)pattern_dict[i].angle_start) / 360U;
        uint32_t end_ticks32   = ((uint32_t)rotation_ticks * (uint32_t)pattern_dict[i].angle_end)   / 360U;

        uint16_t start_ticks = (start_ticks32 > 0xFFFF) ? 0xFFFF : (uint16_t)start_ticks32;
        uint16_t end_ticks   = (end_ticks32   > 0xFFFF) ? 0xFFFF : (uint16_t)end_ticks32;

        // On attend l'angle de début
        delay_until_tick(start_ticks);
        if (new_rotation) break;

        // Affiche le buffer jusqu'à l'angle de fin
        uint16_t duration_ticks = end_ticks - start_ticks;
        if (duration_ticks == 0) duration_ticks = 1;
        display_buffer_during_ticks(pattern_dict[i].buffer, duration_ticks);
    }
}
