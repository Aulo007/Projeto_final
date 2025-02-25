#ifndef LED_CONTROL_H
#define LED_CONTROL_H

#include "pico/stdlib.h"

// Definições dos pinos de LED
#define LED_GREEN_PIN 11
#define LED_RED_PIN 13

// Definições de estados
#define ESTADO_ESTAVEL 1
#define ESTADO_INSTAVEL 2

// Inicialização dos LEDs
void led_init(void);

// Controle dos LEDs baseado no estado e intensidade
void update_leds(int estado_atual, float intensidade);

// Desliga todos os LEDs
void turn_off_leds(void);

#endif // LED_CONTROL_H