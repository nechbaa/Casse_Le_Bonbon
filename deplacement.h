#ifndef DEPLACEMENT_H
#define DEPLACEMENT_H

#include <stdio.h>
#include <conio.h>    // getch()
#include "affichage.h"

// Fonctions principales
void afficherCurseur(int x, int y, char plateau[LIGNES][COLONNES]);
void effacerCurseur(int x, int y, char plateau[LIGNES][COLONNES]);
void deplacerCurseur(char plateau[LIGNES][COLONNES]);

void afficherSelection(char plateau[LIGNES][COLONNES], int x, int y, int estSelectionne) ;

// (Futures fonctions à venir)
void echangerItems(char plateau[LIGNES][COLONNES], int x1, int y1, int x2, int y2);

#endif
