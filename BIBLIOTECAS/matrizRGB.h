#ifndef MATRIZRGB_H
#define MATRIZRGB_H
#include <stdint.h>

// Definição do pixel/LED
typedef struct
{
    uint8_t G, R, B;
} npLED_t;

// Declaração de funções

void npInit(uint8_t pin);
void npClear();
void npWrite();
void setMatrizDeLEDSComIntensidade(int matriz[5][5][3], double intensidadeR, double intensidadeG, double intensidadeB);
int getIndex(int x, int y);

#endif // MATRIZRGB_H