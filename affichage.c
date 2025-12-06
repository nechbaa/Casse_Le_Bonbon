#include "affichage.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>

// --- Fonction pour changer la couleur du texte ---
void Color(int texte, int fond) {
    printf("\033[%d;%dm", texte, fond + 10); // séquence ANSI
}

// --- Fonction pour déplacer le curseur ---
void gotoligcol(int lig, int col) {
    printf("\033[%d;%dH", lig + 1, col + 1);
}

// --- Initialisation aléatoire du plateau ---
void initialiserPlateau(char plateau[LIGNES][COLONNES]) {
    char items[5] = {'S','F','P','O','M'};
    srand(time(NULL));

    for (int i = 0; i < LIGNES; i++) {
        for (int j = 0; j < COLONNES; j++) {
            int r = rand() % 5;
            plateau[i][j] = items[r];
        }
    }
}

// --- Affichage du plateau ---
void afficherPlateau(char plateau[LIGNES][COLONNES]) {
    printf("\033[2J\033[H"); // efface l’écran

    // Bordure haut
    printf("%c", 0xC9);
    for (int j = 0; j < COLONNES; j++) printf("%c", 0xCD);
    printf("%c\n", 0xBB);

    // Corps
    for (int i = 0; i < LIGNES; i++) {
        printf("%c", 0xBA);
        for (int j = 0; j < COLONNES; j++) {
            if (plateau[i][j] == 'S') Color(33, 40); 
            else if (plateau[i][j] == 'F') Color(31, 40); 
            else if (plateau[i][j] == 'P') Color(32, 40); 
            else if (plateau[i][j] == 'O') Color(36, 40); 
            else if (plateau[i][j] == 'M') Color(35, 40); 
            else Color(37, 40); // Blanc

            printf("%c", plateau[i][j]);
        }
        Color(37, 40);
        printf("%c\n", 0xBA);
    }

    // Bordure bas
    printf("%c", 0xC8);
    for (int j = 0; j < COLONNES; j++) printf("%c", 0xCD);
    printf("%c", 0xBC);
}

// --- Affichage du contrat ---
void afficherContrat(int nbS, int nbF, int nbP, int nbO, int nbM, int coupsMax) {
    Color(37, 40);
    gotoligcol(1, COLONNES + 5);
    printf("=== CONTRAT ===");

    gotoligcol(3, COLONNES + 5); printf("Soleils   (S) : %d", nbS);
    gotoligcol(4, COLONNES + 5); printf("Fraises   (F) : %d", nbF);
    gotoligcol(5, COLONNES + 5); printf("Pommes    (P) : %d", nbP);
    gotoligcol(6, COLONNES + 5); printf("Oignons   (O) : %d", nbO);
    gotoligcol(7, COLONNES + 5); printf("Mandarines(M) : %d", nbM);

    gotoligcol(9, COLONNES + 5);
    printf("Coups max : %d", coupsMax);
    Color(37, 40);
}

// --- Effacer message ---
void effacerMessage(void) {
    gotoligcol(LIGNES + 4, 0);
    printf("                                                                                                    ");
}

// --- Afficher message ---
void afficherMessage(const char* fmt, ...) {
    effacerMessage();
    gotoligcol(LIGNES + 4, 0);
    va_list ap;
    va_start(ap, fmt);
    vprintf(fmt, ap);
    va_end(ap);
    Color(37, 40);
}

// --- Rafraîchir écran ---
void refreshScreen(char plateau[LIGNES][COLONNES],
                   int nbS, int nbF, int nbP, int nbO, int nbM, int coupsMax) {
    afficherPlateau(plateau);
    afficherContrat(nbS, nbF, nbP, nbO, nbM, coupsMax);

    gotoligcol(LIGNES + 3, 0);
    Color(37, 40);
    printf("Utilise Z Q S D pour te deplacer, ESPACE pour selectionner, ECHAP pour quitter.\n");
}
