#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include "menu.h"


Menu create_menu(int capacity) {
    Menu m;
    m.options = malloc(sizeof(MenuOption) * capacity);
    m.count = 0;
    m.selected = 0;
    return m;
}

void menu_add_option(Menu *m, const char *label, menu_callback_t cb, void *userdata)
{
    m->options[m->count].label = strdup(label);
    m->options[m->count].callback = cb;
    m->options[m->count].userdata = userdata;
    m->count++;
}


void menu_display(Menu *m) {
    system("cls"); // sous Windows -> "cls"

    for (int i = 0; i < m->count; i++) {
        if (i == m->selected)
            printf(" > %s\n", m->options[i].label);
        else
            printf("   %s\n", m->options[i].label);
    }
}

void menu_run(Menu *m) {
    menu_display(m);

    while (1) {
        int c = getch();

        if (c == 'z' || c == 'Z' || c == 72) {  // flèche haut
            m->selected--;
            if (m->selected < 0)
                m->selected = m->count - 1;
        }
        else if (c == 's' || c == 'S' || c == 80) {  // flèche bas
            m->selected++;
            if (m->selected >= m->count)
                m->selected = 0;
        }
        else if (c == ' ') {  // espace = valider
            if (m->options[m->selected].callback)
                m->options[m->selected].callback(m->options[m->selected].userdata);
            break;
        }

        menu_display(m);
    }
}

