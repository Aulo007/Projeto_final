#include <stdio.h>

#define MATRIX_ROWS 5
#define MATRIX_COLS 5
#define MATRIX_DEPTH 3
#define NUM_FRAMES 12

// Função para converter valores ARGB (0xAARRGGBB) para RGB
void convertToRGB(unsigned int argb, int rgb[3])
{
    rgb[2] = (argb >> 16) & 0xFF; // Red
    rgb[1] = (argb >> 8) & 0xFF;  // Green
    rgb[0] = argb & 0xFF;         // Blue
}

int main()
{
    // Matriz de entrada com os valores ARGB (alterado para unsigned int)
    unsigned int argb_values[NUM_FRAMES][MATRIX_ROWS * MATRIX_COLS] = {

        {0xff000000, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff000000,
         0xff0000ff, 0xff000000, 0xff000000, 0xff000000, 0xff0000ff,
         0xff0000ff, 0xff000000, 0xff000000, 0xff000000, 0xff0000ff,
         0xff0000ff, 0xff000000, 0xff000000, 0xff000000, 0xff0000ff,
         0xff000000, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff000000},
        {0xff000000, 0xff000000, 0xff000000, 0xff00ff00, 0xff000000,
         0xff000000, 0xff000000, 0xff00ff00, 0xff00ff00, 0xff000000,
         0xff000000, 0xff00ff00, 0xff000000, 0xff00ff00, 0xff000000,
         0xff000000, 0xff000000, 0xff000000, 0xff00ff00, 0xff000000,
         0xff000000, 0xff000000, 0xff000000, 0xff00ff00, 0xff000000},
        {0xff000000, 0xffff0000, 0xffff0000, 0xffff0000, 0xff000000,
         0xff000000, 0xff000000, 0xff000000, 0xffff0000, 0xff000000,
         0xff000000, 0xffff0000, 0xffff0000, 0xffff0000, 0xff000000,
         0xff000000, 0xffff0000, 0xff000000, 0xff000000, 0xff000000,
         0xff000000, 0xffff0000, 0xffff0000, 0xffff0000, 0xff000000},
        {0xff000000, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff000000,
         0xff000000, 0xff000000, 0xff000000, 0xff0000ff, 0xff000000,
         0xff000000, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff000000,
         0xff000000, 0xff000000, 0xff000000, 0xff0000ff, 0xff000000,
         0xff000000, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff000000},
        {0xff000000, 0xff00ff00, 0xff000000, 0xff00ff00, 0xff000000,
         0xff000000, 0xff00ff00, 0xff000000, 0xff00ff00, 0xff000000,
         0xff000000, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff000000,
         0xff000000, 0xff000000, 0xff000000, 0xff00ff00, 0xff000000,
         0xff000000, 0xff000000, 0xff000000, 0xff00ff00, 0xff000000},
        {0xff000000, 0xffff0000, 0xffff0000, 0xffff0000, 0xff000000,
         0xff000000, 0xffff0000, 0xff000000, 0xff000000, 0xff000000,
         0xff000000, 0xffff0000, 0xffff0000, 0xffff0000, 0xff000000,
         0xff000000, 0xff000000, 0xff000000, 0xffff0000, 0xff000000,
         0xff000000, 0xffff0000, 0xffff0000, 0xffff0000, 0xff000000},
        {0xff000000, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff000000,
         0xff000000, 0xff0000ff, 0xff000000, 0xff000000, 0xff000000,
         0xff000000, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff000000,
         0xff000000, 0xff0000ff, 0xff000000, 0xff0000ff, 0xff000000,
         0xff000000, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff000000},
        {0xff000000, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff000000,
         0xff000000, 0xff000000, 0xff000000, 0xff00ff00, 0xff000000,
         0xff000000, 0xff000000, 0xff000000, 0xff00ff00, 0xff000000,
         0xff000000, 0xff000000, 0xff000000, 0xff00ff00, 0xff000000,
         0xff000000, 0xff000000, 0xff000000, 0xff00ff00, 0xff000000},
        {0xff000000, 0xffff0000, 0xffff0000, 0xffff0000, 0xff000000,
         0xff000000, 0xffff0000, 0xff000000, 0xffff0000, 0xff000000,
         0xff000000, 0xffff0000, 0xffff0000, 0xffff0000, 0xff000000,
         0xff000000, 0xffff0000, 0xff000000, 0xffff0000, 0xff000000,
         0xff000000, 0xffff0000, 0xffff0000, 0xffff0000, 0xff000000},
        {0xff000000, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff000000,
         0xff000000, 0xff0000ff, 0xff000000, 0xff0000ff, 0xff000000,
         0xff000000, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff000000,
         0xff000000, 0xff000000, 0xff000000, 0xff0000ff, 0xff000000,
         0xff000000, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff000000}};

    // Matriz para armazenar os valores RGB de todos os frames
    int rgb_matrix[NUM_FRAMES][MATRIX_ROWS][MATRIX_COLS][MATRIX_DEPTH];

    // Converter cada frame
    for (int frame = 0; frame < NUM_FRAMES; frame++)
    {
        // Preencher a matriz RGB com a conversão dos valores ARGB
        for (int i = 0; i < MATRIX_ROWS * MATRIX_COLS; i++)
        {
            int rgb[3];
            convertToRGB(argb_values[frame][i], rgb);

            int row = i / MATRIX_COLS;
            int col = i % MATRIX_COLS;

            // Armazenar os valores RGB na matriz
            rgb_matrix[frame][row][col][0] = rgb[0];
            rgb_matrix[frame][row][col][1] = rgb[1];
            rgb_matrix[frame][row][col][2] = rgb[2];
        }
    }

    // Imprimir todos os frames
    for (int frame = 0; frame < NUM_FRAMES; frame++)
    {
        printf("\n{\n");
        for (int i = 0; i < MATRIX_ROWS; i++)
        {
            printf("    {");
            for (int j = 0; j < MATRIX_COLS; j++)
            {
                printf("{%d, %d, %d}",
                       rgb_matrix[frame][i][j][0],
                       rgb_matrix[frame][i][j][1],
                       rgb_matrix[frame][i][j][2]);
                if (j < MATRIX_COLS - 1)
                    printf(", ");
            }
            printf("}");
            if (i < MATRIX_ROWS - 1)
                printf(",");
            printf("\n");
        }
        printf("},\n\n");
    }

    return 0;
}