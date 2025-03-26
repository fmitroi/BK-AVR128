#include "../lib/board.h"

int main(void) {
    ButtonsInit();
    LedsInit();
    LatchInit();

    while(1) {
        uint8_t btn = ButtonsRead();

        switch (btn) {
            case 1:  // Botón 17 (PD0)
                LedSet(LED1, HIGH);  // LED 1 encendido (PA0 = 0)
                LedSet(LED2, LOW);   // LED 2 apagado (PA1 = 1)
                LedSet(LED3, LOW);   // LED 3 apagado (PA2 = 1)
                LedSet(LED4, LOW);   // LED 4 apagado (PA3 = 1)
                break;
            case 2:  // Botón 18 (PD1)
                LedSet(LED1, LOW);   // LED 1 apagado
                LedSet(LED2, HIGH);  // LED 2 encendido
                LedSet(LED3, LOW);   // LED 3 apagado
                LedSet(LED4, LOW);   // LED 4 apagado
                break;
            case 3:  // Botón 19 (PD2)
                LedSet(LED1, LOW);   // LED 1 apagado
                LedSet(LED2, LOW);   // LED 2 apagado
                LedSet(LED3, HIGH);  // LED 3 encendido
                LedSet(LED4, LOW);   // LED 4 apagado
                break;
            case 4:  // Botón 20 (PD3)
                LedSet(LED1, LOW);   // LED 1 apagado
                LedSet(LED2, LOW);   // LED 2 apagado
                LedSet(LED3, LOW);   // LED 3 apagado
                LedSet(LED4, HIGH);  // LED 4 encendido
                break;
            default:  // Ningún botón presionado
                LedSet(LED1, LOW);
                LedSet(LED2, LOW);
                LedSet(LED3, LOW);
                LedSet(LED4, LOW);
                break;
        }

        LatchLeds_On();
        _delay_us(10);
        LatchLeds_Off();
    }
    return 0;
}