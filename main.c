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
    int nbS = 20, nbF = 50, nbP = 20, nbO = 0, nbM = 0, coupsMax = 30;

    // 1) Initialisation + premier affichage complet
    initialiserPlateau(plateau);
    refreshScreen(plateau, nbS, nbF, nbP, nbO, nbM, coupsMax);
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
        if(deplacerCurseur(plateau) == 1) return 0;
    }
    
    return 0;
}
