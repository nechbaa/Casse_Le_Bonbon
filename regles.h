#ifndef REGLES_H
#define REGLES_H

#include "affichage.h"
#define VIDE '.' 


int Suppression(char plateau[LIGNES][COLONNES],int mask[LIGNES][COLONNES]);

char randItem(void);

void Gravite(char plateau[LIGNES][COLONNES], int nbS, int nbF, int nbP, int nbO, int nbM, int coupsMax);

int TrouverGroupesSimples(char plateau[LIGNES][COLONNES],int mask[LIGNES][COLONNES]);

#endif