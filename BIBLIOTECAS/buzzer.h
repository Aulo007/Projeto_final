#ifndef BUZZER_H
#define BUZZER_H

#include "pico/stdlib.h"

#define BUZZ 14

// Inicialização do buzzer
void buzzer_init(void);

// Ligar buzzer
void buzzer_on(void);

// Desligar buzzer
void buzzer_off(void);

// Tocar um breve som
void buzzer_beep(void);

#endif // BUZZER_H