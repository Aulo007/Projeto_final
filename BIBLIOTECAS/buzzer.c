#include "buzzer.h"

void buzzer_init(void)
{
    gpio_init(BUZZ);
    gpio_set_dir(BUZZ, GPIO_OUT);
}

void buzzer_on(void)
{
    gpio_put(BUZZ, 1);
}

void buzzer_off(void)
{
    gpio_put(BUZZ, 0);
}

void buzzer_beep(void)
{
    buzzer_on();
    sleep_ms(300);
    buzzer_off();
    sleep_ms(300);
}