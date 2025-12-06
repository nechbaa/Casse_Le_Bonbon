#include <windows.h>
#include "affichage.h"
#include "regles.h"
#include "deplacement.h"
#include "groupes.h"
#include "jeu.h"
#include "menu.h"
#include <stdio.h>

void options(void* userdata){
    //int* a = (int*)userdata;
    //printf("Valeur de a : %d\n", *a);
    printf("Test 1\n");
}

void jouer(void* userdata){
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
        
        if(deplacerCurseur(plateau) == 1) break;
    }
    
}

void quit(void* userdata){
    printf("Test 3\n");
}

int main() {

    system("cls");


    Menu mainMenu = create_menu(3);
    menu_add_option(&mainMenu, "Nouvelle Partie", jouer, NULL);
    menu_add_option(&mainMenu, "Options", options, NULL);
    menu_add_option(&mainMenu, "Quitter", quit, NULL);

    printf("=== MENU PRINCIPAL ===");

    menu_run(&mainMenu, 0, 3);
    
        
    gotoligcol(LIGNES + 5, 0);

    return 0;
}
