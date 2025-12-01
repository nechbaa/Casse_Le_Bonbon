#include "affichage.h"
#include "regles.h"
#include "deplacement.h"
#include "jeu.h"
#include <conio.h>
#define COUPMAX 30

int main() {
    char plateau[LIGNES][COLONNES];

    // Paramètres du contrat
    int nbS = 20, nbF = 50, nbP = 20, nbO = 0, nbM = 0, coupsMax = COUPMAX;

    while (1) {
        // Initialiser l'état de jeu
        initGameState(nbS, nbF, nbP, nbO, nbM, coupsMax);

        // Initialisation du plateau
        initialiserPlateau(plateau);
        refreshScreen(plateau);

        // Boucle de jeu (déplacements + permutations)
        deplacerCurseur(plateau);

        // Fin de partie : proposer rejouer / quitter
        gotoligcol(LIGNES + 6, 0);
        Color(BLANC, NOIR);
        printf("Partie terminee. Appuie sur R pour rejouer ou Q pour quitter.\n");

        char c;
        while (1) {
            c = getch();
            if (c == 'r' || c == 'R') {
                break; // on relance la boucle while(1) -> nouvelle partie
            }
            if (c == 'q' || c == 'Q' || c == 27) {
                return 0; // quitter le programme
            }
        }
    }

    return 0;
}
