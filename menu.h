#ifndef MENU_MODULE
#define MENU_MODULE

typedef struct
{
    char* description;
    int (*action)();
} Option;

typedef struct
{
    Option* options;
    int total;
} MenuOptions;

typedef struct
{
    char* title;
    MenuOptions menuOptions;
} Menu;

int Menu_registerOption(Menu *menu, Option option);
int Menu_show(Menu *menu);
int Menu_isValidOption(int option, Menu *menu);
int Menu_executeAction(int option, Menu *menu);
int Menu_launch(Menu *menu);
int Menu_appendNewOption(Menu* menu, char* description, int (*action)());
Menu* Menu_create(char* title, char* exitOptionDescription);

#endif