#include "leds.h"
#include "hardware/pwm.h"

// Configuração do PWM
static uint slice_num_red;

void led_init(void)
{
    // Inicializa LED verde como GPIO normal
    gpio_init(LED_GREEN_PIN);
    gpio_set_dir(LED_GREEN_PIN, GPIO_OUT);

    // Inicializa LED vermelho como PWM

    gpio_set_function(LED_RED_PIN, GPIO_FUNC_PWM);
    uint slice = pwm_gpio_to_slice_num(LED_RED_PIN);
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 1.0f); // Define o divisor de clock para evitar flickering
    pwm_config_set_wrap(&config, 4095);   // Mesma resolução do ADC
    pwm_init(slice, &config, true);
}

void update_leds(int estado_atual, float intensidade)
{
    // Primeiro, desliga todos os LEDs
    turn_off_leds();

    if (estado_atual == ESTADO_ESTAVEL)
    {
        // Acende o LED verde
        gpio_put(LED_GREEN_PIN, 1);
    }
    else if (estado_atual == ESTADO_INSTAVEL)
    {
        // Calcula a intensidade do LED vermelho (0-255)
        uint16_t pwm_value = (uint16_t)(intensidade * 50 * 255.0f);
        if (pwm_value > 255)
            pwm_value = 255;

        // Atualiza o PWM do LED vermelho
        pwm_set_gpio_level(LED_RED_PIN, 255);
    }
}

void turn_off_leds(void)
{
    // Desliga LED verde
    gpio_put(LED_GREEN_PIN, 0);

    // Desliga LED vermelho (PWM = 0)
    pwm_set_chan_level(slice_num_red, PWM_CHAN_A, 0);
}