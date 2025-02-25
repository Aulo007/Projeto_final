#ifndef CONVERSOR_H
#define CONVERSOR_H

#include <stdint.h>

// Estrutura para dados da tensão muscular
typedef struct {
    float nivel;               // Nível de tensão muscular em %
    const char* categoria;     // Categoria do nível de tensão
    const char* recomendacao; // Recomendação baseada no nível
} TensaoMuscular;

typedef struct {
    float bpm;
    const char* categoria;
    const char* recomendacao;
} FrequenciaCardiaca;


// Estrutura para dados da qualidade do ar
typedef struct {
    int aqi;                    // Índice de qualidade do ar
    const char* categoria;      // Categoria da qualidade do ar
    const char* recomendacao;   // Recomendação baseada na qualidade
} QualidadeAr;

// Estrutura para armazenar todas as leituras convertidas
typedef struct {
    TensaoMuscular tensao_muscular;  // Dados da tensão muscular
    FrequenciaCardiaca frequencia_cardiaca;           // Dados da respiração
    QualidadeAr qualidade_ar;        // Dados da qualidade do ar
} DadosSensores;

// Funções de conversão
DadosSensores converter_leituras(
    uint16_t emg_value, 
    uint16_t resp_value, 
    uint16_t ar_value,
    int emg_calibrado, 
    int resp_calibrado, 
    int ar_calibrado,
    int emg_desvio, 
    int resp_desvio, 
    int ar_desvio
);

TensaoMuscular converter_emg(uint16_t adc_value, int valor_calibrado, int zona_morta);
FrequenciaCardiaca converter_respiracao(uint16_t adc_value_x, int valor_calibrado, int zona_morta);
QualidadeAr converter_qualidade_ar(uint16_t adc_value_y, int valor_calibrado, int zona_morta);

#endif // CONVERSOR_H