#include "deplacement.h"
#include "jeu.h"
#include "affichage.h"
#include <conio.h>    // getch()

int curX = 0;
int curY = 0;
char touche = 0;

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

    // si la case est en minuscule -> c'est la sélection : conserver son rendu
    if (plateau[y][x] >= 'a' && plateau[y][x] <= 'z') {
        Color(NOIR, VERT);
        printf("%c", plateau[y][x]);  // laisse la minuscule
        Color(BLANC, NOIR);
        return;
    }

    // sinon, couleur normale selon la lettre MAJ
    char c = plateau[y][x];
    switch (c) {
        case 'S': Color(JAUNE, NOIR); break;
        case 'F': Color(ROUGE, NOIR); break;
        case 'P': Color(VERT, NOIR); break;
        case 'O': Color(CYAN, NOIR); break;
        case 'M': Color(MAGENTA, NOIR); break;
        default:  Color(BLANC, NOIR); break;
    }
    printf("%c", c);
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

void InitialiserCurseur(char plateau[LIGNES][COLONNES])
{
    curX = 0; 
    curY = 0;

    afficherCurseur(curX, curY, plateau);
}

int deplacerCurseur(char plateau[LIGNES][COLONNES]) {
    

        touche = getch();

        if (touche == 27) return 1; // ESC = quitter

        int newX = curX, newY = curY;

        // --- On efface toujours le curseur avant de bouger ---
        effacerCurseur(curX, curY, plateau);

        // --- Gestion des directions ---
        switch (touche) {
            case 'z': case 'Z': case 72:
                if (curY > 0) newY--;
                break;
            case 's': case 'S': case 80:
                if (curY < LIGNES - 1) newY++;
                break;
            case 'q': case 'Q': case 75:
                if (curX > 0) newX--;
                break;
            case 'd': case 'D': case 77:
                if (curX < COLONNES - 1) newX++;
                break;
            case ' ':
                gererSelection(plateau, curX, curY);
                break;
        }

         // --- Gestion spéciale si un fruit est sélectionné ---
        if (getSelectionEtat()) {
            int selX = getSelectionX();
            int selY = getSelectionY();
            int distance = abs(newX - selX) + abs(newY - selY);
        
            if (distance == 0 || distance == 1) {
                gererDeplacementAvecSelection(plateau, curX, curY, newX, newY);
                curX = newX; curY = newY;
            }
            else {
                afficherMessage("Tu ne peux bouger que d'une case autour du fruit selectionne !");
                // on ne bouge pas
                newX = curX; newY = curY;
            }
        }

        else {
                // Aucun fruit sélectionné → déplacement libre
                curX = newX;
                curY = newY;
        }

        // --- Affiche le curseur à sa nouvelle position ---
        afficherCurseur(curX, curY, plateau);
    return 0;
    
}

