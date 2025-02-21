#include <stdio.h>
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

// Definindo pinos do Botão A
static const uint32_t BUTTON_A = 5;
static const uint32_t BUTTON_B = 6;

// Definindo constantes para os parâmetros do I2C e do ssd
#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define endereco 0x3C

// Variáveis globais
static ssd1306_t ssd; // Variável global para o ssd
static volatile uint8_t border_style = 0;
static volatile bool calibracao_loading = false;
static volatile bool calibracao_realizada = false;
static volatile uint32_t last_button_time = 0;
static volatile int musculosRelaxados_valor = 0;
const uint32_t DEBOUNCE_DELAY = 200000; // 200ms em microssegundos

// Estrutura para armazenar os dados dos sensores
/*
typedef struct
{
    int nivelTensaoMuscular;
    int frequenciaRespiratoria;
    int qualidadeAr;
    bool arLimpo;
    bool musculosRelaxados;
    bool respiracaoRegular;
}
*/

static void gpio_irq_handle(uint gpio, uint32_t events); // Função para a interrupção
static void calibrar_sensores();

int main(void)
{
    // Inicialização do I2C a 400 kHz
    i2c_init(I2C_PORT, 400 * 1000);

    // Inicializando 3 botões
    gpio_init(SW_PIN);
    gpio_init(BUTTON_A);
    gpio_init(BUTTON_B);

    // Configurando direção dos botões para entrada
    gpio_set_dir(SW_PIN, GPIO_IN);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_set_dir(BUTTON_B, GPIO_IN);

    // Ativando pull up interno para os botões.
    gpio_pull_up(SW_PIN);
    gpio_pull_up(BUTTON_A);
    gpio_pull_up(BUTTON_B);

    // Configura os pinos GPIO para a função I2C
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C); // Configura o pino de dados para I2C
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C); // Configura o pino de clock para I2C
    gpio_pull_up(I2C_SDA);                     // Ativa o pull-up no pino de dados
    gpio_pull_up(I2C_SCL);                     // Ativa o pull-up no pino de clock

    // Inicialização e configuração do ssd SSD1306                                               // Cria a estrutura do ssd
    ssd1306_init(&ssd, WIDTH, HEIGHT, false, endereco, I2C_PORT); // Inicializa o ssd com as especificações fornecidas
    ssd1306_config(&ssd);                                         // Configura os parâmetros do ssd
    ssd1306_send_data(&ssd);                                      // Envia os dados iniciais de configuração para o ssd

    // Limpeza do ssd. O ssd inicia com todos os pixels apagados.
    ssd1306_fill(&ssd, false); // Preenche o ssd com o valor especificado (false = apagado)
    ssd1306_send_data(&ssd);   // Envia os dados de preenchimento para o ssd

    ssd1306_fill(&ssd, false);
    ssd1306_draw_bitmap(&ssd, 0, 0, mensagem_sem_calibrar, 128, 64);
    ssd1306_send_data(&ssd);

    uint16_t adc_value_x;
    uint16_t adc_value_y;

    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handle);
    gpio_set_irq_enabled_with_callback(BUTTON_B, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handle);

    while (true)

    {

        /*
Explicação sobre os valores lidos do ADC, acontece que, ao usar o código exemplo, no qual configura o pino 26 como eixo x e 27 como eixo y, uma coisa me incomodou
no caso, ele lia nessa configuração o x na direção vertical do joystick e y na honrizontal.
*/

        // Seleciona o ADC para eixo Y. O pino 26 como entrada analógica
        adc_select_input(0);
        adc_value_y = adc_read(); // Inverte o valor lido do eixo Y

        // Seleciona o ADC para eixo X. O pino 27 como entrada analógica
        adc_select_input(1);
        adc_value_x = adc_read(); // Inverte o valor lido do eixo X

        if (calibracao_loading == true)
        {
            sleep_ms(200);
        }

        if (calibracao_loading == true && calibracao_realizada == true)
        {
            sleep_ms(200);
        }
    }
}

static void gpio_irq_handle(uint gpio, uint32_t events)
{
    // Cria uma varíavel que pega o tempo atual do sistema em microsegundos.
    uint32_t current_time_us = to_us_since_boot(get_absolute_time());
    char str[20];

    if (current_time_us - last_button_time > DEBOUNCE_DELAY)

    {
        last_button_time = current_time_us;
        if (gpio == BUTTON_A)
        {
            printf("oi");
        }
        else if (gpio == BUTTON_B)
        {
            if (calibracao_loading == true)
            {
                printf("oi");
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
