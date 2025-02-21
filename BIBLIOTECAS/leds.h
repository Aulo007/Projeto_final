#ifndef LED_CONTROL_H
#define LED_CONTROL_H

#include "pico/stdlib.h"

// Definições dos pinos de LED
#define LED1_R 16
#define LED1_G 17
#define LED1_B 18
#define LED2_R 19
#define LED2_G 20
#define LED2_B 21
#define LED3_R 22
#define LED3_G 26
#define LED3_B 27

// Inicialização dos LEDs
void led_init(void);

void sequential_led(void);

// Adicione mais funções aqui

#endif // LED_CONTROL_H