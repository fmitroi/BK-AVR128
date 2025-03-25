#include "../lib/board.h"

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

int main(void)
{
    LatchInit();
    LatchSegments_On();
    LatchDigits_On();
    LatchLeds_On();
}