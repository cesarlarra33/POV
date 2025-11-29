
#include "clock_rounded.h"
#include "uart.h"
#include <stdio.h>


// tableau de pattern_t template de la cock rounded pouru l'instant vide, bientot on met hello 
const pattern_t rounded_clock_base_pattern[CLOCK_PATTERN_SIZE] PROGMEM = { 
    {.angle =   0U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =   3U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =   6U, .mask = MASK16(0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0)},
    {.angle =   9U, .mask = MASK16(0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =  12U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =  15U, .mask = MASK16(0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0)},
    {.angle =  19U, .mask = MASK16(0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =  23U, .mask = MASK16(0,0,0,0,0,0,0,1,1,0,0,1,0,0,0,0)},
    {.angle =  27U, .mask = MASK16(0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0)},
    {.angle =  30U, .mask = MASK16(0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0)},
    {.angle =  33U, .mask = MASK16(0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0)},
    {.angle =  36U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =  39U, .mask = MASK16(0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0)},
    {.angle =  43U, .mask = MASK16(0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0)},
    {.angle =  47U, .mask = MASK16(0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0)},
    {.angle =  51U, .mask = MASK16(0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0)},
    {.angle =  55U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =  57U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =  60U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =  63U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =  66U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =  69U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =  72U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =  75U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =  79U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =  83U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =  87U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =  90U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},

    {.angle =  93U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =  96U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =  99U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 102U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 105U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 108U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 112U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 117U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 120U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 123U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 126U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 129U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 132U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 135U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 138U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 141U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 144U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 147U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 150U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 153U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 156U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 159U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 162U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 165U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 169U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 173U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 177U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 180U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 183U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 186U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 189U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 192U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 201U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 205U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 207U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 210U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 213U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 216U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 219U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 223U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 226U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 229U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 232U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 235U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 238U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 240U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 243U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 246U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 249U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 252U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 255U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 259U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 263U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},

    {.angle = 267U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 271U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 274U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 277U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 280U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 283U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 286U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 290U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 293U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 296U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 298U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 300U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 303U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 306U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 310U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 313U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 316U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 319U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 323U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 326U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 330U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 333U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 336U, .mask = MASK16(0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0)},
    {.angle = 340U, .mask = MASK16(0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0)},
    {.angle = 343U, .mask = MASK16(0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0)},
    {.angle = 348U, .mask = MASK16(0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0)},
    {.angle = 352U, .mask = MASK16(0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0)},
    {.angle = 357U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
};

// tableaux de pattern_t correspondant à tous les symboles dont on besoin 
const pattern_t colon_pattern[COLUN_WIDTH] PROGMEM = { 
    {.angle =   0U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =   3U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =   6U, .mask = MASK16(0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0)},
    {.angle =   9U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =  12U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)}
};

const pattern_t number_0[NUMBER_WIDTH] PROGMEM = { 
    {.angle =   0U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =   3U, .mask = MASK16(0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0)},
    {.angle =   6U, .mask = MASK16(0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0)},
    {.angle =   9U, .mask = MASK16(0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0)},
    {.angle =  12U, .mask = MASK16(0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0)},
    {.angle =  15U, .mask = MASK16(0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0)},
    {.angle =  19U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)}
};

const pattern_t number_1[NUMBER_WIDTH] PROGMEM = { 
    {.angle =   0U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =   3U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0)},
    {.angle =   6U, .mask = MASK16(0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0)},
    {.angle =   9U, .mask = MASK16(0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0)},
    {.angle =  12U, .mask = MASK16(0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0)},
    {.angle =  15U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =  19U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)}
};

const pattern_t number_2[NUMBER_WIDTH] PROGMEM = { 
    {.angle =   0U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =   3U, .mask = MASK16(0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0)},
    {.angle =   6U, .mask = MASK16(0,0,0,1,1,0,0,0,0,0,0,0,1,0,0,0)},
    {.angle =   9U, .mask = MASK16(0,0,0,1,0,1,1,0,0,0,0,0,1,0,0,0)},
    {.angle =  12U, .mask = MASK16(0,0,0,1,0,0,0,1,1,1,0,0,1,0,0,0)},
    {.angle =  15U, .mask = MASK16(0,0,0,1,0,0,0,0,0,0,1,1,0,0,0,0)},
    {.angle =  19U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)}
};

const pattern_t number_3[NUMBER_WIDTH] PROGMEM = { 
    {.angle =   0U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =   3U, .mask = MASK16(0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0)},
    {.angle =   6U, .mask = MASK16(0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0)},
    {.angle =   9U, .mask = MASK16(0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0)},
    {.angle =  12U, .mask = MASK16(0,0,0,1,0,0,0,1,1,1,0,0,1,0,0,0)},
    {.angle =  15U, .mask = MASK16(0,0,0,0,1,1,1,0,0,1,1,1,0,0,0,0)},
    {.angle =  19U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)}
};

const pattern_t number_4[NUMBER_WIDTH] PROGMEM = { 
    {.angle =   0U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =   3U, .mask = MASK16(0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0)},
    {.angle =   6U, .mask = MASK16(0,0,0,0,0,0,1,0,0,1,1,0,0,0,0,0)},
    {.angle =   9U, .mask = MASK16(0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0)},
    {.angle =  12U, .mask = MASK16(0,0,0,1,1,1,1,1,1,0,0,0,1,0,0,0)},
    {.angle =  15U, .mask = MASK16(0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0)},
    {.angle =  19U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)}
};

