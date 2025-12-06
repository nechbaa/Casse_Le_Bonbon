#ifndef MENU_H
#define MENU_H

typedef void (*menu_callback_t)(void *userdata);

typedef struct {
    char *label;
    menu_callback_t callback;
    void *userdata;
} MenuOption;

typedef struct {
    MenuOption *options;
    int count;
    int selected;
} Menu;


Menu create_menu(int capacity);
void menu_add_option(Menu *m, const char *label, menu_callback_t cb, void *userdata);
void menu_display(Menu *m, int posX, int posY);
void menu_run(Menu *m, int posX, int posY);


#endif