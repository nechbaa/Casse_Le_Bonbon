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
#define JAUNE_FONCE 6
#define GRIS_CLAIR 7
#define GRIS_FONCE 8
#define BLEU_CLAIR 9
#define VERT_CLAIR 10
#define CYAN_CLAIR 11
#define ROUGE_CLAIR 12
#define ROSE 13
#define JAUNE 14
#define BLANC 15

// Prototypes
void Color(int texte, int fond);
void gotoligcol(int lig, int col);

void initialiserPlateau(char plateau[LIGNES][COLONNES]);
void remplirPlateau(char plateau[LIGNES][COLONNES], int mask[LIGNES][COLONNES]);
void afficherPlateau(char plateau[LIGNES][COLONNES]);

void afficherProgression(void);
void afficherContrat(void);

void effacerMessage(void);
void afficherMessage(const char* fmt, ...);

void refreshScreen(char plateau[LIGNES][COLONNES]);

void cleanArea(int x1, int x2, int y1, int y2);

#endif
