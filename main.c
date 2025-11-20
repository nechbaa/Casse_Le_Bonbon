#include <windows.h>
#include "affichage.h"
#include "regles.h"
#include "deplacement.h"
#include "jeu.h"
#include <stdio.h>



int main() {
    char plateau[LIGNES][COLONNES];
    int mask[LIGNES][COLONNES] = {0};

    // Paramètres du contrat
    int nbS = 20, nbF = 50, nbP = 20, nbO = 0, nbM = 0, coupsMax = 30;

    // 1) Initialisation + premier affichage complet
    initialiserPlateau(plateau);
    refreshScreen(plateau, nbS, nbF, nbP, nbO, nbM, coupsMax);
    Sleep(1000);
    // 2) DEBUG : test de TrouverGroupesSimples sur le plateau initial
    int points = TrouverGroupesSimples(plateau, mask);

    gotoligcol(LIGNES + 2, 0);
    Color(BLANC, NOIR);
    printf("Debug - Points detectes au depart : %d   ", points);
    Sleep(3000);

    // 3) Si des groupes existent, on les supprime et on applique la gravite
    if (points > 0) {
        Sleep(2000);
        int supprimees = Suppression(plateau, mask);

        Gravite(plateau, nbS, nbF, nbP, nbO, nbM, coupsMax);

        // On réaffiche le plateau + contrat après la gravité
        refreshScreen(plateau, nbS, nbF, nbP, nbO, nbM, coupsMax);

        gotoligcol(LIGNES + 2, 0);
        Color(BLANC, NOIR);
        printf("Debug - Points detectes au depart : %d (cases supprimees : %d)   ",
               points, supprimees);
    }
    // 5) Gestion du deplacement (jeu normal)
    deplacerCurseur(plateau);

    return 0;
}
