#include "affichage.h"  // pour LIGNES, COLONNES
#include "regles.h"
#include <stdio.h>
#define VIDE '.'   // definition claire du caractère représentant une case vide

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
                plateau[i][j] = VIDE;
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
            if (plateau[row][col] != VIDE) {
                plateau[write][col] = plateau[row][col];
                write--;
            }
        }

        // 2) Remplir le haut avec du random
        for (int row = write; row >= 0; row--) {
            plateau[row][col] = randItem();
        }
    }

}