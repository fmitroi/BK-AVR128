#include "../lib/leds.h"

int main(void)
{
    LedsInit();

    while(1)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        LEDS_PORT |= (1 << i);
        _delay_ms(100);
        LedClearPort();
        
    }
    
}

}