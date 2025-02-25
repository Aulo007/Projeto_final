#include "menu.h"
#include "stdlib.h"

bool menu_is_valid_option(const MenuOption *options, int num_options, char input)
{
    for (int i = 0; i < num_options; i++)
    {
        if (options[i].key == input)
        {
            return true;
        }
    }
    return false;
}

void menu_display(const MenuOption *options, int num_options)
{
    printf("\033[2J\033[H");
    system("cls");
    printf("=== Sistema Iniciado ===\n");
    printf("Pressione uma tecla para escolher uma opcao:\n\n");

    for (int i = 0; i < num_options; i++)
    {
        printf("%c: %s\n", options[i].key, options[i].description);
    }
    printf("\n");
}