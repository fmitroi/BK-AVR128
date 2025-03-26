#ifndef BUZZER_H_
#define BUZZER_H_

#include <avr/io.h>

#define BUZZER_DIR  DDRE
#define BUZZER_PORT PORTE
#define BUZZER_PIN  PE7

static inline void BuzzerInit(void)
{
    BUZZER_DIR |= (1 << BUZZER_PIN);    // PE7 as Output
    BUZZER_PORT &= ~(1 << BUZZER_PIN);  // PE7 = 0(Buzzer Off)
}

static inline void BuzzerOn (void)
{
    BUZZER_PORT |= (1 << BUZZER_PIN);
}

static inline void BuzzerOff(void)
{
    BUZZER_PORT &= ~(1 << BUZZER_PIN);
}


#endif