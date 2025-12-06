#ifndef MENU_H
#define MENU_H

// Définition du type de fonction de rappel pour les options de menu
typedef int (*menu_callback_t)(void *userdata);

typedef struct {
    char *label;
    menu_callback_t callback;
    int color;
    void *userdata;
} MenuOption;

typedef struct {
    MenuOption *options;
    int count;
    int selected;
} Menu;


Menu create_menu(int capacity);
void menu_add_option(Menu *m, const char *label, menu_callback_t cb, int color, void *userdata);
void menu_display(Menu *m, int posX, int posY);
int menu_run(Menu *m, int posX, int posY);


#endif