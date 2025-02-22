#include <stdio.h>
#include <math.h> // Necessário para sqrt()
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/pwm.h"
#include "hardware/i2c.h"
#include "BIBLIOTECAS/ssd1306.h"
#include "BIBLIOTECAS/buzzer.h"
#include "BIBLIOTECAS/desenho.h"
#include "BIBLIOTECAS/leds.h"
#include "BIBLIOTECAS/matrizRGB.h"
#include "BIBLIOTECAS/menu.h"
#include "BIBLIOTECAS/bitmaps.h"

// Definindo pinos do joystick
static const uint32_t VRY_PIN = 27;
static const uint32_t VRX_PIN = 26;
static const uint32_t SW_PIN = 22;

// Definindo pinos dos Botões A e B
static const uint32_t BUTTON_A = 5;
static const uint32_t BUTTON_B = 6;

// Definindo pino do microfone
const uint microfone = 28; // GPIO28 para ADC2 (Microfone)

// Definindo constantes para os parâmetros do I2C e do SSD1306
#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define endereco 0x3C

// Variáveis globais
static ssd1306_t ssd; // Variável global para o SSD1306
static volatile uint8_t border_style = 0;
static volatile bool calibracao_loading = false;
static volatile bool calibracao_realizada = false;
static volatile uint32_t last_button_time = 0;
static volatile int Eletromiografia_calibrado = 0;                  // Valor médio calibrado do microfone
static volatile int Sensor_de_Respiracao_calibrado = 0;             // Valor médio calibrado do joystick (eixo X)
static volatile int Sensor_de_Qualidade_do_Ar_calibrado = 0;        // Valor médio calibrado do joystick (eixo Y)
static volatile int Eletromiografia_calibrado_desvio = 0;           // Desvio  calibrado do microfone
static volatile int Sensor_de_Respiracao_calibrado_desvio = 0;      // Desvio calibrado do joystick (eixo X)
static volatile int Sensor_de_Qualidade_do_Ar_calibrado_desvio = 0; // Desvio médio calibrado do joystick (eixo Y)

const uint32_t DEBOUNCE_DELAY = 200000; // 200ms em microssegundos

// Variáveis para leitura do ADC
uint16_t adc_value_x;
uint16_t adc_value_y;
uint16_t mic_value;

static void gpio_irq_handle(uint gpio, uint32_t events); // Função para a interrupção

