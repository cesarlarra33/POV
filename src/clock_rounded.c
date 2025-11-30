#include "clock_rounded.h"
#include "uart.h"
#include <string.h>
#include <stdio.h>


// tableau de pattern_t template de la cock rounded pouru l'instant vide 
const pattern_t rounded_clock_base_pattern[CLOCK_PATTERN_SIZE] PROGMEM = { 
    {.angle =   0U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =   3U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =   6U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =   9U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =  12U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =  15U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =  19U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =  23U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =  27U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =  30U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =  33U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =  36U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =  39U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =  43U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =  47U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =  51U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
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
    {.angle = 336U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 340U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 343U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 348U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 352U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle = 357U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
};

// tableaux de pattern_t correspondant à tous les symboles dont on besoin :
// ":"
const pattern_t colon_pattern[COLUN_WIDTH] PROGMEM = { 
    {.angle =   0U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =   3U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =   6U, .mask = MASK16(0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0)},
    {.angle =   9U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =  12U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)}
};

// "0"
const pattern_t number_0[NUMBER_WIDTH] PROGMEM = { 
    {.angle =   0U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =   3U, .mask = MASK16(0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0)},
    {.angle =   6U, .mask = MASK16(0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0)},
    {.angle =   9U, .mask = MASK16(0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0)},
    {.angle =  12U, .mask = MASK16(0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0)},
    {.angle =  15U, .mask = MASK16(0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0)},
    {.angle =  19U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)}
};

// "1"
const pattern_t number_1[NUMBER_WIDTH] PROGMEM = { 
    {.angle =   0U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =   3U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0)},
    {.angle =   6U, .mask = MASK16(0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0)},
    {.angle =   9U, .mask = MASK16(0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0)},
    {.angle =  12U, .mask = MASK16(0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0)},
    {.angle =  15U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =  19U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)}
};

// "2"
const pattern_t number_2[NUMBER_WIDTH] PROGMEM = { 
    {.angle =   0U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =   3U, .mask = MASK16(0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0)},
    {.angle =   6U, .mask = MASK16(0,0,0,1,1,0,0,0,0,0,0,0,1,0,0,0)},
    {.angle =   9U, .mask = MASK16(0,0,0,1,0,1,1,0,0,0,0,0,1,0,0,0)},
    {.angle =  12U, .mask = MASK16(0,0,0,1,0,0,0,1,1,1,0,0,1,0,0,0)},
    {.angle =  15U, .mask = MASK16(0,0,0,1,0,0,0,0,0,0,1,1,0,0,0,0)},
    {.angle =  19U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)}
};

// "3"
const pattern_t number_3[NUMBER_WIDTH] PROGMEM = { 
    {.angle =   0U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =   3U, .mask = MASK16(0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0)},
    {.angle =   6U, .mask = MASK16(0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0)},
    {.angle =   9U, .mask = MASK16(0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0)},
    {.angle =  12U, .mask = MASK16(0,0,0,1,0,0,0,1,1,1,0,0,1,0,0,0)},
    {.angle =  15U, .mask = MASK16(0,0,0,0,1,1,1,0,0,1,1,1,0,0,0,0)},
    {.angle =  19U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)}
};

// "4"
const pattern_t number_4[NUMBER_WIDTH] PROGMEM = { 
    {.angle =   0U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =   3U, .mask = MASK16(0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0)},
    {.angle =   6U, .mask = MASK16(0,0,0,0,0,0,1,0,0,1,1,0,0,0,0,0)},
    {.angle =   9U, .mask = MASK16(0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0)},
    {.angle =  12U, .mask = MASK16(0,0,0,1,1,1,1,1,1,0,0,0,1,0,0,0)},
    {.angle =  15U, .mask = MASK16(0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0)},
    {.angle =  19U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)}
};

// "5"
const pattern_t number_5[NUMBER_WIDTH] PROGMEM = { 
    {.angle =   0U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =   3U, .mask = MASK16(0,0,0,0,1,0,0,0,1,1,1,1,1,0,0,0)},
    {.angle =   6U, .mask = MASK16(0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0)},
    {.angle =   9U, .mask = MASK16(0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0)},
    {.angle =  12U, .mask = MASK16(0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0)},
    {.angle =  15U, .mask = MASK16(0,0,0,0,1,1,1,1,0,0,0,0,1,0,0,0)},
    {.angle =  19U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)}
};

