#ifndef JEU_H
#define JEU_H

#include "affichage.h"



int Suppression(char plateau[LIGNES][COLONNES],int mask[LIGNES][COLONNES]);

char randItem(void);

void Gravite(char plateau[LIGNES][COLONNES]);

#endif