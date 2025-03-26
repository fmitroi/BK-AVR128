#include "../lib/board.h"

int main(void)
{
    BoardInit();
    LedsInit();
    LatchInit();

    while (1)
    {
        LedSet(LED1);
        _delay_ms(100);
        LedClear(LED1);
        _delay_ms(100);

        LatchLeds_On();
        _delay_ms(10);
        LatchLeds_Off();
    }
    
}