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

    getch();

    cleanArea(0, 40, 6, 20);

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
            Color(ROUGE_CLAIR, NOIR);
            afficherMessage("Defaite ! Appuyez sur une touche pour quitter.");
            getch();
            break;
        }

        if(checkVictory()) {
            Color(VERT_CLAIR, NOIR);
            afficherMessage("Victoire ! Appuyez sur une touche pour quitter.");
            getch();
            break;
        }
        
        if(deplacerCurseur(plateau) == 1) break;
    }

    int totalScore = getScoreTotal();
    char* player_name = (char*)userdata;
    int previousHighscore = getHighscore("highscores.txt", player_name);
    if (totalScore > previousHighscore) {
        update_highscore("highscores.txt", player_name, totalScore);
        afficherMessage("Nouveau record ! Score : %d. Appuyez sur une touche pour quitter.", totalScore);
    } else {
        afficherMessage("Score final : %d. Appuyez sur une touche pour quitter.", totalScore);
    }

    getch();
    
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
    
    printBestScores("highscores.txt", 3);

    getch();

    cleanArea(0, 40, 6, 20);

    return 1;
}

int quit(void* userdata){
    return 0;
}

int main() {

    system("cls");
    Color(BLANC, NOIR);

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
