#include <stdio.h>
#include "affichage.h"  // pour LIGNES, COLONNES
#include "regles.h"
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


// --- Gravité ANIMÉE : les fruits descendent petit à petit ---
void Gravite(char plateau[LIGNES][COLONNES])
{
    int moved;

    // 1) Faire tomber les fruits petit à petit
    do {
        moved = 0;

        for (int col = 0; col < COLONNES; col++) {
            for (int row = LIGNES - 1; row > 0; row--) {
                if (plateau[row][col] == VIDE && plateau[row - 1][col] != VIDE) {
                    plateau[row][col]     = plateau[row - 1][col];
                    plateau[row - 1][col] = VIDE;
                    moved = 1;
                }
            }
        }

        if (moved) {
            // On rafraîchit TOUT l'écran : plateau + contrat + messages
            refreshScreen(plateau);
            Sleep(50);  // petite pause pour l'effet visuel
        }

    } while (moved);

    // 2) Remplir les cases vides en haut avec des fruits aléatoires, animés aussi
    for (int col = 0; col < COLONNES; col++) {
        for (int row = 0; row < LIGNES; row++) {
            if (plateau[row][col] == VIDE) {
                plateau[row][col] = randItem();
                refreshScreen(plateau);
                Sleep(50);
            }
        }
    }
}

// --- Compter combien de S/F/P/O/M vont être supprimés ---
void CompterFruitsSupprimes(char plateau[LIGNES][COLONNES],
                            int mask[LIGNES][COLONNES],
                            int *nbS, int *nbF, int *nbP, int *nbO, int *nbM)
{
    *nbS = *nbF = *nbP = *nbO = *nbM = 0;

    for (int i = 0; i < LIGNES; i++) {
        for (int j = 0; j < COLONNES; j++) {
            if (mask[i][j] == 1) {
                char c = plateau[i][j];
                switch (c) {
                    case 'S': (*nbS)++; break;
                    case 'F': (*nbF)++; break;
                    case 'P': (*nbP)++; break;
                    case 'O': (*nbO)++; break;
                    case 'M': (*nbM)++; break;
                    default: break;
                }
            }
        }
    }
}


