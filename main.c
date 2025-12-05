#include <windows.h>
#include "affichage.h"
#include "regles.h"
#include "deplacement.h"
#include "groupes.h"
#include "jeu.h"
#include "menu.h"
#include <stdio.h>

void test1(void* userdata){
    int* a = (int*)userdata;
    printf("Valeur de a : %d\n", *a);
}

void test2(void* userdata){
    printf("Test 2\n");
}

void test3(void* userdata){
    printf("Test 3\n");
}

int main() {

    int a = 2;

    Menu mainMenu = create_menu(3);
    menu_add_option(&mainMenu, "Nouvelle Partie", test1, &a);
    menu_add_option(&mainMenu, "Options", test2, NULL);
    menu_add_option(&mainMenu, "Quitter", test3, NULL);

    while (1)
    {
        menu_run(&mainMenu);
    }
    
    






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
        if(isGameOver()) {
            afficherMessage("Défaite ! Appuyez sur une touche pour quitter.");
            getch();
            break;
        }

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
