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

void gererSelection(char plateau[LIGNES][COLONNES], int x, int y) {
    // Aucun fruit sélectionné -> on sélectionne la case courante
    if (!estSelectionne) {
        estSelectionne = 1;
        selX = x; selY = y;
        afficherSelection(plateau, selX, selY, 1); // minuscule
        gotoligcol(LIGNES + 4, 0);
        Color(JAUNE, NOIR); printf("Fruit selectionne (%d,%d).", selX, selY); Color(BLANC, NOIR);
        return;
    }

    // Un fruit est sélectionné
    if (tentativeActive) {
        // ESPACE = valider la permutation temporaire
        // -> remettre les deux cases en “non sélectionné” (maj), vider les états
        afficherSelection(plateau, selX, selY, 0);   // majuscule
        afficherSelection(plateau, tmpX, tmpY, 0);   // majuscule
        estSelectionne = 0;
        tentativeActive = 0;
        selX = selY = tmpX = tmpY = -1;

        gotoligcol(LIGNES + 4, 0);
        Color(VERT, NOIR); afficherMessage("Permutation validee."); Color(BLANC, NOIR);
        return;
    }

    // Pas de tentative, on a rappuyé ESPACE sur la même case -> désélection simple
    if (x == selX && y == selY) {
        afficherSelection(plateau, selX, selY, 0);   // majuscule
        estSelectionne = 0;
        selX = selY = -1;

        gotoligcol(LIGNES + 4, 0);
        Color(BLANC, NOIR); afficherMessage("Deselection."); 
        return;
    }

    // Sinon (sélection active mais pas de tentative et autre case) : on ne fait rien ici.
    // C’est le déplacement (ZQSD/flèches) qui déclenchera la tentative sur voisin.
}


void gererDeplacementAvecSelection(char plateau[LIGNES][COLONNES],int oldX, int oldY, int newX, int newY) {
    if (!estSelectionne) return;

    int distance = abs(newX - selX) + abs(newY - selY);

    // Aucune tentative en cours : on autorise uniquement le déplacement SUR un voisin de (selX,selY)
    if (!tentativeActive) {
        if (distance == 1) {
            // Lancer la permutation temporaire (sel <-> voisin)
            permuterItems(plateau, selX, selY, newX, newY);

            // Visuel : la case d'origine RESTE la sélection (minuscule),
            //          le voisin doit être en non-sélection (majuscule).
            afficherSelection(plateau, selX, selY, 1);   // minuscule à l'origine (quel que soit le symbole après swap)
            afficherSelection(plateau, newX, newY, 0);   // majuscule sur le voisin

            tmpX = newX; tmpY = newY;
            tentativeActive = 1;

            gotoligcol(LIGNES + 4, 0);
            Color(JAUNE, NOIR); afficherMessage("Permutation temporaire (%d,%d). Valide avec ESPACE ou reviens a l'origine.", newX, newY);
            Color(BLANC, NOIR);
        
        }
        return;
    }

    // Tentative en cours
    // 1) Revenir exactement sur la case d’origine -> annuler la permutation temporaire
    if (distance == 0) {
        // annuler le swap
        permuterItems(plateau, selX, selY, tmpX, tmpY);

        // visuel : origine reste sélection (minuscule), voisin redevient non-sélection
        afficherSelection(plateau, selX, selY, 1);
        afficherSelection(plateau, tmpX, tmpY, 0);

        tentativeActive = 0;
        tmpX = tmpY = -1;

        gotoligcol(LIGNES + 4, 0);
        Color(BLEU, NOIR); afficherMessage("Permutation annulee. Tu peux tenter un autre voisin.");
        Color(BLANC, NOIR);
        return;
    }

}



// --- Fonction de permutation de deux fruits ---
int permuterItems(char plateau[LIGNES][COLONNES], int x1, int y1, int x2, int y2) {
    

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
