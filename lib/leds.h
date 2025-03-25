#ifndef LEDS_H
#define LEDS__H

#ifndef F_CPU
#define F_CPU   8000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include "74hc573.h"

#define LEDS_DDR    DDRA
#define LEDS_PORT   PORTA
#define HIGH        0
#define LOW         1

// Leds Aliases
#define LED1 0
#define LED2 1
#define LED3 2
#define LED4 3
#define LED5 4
#define LED6 5
#define LED7 6
#define LED8 7

void LedsInit(void);
void LedShuffle(void);
void LedSet(uint8_t bit,uint8_t state);



#endif