int main(void)
{
    // Inicializa comunicação serial
    stdio_init_all();

    // Configuração do ADC
    adc_init();
    adc_gpio_init(VRX_PIN);
    adc_gpio_init(VRY_PIN);
    adc_gpio_init(microfone); // Configura GPIO28 como entrada ADC para o microfone

    // Inicialização do I2C a 400 kHz
    i2c_init(I2C_PORT, 400 * 1000);

    // Inicializando os botões
    gpio_init(SW_PIN);
    gpio_init(BUTTON_A);
    gpio_init(BUTTON_B);

    // Configurando os pinos dos botões como entrada com pull-up
    gpio_set_dir(SW_PIN, GPIO_IN);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_set_dir(BUTTON_B, GPIO_IN);
    gpio_pull_up(SW_PIN);
    gpio_pull_up(BUTTON_A);
    gpio_pull_up(BUTTON_B);

    // Configura os pinos para a função I2C
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    // Inicialização e configuração do SSD1306
    ssd1306_init(&ssd, WIDTH, HEIGHT, false, endereco, I2C_PORT);
    ssd1306_config(&ssd);
    ssd1306_send_data(&ssd);

    // Limpa o SSD1306 e exibe mensagem de "sem calibrar"
    ssd1306_fill(&ssd, false);
    ssd1306_send_data(&ssd);
    ssd1306_fill(&ssd, false);
    ssd1306_draw_bitmap(&ssd, 0, 0, mensagem_sem_calibrar, 128, 64);
    ssd1306_send_data(&ssd);

    // Configura as interrupções para os botões
    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handle);
    gpio_set_irq_enabled_with_callback(BUTTON_B, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handle);

    while (true)
    {
        /*
         * Leitura dos sensores fora do modo de calibração:
         * (Note que os valores lidos aqui podem ser usados para outras funções,
         * mas durante a calibração, eles serão atualizados novamente dentro do loop)
         */
        adc_select_input(0);
        adc_value_y = adc_read();

        adc_select_input(1);
        adc_value_x = adc_read();

        adc_select_input(2);
        mic_value = adc_read();

        // Se a calibração estiver em andamento, entre no bloco de calibração
        if (calibracao_loading)
        {
            // Variáveis locais para acumular os valores e os quadrados
            int contador_calibracao = 0;
            unsigned long long soma_mic = 0;
            unsigned long long soma_mic_sq = 0;
            unsigned long long soma_adc_x = 0;
            unsigned long long soma_adc_x_sq = 0;
            unsigned long long soma_adc_y = 0;
            unsigned long long soma_adc_y_sq = 0;

            do
            {
                // Releia os valores dos sensores para cada amostra
                adc_select_input(0);
                adc_value_y = adc_read();
                adc_select_input(1);
                adc_value_x = adc_read();
                adc_select_input(2);
                mic_value = adc_read();

                // Acumula os valores e os quadrados para os cálculos estatísticos
                soma_mic += mic_value;
                soma_mic_sq += (unsigned long long)mic_value * mic_value;
                soma_adc_x += adc_value_x;
                soma_adc_x_sq += (unsigned long long)adc_value_x * adc_value_x;
                soma_adc_y += adc_value_y;
                soma_adc_y_sq += (unsigned long long)adc_value_y * adc_value_y;

                contador_calibracao++;
                sleep_us(50); // Coleta uma amostra a cada 50 µs.
            } while (contador_calibracao < 100000); // 100.000 amostras

            // Cálculo da média (valores inteiros)
            Eletromiografia_calibrado = soma_mic / contador_calibracao;
            Sensor_de_Respiracao_calibrado = soma_adc_x / contador_calibracao;
            Sensor_de_Qualidade_do_Ar_calibrado = soma_adc_y / contador_calibracao;

            // Cálculo da variância (usando divisão inteira)
            int var_mic = (soma_mic_sq / contador_calibracao) - (Eletromiografia_calibrado * Eletromiografia_calibrado);
            int var_adc_x = (soma_adc_x_sq / contador_calibracao) - (Sensor_de_Respiracao_calibrado * Sensor_de_Respiracao_calibrado);
            int var_adc_y = (soma_adc_y_sq / contador_calibracao) - (Sensor_de_Qualidade_do_Ar_calibrado * Sensor_de_Qualidade_do_Ar_calibrado);

            // Cálculo do desvio padrão (convertido para inteiro)
            int Eletromiografia_calibrado_desvio = (int)sqrt(var_mic);
            int Sensor_de_Respiracao_calibrado_desvio = (int)sqrt(var_adc_x);
            int Sensor_de_Qualidade_do_Ar_calibrado_desvio = (int)sqrt(var_adc_y);

            calibracao_realizada = true;
            calibracao_loading = false; // Finaliza a calibração para não repetir

            // Exibe os resultados da calibração
            printf("Valor do mic calibrado: Média = %d, Desvio = %d\n", Eletromiografia_calibrado, Eletromiografia_calibrado_desvio);
            printf("Valor da respiração calibrado: Média = %d, Desvio = %d\n", Sensor_de_Respiracao_calibrado, Sensor_de_Respiracao_calibrado_desvio);
            printf("Valor da qualidade do ar calibrado: Média = %d, Desvio = %d\n", Sensor_de_Qualidade_do_Ar_calibrado, Sensor_de_Qualidade_do_Ar_calibrado_desvio);
        }

        // Caso a calibração esteja em andamento e já tenha sido realizada, aguarda um tempo
        if (calibracao_realizada)
        {
            sleep_ms(200);
        }
    }
}

static void gpio_irq_handle(uint gpio, uint32_t events)
{
    // Obtém o tempo atual em microssegundos
    uint32_t current_time_us = to_us_since_boot(get_absolute_time());

    if (current_time_us - last_button_time > DEBOUNCE_DELAY)
    {
        last_button_time = current_time_us;
        if (gpio == BUTTON_A)
        {
            printf("oi\n");
        }
        else if (gpio == BUTTON_B)
        {
            if (calibracao_realizada == true)
            {
                printf("oi\n");
            }
            else
            {
                ssd1306_fill(&ssd, false);
                ssd1306_send_data(&ssd);
                calibracao_loading = true;
            }
        }
    }
}
