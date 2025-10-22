#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define LIGNES 10
#define COLONNES 10

// Codes couleurs (texte uniquement)
#define NOIR 0
#define BLEU 1
#define VERT 2
#define CYAN 3
#define ROUGE 4
#define MAGENTA 5
#define GRIS_CLAIR 7
#define GRIS_FONCE 8
#define JAUNE 14
#define BLANC 15

// Prototypes
void Color(int texte, int fond);


void gotoligcol(int lig, int col);


void initialiserPlateau(char plateau[LIGNES][COLONNES]);


void afficherPlateau(char plateau[LIGNES][COLONNES]);

void afficherProgression (int nbS, int nbF, int nbP, int nbO, int nbM, int nbCoups);

void afficherContrat(int nbS, int nbF, int nbP, int nbO, int nbM, int coupsMax);

#endif