// "6"
const pattern_t number_6[NUMBER_WIDTH] PROGMEM = { 
    {.angle =   0U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =   3U, .mask = MASK16(0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0)},
    {.angle =   6U, .mask = MASK16(0,0,0,1,0,0,0,1,0,1,1,0,0,0,0,0)},
    {.angle =   9U, .mask = MASK16(0,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0)},
    {.angle =  12U, .mask = MASK16(0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0)},
    {.angle =  15U, .mask = MASK16(0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0)},
    {.angle =  19U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)}
};

// "7"
const pattern_t number_7[NUMBER_WIDTH] PROGMEM = { 
    {.angle =   0U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =   3U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0)},
    {.angle =   6U, .mask = MASK16(0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0)},
    {.angle =   9U, .mask = MASK16(0,0,0,1,1,1,1,0,0,1,0,0,1,0,0,0)},
    {.angle =  12U, .mask = MASK16(0,0,0,0,0,0,0,1,1,1,0,0,1,0,0,0)},
    {.angle =  15U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0)},
    {.angle =  19U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)}
};

// "8"
const pattern_t number_8[NUMBER_WIDTH] PROGMEM = { 
    {.angle =   0U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =   3U, .mask = MASK16(0,0,0,0,1,1,1,0,0,1,1,1,0,0,0,0)},
    {.angle =   6U, .mask = MASK16(0,0,0,1,0,0,0,1,1,0,0,0,1,0,0,0)},
    {.angle =   9U, .mask = MASK16(0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0)},
    {.angle =  12U, .mask = MASK16(0,0,0,1,0,0,0,1,1,0,0,0,1,0,0,0)},
    {.angle =  15U, .mask = MASK16(0,0,0,0,1,1,1,0,0,1,1,1,0,0,0,0)},
    {.angle =  19U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)}
};

// "9"
const pattern_t number_9[NUMBER_WIDTH] PROGMEM = { 
    {.angle =   0U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =   3U, .mask = MASK16(0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0)},
    {.angle =   6U, .mask = MASK16(0,0,0,1,0,0,0,1,1,0,0,1,1,0,0,0)},
    {.angle =   9U, .mask = MASK16(0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0)},
    {.angle =  12U, .mask = MASK16(0,0,0,1,0,0,0,1,1,0,0,1,1,0,0,0)},
    {.angle =  15U, .mask = MASK16(0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0)},
    {.angle =  19U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)}
};

// "a"
const pattern_t char_a[LETTER_WIDTH] PROGMEM = {
    {.angle =   0U, .mask = MASK16(0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0)},
    {.angle =   3U, .mask = MASK16(0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0)},
    {.angle =   6U, .mask = MASK16(0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0)},
    {.angle =   9U, .mask = MASK16(0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0)},
};

// "b"
const pattern_t char_b[LETTER_WIDTH] PROGMEM = {
    {.angle =   0U, .mask = MASK16(0,0,0,0,0,1,1,0,1,1,1,0,0,0,0,0)},
    {.angle =   3U, .mask = MASK16(0,0,0,0,1,0,0,1,0,0,1,0,0,0,0,0)},
    {.angle =   6U, .mask = MASK16(0,0,0,0,1,0,0,1,0,0,1,0,0,0,0,0)},
    {.angle =   9U, .mask = MASK16(0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0)},
};

// "c"
const pattern_t char_c[LETTER_WIDTH] PROGMEM = {
    {.angle =   0U, .mask = MASK16(0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0)},
    {.angle =   3U, .mask = MASK16(0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0)},
    {.angle =   6U, .mask = MASK16(0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0)},
    {.angle =   9U, .mask = MASK16(0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0)},
};

// "d"
const pattern_t char_d[LETTER_WIDTH] PROGMEM = {
    {.angle =   0U, .mask = MASK16(0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0)},
    {.angle =   3U, .mask = MASK16(0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0)},
    {.angle =   6U, .mask = MASK16(0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0)},
    {.angle =   9U, .mask = MASK16(0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0)},
};

