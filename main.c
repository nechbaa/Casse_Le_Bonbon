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
    int nbS = 20, nbF = 50, nbP = 20, nbO = 0, nbM = 0, coupsMax = 20;

    // 1) Initialisation + premier affichage complet
    initialiserPlateau(plateau);
    refreshScreen(plateau);
    Sleep(1000);
   

    

    while (1)
    {
        int supprimees = Suppression(plateau, mask);
        Gravite(plateau);
        //TrouverGroupesSimples(plateau,mask);
        refreshScreen(plateau);
        deplacerCurseur(plateau);
    }
    
    return 0;
}
