#include "snake.h"
#include "matrizRGB.h"
#include <stdlib.h>
#include "pico/time.h"

#define SNAKE_SPEED_MS 300
#define FOOD_COLOR 0, 255, 0
#define SNAKE_COLOR 255, 0, 0

void snake_init(SnakeGame *game)
{
    game->body[0].x = 2;
    game->body[0].y = 2;
    game->length = 1;
    game->current_dir = DIR_NONE;
    game->score = 0;
    game->game_over = false;

    // Gera comida inicial
    game->food.x = rand() % 5;
    game->food.y = rand() % 5;
}

void snake_generate_food(SnakeGame *game)
{
    bool valid;
    do
    {
        valid = true;
        game->food.x = rand() % 5;
        game->food.y = rand() % 5;

        // Verifica colisão com a cobra
        for (int i = 0; i < game->length; i++)
        {
            if (game->body[i].x == game->food.x && game->body[i].y == game->food.y)
            {
                valid = false;
                break;
            }
        }
    } while (!valid);
}

void snake_update(SnakeGame *game, Direction new_dir)
{
    if (game->game_over)
        return;

    // Prevenção de movimento inverso
    if ((game->current_dir == DIR_UP && new_dir == DIR_DOWN) ||
        (game->current_dir == DIR_DOWN && new_dir == DIR_UP) ||
        (game->current_dir == DIR_LEFT && new_dir == DIR_RIGHT) ||
        (game->current_dir == DIR_RIGHT && new_dir == DIR_LEFT))
    {
        new_dir = game->current_dir;
    }

    if (new_dir != DIR_NONE)
        game->current_dir = new_dir;

    Position new_head = game->body[0];

    // Calcula nova posição
    switch (game->current_dir)
    {
    case DIR_UP:
        new_head.y--;
        break;
    case DIR_DOWN:
        new_head.y++;
        break;
    case DIR_LEFT:
        new_head.x--;
        break;
    case DIR_RIGHT:
        new_head.x++;
        break;
    default:
        return;
    }

    // Verifica colisão com as paredes
    if (new_head.x < 0 || new_head.x >= 5 || new_head.y < 0 || new_head.y >= 5)
    {
        game->game_over = true;
        game->score -= 10;
        return;
    }

    // Verifica colisão com o corpo
    for (int i = 0; i < game->length; i++)
    {
        if (new_head.x == game->body[i].x && new_head.y == game->body[i].y)
        {
            game->game_over = true;
            game->score -= 10;
            return;
        }
    }

    // Verifica se comeu a comida
    if (new_head.x == game->food.x && new_head.y == game->food.y)
    {
        game->length++;
        game->score += 5;
        snake_generate_food(game);
    }
    else
    {
        // Move o corpo
        for (int i = game->length - 1; i > 0; i--)
        {
            game->body[i] = game->body[i - 1];
        }
    }

    game->body[0] = new_head;
}

void snake_draw(SnakeGame *game)
{
    int matriz[5][5][3] = {{{0}}};

    // Cobra VERDE (corpo)
    for (int i = 0; i < game->length; i++)
    {
        int x = game->body[i].x;
        int y = game->body[i].y;
        matriz[y][x][1] = 255; // Canal GREEN
    }

    // Comida VERMELHA
    matriz[game->food.y][game->food.x][0] = 255; // Canal RED

    setMatrizDeLEDSComIntensidade(matriz, 1.0, 1.0, 1.0);
}


int snake_get_score(const SnakeGame *game)
{
    return game->score;
}

void snake_reset_score(SnakeGame *game)
{
    game->score = 0;
}

bool snake_is_game_over(const SnakeGame *game)
{
    return game->game_over;
}
