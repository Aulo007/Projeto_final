# Neurokardy: Sistema Vestível de Monitoramento e Intervenção em Saúde Mental

## 📋 Visão Geral
O Neurokardy é um dispositivo vestível inovador, desenvolvido para monitorar continuamente sinais fisiológicos associados aos estados mentais – com ênfase em ansiedade e estresse. Ao capturar dados em tempo real por meio de diversos sensores e fornecer feedback imediato, o sistema auxilia os usuários a gerenciar seu bem-estar emocional através de técnicas de relaxamento e maior autoconhecimento.

## 🎯 Características Principais
- **Monitoramento Fisiológico Contínuo**: Acompanha em tempo real a tensão muscular (EMG), a frequência cardíaca e a qualidade do ar.
- **Calibração Personalizada**: Adapta-se à linha de base fisiológica única de cada usuário.
- **Sistema de Feedback Imediato**: Fornece alertas visuais, auditivos e interativos sempre que os parâmetros indicam sinais de estresse ou ansiedade.
- **Ferramenta Interativa de Relaxamento**: Disponibiliza um jogo da cobrinha para promover distração e relaxamento durante períodos de alta tensão.
- **Alerta Multimodal**: Utiliza display OLED, matriz de LED e buzzer para oferecer um feedback abrangente.

## 🔧 Componentes de Hardware
- **Microcontrolador RP2040**: Processa os dados dos sensores e coordena as respostas do sistema.
- **Sensor EMG**: Detecta a tensão muscular (simulado com microfone no protótipo).
- **Sensor MAX30100**: Monitora a frequência cardíaca e os níveis de oxigênio no sangue (simulado com o eixo X do joystick no protótipo).
- **Sensor MQ-135**: Avalia a qualidade do ar e detecta poluentes (simulado com o eixo Y do joystick no protótipo).
- **Display OLED 128x64**: Exibe as leituras dos sensores e o status do sistema.
- **Matriz de LED 5x5**: Proporciona feedback visual por meio de padrões de cores.
- **LEDs RGB**: Indicam o status do sistema (verde para estável, vermelho para instável).
- **Buzzer**: Emite alertas sonoros quando os valores dos sensores ultrapassam os limites previamente calibrados.

## 💻 Arquitetura de Software
O firmware do sistema está estruturado em três camadas principais:
1. **Camada de Aplicação**: Responsável pelo monitoramento, calibração e funcionalidades interativas.
2. **Camada de Processamento de Dados**: Analisa os dados dos sensores e determina o estado do sistema.
3. **Camada de Driver**: Gerencia a comunicação e o controle dos componentes de hardware.

## ⚙️ Funcionamento do Sistema
1. **Calibração Inicial**: O sistema coleta 100.000 amostras de cada sensor para definir limites personalizados.
2. **Monitoramento Contínuo**: Os sinais fisiológicos são rastreados e comparados com os parâmetros calibrados.
3. **Feedback Imediato**: Ao identificar desvios significativos, o sistema ativa:
   - Alertas visuais no display OLED e na matriz de LED;
   - Alertas sonoros através do buzzer;
   - Sugestões de intervenções interativas.
4. **Intervenção com Jogo**: O usuário pode iniciar o jogo da cobrinha como uma técnica de distração durante picos de estresse.

## 🔬 Fundamentação Científica
- **Variabilidade da Frequência Cardíaca (VFC)**: Estudos da American Psychological Association comprovam que a VFC é um marcador confiável para estresse agudo.
- **Impacto da Qualidade do Ar**: Dados da Organização Mundial da Saúde indicam que 90% da população mundial respira ar poluído, o que pode agravar transtornos de saúde mental.
- **Tensão Muscular**: Pesquisas publicadas no Journal of Clinical Psychology associam a tensão muscular a 70% dos casos clínicos de ansiedade.

## 🚀 Melhorias Futuras
- Integração com Wi-Fi para armazenamento e análise de dados na nuvem.
- Inclusão de um módulo GPS para suporte baseado em localização.
- Implementação de reconhecimento de voz para operação sem o uso das mãos.
- Integração com inteligência artificial para reconhecimento avançado de padrões e intervenções personalizadas.

## 🛠️ Implementação Técnica
- **Linguagem de Programação**: C
- **Plataforma de Desenvolvimento**: Raspberry Pi Pico SDK
- **IDE**: VSCode com a extensão Pico
- **Principais Bibliotecas**: Bibliotecas de controle de hardware para ADC, I2C, GPIO e PWM

---

## Instruções de Uso
Clone o repositório para a pasta desejada:
```bash
git clone <URL_do_repositorio>
