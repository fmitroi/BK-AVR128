#include "../lib/leds.h"

int main(void)
{
    LedsInit();

    while(1)
{
    LedShuffle();
}

}