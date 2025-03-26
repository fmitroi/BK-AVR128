#include "../lib/board.h"

int main(void)
{   
    MCU_SavePowerInit();                            // Call function to deactivate periferals
    PORT_SetPinDirection(&PORTE,7,PORT_DIR_OUT);    // PE7 as Output
    PORT_WritePin(&PORTE,7,false);                  // Start PE7 in Low


    while (1)
    {
        PORT_WritePin(&PORTE, 7, true);             // PE7 High
        _delay_ms(50);                              // Wait for 50ms
        PORT_WritePin(&PORTE, 7 , false);           // PE7 Low
        _delay_ms(950);                             // Wait for 950ms
    }
    
}