#include "hall_sensor.h"

// attribution des 2 variables qui sont extern dans l .h, donc plus extern mais toujours volatile pour dire au compilateur
// qu'elles peuvent changer en dehors du flux normal du programme
// uint16_t car TCNT1 fait 16bits
volatile uint16_t rotation_time = 0;
volatile uint8_t new_rotation = 0;

ISR(HALL_INT) {
    
    // Recup la valeur du Time Counter Timer, la valeur de la clock du processeur sur un int de 16bits 
    rotation_time = TCNT1; 
    // remet le compteur à zéro 
    TCNT1 = 0;              
    new_rotation = 1;    
    // décomenter pour verifie que ca fonctionne si on a bien une ligne dasn l'axe du capteur. 
    //delay_us_ticks(50000); 
    //display_mask_during_us(0xFFFF, 10);
}

void configure_HALL_interrupt(){
    // lire ca : https://wikigeii.iut-troyes.univ-reims.fr/index.php?title=Cours:Atmega328p
    // pour bien tout comprendre
    
    // "Le registre EICRA permet de choisir le mode de déclenchement de l'interruption."
    // il faut que les bits IS01 et IS00 soient respectivement à 1 et 0 pour déclencher l'interruption sur un front descendant de HALL
    set_pin(&EICRA, ISC01, 1);       
    set_pin(&EICRA, ISC00, 0);

    // "Le registre EIMSK permet d'autoriser ou non les interruptions INT1 et INT0."
    set_pin(&EIMSK, INT0, 1);        // on met 1 sur le INT0-ième bit de EIMSK pour activer l'interruption INT0 (PD2)

    // lire https://txplore.freshdesk.com/support/solutions/articles/35000024878-understanding-atmega-timers pour comprendre 
    // on veut mettre le bit CS11 de TCCR1B pour qu'il s'incrémente à F_CPU/8 = coeff_incr_hall 
    // enfait je crois que c'est pas assez et donc ya un overflow dans le timer 
    // de 16 bits donc je mets FCPU/64
    set_pin(&TCCR1B, CS12, 0); 
    set_pin(&TCCR1B, CS11, 1); 
    set_pin(&TCCR1B, CS10, 1);

    // active les interruptions globalement 
    sei(); 
}

uint16_t get_rotation_ticks (){
    // désactive INT0 le temps de lire 
    set_pin(&EIMSK, INT0, 0);          
    uint16_t ticks = rotation_time;
    new_rotation = 0; 
    // réactive INT0
    set_pin(&EIMSK, INT0, 1); 
    return ticks;
}

uint16_t convert_angle_to_ticks(uint32_t angle_deg){
    uint16_t rotation_ticks = get_rotation_ticks();
    return (rotation_ticks * angle_deg) / 360U; //U cc'est pour usigned int
} 

void set_HALL_as_input(){
    set_as_input(&DDRD, HALL); 
    // Le PIN D2 (HALL) peut être flottant il faut le forcer à 1 (et il passera bien a 0 si on passe devant le capteur avec l'aimant)
    set_pin(&PORTD, HALL,1);
    configure_HALL_interrupt(); 
}

uint8_t read_HALL(){
    return read_pin(&PIND, HALL); 
}