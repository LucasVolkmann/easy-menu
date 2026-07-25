#include <stdio.h>
#include <stdbool.h>
#include "./utils.h"

#define MAX_OPTIONS_AMOUNT 5

#define MAX_OPTIONS_REACHED_ERROR_CODE -2

typedef struct
{
    char description[50];
    int (*action)();
} Option;

typedef struct
{
    Option options[MAX_OPTIONS_AMOUNT + 1];
    int total;
} Options;

typedef struct
{
    char title[50];
    Options options;
} Menu;

int Menu_register_option(Menu *menu, Option *option);
int Menu_show(Menu *menu);
int Menu_is_valid_option(int option, Menu *menu);
int Menu_execute_action(int option, Menu *menu);
int Menu_launch(Menu *menu);

int Menu_launch(Menu *menu)
{
    int option = 0;
    while (1)
    {
        Menu_show(menu);

        printf(">> ");
        int result = scanf(" %d", &option);
        cleanScanfBuffer();

        if (result != 1)
        {
            printf("Opção inválida! Tente novamente.\n");
            continue;
        }
        if (Menu_is_valid_option(option, menu)) continue;

        if (option == 0) break;

        // TODO: add 'wait for user'
        // TODO: clear 

        Menu_execute_action(option, menu);
    }
}

int Menu_register_option(Menu *menu, Option *option)
{
    if (option == NULL || option == 0)
    {
        printf("Option cannot be NULL. \n");
        return 1;
    }
    if (option->action == NULL || option->action == 0)
    {
        printf("Option action cannot be NULL. Aborting registration\n");
        return 1;
    }
    if (menu->options.total >= MAX_OPTIONS_AMOUNT + 1)
    {
        return MAX_OPTIONS_REACHED_ERROR_CODE;
    }

    menu->options.options[menu->options.total++] = *option;

    return 0;
}

int Menu_show(Menu *m)
{
    Menu menu = *m;

    printf("-------------- %s --------------\n", menu.title);
    printf("\n");

    for (int i = 0; i < menu.options.total; i++)
    {
        printf("[%d] -> %s\n", i, menu.options.options[i].description);
    }
}

int Menu_is_valid_option(int option, Menu *menu)
{
    if (menu->options.total <= 1) {
        printf("No option was registered for '%s'\n", menu->title);
        return 1;
    }
    if (option < 0 || option >= menu->options.total)
    {
        printf("Invalid option '%d' for menu '%s' (total options = %d)\n", option, menu->title, menu->options.total);
        return 1;
    }

    return 0;
}

int Menu_execute_action(int option, Menu *menu)
{
    menu->options.options[option].action();
}
