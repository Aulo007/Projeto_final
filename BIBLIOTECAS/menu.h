#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <stdbool.h>

// Estrutura para armazenar informações do menu
typedef struct {
    char key;
    const char* description;
} MenuOption;

// Função para exibir menu com opções dinâmicas
void menu_display(const MenuOption* options, int num_options);

// Função para verificar se uma tecla é válida no menu
bool menu_is_valid_option(const MenuOption* options, int num_options, char input);

#endif // MENU_H