#include "desenho.h"

// Matriz 4d, na qual cada bloco de elemento [5][5][3] correspondende a um desenho
// Cada desenho[matriz3d] tem 5 linhas, 5 colunas e 3 cores R, G e B

int caixa_de_desenhos[10][5][5][3] =
    {
        {{{0, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {0, 0, 0}},
         {{255, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 0, 0}},
         {{255, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 0, 0}},
         {{255, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 0, 0}},
         {{0, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {0, 0, 0}}},

        {{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 255, 0}, {0, 0, 0}},
         {{0, 0, 0}, {0, 0, 0}, {0, 255, 0}, {0, 255, 0}, {0, 0, 0}},
         {{0, 0, 0}, {0, 255, 0}, {0, 0, 0}, {0, 255, 0}, {0, 0, 0}},
         {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 255, 0}, {0, 0, 0}},
         {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 255, 0}, {0, 0, 0}}},

        {{{0, 0, 0}, {0, 0, 255}, {0, 0, 255}, {0, 0, 255}, {0, 0, 0}},
         {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 255}, {0, 0, 0}},
         {{0, 0, 0}, {0, 0, 255}, {0, 0, 255}, {0, 0, 255}, {0, 0, 0}},
         {{0, 0, 0}, {0, 0, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
         {{0, 0, 0}, {0, 0, 255}, {0, 0, 255}, {0, 0, 255}, {0, 0, 0}}},

        {{{0, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {0, 0, 0}},
         {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 0, 0}, {0, 0, 0}},
         {{0, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {0, 0, 0}},
         {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 0, 0}, {0, 0, 0}},
         {{0, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {0, 0, 0}}},

        {{{0, 0, 0}, {0, 255, 0}, {0, 0, 0}, {0, 255, 0}, {0, 0, 0}},
         {{0, 0, 0}, {0, 255, 0}, {0, 0, 0}, {0, 255, 0}, {0, 0, 0}},
         {{0, 0, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 0, 0}},
         {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 255, 0}, {0, 0, 0}},
         {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 255, 0}, {0, 0, 0}}},

        {{{0, 0, 0}, {0, 0, 255}, {0, 0, 255}, {0, 0, 255}, {0, 0, 0}},
         {{0, 0, 0}, {0, 0, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
         {{0, 0, 0}, {0, 0, 255}, {0, 0, 255}, {0, 0, 255}, {0, 0, 0}},
         {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 255}, {0, 0, 0}},
         {{0, 0, 0}, {0, 0, 255}, {0, 0, 255}, {0, 0, 255}, {0, 0, 0}}},

        {{{0, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {0, 0, 0}},
         {{0, 0, 0}, {255, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
         {{0, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {0, 0, 0}},
         {{0, 0, 0}, {255, 0, 0}, {0, 0, 0}, {255, 0, 0}, {0, 0, 0}},
         {{0, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {0, 0, 0}}},

        {{{0, 0, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 0, 0}},
         {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 255, 0}, {0, 0, 0}},
         {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 255, 0}, {0, 0, 0}},
         {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 255, 0}, {0, 0, 0}},
         {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 255, 0}, {0, 0, 0}}},

        {{{0, 0, 0}, {0, 0, 255}, {0, 0, 255}, {0, 0, 255}, {0, 0, 0}},
         {{0, 0, 0}, {0, 0, 255}, {0, 0, 0}, {0, 0, 255}, {0, 0, 0}},
         {{0, 0, 0}, {0, 0, 255}, {0, 0, 255}, {0, 0, 255}, {0, 0, 0}},
         {{0, 0, 0}, {0, 0, 255}, {0, 0, 0}, {0, 0, 255}, {0, 0, 0}},
         {{0, 0, 0}, {0, 0, 255}, {0, 0, 255}, {0, 0, 255}, {0, 0, 0}}},

        {{{0, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {0, 0, 0}},
         {{0, 0, 0}, {255, 0, 0}, {0, 0, 0}, {255, 0, 0}, {0, 0, 0}},
         {{0, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {0, 0, 0}},
         {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 0, 0}, {0, 0, 0}},
         {{0, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {0, 0, 0}}},
};

int vermelho[1][5][5][3] =
    {
        {{{255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}},
         {{255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}},
         {{255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}},
         {{255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}},
         {{255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}}},
};

int verde[1][5][5][3] =
    {

        {{{0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}},
         {{0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}},
         {{0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}},
         {{0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}},
         {{0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}}},
};