#include "joystick.h"
#include "hardware/gpio.h"

#define VRY_PIN 27
#define VRX_PIN 26
#define SW_PIN 22

static volatile bool pwm_enabled = true;

void joystick_init(void)
{
    adc_init();
    adc_gpio_init(VRX_PIN);
    adc_gpio_init(VRY_PIN);

    gpio_init(SW_PIN);
    gpio_set_dir(SW_PIN, GPIO_IN);
    gpio_pull_up(SW_PIN);
}

void joystick_read_values(uint16_t *x, uint16_t *y)
{
    adc_select_input(1);
    *x = adc_read();
    adc_select_input(0);
    *y = adc_read();
}

bool joystick_is_pwm_enabled(void)
{
    return pwm_enabled;
}

void joystick_setup_pwm(uint gpio)
{
    gpio_set_function(gpio, GPIO_FUNC_PWM);
    uint slice = pwm_gpio_to_slice_num(gpio);
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 1.0f);
    pwm_config_set_wrap(&config, 4095);
    pwm_init(slice, &config, true);
}

void joystick_set_pwm(uint gpio, uint16_t value)
{
    if (pwm_enabled)
        pwm_set_gpio_level(gpio, value);
    else
        pwm_set_gpio_level(gpio, 0);
}

uint16_t joystick_map_to_pwm(uint16_t value)
{
    int16_t centered = value - 2048;
    if (abs(centered) < 100)
        return 0;
    return (uint16_t)abs(centered);
}