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
// --- Gère le déplacement du curseur avec ZQSD ---
void deplacerCurseur(char plateau[LIGNES][COLONNES]) {
    int x = 0, y = 0;
    char touche;

    afficherCurseur(x, y, plateau); // affiche la position initiale

    while (1) {
        touche = getch();
        effacerCurseur(x, y, plateau); // efface l’ancien curseur

        switch (touche) {
            case 'z': case 'Z': if (y > 0) y--; break;
            case 's': case 'S': if (y < LIGNES - 1) y++; break;
            case 'q': case 'Q': if (x > 0) x--; break;
            case 'd': case 'D': if (x < COLONNES - 1) x++; break;
            case 27: // ESC → quitter
                gotoligcol(LIGNES + 3, 0);
                Color(BLANC, NOIR);
                printf("\n");
                return;
            case ' ': // ESPACE → sélectionner / désélectionner
                selectionnerItem(plateau, x, y);
                break;
        }

        afficherCurseur(x, y, plateau); // redessine à la nouvelle position
    }
}

// --- (bientôt) Sélection et échange ---
void selectionnerItem(char plateau[LIGNES][COLONNES], int x, int y) {
    gotoligcol(y + 1, x + 1);

    if (plateau[y][x] >= 'a' && plateau[y][x] <= 'z') {
        plateau[y][x] -= 32; // redevenir majuscule
        Color(BLANC, BLEU);
    } else {
        plateau[y][x] += 32; // passer en minuscule
        Color(NOIR, JAUNE);
    }

    printf("%c", plateau[y][x]);
    Color(BLANC, NOIR);
    gotoligcol(LIGNES + 3, 0);
}

void echangerItems(char plateau[LIGNES][COLONNES], int x1, int y1, int x2, int y2) {
    // sera implémentée plus tard
}
