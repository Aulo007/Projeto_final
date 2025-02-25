#ifndef BITMAPS_H
#define BITMAPS_H

#include "pico/stdlib.h"

extern const uint8_t mensagem_sem_calibrar[]; // Mensagem a ser exibida quando o usuário não calibrou os sensores
extern const unsigned char calibration_animation_2[];
extern const unsigned char calibration_animation_3[];
extern const unsigned char calibration_animation_4[];
extern const unsigned char calibration_animation_5[];
extern const unsigned char calibration_animation_6[];
extern const unsigned char calibration_animation_7[];
extern const unsigned char calibration_animation_8[];
extern const unsigned char calibration_animation_9[];
extern const unsigned char calibration_animation_10[];
extern const unsigned char calibration_animation_11[];
extern const unsigned char calibration_animation_12[];
extern const unsigned char calibration_animation_13[];
extern const unsigned char calibration_animation_14[];
extern const int calibration_animation_LEN;
extern const unsigned char *calibration_animation[13];
extern const unsigned char calibracao_pronta[];

extern const unsigned char imagens_para_valores_estaveis_24[];
extern const unsigned char imagens_para_valores_estaveis_25[];
extern const unsigned char imagens_para_valores_estaveis_26[];
extern const unsigned char imagens_para_valores_estaveis_27[];
extern const unsigned char imagens_para_valores_instaveis_28[];
extern const unsigned char imagens_para_valores_instaveis_29[];
extern const unsigned char imagens_para_valores_instaveis_30[];
extern const unsigned char imagens_para_valores_instaveis_31[];

extern const int imagens_para_valores_estaveis_LEN;
extern const int imagens_para_valores_instaveis_LEN;
extern const unsigned char *imagens_para_valores_estaveis_allArray[4];
extern const unsigned char *imagens_para_valores_instaveis_allArray[4];

#endif // BITMAPS_H