#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "./utils.h"
#include "./menu.h"

Menu* Menu_create(char* title, char* exitOptionDescription)
{
    Menu* newMenu = malloc(sizeof(Menu)); 

    if (newMenu == NULL)
        return NULL;
    
    newMenu->title = malloc(strlen(title));
    strcpy(newMenu->title, title);

    newMenu->menuOptions.options = malloc(5 * sizeof(Option));
    if (newMenu->menuOptions.options == NULL)
    {
        free(newMenu);
        return NULL;
    }

    newMenu->menuOptions.total = 1;
    
    newMenu->menuOptions.options[0].description = malloc(strlen(exitOptionDescription));
    strcpy(newMenu->menuOptions.options[0].description, exitOptionDescription);
    newMenu->menuOptions.options[0].action = NULL;
    
    return newMenu;
}

int Menu_appendNewOption(Menu* menu, char* description, int (*action)())
{
    Option firstOption = {
        .action = action
    };
    firstOption.description = malloc(strlen(description));
    strcpy(firstOption.description, description);

    Menu_registerOption(menu, firstOption);
}

int Menu_launch(Menu *menu)
{
    if (menu->menuOptions.total <= 0) {
        printf("No option was registered!\n");
        return -1;
    }

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
        if (Menu_isValidOption(option, menu)) continue;

        if (option == 0) break;

        // TODO: add 'wait for user'
        // TODO: clear 

        Menu_executeAction(option, menu);
    }
}

int Menu_registerOption(Menu *menu, Option option)
{
    if (option.action == NULL || option.action == 0)
    {
        printf("Option action cannot be NULL. Aborting registration\n");
        return 1;
    }

    menu->menuOptions.options[menu->menuOptions.total++] = option;

    return 0;
}

int Menu_show(Menu *menuToOpen)
{
    Menu menu = *menuToOpen;

    printf("-------------- %s --------------\n", menu.title);
    printf("\n");

    for (int i = 0; i < menu.menuOptions.total; i++)
    {
        printf("[%d] -> %s\n", i, menu.menuOptions.options[i].description);
    }
}

int Menu_isValidOption(int option, Menu *menu)
{
    if (option < 0 || option >= menu->menuOptions.total)
    {
        printf("Invalid option '%d' for menu '%s' (total options = %d)\n", option, menu->title, menu->menuOptions.total);
        return 1;
    }

    return 0;
}

int Menu_executeAction(int option, Menu *menu)
{
    menu->menuOptions.options[option].action();
}
