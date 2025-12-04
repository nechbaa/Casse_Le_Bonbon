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

// --- Affichage coloré du plateau ---
void afficherPlateau(char plateau[LIGNES][COLONNES]) {
    system("cls"); // nettoyage console

    // Bordure supérieure
    putchar(0xC9);
    for (int j = 0; j < COLONNES; j++) putchar(0xCD);
    putchar(0xBB);
    putchar('\n');

    // Corps du plateau
    for (int i = 0; i < LIGNES; i++) {
        putchar(0xBA);
        for (int j = 0; j < COLONNES; j++) {
            switch (plateau[i][j]) {
                case 'S': Color(JAUNE, NOIR); break;
                case 'F': Color(ROUGE, NOIR); break;
                case 'P': Color(VERT, NOIR); break;
                case 'O': Color(CYAN, NOIR); break;
                case 'M': Color(MAGENTA, NOIR); break;
                default:  Color(BLANC, NOIR); break;
            }
            putchar(plateau[i][j]);
        }
        Color(BLANC, NOIR);
        putchar(0xBA);
        putchar('\n');
    }

    // Bordure inférieure
    putchar(0xC8);
    for (int j = 0; j < COLONNES; j++) putchar(0xCD);
    putchar(0xBC);
}