// "e"
const pattern_t char_e[LETTER_WIDTH] PROGMEM = {
    {.angle =   0U, .mask = MASK16(0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0)},
    {.angle =   3U, .mask = MASK16(0,0,0,0,1,0,0,1,0,0,1,0,0,0,0,0)},
    {.angle =   6U, .mask = MASK16(0,0,0,0,1,0,0,1,0,0,1,0,0,0,0,0)},
    {.angle =   9U, .mask = MASK16(0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0)},
};

// "f"
const pattern_t char_f[LETTER_WIDTH] PROGMEM = {
    {.angle =   0U, .mask = MASK16(0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =   3U, .mask = MASK16(0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0)},
    {.angle =   6U, .mask = MASK16(0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0)},
    {.angle =   9U, .mask = MASK16(0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0)},
};

// "g"
const pattern_t char_g[LETTER_WIDTH] PROGMEM = {
    {.angle =   0U, .mask = MASK16(0,0,0,0,0,1,0,0,1,1,0,0,0,0,0,0)},
    {.angle =   3U, .mask = MASK16(0,0,0,0,1,0,0,0,1,0,1,0,0,0,0,0)},
    {.angle =   6U, .mask = MASK16(0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0)},
    {.angle =   9U, .mask = MASK16(0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0)},
};

// "h"
const pattern_t char_h[LETTER_WIDTH] PROGMEM = {
    {.angle =   0U, .mask = MASK16(0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0)},
    {.angle =   3U, .mask = MASK16(0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0)},
    {.angle =   6U, .mask = MASK16(0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0)},
    {.angle =   9U, .mask = MASK16(0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0)},
};

// "i"
const pattern_t char_i[THIN_LETTER_WIDTH] PROGMEM = {
    {.angle =   0U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =   3U, .mask = MASK16(0,0,0,0,1,0,1,1,1,1,1,0,0,0,0,0)},
    {.angle =   6U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
};

// "j"
const pattern_t char_j[LETTER_WIDTH] PROGMEM = {
    {.angle =   0U, .mask = MASK16(0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0)},
    {.angle =   3U, .mask = MASK16(0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0)},
    {.angle =   6U, .mask = MASK16(0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0)},
    {.angle =   9U, .mask = MASK16(0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0)},
};

// "k"
const pattern_t char_k[LETTER_WIDTH] PROGMEM = {
    {.angle =   0U, .mask = MASK16(0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0)},
    {.angle =   3U, .mask = MASK16(0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0)},
    {.angle =   6U, .mask = MASK16(0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0)},
    {.angle =   9U, .mask = MASK16(0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0)},
};

// "l"
const pattern_t char_l[THIN_LETTER_WIDTH] PROGMEM = {
    {.angle =  0U, .mask = MASK16(0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0)},
    {.angle =  3U, .mask = MASK16(0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =  6U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)}
}; 

// "m"
const pattern_t char_m[WIDE_LETTER_WIDTH] PROGMEM = {
    {.angle =   0U, .mask = MASK16(0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0)},
    {.angle =   3U, .mask = MASK16(0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0)},
    {.angle =   6U, .mask = MASK16(0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0)},
    {.angle =   9U, .mask = MASK16(0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0)},
    {.angle =   9U, .mask = MASK16(0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0)}
};

// "n"
const pattern_t char_n[LETTER_WIDTH] PROGMEM = {
    {.angle =   0U, .mask = MASK16(0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0)},
    {.angle =   3U, .mask = MASK16(0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0)},
    {.angle =   6U, .mask = MASK16(0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0)},
    {.angle =   9U, .mask = MASK16(0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0)},
};

// "o"
const pattern_t char_o[LETTER_WIDTH] PROGMEM = {
    {.angle =   0U, .mask = MASK16(0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0)},
    {.angle =   3U, .mask = MASK16(0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0)},
    {.angle =   6U, .mask = MASK16(0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0)},
    {.angle =   9U, .mask = MASK16(0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0)},
};

// "p"
const pattern_t char_p[LETTER_WIDTH] PROGMEM = {
    {.angle =   0U, .mask = MASK16(0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0)},
    {.angle =   3U, .mask = MASK16(0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0)},
    {.angle =   6U, .mask = MASK16(0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0)},
    {.angle =   9U, .mask = MASK16(0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0)},
};

// "q"
const pattern_t char_q[LETTER_WIDTH] PROGMEM = {
    {.angle =   0U, .mask = MASK16(0,0,0,0,0,0,1,1,1,1,0,1,0,0,0,0)},
    {.angle =   3U, .mask = MASK16(0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0)},
    {.angle =   6U, .mask = MASK16(0,0,0,0,0,1,0,0,0,1,1,0,0,0,0,0)},
    {.angle =   9U, .mask = MASK16(0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0)},
};

// "r"
const pattern_t char_r[LETTER_WIDTH] PROGMEM = {
    {.angle =   0U, .mask = MASK16(0,0,0,0,0,1,1,0,0,0,1,0,0,0,0,0)},
    {.angle =   3U, .mask = MASK16(0,0,0,0,1,0,0,1,0,1,0,0,0,0,0,0)},
    {.angle =   6U, .mask = MASK16(0,0,0,0,1,0,0,1,1,0,0,0,0,0,0,0)},
    {.angle =   9U, .mask = MASK16(0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0)},
};

// "s"
const pattern_t char_s[LETTER_WIDTH] PROGMEM = {
    {.angle =   0U, .mask = MASK16(0,0,0,0,1,0,0,0,1,1,0,0,0,0,0,0)},
    {.angle =   3U, .mask = MASK16(0,0,0,0,1,0,0,1,0,0,1,0,0,0,0,0)},
    {.angle =   6U, .mask = MASK16(0,0,0,0,1,0,0,1,0,0,1,0,0,0,0,0)},
    {.angle =   9U, .mask = MASK16(0,0,0,0,0,1,1,0,0,0,1,0,0,0,0,0)},
};

// "t"
const pattern_t char_t[LETTER_WIDTH] PROGMEM = {
    {.angle =   0U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
    {.angle =   3U, .mask = MASK16(0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0)},
    {.angle =   6U, .mask = MASK16(0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0)},
    {.angle =   9U, .mask = MASK16(0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0)},
};

// "u"
const pattern_t char_u[LETTER_WIDTH] PROGMEM = {
    {.angle =   0U, .mask = MASK16(0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0)},
    {.angle =   3U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0)},
    {.angle =   6U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0)},
    {.angle =   9U, .mask = MASK16(0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0)},
};

// "v"
const pattern_t char_v[LETTER_WIDTH] PROGMEM = {
    {.angle =   0U, .mask = MASK16(0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0)},
    {.angle =   3U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0)},
    {.angle =   6U, .mask = MASK16(0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0)},
    {.angle =   9U, .mask = MASK16(0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0)},
};

