#include "../lib/board.h"

int main(void) {
    ButtonsInit();
    LedsInit();
    LatchInit();

    while(1) {
        uint8_t btn = ButtonsRead();

        switch (btn) {
            case 1:  // Botón 17 (PD0)
                LedSet(LED1);  // LED 1 encendido (PA0 = 0)
                LedSet(LED2);   // LED 2 apagado (PA1 = 1)
                LedSet(LED3);   // LED 3 apagado (PA2 = 1)
                LedSet(LED4);   // LED 4 apagado (PA3 = 1)
                break;
            case 2:  // Botón 18 (PD1)
                LedSet(LED1);   // LED 1 apagado
                LedSet(LED2);  // LED 2 encendido
                LedSet(LED3);   // LED 3 apagado
                LedSet(LED4);   // LED 4 apagado
                break;
            case 3:  // Botón 19 (PD2)
                LedSet(LED1);   // LED 1 apagado
                LedSet(LED2);   // LED 2 apagado
                LedSet(LED3);  // LED 3 encendido
                LedSet(LED4);   // LED 4 apagado
                break;
            case 4:  // Botón 20 (PD3)
                LedSet(LED1);   // LED 1 apagado
                LedSet(LED2);   // LED 2 apagado
                LedSet(LED3);   // LED 3 apagado
                LedSet(LED4);  // LED 4 encendido
                break;
            default:  // Ningún botón presionado
                LedSet(LED1);
                LedSet(LED2);
                LedSet(LED3);
                LedSet(LED4);
                break;
        }

        LatchLeds_On();
        _delay_us(10);
        LatchLeds_Off();
    }
    return 0;
}