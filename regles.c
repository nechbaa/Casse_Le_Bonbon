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


// --- Gravité ANIMÉE : les fruits descendent petit à petit ---
void Gravite(char plateau[LIGNES][COLONNES], int nbS, int nbF, int nbP, int nbO, int nbM, int coupsMax)
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
            refreshScreen(plateau, nbS, nbF, nbP, nbO, nbM, coupsMax);
            Sleep(200);  // petite pause pour l'effet visuel
        }

    } while (moved);

    // 2) Remplir les cases vides en haut avec des fruits aléatoires, animés aussi
    for (int col = 0; col < COLONNES; col++) {
        for (int row = 0; row < LIGNES; row++) {
            if (plateau[row][col] == VIDE) {
                plateau[row][col] = randItem();
                refreshScreen(plateau, nbS, nbF, nbP, nbO, nbM, coupsMax);
                Sleep(200);
            }
        }
    }
}

// --- Recherche des groupes horizontaux / verticaux de taille >= 3 ---
// Remplit mask à 1 sur toutes les cases appartenant à un groupe.
// Retourne le nombre total de cases marquées (score de base).
int TrouverGroupesSimples(char plateau[LIGNES][COLONNES],int mask[LIGNES][COLONNES])
{
    // 0) Réinitialiser le masque : au départ, aucune case n'est marquée
    for (int i = 0; i < LIGNES; i++) {
        for (int j = 0; j < COLONNES; j++) {
            mask[i][j] = 0;
        }
    }

    int nbCases = 0;  // compteur global de cases à supprimer

    // Horizontaux
    for (int i = 0; i < LIGNES; i++) {     // on parcourt chaque ligne
        int j = 0;
        while (j < COLONNES) {             // parcours de gauche à droite
            char c = plateau[i][j];

            // Si c'est une case vide, on passe à la suivante
            if (c == VIDE) {
                j++;
                continue;
            }

            // On cherche la longueur du "run" (suite) de même lettre
            int k = j + 1;
            while (k < COLONNES && plateau[i][k] == c) {
                k++;
            }
            // - les colonnes j à (k-1) contiennent le même symbole c
            // - k est la première colonne différente (ou égale à COLONNES)

            int len = k - j;   // longueur du groupe

            // Si on a au moins 3 symboles consécutifs -> groupe valide
            if (len >= 3) {
                // On marque toutes les cases du groupe dans mask
                for (int col = j; col < k; col++) {
                    // On ne recompte pas deux fois la même case :
                    // si elle est déjà marquée (par ex. par un groupe vertical),
                    // on ne l'incrémente pas encore.
                    if (mask[i][col] == 0) {
                        mask[i][col] = 1;
                        nbCases++;
                    }
                }
            }

            // On saute directement au premier symbole différent
            j = k;
        }
    }

    // Groupes Verticaux
    for (int j = 0; j < COLONNES; j++) {   // on parcourt chaque colonne
        int i = 0;
        while (i < LIGNES) {               // parcours de haut en bas
            char c = plateau[i][j];

            // Si c'est une case vide, on passe à la suivante
            if (c == VIDE) {
                i++;
                continue;
            }

            // On cherche la longueur de la suite verticale de même lettre
            int k = i + 1;
            while (k < LIGNES && plateau[k][j] == c) {
                k++;
            }
            // À ce stade :
            // - les lignes i à (k-1) contiennent le même symbole c
            // - k est la première ligne différente (ou égale à LIGNES)

            int len = k - i;   // longueur du groupe

            // Si on a au moins 3 symboles consécutifs -> groupe valide
            if (len >= 3) {
                // On marque toutes les cases du groupe dans mask
                for (int lig = i; lig < k; lig++) {
                    // Toujours éviter de compter deux fois la même case
                    if (mask[lig][j] == 0) {
                        mask[lig][j] = 1;
                        nbCases++;
                    }
                }
            }

            // On saute directement à la première case différente
            i = k;
        }
    }

    // nbCases = nombre total de cases appartenant à un groupe (H ou V)
    return nbCases;
}

