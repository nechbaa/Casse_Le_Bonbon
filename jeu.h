#ifndef JEU_H
#define JEU_H

#include "affichage.h"

// --- Gestion de la sélection ---
void gererSelection(char plateau[LIGNES][COLONNES], int x, int y);
int  getSelectionEtat(void);
int  getSelectionX(void);
int  getSelectionY(void);
void resetSelection(void);

// --- Gestion des échanges ---
int  permuterItems(char plateau[LIGNES][COLONNES], int x1, int y1, int x2, int y2);
void gererDeplacementAvecSelection(char plateau[LIGNES][COLONNES],
                                   int oldX, int oldY, int newX, int newY);

// --- État de jeu global (contrat, progression, coups) ---
void initGameState(int nbS, int nbF, int nbP, int nbO, int nbM, int coupsMax);

int  getContratS(void);
int  getContratF(void);
int  getContratP(void);
int  getContratO(void);
int  getContratM(void);
int  getCoupsMax(void);

int  getProgS(void);
int  getProgF(void);
int  getProgP(void);
int  getProgO(void);
int  getProgM(void);
int  getCoupsUtilises(void);

int  isGameOver(void);   // 1 si partie terminée (défaite ou victoire), 0 sinon

#endif
