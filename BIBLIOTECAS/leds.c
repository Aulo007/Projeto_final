#include "leds.h"

static uint led_pins[9] = {
    LED1_R, LED1_G, LED1_B,
    LED2_R, LED2_G, LED2_B,
    LED3_R, LED3_G, LED3_B};

void led_init(void)
{
    for (int i = 0; i < 9; i++)
    {
        gpio_init(led_pins[i]);
        gpio_set_dir(led_pins[i], GPIO_OUT);
    }
}

void sequential_led(void)
{
    for (int i = 0; i < 9; i++)
    {
        gpio_put(led_pins[i], 1);
        sleep_ms(300);
        gpio_put(led_pins[i], 0);
    }
}
