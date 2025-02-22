#include "conversor.h"
#include <stdlib.h>

// Constantes para conversão EMG
#define EMG_MIN_TENSAO 0.0f    // Tensão mínima em mV
#define EMG_MAX_TENSAO 3300.0f // Tensão máxima em mV (3.3V)
#define EMG_MIN_NIVEL 0.0f     // Nível mínimo de tensão muscular em %
#define EMG_MAX_NIVEL 100.0f   // Nível máximo de tensão muscular em %

// Constantes para conversão Respiração (eixo X do joystick)
#define RESP_MIN_RATE 8.0f    // Respirações por minuto (muito lenta)
#define RESP_MAX_RATE 30.0f   // Respirações por minuto (muito rápida)
#define RESP_NORMAL_MIN 12.0f // Respiração normal mínima
#define RESP_NORMAL_MAX 20.0f // Respiração normal máxima

// Constantes para qualidade do ar (eixo Y do joystick)
#define AQI_MIN 0     // Índice mínimo de qualidade do ar
#define AQI_MAX 500   // Índice máximo de qualidade do ar
#define AQI_NORMAL 50 // Valor considerado normal/bom para qualidade do ar

TensaoMuscular converter_emg(uint16_t adc_value, int valor_calibrado, int zona_morta)
{
    TensaoMuscular resultado;

    // Se o valor estiver dentro da zona morta, considera relaxado
    if (abs(adc_value - valor_calibrado) <= zona_morta)
    {
        resultado.nivel = 0.0f;
        resultado.categoria = "Relaxado";
        resultado.recomendacao = "Nível normal de tensão muscular";
        return resultado;
    }

    // Calcula o nível de tensão
    float nivel;
    if (adc_value > valor_calibrado)
    {
        nivel = ((float)(adc_value - (valor_calibrado + zona_morta)) /
                 (4096.0f - (valor_calibrado + zona_morta))) *
                100.0f;
    }
    else
    {
        nivel = ((float)((valor_calibrado - zona_morta) - adc_value) /
                 (valor_calibrado - zona_morta)) *
                100.0f;
    }

    // Limita entre 0% e 100%
    if (nivel < EMG_MIN_NIVEL)
        nivel = EMG_MIN_NIVEL;
    if (nivel > EMG_MAX_NIVEL)
        nivel = EMG_MAX_NIVEL;

    resultado.nivel = nivel;

    // Categoriza o nível de tensão
    if (nivel <= 20.0f)
    {
        resultado.categoria = "Tensão Leve";
        resultado.recomendacao = "Mantenha-se atento à sua postura";
    }
    else if (nivel <= 40.0f)
    {
        resultado.categoria = "Tensão Moderada";
        resultado.recomendacao = "Considere fazer pausas para alongamento";
    }
    else if (nivel <= 60.0f)
    {
        resultado.categoria = "Tensão Alta";
        resultado.recomendacao = "Faça exercícios de relaxamento e alongamento";
    }
    else if (nivel <= 80.0f)
    {
        resultado.categoria = "Tensão Muito Alta";
        resultado.recomendacao = "Necessário intervalo e técnicas de relaxamento";
    }
    else
    {
        resultado.categoria = "Tensão Extrema";
        resultado.recomendacao = "Pare a atividade e procure ajuda profissional";
    }

    return resultado;
}