const pattern_t number_5[NUMBER_WIDTH] PROGMEM = { 
    {.angle =   0U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =   3U, .mask = MASK16(0,0,0,0,1,0,0,0,1,1,1,1,1,0,0,0)},
    {.angle =   6U, .mask = MASK16(0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0)},
    {.angle =   9U, .mask = MASK16(0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0)},
    {.angle =  12U, .mask = MASK16(0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0)},
    {.angle =  15U, .mask = MASK16(0,0,0,0,1,1,1,1,0,0,0,0,1,0,0,0)},
    {.angle =  19U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)}
};

const pattern_t number_6[NUMBER_WIDTH] PROGMEM = { 
    {.angle =   0U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =   3U, .mask = MASK16(0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0)},
    {.angle =   6U, .mask = MASK16(0,0,0,1,0,0,0,1,0,1,1,0,0,0,0,0)},
    {.angle =   9U, .mask = MASK16(0,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0)},
    {.angle =  12U, .mask = MASK16(0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0)},
    {.angle =  15U, .mask = MASK16(0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0)},
    {.angle =  19U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)}
};

const pattern_t number_7[NUMBER_WIDTH] PROGMEM = { 
    {.angle =   0U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =   3U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0)},
    {.angle =   6U, .mask = MASK16(0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0)},
    {.angle =   9U, .mask = MASK16(0,0,0,0,1,1,1,0,0,1,0,0,1,0,0,0)},
    {.angle =  12U, .mask = MASK16(0,0,0,0,0,0,0,1,1,1,0,0,1,0,0,0)},
    {.angle =  15U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0)},
    {.angle =  19U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)}
};

const pattern_t number_8[NUMBER_WIDTH] PROGMEM = { 
    {.angle =   0U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =   3U, .mask = MASK16(0,0,0,0,1,1,1,0,0,1,1,1,0,0,0,0)},
    {.angle =   6U, .mask = MASK16(0,0,0,1,0,0,0,1,1,0,0,0,1,0,0,0)},
    {.angle =   9U, .mask = MASK16(0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0)},
    {.angle =  12U, .mask = MASK16(0,0,0,1,0,0,0,1,1,0,0,0,1,0,0,0)},
    {.angle =  15U, .mask = MASK16(0,0,0,0,1,1,1,0,0,1,1,1,0,0,0,0)},
    {.angle =  19U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)}
};

const pattern_t number_9[NUMBER_WIDTH] PROGMEM = { 
    {.angle =   0U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =   3U, .mask = MASK16(0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0)},
    {.angle =   6U, .mask = MASK16(0,0,0,1,0,0,0,1,1,0,0,1,1,0,0,0)},
    {.angle =   9U, .mask = MASK16(0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0)},
    {.angle =  12U, .mask = MASK16(0,0,0,1,0,0,0,1,1,0,0,1,1,0,0,0)},
    {.angle =  15U, .mask = MASK16(0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0)},
    {.angle =  19U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)}
};


// Superpose un symbole (chiffre, ou ":") sur le buffer à un index donné
void superpose_symbol(const pattern_t *symbol_pattern, uint8_t pattern_width, int pattern_index) {
    for (uint8_t i = 0; i < pattern_width; ++i) {
        // recup le pattern_t symbol_pattenr[i]
        uint16_t mask = pgm_read_word(&(symbol_pattern[i].mask));

        // calcul de l'index cible dans le template
        int target_index = pattern_index + i;

        // Copie le mask dans le buffer d'affichage
        display_pattern_buffer[target_index].mask |= mask;
    }
}

const pattern_t* symbol_patterns[NUM_SYMBOLS] = {
    number_0,
    number_1,
    number_2,
    number_3,
    number_4,
    number_5,
    number_6,
    number_7,
    number_8,
    number_9,
    colon_pattern
};



// fonction de maj de la clock rounded
void update_rounded_d_clock(){
    load_template(rounded_clock_base_pattern);

    // recup les chiffres à afficher
    int h_tens = current_time.hours / 10;
    int h_units = current_time.hours % 10;
    int m_tens = current_time.minutes / 10;
    int m_units = current_time.minutes % 10;
    int s_tens = current_time.seconds / 10;
    int s_units = current_time.seconds % 10;

    
    // on repartit automatiquement dans un intervalle 
    double angle_start = 95.0;
    double angle_end = 240.0; 
    double angle_step = (angle_end - angle_start) / 7.0; // 7 intervalles pour 8 elements 
    int angles[8];
    for (int i = 0; i < 8; ++i) {
        angles[i] = (int)(angle_start + i * angle_step + 0.5); 
    }

    // on va chercher les angles qui existent dans display_pattenr_buffer
    int idx[8];
    for (int i = 0; i < 8; ++i) {
        idx[i] = find_index_by_angle_nearest(display_pattern_buffer, CLOCK_PATTERN_SIZE, angles[i]);
    }

    // on superpose tous les nombres un à un à leur position
    superpose_symbol(symbol_patterns[h_tens], NUMBER_WIDTH, idx[0]);
    superpose_symbol(symbol_patterns[h_units], NUMBER_WIDTH, idx[1]);
    superpose_symbol(symbol_patterns[COLON], COLUN_WIDTH, idx[2]);
    superpose_symbol(symbol_patterns[m_tens], NUMBER_WIDTH, idx[3]);
    superpose_symbol(symbol_patterns[m_units], NUMBER_WIDTH, idx[4]);
    superpose_symbol(symbol_patterns[COLON], COLUN_WIDTH, idx[5]);
    superpose_symbol(symbol_patterns[s_tens], NUMBER_WIDTH, idx[6]);
    superpose_symbol(symbol_patterns[s_units], NUMBER_WIDTH, idx[7]);
}