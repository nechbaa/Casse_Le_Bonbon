#include <windows.h>
#include "affichage.h"
#include "regles.h"
#include "deplacement.h"
#include "groupes.h"
#include "jeu.h"
#include "menu.h"
#include "highscore.h"
#include <stdio.h>

int options(void* userdata){
    //int* a = (int*)userdata;
    //printf("Valeur de a : %d\n", *a);
    printf("Test 1\n");
    return 1;
}



int jouer(void* userdata){
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
            afficherMessage("Defaite ! Appuyez sur une touche pour quitter.");
            getch();
            break;
        }

        int supprimees = 0;
        
        if(deplacerCurseur(plateau) == 1) break;
    }
    
    return 0;
}

int optionsDeJeu(void* userdata){
    printf("\nEntrez votre nom : ");
    char player_name[100];
    scanf("%99s", player_name);
    Sleep(300);

    return jouer(player_name);
}

int leaderboard(void* userdata){
    
    printAllScores("highscores.txt");

    getch();

    return 1;
}

int quit(void* userdata){
    return 0;
}

int main() {

    system("cls");


    Menu mainMenu = create_menu(4);
    menu_add_option(&mainMenu, "Nouvelle Partie", optionsDeJeu, NULL);
    menu_add_option(&mainMenu, "Leaderboard", leaderboard, NULL);
    menu_add_option(&mainMenu, "Options", options, NULL);
    menu_add_option(&mainMenu, "Quitter", quit, NULL);

    printf("=== MENU PRINCIPAL ===");

    int boucle = 1;

    while (boucle)
    {
        boucle = 0;

        int result = menu_run(&mainMenu, 0, 2);
        switch (result)
        {
        case 1:
            boucle = 1;
            break;
        
        default:
            break;
        }
    }
        
    gotoligcol(LIGNES + 5, 0);

    return 0;
}
