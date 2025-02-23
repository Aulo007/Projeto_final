#include <stdio.h>
#include <stdlib.h>
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
#include "BIBLIOTECAS/conversor.h"

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
static volatile uint32_t last_calibration_time = 0;
static volatile uint32_t last_running_time = 0;
static volatile int contador_imagens_estaveis = 0;                  // Contador
static volatile int contador_imagens_instaveis = 0;                 // Contador
static volatile int Eletromiografia_calibrado = 0;                  // Valor médio calibrado do microfone
static volatile int Sensor_de_Respiracao_calibrado = 0;             // Valor médio calibrado do joystick (eixo X)
static volatile int Sensor_de_Qualidade_do_Ar_calibrado = 0;        // Valor médio calibrado do joystick (eixo Y)
static volatile int Eletromiografia_calibrado_desvio = 0;           // Desvio  calibrado do microfone
static volatile int Sensor_de_Respiracao_calibrado_desvio = 0;      // Desvio calibrado do joystick (eixo X)
static volatile int Sensor_de_Qualidade_do_Ar_calibrado_desvio = 0; // Desvio médio calibrado do joystick (eixo Y)
static volatile int estado_atual = 0;                               // 0 = indefinido, 1 = estável, 2 = instável
static volatile int contador_confirmacao = 0;
#define CONFIRMACAO_NECESSARIA 3 // Número de leituras consecutivas para confirmar mudança
#define EMG_FATOR_DESVIO 1.0f
#define RESP_FATOR_DESVIO 3.0f
#define AR_FATOR_DESVIO 2.0f

