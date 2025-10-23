#include "deplacement.h"
#include "jeu.h"
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
    int x = 0, y = 0;
    char touche;

    afficherCurseur(x, y, plateau);

    while (1) {
        touche = getch();

        if (touche == 27) return; // ESC = quitter

        int newX = x, newY = y;

        // --- On efface toujours le curseur avant de bouger ---
        effacerCurseur(x, y, plateau);

        // --- Gestion des directions ---
        switch (touche) {
            case 'z': case 'Z': case 72:
                if (y > 0) newY--;
                break;
            case 's': case 'S': case 80:
                if (y < LIGNES - 1) newY++;
                break;
            case 'q': case 'Q': case 75:
                if (x > 0) newX--;
                break;
            case 'd': case 'D': case 77:
                if (x < COLONNES - 1) newX++;
                break;
            case ' ':
                gererActionSelectionOuValidation(plateau, x, y);
                break;
        }

        // --- Si déplacement du curseur ---
        if (newX != x || newY != y) {
            // 🧠 Vérifie si on a un fruit sélectionné
            if (getSelectionEtat()) {
                int selX = getSelectionX();
                int selY = getSelectionY();
                int distance = abs(newX - selX) + abs(newY - selY);

                if (distance == 1) {
                    // ✅ Autorisé : le curseur bouge d’une case voisine → tentative d’échange
                    gererDeplacementAvecSelection(plateau, x, y, newX, newY);
                    x = newX;
                    y = newY;
                } else {
                    // 🚫 Interdit : trop loin de la sélection
                    gotoligcol(LIGNES + 4, 0);
                    Color(ROUGE, NOIR);
                    printf("⚠ Tu ne peux te déplacer qu'à une case voisine du fruit sélectionné !");
                    Color(BLANC, NOIR);

                    // On ne bouge pas le curseur
                    newX = x;
                    newY = y;
                }
            } else {
                // Aucun fruit sélectionné → déplacement libre
                x = newX;
                y = newY;
            }
        }

        // --- Affiche le curseur à sa nouvelle position ---
        afficherCurseur(x, y, plateau);
    }
}

// --- (bientôt) Sélection et échange ---



void echangerItems(char plateau[LIGNES][COLONNES], int x1, int y1, int x2, int y2) {
    // sera implémentée plus tard
}
