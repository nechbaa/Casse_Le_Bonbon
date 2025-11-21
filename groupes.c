#include <stdio.h>
#include "affichage.h"  // pour LIGNES, COLONNES
#include "groupes.h"

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

    char deleteAll[5];

    // Horizontaux
    nbCases += TrouverGroupesHorizontaux(plateau, mask, deleteAll);

    // Groupes Verticaux
    nbCases += TrouverGroupesVerticaux(plateau, mask, deleteAll);

    int i = 0;
    while (deleteAll[i] != '\0')
    {
        nbCases += DeleteAllFruit(plateau, mask, deleteAll[i]);
    }
    
    // nbCases = nombre total de cases appartenant à un groupe (H ou V)
    return nbCases;
}


int TrouverGroupesHorizontaux(char plateau[LIGNES][COLONNES],int mask[LIGNES][COLONNES], char deleteAll[5])
{
    int nbCases = 0;

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
            // À ce stade :
            // - les colonnes j à (k-1) contiennent le même symbole c
            // - k est la première colonne différente (ou égale à COLONNES)

            int len = k - j;   // longueur du groupe

            // Si on a au moins 6 symboles consécutifs -> groupe valide
            if (len > 5) {

                // ajoute le fruit pour les supprimer tous
                FillIfNotContain(deleteAll, c);

                k = j + 6; // on ne garde que les 6 premiers
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
            else if(len > 3) // Si on en a 4
            {
                k = j + 4; // on ne garde que les 4 premiers
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

    return nbCases;
}


int TrouverGroupesVerticaux(char plateau[LIGNES][COLONNES],int mask[LIGNES][COLONNES], char deleteAll[5])
{
    int nbCases = 0;

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

            // Si on a au moins 6 symboles consécutifs -> groupe valide
            if (len > 5) {

                FillIfNotContain(deleteAll, c);

                k = i + 6;

                // On marque toutes les cases du groupe dans mask
                for (int lig = i; lig < k; lig++) {
                    // Toujours éviter de compter deux fois la même case
                    if (mask[lig][j] == 0) {
                        mask[lig][j] = 1;
                        nbCases++;
                    }
                }
            }
            else if (len > 3) {
                k = i + 4;

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

    return nbCases;
}

int DeleteAllFruit(char plateau[LIGNES][COLONNES],int mask[LIGNES][COLONNES], char fruit)
{
    int nbCases = 0;
    for (int i = 0; i < LIGNES; i++)
    {
        for (int j = 0; j < COLONNES; j++)
        {
            if(plateau[i][j] == fruit && mask[i][j] == 0)
            {
                mask[i][j] = 1;
                nbCases++;
            }
        }
    }
    
    return nbCases;
}

void FillIfNotContain(char tab[5], char c) {
    for (int i = 0; i < 5; i++) {
        if (tab[i] == c) return;
    }
    for (int i = 0; i < 5; i++) {
        if (tab[i] == '\0') {
            tab[i] = c;
            return;
        }
    }
}