// "w"
const pattern_t char_w[WIDE_LETTER_WIDTH] PROGMEM = {
    {.angle =   0U, .mask = MASK16(0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0)},
    {.angle =   3U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0)},
    {.angle =   6U, .mask = MASK16(0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0)},
    {.angle =   9U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0)},
    {.angle =   9U, .mask = MASK16(0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0)}
};

// "x"
const pattern_t char_x[LETTER_WIDTH] PROGMEM = {
    {.angle =   0U, .mask = MASK16(0,0,0,0,0,1,1,0,1,1,1,0,0,0,0,0)},
    {.angle =   3U, .mask = MASK16(0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0)},
    {.angle =   6U, .mask = MASK16(0,0,0,0,0,1,1,0,1,1,1,0,0,0,0,0)},
    {.angle =   9U, .mask = MASK16(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)},
};

// "y"
const pattern_t char_y[LETTER_WIDTH] PROGMEM = {
    {.angle =   0U, .mask = MASK16(0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0)},
    {.angle =   3U, .mask = MASK16(0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0)},
    {.angle =   6U, .mask = MASK16(0,0,0,0,0,0,1,0,0,1,1,0,0,0,0,0)},
    {.angle =   9U, .mask = MASK16(0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0)},
};

// "z"
const pattern_t char_z[LETTER_WIDTH] PROGMEM = {
    {.angle =   0U, .mask = MASK16(0,0,0,0,1,1,0,0,0,0,1,0,0,0,0,0)},
    {.angle =   3U, .mask = MASK16(0,0,0,0,1,0,1,1,0,0,1,0,0,0,0,0)},
    {.angle =   6U, .mask = MASK16(0,0,0,0,1,0,0,0,1,0,1,0,0,0,0,0)},
    {.angle =   9U, .mask = MASK16(0,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0)},
};

