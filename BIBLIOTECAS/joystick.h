#pragma once
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/pwm.h"

void joystick_init(void);
void joystick_read_values(uint16_t *x, uint16_t *y);
bool joystick_is_pwm_enabled(void);
void joystick_setup_pwm(uint gpio);
void joystick_set_pwm(uint gpio, uint16_t value);
uint16_t joystick_map_to_pwm(uint16_t value);