Respiracao converter_respiracao(uint16_t adc_value_x, int valor_calibrado, int zona_morta)
{
    Respiracao resultado;

    // Se estiver na zona morta, considera respiração normal
    if (abs(adc_value_x - valor_calibrado) <= zona_morta)
    {
        resultado.freq = RESP_NORMAL_MIN;
        resultado.categoria = "Normal";
        resultado.recomendacao = "Padrão respiratório saudável";
        return resultado;
    }

    // Calcula a frequência respiratória
    float freq;
    if (adc_value_x > valor_calibrado)
    {
        float variacao = (float)(adc_value_x - (valor_calibrado + zona_morta)) /
                         (4096.0f - (valor_calibrado + zona_morta));
        freq = RESP_NORMAL_MAX + (variacao * (RESP_MAX_RATE - RESP_NORMAL_MAX));
    }
    else
    {
        float variacao = (float)((valor_calibrado - zona_morta) - adc_value_x) /
                         (valor_calibrado - zona_morta);
        freq = RESP_NORMAL_MIN - (variacao * (RESP_NORMAL_MIN - RESP_MIN_RATE));
    }

    // Limita os valores
    if (freq < RESP_MIN_RATE)
        freq = RESP_MIN_RATE;
    if (freq > RESP_MAX_RATE)
        freq = RESP_MAX_RATE;

    resultado.freq = freq;

    // Categoriza o padrão respiratório
    if (freq < 12.0f)
    {
        resultado.categoria = "Bradipneia";
        resultado.recomendacao = "Respiração muito lenta. Procure respirar mais naturalmente";
    }
    else if (freq >= 12.0f && freq <= 20.0f)
    {
        resultado.categoria = "Normal";
        resultado.recomendacao = "Mantenha este ritmo saudável";
    }
    else if (freq > 20.0f && freq <= 24.0f)
    {
        resultado.categoria = "Taquipneia Leve";
        resultado.recomendacao = "Respire mais devagar. Considere exercícios de respiração";
    }
    else if (freq > 24.0f && freq <= 27.0f)
    {
        resultado.categoria = "Taquipneia Moderada";
        resultado.recomendacao = "Faça exercícios de respiração profunda e controlada";
    }
    else
    {
        resultado.categoria = "Taquipneia Grave";
        resultado.recomendacao = "Respire mais devagar! Procure ajuda se persistir";
    }

    return resultado;
}

QualidadeAr converter_qualidade_ar(uint16_t adc_value_y, int valor_calibrado, int zona_morta)
{
    QualidadeAr resultado;

    // Se estiver na zona morta, retorna qualidade do ar boa
    if (abs(adc_value_y - valor_calibrado) <= zona_morta)
    {
        resultado.aqi = AQI_NORMAL;
        resultado.categoria = "Boa";
        resultado.recomendacao = "Ar seguro";
        return resultado;
    }

    // Calcula o AQI baseado no quanto o valor passou da zona morta
    int aqi;
    if (adc_value_y > valor_calibrado)
    {
        float variacao = (float)(adc_value_y - (valor_calibrado + zona_morta)) /
                         (4096.0f - (valor_calibrado + zona_morta));
        aqi = AQI_NORMAL + (int)(variacao * (AQI_MAX - AQI_NORMAL));
    }
    else
    {
        float variacao = (float)((valor_calibrado - zona_morta) - adc_value_y) /
                         (valor_calibrado - zona_morta);
        aqi = AQI_NORMAL - (int)(variacao * AQI_NORMAL);
    }

    // Limita o AQI entre 0 e 500
    if (aqi > AQI_MAX)
        aqi = AQI_MAX;
    if (aqi < AQI_MIN)
        aqi = AQI_MIN;

    resultado.aqi = aqi;

    // Classifica a qualidade do ar baseado no AQI
    if (aqi <= 50)
    {
        resultado.categoria = "Boa";
        resultado.recomendacao = "Ar seguro";
    }
    else if (aqi <= 100)
    {
        resultado.categoria = "Moderada";
        resultado.recomendacao = "Grupos sensíveis: reduzir exposição prolongada";
    }
    else if (aqi <= 150)
    {
        resultado.categoria = "Insalubre para Grupos Sensíveis";
        resultado.recomendacao = "Usar máscara recomendada";
    }
    else if (aqi <= 200)
    {
        resultado.categoria = "Insalubre";
        resultado.recomendacao = "Usar máscara N95/PFF2";
    }
    else if (aqi <= 300)
    {
        resultado.categoria = "Muito Insalubre";
        resultado.recomendacao = "Evitar exposição externa";
    }
    else
    {
        resultado.categoria = "Perigosa";
        resultado.recomendacao = "Emergência de Saúde";
    }

    return resultado;
}

DadosSensores converter_leituras(
    uint16_t emg_value,
    uint16_t resp_value,
    uint16_t ar_value,
    int emg_calibrado,
    int resp_calibrado,
    int ar_calibrado,
    int emg_desvio,
    int resp_desvio,
    int ar_desvio)
{
    DadosSensores dados;

    dados.tensao_muscular = converter_emg(emg_value, emg_calibrado, emg_desvio);
    dados.respiracao = converter_respiracao(resp_value, resp_calibrado, resp_desvio);
    dados.qualidade_ar = converter_qualidade_ar(ar_value, ar_calibrado, ar_desvio);

    return dados;
}