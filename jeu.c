#include "jeu.h"
#include "deplacement.h"
#include "affichage.h"

static int estSelectionne = 0;
static int tentativeActive = 0;
static int tmpX, tmpY;

// --- Variables internes à la sélection ---
static int selX = -1;
static int selY = -1;

// --- Fonctions d’accès à l’état de sélection ---
int getSelectionEtat() {
    return estSelectionne;
}

int getSelectionX() {
    return selX;
}

int getSelectionY() {
    return selY;
}

void gererActionSelectionOuValidation(char plateau[LIGNES][COLONNES], int x, int y) {
    if (!estSelectionne) {
        estSelectionne = 1;
        selX = x; selY = y;
        afficherSelection(plateau, x, y, 1);
    } 
    else if (tentativeActive) {
        // Valide la permutation temporaire
        afficherSelection(plateau, tmpX, tmpY, 0);
        estSelectionne = tentativeActive = 0;
    } 
    else if (x == selX && y == selY) {
        // Désélection simple
        afficherSelection(plateau, x, y, 0);
        estSelectionne = 0;
    }
}

void gererDeplacementAvecSelection(char plateau[LIGNES][COLONNES], int oldX, int oldY, int newX, int newY) {
    if (!estSelectionne) return;

    if (!tentativeActive) {
        if (abs(newX - selX) + abs(newY - selY) == 1) {
            // tentative d’échange
            permuterItems(plateau, selX, selY, newX, newY);
            tmpX = newX; tmpY = newY;
            tentativeActive = 1;
        } else {
            // mouvement interdit
            gotoligcol(LIGNES + 4, 0);
            Color(ROUGE, NOIR);
            printf("⚠ Déplacement invalide pendant sélection !");
            Color(BLANC, NOIR);
        }
    } 
    else if (newX == selX && newY == selY) {
        // annulation
        permuterItems(plateau, selX, selY, tmpX, tmpY);
        tentativeActive = 0;
    }
}


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
