#ifndef LED_CONTROL_H
#define LED_CONTROL_H

#include "pico/stdlib.h"

// Definições dos pinos de LED
#define LED_GREEN_PIN 11
#define LED_BLUE_PIN 12
#define LED_RED_PIN 13

// Inicialização dos LEDs
void led_init(void);

void sequential_led(void);

// Adicione mais funções aqui

#endif // LED_CONTROL_H