#include "affichage.h"
#include "regles.h"
#include "deplacement.h"
#include "jeu.h"


int main() {
    char plateau[LIGNES][COLONNES];

    int mask[LIGNES][COLONNES] = {0};
    mask[0][0] = 1;
    mask[1][3] = 1;

    // Paramètres du contrat
    int nbS = 20, nbF = 50, nbP = 20, nbO = 0, nbM = 0, coupsMax = 30;

    // Initialisation et affichages
    initialiserPlateau(plateau);
    refreshScreen(plateau, nbS, nbF, nbP, nbO, nbM, coupsMax);


    int n = Suppression(plateau, mask);
    Gravite(plateau);


    gotoligcol(LIGNES + 2, 0);
    Color(BLANC, NOIR);
    printf("Supprimees = %d (attendu 2)\n", n);

 // 4) Réaffichage complet après suppression + gravité
    refreshScreen(plateau, nbS, nbF, nbP, nbO, nbM, coupsMax);


    // Gestion du déplacement uniquement
    deplacerCurseur(plateau);

    gotoligcol(LIGNES + 5, 0);
    printf("\nFin du jeu.\n");
    return 0;
}