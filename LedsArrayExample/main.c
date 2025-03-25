#include "../lib/leds.h"

int main(void)
{
    LedsInit();

    while(1)
{
    LedSet(LED1, HIGH);
    _delay_ms(250);
    LedSet(LED1, LOW);
    _delay_ms(250);
}

}