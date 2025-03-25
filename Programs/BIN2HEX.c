#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char binario[9]; // 8 bits + terminador nulo
    int decimal;
    
    printf("Ingrese un numero binario de 8 bits: ");
    scanf("%8s", binario); // Leer hasta 8 caracteres
    
    // Verificar si la entrada tiene solo '0' o '1'
    for (int i = 0; i < 8; i++) {
        if (binario[i] != '0' && binario[i] != '1') {
            printf("Entrada invalida. Solo se permiten 0 y 1.\n");
            return 1;
        }
    }

    // Convertir binario a decimal
    decimal = strtol(binario, NULL, 2);
    
    // Imprimir en hexadecimal
    printf("El valor en hexadecimal es: 0x%02X\n", decimal);
    
    return 0;
}