// on initialise 'hello' comme message par défaut et les flags associés
volatile char message_buffer[MAX_MESSAGE_LENGTH] = {'h','e','l','l','o','\0'};
volatile uint8_t new_message = 1;
volatile uint8_t current_message_active = 1;

// tabeau de letter_entry_t en PROGMEM pour l'alphabet
const letter_entry_t alphabet[ALPHABET_SIZE] PROGMEM = {
    [CHAR_A] = { .pattern = char_a, .width = LETTER_WIDTH },
    [CHAR_B] = { .pattern = char_b, .width = LETTER_WIDTH },
    [CHAR_C] = { .pattern = char_c, .width = LETTER_WIDTH },
    [CHAR_D] = { .pattern = char_d, .width = LETTER_WIDTH },
    [CHAR_E] = { .pattern = char_e, .width = LETTER_WIDTH },
    [CHAR_F] = { .pattern = char_f, .width = LETTER_WIDTH },
    [CHAR_G] = { .pattern = char_g, .width = LETTER_WIDTH },
    [CHAR_H] = { .pattern = char_h, .width = LETTER_WIDTH },
    [CHAR_I] = { .pattern = char_i, .width = THIN_LETTER_WIDTH },
    [CHAR_J] = { .pattern = char_j, .width = LETTER_WIDTH },
    [CHAR_K] = { .pattern = char_k, .width = LETTER_WIDTH },
    [CHAR_L] = { .pattern = char_l, .width = THIN_LETTER_WIDTH },
    [CHAR_M] = { .pattern = char_m, .width = WIDE_LETTER_WIDTH },
    [CHAR_N] = { .pattern = char_n, .width = LETTER_WIDTH },
    [CHAR_O] = { .pattern = char_o, .width = LETTER_WIDTH },
    [CHAR_P] = { .pattern = char_p, .width = LETTER_WIDTH },
    [CHAR_Q] = { .pattern = char_q, .width = LETTER_WIDTH },
    [CHAR_R] = { .pattern = char_r, .width = LETTER_WIDTH },
    [CHAR_S] = { .pattern = char_s, .width = LETTER_WIDTH },
    [CHAR_T] = { .pattern = char_t, .width = LETTER_WIDTH },
    [CHAR_U] = { .pattern = char_u, .width = LETTER_WIDTH },
    [CHAR_V] = { .pattern = char_v, .width = LETTER_WIDTH },
    [CHAR_W] = { .pattern = char_w, .width = WIDE_LETTER_WIDTH },
    [CHAR_X] = { .pattern = char_x, .width = LETTER_WIDTH },
    [CHAR_Y] = { .pattern = char_y, .width = LETTER_WIDTH },
    [CHAR_Z] = { .pattern = char_z, .width = LETTER_WIDTH }
};

// Superpose un symbole (chiffre, ou ":") sur le buffer à un index donné
void superpose_symbol(const pattern_t *symbol_pattern, uint8_t pattern_width, int pattern_index) {
    // on parcourt chaque mask du pattern_t qu'on veut superposer
    for (uint8_t i = 0; i < pattern_width; i++) {
        int target_index = pattern_index + i;
        // si l'index cible est hors limites, on skip
        if (target_index < 0 || target_index >= CLOCK_PATTERN_SIZE) continue;
        // va lire depuis PROGMEM le mask du symbole à superposer
        uint16_t mask = pgm_read_word(&(symbol_pattern[i].mask));
        // le |= fait une superposition, colle sans supprimer ce qui y était déjà
        display_pattern_buffer[target_index].mask |= mask;
    }
}