const uint32_t DEBOUNCE_DELAY = 200000;            // 200ms em microssegundos
const uint32_t ANIMATION_UPDATE_INTERVAL = 400000; // 400ms em microssegundos

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

    // Inicializar o Buzzer
    buzzer_init();

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

    // Inicializa os LEDs
    led_init();

    // Limpa o SSD1306 e exibe mensagem de "sem calibrar"
    ssd1306_fill(&ssd, false);
    ssd1306_send_data(&ssd);
    ssd1306_draw_bitmap(&ssd, 0, 0, mensagem_sem_calibrar, 128, 64);
    ssd1306_send_data(&ssd);

    // Configura as interrupções para os botões
    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handle);
    gpio_set_irq_enabled(BUTTON_B, GPIO_IRQ_EDGE_FALL, true);
    gpio_set_irq_enabled(SW_PIN, GPIO_IRQ_EDGE_FALL, true); // Adiciona interrupção para o botão do joystick

    while (true)
    {
        /*
         * Leitura dos sensores fora do modo de calibração:
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
            int contador_calibracao_imagens = 0;
            uint64_t soma_mic = 0;
            uint64_t soma_mic_sq = 0;
            uint64_t soma_adc_x = 0;
            uint64_t soma_adc_x_sq = 0;
            uint64_t soma_adc_y = 0;
            uint64_t soma_adc_y_sq = 0;
            uint32_t current_calibration_us;

            last_calibration_time = to_us_since_boot(get_absolute_time());

            do
            {
                // Atualiza as leituras dentro do loop de calibração
                adc_select_input(2);
                mic_value = adc_read();

                adc_select_input(1);
                adc_value_x = adc_read();

                adc_select_input(0);
                adc_value_y = adc_read();

                // Acumula os valores e os quadrados para os cálculos estatísticos
                soma_mic += mic_value;
                soma_mic_sq += (uint64_t)mic_value * mic_value;
                soma_adc_x += adc_value_x;
                soma_adc_x_sq += (uint64_t)adc_value_x * adc_value_x;
                soma_adc_y += adc_value_y;
                soma_adc_y_sq += (uint64_t)adc_value_y * adc_value_y;

                // Atualiza o tempo atual dentro do loop
                current_calibration_us = to_us_since_boot(get_absolute_time());

                if ((current_calibration_us - last_calibration_time > ANIMATION_UPDATE_INTERVAL) && contador_calibracao_imagens < 13) // 360 ms
                {
                    ssd1306_fill(&ssd, false);
                    ssd1306_send_data(&ssd);
                    ssd1306_draw_bitmap(&ssd, 0, 0, calibration_animation[contador_calibracao_imagens], 128, 64);
                    ssd1306_send_data(&ssd);
                    last_calibration_time = current_calibration_us;
                    contador_calibracao_imagens++;
                }

                contador_calibracao++;

                sleep_us(50); // Coleta uma amostra a cada 50 µs.
            } while (contador_calibracao < 100000); // 100.000 amostras

            // Cálculo da média (valores inteiros)
            Eletromiografia_calibrado = soma_mic / contador_calibracao;
            Sensor_de_Respiracao_calibrado = soma_adc_x / contador_calibracao;
            Sensor_de_Qualidade_do_Ar_calibrado = soma_adc_y / contador_calibracao;

            // Cálculo da variância (usando divisão inteira)
            uint32_t var_mic = (soma_mic_sq / contador_calibracao) - ((uint64_t)Eletromiografia_calibrado * Eletromiografia_calibrado);
            uint32_t var_adc_x = (soma_adc_x_sq / contador_calibracao) - ((uint64_t)Sensor_de_Respiracao_calibrado * Sensor_de_Respiracao_calibrado);
            uint32_t var_adc_y = (soma_adc_y_sq / contador_calibracao) - ((uint64_t)Sensor_de_Qualidade_do_Ar_calibrado * Sensor_de_Qualidade_do_Ar_calibrado);

            // Cálculo do desvio padrão (atualiza as variáveis globais)
            Eletromiografia_calibrado_desvio = (int)sqrt(var_mic);
            Sensor_de_Respiracao_calibrado_desvio = (int)sqrt(var_adc_x);
            Sensor_de_Qualidade_do_Ar_calibrado_desvio = (int)sqrt(var_adc_y);

            calibracao_realizada = true;
            calibracao_loading = false; // Finaliza a calibração para não repetir

            // Exibe os resultados da calibração no terminal
            printf("Valor do mic calibrado: Média = %d, Desvio = %d\n", Eletromiografia_calibrado, Eletromiografia_calibrado_desvio);
            printf("Valor da respiração calibrado: Média = %d, Desvio = %d\n", Sensor_de_Respiracao_calibrado, Sensor_de_Respiracao_calibrado_desvio);
            printf("Valor da qualidade do ar calibrado: Média = %d, Desvio = %d\n", Sensor_de_Qualidade_do_Ar_calibrado, Sensor_de_Qualidade_do_Ar_calibrado_desvio);

            sleep_us(ANIMATION_UPDATE_INTERVAL / 2);

            ssd1306_fill(&ssd, false);
            ssd1306_send_data(&ssd);
            ssd1306_draw_bitmap(&ssd, 0, 0, calibracao_pronta, 128, 64);
            ssd1306_send_data(&ssd);

            sleep_us(ANIMATION_UPDATE_INTERVAL / 2);
        }

        // Exemplo de uso dos valores calibrados (fora do modo de calibração)
        if (calibracao_realizada)
        {

            uint32_t current_calibration_sucessful_us;

            // Converte todas as leituras de uma vez
            DadosSensores dados = converter_leituras(
                mic_value,   // EMG
                adc_value_x, // Respiração
                adc_value_y, // Qualidade do ar
                Eletromiografia_calibrado,
                Sensor_de_Respiracao_calibrado,
                Sensor_de_Qualidade_do_Ar_calibrado,
                Eletromiografia_calibrado_desvio,
                Sensor_de_Respiracao_calibrado_desvio,
                Sensor_de_Qualidade_do_Ar_calibrado_desvio);

            // printf("\nTensão Muscular:\n");
            // printf("Nível: %.1f%%\n", dados.tensao_muscular.nivel);
            // printf("Estado: %s\n", dados.tensao_muscular.categoria);
            // printf("Recomendação: %s\n", dados.tensao_muscular.recomendacao);

            // printf("\nRespiração:\n");
            // printf("Frequência: %.1f resp/min\n", dados.respiracao.freq);
            // printf("Estado: %s\n", dados.respiracao.categoria);
            // printf("Recomendação: %s\n", dados.respiracao.recomendacao);

            // printf("\nQualidade do Ar:\n");
            // printf("AQI: %d\n", dados.qualidade_ar.aqi);
            // printf("Estado: %s\n", dados.qualidade_ar.categoria);
            // printf("Recomendação: %s\n", dados.qualidade_ar.recomendacao);

            bool emg_condicao = abs(Eletromiografia_calibrado - mic_value) <= Eletromiografia_calibrado_desvio * EMG_FATOR_DESVIO;
            bool respiracao_condicao = abs(Sensor_de_Respiracao_calibrado - adc_value_x) <= Sensor_de_Respiracao_calibrado_desvio * RESP_FATOR_DESVIO;
            bool qualidade_ar_condicao = abs(Sensor_de_Qualidade_do_Ar_calibrado - adc_value_y) <= Sensor_de_Qualidade_do_Ar_calibrado_desvio * AR_FATOR_DESVIO;
            current_calibration_sucessful_us = to_us_since_boot(get_absolute_time());

            if (current_calibration_sucessful_us - last_running_time >= ANIMATION_UPDATE_INTERVAL)
            {
                bool condicoes_estaveis = emg_condicao && respiracao_condicao && qualidade_ar_condicao;

                // Criar buffers para as strings
                char emg_str[10];
                char resp_str[10];
                char aqi_str[10];

                // Formatar os valores
                snprintf(emg_str, sizeof(emg_str), "%.1f%%", dados.tensao_muscular.nivel);
                snprintf(resp_str, sizeof(resp_str), "%.1f", dados.respiracao.freq);
                snprintf(aqi_str, sizeof(aqi_str), "%d", dados.qualidade_ar.aqi);

                // Debug mais detalhado
                printf("EMG: %d (%d vs %d), RESP: %d (%d vs %d), AR: %d (%d vs %d), Estado: %d, Cont_Conf: %d\n",
                       emg_condicao, mic_value, Eletromiografia_calibrado,
                       respiracao_condicao, adc_value_x, Sensor_de_Respiracao_calibrado,
                       qualidade_ar_condicao, adc_value_y, Sensor_de_Qualidade_do_Ar_calibrado,
                       estado_atual, contador_confirmacao);

                // Nova lógica de transição de estado
                if (condicoes_estaveis)
                {
                    if (estado_atual != 1)
                    {
                        contador_confirmacao++;
                        if (contador_confirmacao >= CONFIRMACAO_NECESSARIA)
                        {
                            estado_atual = 1;
                            contador_imagens_estaveis = 0;
                            contador_imagens_instaveis = 0;
                            contador_confirmacao = 0;
                            printf("Transição para ESTÁVEL\n");
                        }
                    }
                    else
                    {
                        contador_confirmacao = 0; // Reset se já estiver no estado correto
                    }
                }
                else
                {
                    if (estado_atual != 2)
                    {
                        contador_confirmacao++;
                        if (contador_confirmacao >= CONFIRMACAO_NECESSARIA)
                        {
                            estado_atual = 2;
                            contador_imagens_estaveis = 0;
                            contador_imagens_instaveis = 0;
                            contador_confirmacao = 0;
                            printf("Transição para INSTÁVEL\n");
                        }
                    }
                    else
                    {
                        contador_confirmacao = 0; // Reset se já estiver no estado correto
                    }
                }

                // Atualiza display baseado no estado atual
                if (estado_atual == 1)
                {
                    ssd1306_fill(&ssd, false);
                    ssd1306_send_data(&ssd);
                    ssd1306_draw_bitmap(&ssd, 0, 0, imagens_para_valores_estaveis_allArray[contador_imagens_estaveis], 128, 64);
                    ssd1306_draw_string(&ssd, emg_str, 3, 22);
                    ssd1306_draw_string(&ssd, resp_str, 52, 22);
                    ssd1306_draw_string(&ssd, aqi_str, 89, 22);
                    ssd1306_send_data(&ssd);
                    contador_imagens_estaveis = (contador_imagens_estaveis + 1) % 3;
                }
                else if (estado_atual == 2)
                {
                    ssd1306_fill(&ssd, false);
                    ssd1306_send_data(&ssd);
                    ssd1306_draw_bitmap(&ssd, 0, 0, imagens_para_valores_instaveis_allArray[contador_imagens_instaveis], 128, 64);
                    ssd1306_draw_string(&ssd, emg_str, 3, 22);
                    ssd1306_draw_string(&ssd, resp_str, 52, 22);
                    ssd1306_draw_string(&ssd, aqi_str, 89, 22);
                    ssd1306_send_data(&ssd);
                    contador_imagens_instaveis = (contador_imagens_instaveis + 1) % 3;
                }

                last_running_time = current_calibration_sucessful_us;
            }

            // printf("Mic: %d", mic_value);

            // Para o microfone
            buzzer_control(Eletromiografia_calibrado, Eletromiografia_calibrado_desvio, mic_value, MICROFONE_PIN);

            // Para o joystick X
            buzzer_control(Sensor_de_Respiracao_calibrado, Sensor_de_Respiracao_calibrado_desvio, adc_value_x, VRX_PIN);

            // Para o joystick Y
            buzzer_control(Sensor_de_Qualidade_do_Ar_calibrado, Sensor_de_Qualidade_do_Ar_calibrado_desvio, adc_value_y, VRY_PIN);
            sleep_us(125);
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
            printf("Botão A pressionado\n");
            // Implemente sua lógica para o botão A aqui
        }
        else if (gpio == BUTTON_B)
        {
            if (calibracao_realizada == true)
            {
                printf("Recalibração solicitada\n");
                // Lógica para recalibração, se necessário
            }
            else
            {
                printf("Iniciando calibração...\n");
                calibracao_loading = true;
            }
        }
        else if (gpio == SW_PIN)
        {
            printf("Botão do joystick pressionado\n");
            // Implemente sua lógica para o botão do joystick aqui
        }
    }
}