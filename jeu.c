#include "jeu.h"

// --- Fonction de permutation de deux fruits ---
int permuterItems(char plateau[LIGNES][COLONNES], int x1, int y1, int x2, int y2) {
    // Vérifie que les deux cases sont bien voisines
    int dx = x2 - x1;
    int dy = y2 - y1;

    if (!((dx == 0 && (dy == 1 || dy == -1)) || ((dx == 1 || dx == -1) && dy == 0))) {
        return 0; // pas adjacentes → permutation impossible
    }

    // Échange les deux fruits
    char temp = plateau[y1][x1];
    plateau[y1][x1] = plateau[y2][x2];
    plateau[y2][x2] = temp;

    // Réaffiche uniquement les deux cases échangées
    gotoligcol(y1 + 1, x1 + 1);
    switch (plateau[y1][x1]) {
        case 'S': Color(JAUNE, NOIR); break;
        case 'F': Color(ROUGE, NOIR); break;
        case 'P': Color(VERT, NOIR); break;
        case 'O': Color(CYAN, NOIR); break;
        case 'M': Color(MAGENTA, NOIR); break;
        default: Color(BLANC, NOIR); break;
    }
    printf("%c", plateau[y1][x1]);

    gotoligcol(y2 + 1, x2 + 1);
    switch (plateau[y2][x2]) {
        case 'S': Color(JAUNE, NOIR); break;
        case 'F': Color(ROUGE, NOIR); break;
        case 'P': Color(VERT, NOIR); break;
        case 'O': Color(CYAN, NOIR); break;
        case 'M': Color(MAGENTA, NOIR); break;
        default: Color(BLANC, NOIR); break;
    }
    printf("%c", plateau[y2][x2]);

    Color(BLANC, NOIR);
    gotoligcol(LIGNES + 3, 0);

    return 1; // succès
}
