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

const uint8_t bitmap_128x64[] = {
    0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x80,
    0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x80,
    0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0xc0,
    0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x60,
    0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x0c,
    0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x80, 0x03, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x70, 0x00,
    0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x80, 0x07, 0x00,
    0x00, 0x00, 0x00, 0xc0, 0x00, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x07, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xc0, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x0f, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xdf, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x78, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xc0, 0x00, 0x00, 0x00, 0x00,
    0x00, 0xf0, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x07, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x01, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00,
    0x60, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00,
    0x18, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00,
    0x08, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00,
    0x08, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00,
    0x18, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00,
    0x80, 0x07, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00,
    0x00, 0xc0, 0x3f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xc7, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xf8, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x1f, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xc0, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x80, 0x03, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xc0, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x70, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xc0, 0x00, 0xc0, 0x01, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x03, 0x00,
    0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x18, 0x00,
    0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x60, 0x00,
    0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x80, 0x00,
    0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x03,
    0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x04,
    0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x08,
    0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x10,
    0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x10,
    0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x10,
    0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x10,
    0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x10,
    0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x18,
    0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x04,
    0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x80, 0x00,
    0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x30, 0x00,
    0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x06, 0x00,
    0x00, 0x00, 0x00, 0xc0, 0x00, 0xc0, 0x01, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x3c, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xc0, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xe0, 0x01, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xc0, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x07, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xc0, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x0f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x1c, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00,
    0x80, 0x01, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00,
    0x40, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00,
    0x40, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00,
    0x40, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00,
    0x80, 0x01, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x0e, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00,
    0x00, 0xc0, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0xc0, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xf0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc3, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xdc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xc0, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x78, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xc0, 0xc0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x07, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xc0, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0xe0, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x06, 0x00,
    0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x30, 0x00,
    0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x80, 0x01,
    0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x0c,
    0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x30};

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
static volatile bool calibracao_realizada = false;
static volatile uint32_t last_button_time = 0;
const uint32_t DEBOUNCE_DELAY = 200000; // 200ms em microssegundos

// Estrutura para armazenar os dados dos sensores
typedef struct
{
    int nivelTensaoMuscular;
    int frequenciaRespiratoria;
    int qualidadeAr;
    bool arLimpo;
    bool musculosRelaxados;
    bool respiracaoRegular;
} DadosSensores;

static void gpio_irq_handle(uint gpio, uint32_t events); // Função para a interrupção
static void calibrar_sensores();

int main(void)
{
    // Inicialização do I2C a 400 kHz
    i2c_init(I2C_PORT, 400 * 1000);

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

    ssd1306_draw_bitmap(&ssd, 0, 0, bitmap_128x64, 128, 64);

    // Envia os dados para o ssd
    ssd1306_send_data(&ssd);

    while (true)

    {

        if (calibracao_realizada == true)
        {
            sleep_ms(200);
        }

        else
        {
            ssd1306_fill(&ssd, false);
            ssd1306_draw_bitmap(&ssd, 0, 0, bitmap_128x64, 128, 64);
            ssd1306_send_data(&ssd);
        }
    }
}