// inverse latéralemennt un mask le 1er elt devuent le dernier etc
uint16_t reverse_mask(uint16_t mask) {
    uint16_t result = 0;
    for (int i = 0; i < 16; i++) {
        if (mask & (1 << i)) {
            result |= (1 << (15 - i));
        }
    }
    return result;
}

// superpose un symbole (chiffre, ou ":") inversé sur le buffer à un index donné
// utile pour les patterns de chuiffres qu'on veut afficher en haut dans le message, 
// mais qui sont prévus pour aller en bas (donc à inverser)
// et commmence à afficher le dernier élément du pattern à l'index donné + la largeur du pattern
void superpose_symbol_reversed(const pattern_t *symbol_pattern, uint8_t pattern_width, int pattern_index) {
    // On affiche le pattern en miroir : le dernier élément du pattern devient le premier affiché
    for (uint8_t i = 0; i < pattern_width; i++) {
        int target_index = pattern_index + i;
        if (target_index < 0 || target_index >= CLOCK_PATTERN_SIZE) continue;
        // On lit le mask en partant de la fin du pattern
        uint16_t mask = pgm_read_word(&(symbol_pattern[pattern_width - 1 - i].mask));
        mask = reverse_mask(mask);
        display_pattern_buffer[target_index].mask |= mask;
    }
}

// superpose un message en entier sur le template
void superpose_message(char *message_buffer) {

    // buffer vide pour le message nettoyé
    char clean_buffer[MAX_MESSAGE_LENGTH];
    uint8_t clean_length = 0;
    // on nettoie le message pour ne garder que les caractères valides (a-z,0-9)
    for (uint8_t i = 0; i < strlen(message_buffer); ++i) {
        char c = message_buffer[i];
        if ((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) {
            clean_buffer[clean_length++] = c;
        }
    }
    // finir la chaîne 
    clean_buffer[clean_length] = '\0';

    // liste des angles où doivent tomber les lettres
    int angles[clean_length];
    int center_angle = 0;
    int letter_spacing = 20; // écart angulaire entre chaque début de lettre
    // on remplit angles[] en centrant le message autour de center_angle
    for (int i = 0; i < clean_length; ++i) {
        double offset = ((clean_length - 1) / 2.0 - i) * letter_spacing;
        int angle = (int)(center_angle + offset + 360) % 360;
        angles[i] = angle;
    }

    // liste des index dans display_pattern_buffer correspondant aux angles
    int idx[clean_length];
    for (int i = 0; i < clean_length; ++i) {
        idx[i] = find_index_by_angle_nearest(display_pattern_buffer, CLOCK_PATTERN_SIZE, angles[i]);
    }

    for(int i = 0; i < clean_length; ++i){
        char c = clean_buffer[i];
        // si c est une lettre on la superpose normalement
        if (c >= 'a' && c <= 'z') {
            superpose_symbol(
                // lire depuis progmem le pattern correspondant à la bonne lettre 
                // dans le tableau alphabet[], et sa largeur aussi.
                pgm_read_ptr(&(alphabet[(uint8_t)c - 'a'].pattern)), 
                pgm_read_byte(&(alphabet[(uint8_t)c - 'a'].width)), 
                idx[i]);
        }
        // si c est un chiffre on le superpose en miroir 
        else if (c >= '0' && c <= '9') 
        {
            superpose_symbol_reversed(
                symbol_patterns[(uint8_t)c - '0'],
                NUMBER_WIDTH,
                idx[i]);
        }
    }
}

// tableua de pointeurs vers les patterns des symboles 1,2,3,...9 et ":"
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

// superpose l'heure actuelle en format HH:MM:SS sur le template arrondi
// (c'est a peu près la même logique que superpose_message())
void superpose_hour_rounded() {
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
        angles[i] = (int)(angle_start +i * angle_step + 0.5); 
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

// fonction de maj de la clock rounded
// sera appelée dans le main loop de start_clock.c ssi le mode rounded_d_clock est actif
void update_rounded_d_clock(){
    load_template(rounded_clock_base_pattern);

    superpose_hour_rounded();

    if(new_message){
        current_message_active = 1;
        new_message = 0;
    }
    if(current_message_active){
        superpose_message((char *)message_buffer);
    }
}



