#include "../lib/board.h"

int main(void)
{
    MCU_SavePowerInit();  
    PORTB_set_pin_dir(4, PORT_DIR_OUT);
    PORTB_set_pin_level(4, false);
    BuzzerOFF();

    while (1)
    {
        PORTB_set_pin_level(4, true);
        _delay_ms(100);
        PORTB_set_pin_level(4, false);
        _delay_ms(100);
    }
    
}