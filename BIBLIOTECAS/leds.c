#include "leds.h"

static uint led_pins[3] = {
    LED_BLUE_PIN, LED_GREEN_PIN, LED_RED_PIN

};

void led_init(void)
{
    for (int i = 0; i < 3; i++)
    {
        gpio_init(led_pins[i]);
        gpio_set_dir(led_pins[i], GPIO_OUT);
    }
}

void sequential_led(void)
{
    for (int i = 0; i < 3; i++)
    {
        gpio_put(led_pins[i], 1);
        sleep_ms(300);
        gpio_put(led_pins[i], 0);
    }
}
