
#ifndef JEU_H
#define JEU_H

#include "affichage.h"

// --- Fonctions principales du moteur de jeu ---

// Permute deux items si c’est possible (voisins dans la grille)
int permuterItems(char plateau[LIGNES][COLONNES], int x1, int y1, int x2, int y2);

// Vérifie et supprime les groupes de 3+ identiques
int supprimerGroupes(char plateau[LIGNES][COLONNES]);

// Applique la gravité sur le plateau après suppression
void appliquerGravite(char plateau[LIGNES][COLONNES]);

// Remplit les vides en haut avec de nouveaux fruits
void remplirPlateau(char plateau[LIGNES][COLONNES]);

// Fonction globale de stabilisation (boucle complète)
void stabiliserPlateau(char plateau[LIGNES][COLONNES]);

#endif
