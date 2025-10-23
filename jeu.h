#ifndef JEU_H
#define JEU_H

#include "affichage.h"

// --- Gestion de la sélection ---
void gererSelection(char plateau[LIGNES][COLONNES], int x, int y);
int getSelectionEtat();
int getSelectionX();
int getSelectionY();
void resetSelection();

// --- Gestion des échanges ---
void essayerPermutation(char plateau[LIGNES][COLONNES], int x, int y);

// --- Mécanique du jeu ---
int permuterItems(char plateau[LIGNES][COLONNES], int x1, int y1, int x2, int y2);

void gererActionSelectionOuValidation(char plateau[LIGNES][COLONNES], int x, int y);
void gererDeplacementAvecSelection(char plateau[LIGNES][COLONNES], int oldX, int oldY, int newX, int newY);

#endif
