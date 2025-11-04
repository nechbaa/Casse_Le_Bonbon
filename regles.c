#include "affichage.h"  // pour LIGNES, COLONNES
#include <stdio.h>

// --- Génère un item aléatoire parmi {S,F,P,O,M}
char randItem(void) {
    const char t[5] = {'S','F','P','O','M'};
    return t[rand() % 5];
}

//creation et initialisation du masque binaire de la meme taille que le plateau qui mes a 1 les cases quiq doivent etre supprimés 0 sinon
//applique la suppression detectée dans le masque sur le plateau de jeu actuel
int Suppression(char plateau[LIGNES][COLONNES],int mask[LIGNES][COLONNES])
{
    int supprimees = 0;

    for (int i = 0; i < LIGNES; i++) {
        for (int j = 0; j < COLONNES; j++) {
            if (mask[i][j] == 1) {
                plateau[i][j] = ' ';
                supprimees++;
            }
        }
    }

    return supprimees;
}


void Gravite(char plateau[LIGNES][COLONNES]) {
    for (int col = 0; col < COLONNES; col++) {
        int write = LIGNES - 1;     // position d'écriture depuis le bas

        // 1) Descendre tous les items non vides
        for (int row = LIGNES - 1; row >= 0; row--) {
            if (plateau[row][col] != '.') {
                plateau[write][col] = plateau[row][col];
                write--;
            }
        }

        // 2) Remplir le haut avec du random
        for (int row = write; row >= 0; row--) {
            plateau[row][col] = rndItem();
        }
    }

    // 3) Réaffichage du plateau (on fait simple : tout redessiner)
    for (int i = 0; i < LIGNES; i++) {
        gotoligcol(i + 1, 1);
        for (int j = 0; j < COLONNES; j++) {
            // couleur “neutre” ici; si tu as un affichage coloré par lettre,
            // tu peux réutiliser le switch de afficherPlateau()
            Color(BLANC, NOIR);
            printf("%c", plateau[i][j]);
        }
    }
    Color(BLANC, NOIR);
}