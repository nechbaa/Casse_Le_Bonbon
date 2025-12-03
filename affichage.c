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
