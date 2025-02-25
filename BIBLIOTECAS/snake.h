#ifndef SNAKE_H
#define SNAKE_H

#include <stdbool.h>

#define SNAKE_SPEED_MS 300  // Definição adicionada aqui
#define MAX_SNAKE_LENGTH 25

typedef struct {
    int x;
    int y;
} Position;

typedef enum {
    DIR_UP,
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT,
    DIR_NONE
} Direction;

typedef struct {
    Position body[MAX_SNAKE_LENGTH];
    int length;
    Direction current_dir;
    Position food;
    int score;
    bool game_over;
} SnakeGame;

// Protótipos das funções
void snake_init(SnakeGame *game);
void snake_update(SnakeGame *game, Direction new_dir);
void snake_draw(SnakeGame *game);
int snake_get_score(const SnakeGame *game);
void snake_reset_score(SnakeGame *game);
bool snake_is_game_over(const SnakeGame *game);

#endif