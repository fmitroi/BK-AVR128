#include "leds.h"

void LedsInit(void)
{
    LEDS_DDR = 0XFF;    // All PORTA as Output
    LEDS_PORT = 0XFF;   // Leds Off
    LatchInit();        // Init 74HC573
    LatchLeds_On();     // Active 74HC573 Outputs

    // Five short blinks on Leds Init
    for(uint8_t counter = 0; counter < 10; counter++)
    {
        LEDS_PORT ^= 0XFF;  // Toggle All PORTA
        _delay_ms(50);
    }
}

void LedSet(uint8_t bit, uint8_t state)
{
    if (bit > 7) return;
    if(state == HIGH)
    {
        LEDS_PORT &= ~(1 << bit);
    } 
    else
    {
        LEDS_PORT |= (1 << bit);
    }
}

void LedShuffle(void)
{
        for (uint8_t i = 0; i < 8; i++) 
        {
            LedSet(i, HIGH);    // Led On
            _delay_ms(100);     // Wait for 100ms
            LedSet(i, LOW);     // Led Off
            _delay_ms(100);     // Wait for 100ms
        }    
}