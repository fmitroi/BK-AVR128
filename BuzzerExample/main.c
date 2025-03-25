#include "../lib/board.h"

int main(void)
{   
    MCU_LowPowerInit();
    PORTE_set_pin_dir(7, PORT_DIR_OUT);
    PORTE_set_pin_level(7, false);


    while (1)
    {
        PORTE_set_pin_level(7, true);
        _delay_ms(50);
        PORTE_set_pin_level(7, false);
        _delay_ms(950);
    }
    
}