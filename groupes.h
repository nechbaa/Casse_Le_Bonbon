#ifndef GROUPES_H
#define GROUPES_H

#include "affichage.h"

int TrouverGroupes(char plateau[LIGNES][COLONNES],int mask[LIGNES][COLONNES]);

int TrouverGroupesHorizontaux(char plateau[LIGNES][COLONNES],int mask[LIGNES][COLONNES], char deleteAll[5]);

int TrouverGroupesVerticaux(char plateau[LIGNES][COLONNES],int mask[LIGNES][COLONNES], char deleteAll[5]);

int TrouverGroupesRectangles(char plateau[LIGNES][COLONNES],int mask[LIGNES][COLONNES]);

int TrouverGroupesFormeH(char plateau[LIGNES][COLONNES],int mask[LIGNES][COLONNES]);

int DeleteAllFruit(char plateau[LIGNES][COLONNES],int mask[LIGNES][COLONNES], char fruit);

void FillIfNotContain(char tab[5], char c);

#endif