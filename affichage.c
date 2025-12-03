#include "affichage.h"
#include <stdarg.h>
#include <time.h>
#include <windows.h>

// --- Fonction pour changer la couleur du texte ---
static inline void Color(int texte, int fond) {
    static HANDLE H = NULL;
    if (!H) H = GetStdHandle(STD_OUTPUT_HANDLE); // évite de rappeler GetStdHandle à chaque fois
    SetConsoleTextAttribute(H, (fond << 4) | texte);
}
// --- Fonction pour déplacer le curseur ---
static inline void gotoligcol(int lig, int col) {
    COORD mycoord = { (SHORT)col, (SHORT)lig };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), mycoord);
}
// --- Initialisation aléatoire du plateau ---
void initialiserPlateau(char plateau[LIGNES][COLONNES]) {
    static const char items[] = {'S', 'F', 'P', 'O', 'M'};
    srand((unsigned)time(NULL));

    for (int i = 0; i < LIGNES; i++) {
        for (int j = 0; j < COLONNES; j++) {
            plateau[i][j] = items[rand() % (sizeof(items)/sizeof(items[0]))];
        }
    }
}
