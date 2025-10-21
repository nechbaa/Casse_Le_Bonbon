#include "deplacement.h"
#include "affichage.h"
#include <conio.h>    // getch()

// --- Affiche le plateau avec le curseur en (x, y) ---
void afficherCurseur(int x, int y, char plateau[LIGNES][COLONNES]) {
    gotoligcol(y + 1, x + 1); // +1 car bordures en haut/gauche
    Color(BLANC, GRIS_FONCE);
    printf("%c", plateau[y][x]);
    Color(BLANC, NOIR);
    gotoligcol(LIGNES + 3, 0); // repositionne le curseur en bas après affichage
}
// --- Efface le curseur précédent ---
void effacerCurseur(int x, int y, char plateau[LIGNES][COLONNES]) {
    gotoligcol(y + 1, x + 1);
    // remettre la couleur de base de la case
    switch (plateau[y][x]) {
        case 'S': Color(JAUNE, NOIR); break;
        case 'F': Color(ROUGE, NOIR); break;
        case 'P': Color(VERT, NOIR); break;
        case 'O': Color(CYAN, NOIR); break;
        case 'M': Color(MAGENTA, NOIR); break;
        default:  Color(BLANC, NOIR); break;
    }
    printf("%c", plateau[y][x]);
    Color(BLANC, NOIR);
}

// --- Affichage visuel de la sélection ---
void afficherSelection(char plateau[LIGNES][COLONNES], int x, int y, int estSelectionne) {
    gotoligcol(y + 1, x + 1);
    if (estSelectionne){
        // Mettre la lettre en minuscule
        if (plateau[y][x] >= 'A' && plateau[y][x] <= 'Z')
            plateau[y][x] += 32;
        Color(NOIR, VERT);} // fond vert = sélectionné
    else {
        // Remettre en majuscule
        if (plateau[y][x] >= 'a' && plateau[y][x] <= 'z')
            plateau[y][x] -= 32;
        // couleur normale
        switch (plateau[y][x]) {
            case 'S': Color(JAUNE, NOIR); break;
            case 'F': Color(ROUGE, NOIR); break;
            case 'P': Color(VERT, NOIR); break;
            case 'O': Color(CYAN, NOIR); break;
            case 'M': Color(MAGENTA, NOIR); break;
            default: Color(BLANC, NOIR); break;
        }
    }
    printf("%c", plateau[y][x]);
    Color(BLANC, NOIR);
}


// --- Déplacement + sélection simple ---
void deplacerCurseur(char plateau[LIGNES][COLONNES]) {
    int x = 0, y = 0;                // position du curseur
    int selX = -1, selY = -1;        // position du fruit sélectionné
    int itemSelectionne = 0;         // 0 = rien, 1 = un fruit sélectionné
    char touche;

    afficherCurseur(x, y, plateau);

    while (1) {
        touche = getch();

        // efface ancien curseur (si pas sur sélection)
        if (!(itemSelectionne && x == selX && y == selY))
            effacerCurseur(x, y, plateau);

        // --- Gestion des touches ---
        switch (touche) {
            // === Déplacements ===
            case 'z': case 'Z': case 72 :
                if (!itemSelectionne && y > 0) y--;
                else if (itemSelectionne) {
                    gotoligcol(LIGNES + 4, 0);
                    Color(ROUGE, NOIR);
                    printf("⚠ Tu dois deselectionner le fruit avant de te deplacer ou echanger !");
                    Color(BLANC, NOIR);
                }
                break;

            case 's': case 'S': case 80 :
                if (!itemSelectionne && y < LIGNES - 1) y++;
                else if (itemSelectionne) {
                    gotoligcol(LIGNES + 4, 0);
                    Color(ROUGE, NOIR);
                    printf("⚠ Tu dois deselectionner le fruit avant de te deplacer ou echanger !");
                    Color(BLANC, NOIR);
                }
                break;

            case 'q': case 'Q': case 75 :
                if (!itemSelectionne && x > 0) x--;
                else if (itemSelectionne) {
                    gotoligcol(LIGNES + 4, 0);
                    Color(ROUGE, NOIR);
                    printf("⚠ Tu dois deselectionner le fruit avant de te deplacer ou echanger !");
                    Color(BLANC, NOIR);
                }
                break;

            case 'd': case 'D': case 77 :
                if (!itemSelectionne && x < COLONNES - 1) x++;
                else if (itemSelectionne) {
                    gotoligcol(LIGNES + 4, 0);
                    Color(ROUGE, NOIR);
                    printf("⚠ Tu dois deselectionner le fruit avant de te deplacer ou echanger !");
                    Color(BLANC, NOIR);
                }
                break;

            // === Sélection ===
            case ' ': // ESPACE -> sélection / désélection
                gotoligcol(LIGNES + 4, 0);
                printf("                                                                               "); // efface ancien message

                if (itemSelectionne == 0) {
                    itemSelectionne = 1;
                    selX = x;
                    selY = y;
                    afficherSelection(plateau, selX, selY, 1);
                } 
                else if (x == selX && y == selY) {
                    // désélection du même fruit
                    itemSelectionne = 0;
                    selX = selY = -1;
                    afficherSelection(plateau, x, y, 0);
                }
                break;

            // === Quitter ===
            case 27: // ESC -> quitter
                gotoligcol(LIGNES + 5, 0);
                Color(BLANC, NOIR);
                printf("\n");
                return;
        }

        afficherCurseur(x, y, plateau);
    }
}

// --- (bientôt) Sélection et échange ---
void selectionnerItem(char plateau[LIGNES][COLONNES], int x, int y, int *selX, int *selY, int *itemSelectionne) {
   // si rien n’est sélectionné → on sélectionne cette case
    if (*itemSelectionne == 0) {
        *itemSelectionne = 1;
        *selX = x;
        *selY = y;

        gotoligcol(y + 1, x + 1);
        Color(NOIR, VERT); // fond vert pour indiquer la sélection
        printf("%c", plateau[y][x]);
        Color(BLANC, NOIR);
    } 
    // si on reclique sur la même case → on la désélectionne
    else if (x == *selX && y == *selY) {
        *itemSelectionne = 0;

        gotoligcol(y + 1, x + 1);
        // remettre la couleur normale
        switch (plateau[y][x]) {
            case 'S': Color(JAUNE, NOIR); break;
            case 'F': Color(ROUGE, NOIR); break;
            case 'P': Color(VERT, NOIR); break;
            case 'O': Color(CYAN, NOIR); break;
            case 'M': Color(MAGENTA, NOIR); break;
            default: Color(BLANC, NOIR); break;
        }
        printf("%c", plateau[y][x]);
        Color(BLANC, NOIR);
        *selX = -1;
        *selY = -1;
    }

    gotoligcol(LIGNES + 3, 0);
}

void echangerItems(char plateau[LIGNES][COLONNES], int x1, int y1, int x2, int y2) {
    // sera implémentée plus tard
}
