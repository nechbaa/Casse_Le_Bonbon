#ifndef REGLES_H
#define REGLES_H

#include "affichage.h"

#define VIDE '.'   // caractère représentant une case vide

int  Suppression(char plateau[LIGNES][COLONNES], int mask[LIGNES][COLONNES]);
char randItem(void);
void Gravite(char plateau[LIGNES][COLONNES]);

int  TrouverGroupesSimples(char plateau[LIGNES][COLONNES], int mask[LIGNES][COLONNES]);

// Compter nombre de S/F/P/O/M qui vont être supprimés suivant le masque
void CompterFruitsSupprimes(char plateau[LIGNES][COLONNES],
                            int mask[LIGNES][COLONNES],
                            int *nbS, int *nbF, int *nbP, int *nbO, int *nbM);

#endif
