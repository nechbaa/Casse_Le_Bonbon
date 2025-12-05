#include <windows.h>
#include "affichage.h"
#include "regles.h"
#include "deplacement.h"
#include "groupes.h"
#include "jeu.h"
#include <stdio.h>



int main() {

    char plateau[LIGNES][COLONNES];
    int mask[LIGNES][COLONNES] = {0};

    // Paramètres du contrat
    int nbS = 20, nbF = 50, nbP = 20, nbO = 0, nbM = 0, coupsMax = 20;

    // 1) Initialisation + premier affichage complet
    initialiserPlateau(plateau);

    int nbGroupes = TrouverGroupes(plateau,mask);

    while (nbGroupes > 0)
    {
        remplirPlateau(plateau,mask);
        nbGroupes = TrouverGroupes(plateau,mask);
    }
    

    initGameState(nbS,nbF,nbP,nbO,nbM,coupsMax);
    refreshScreen(plateau);
    Sleep(1000);
   

    

    while (1)
    {
        int supprimees = 0;
        /*while(TrouverGroupes(plateau,mask) > 0)
        {
            int a = TrouverGroupes(plateau,mask);
            gotoligcol(LIGNES + 5, 0);
            printf("Groupes trouves : %d\n", a);
            supprimees += Suppression(plateau, mask);
            Gravite(plateau, nbS, nbF, nbP, nbO, nbM, coupsMax);
        }*/
        if(deplacerCurseur(plateau) == 1) break;
    }
    
    gotoligcol(LIGNES + 5, 0);

    return 0;
}
