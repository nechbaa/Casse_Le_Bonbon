#include <windows.h>
#include "affichage.h"
#include "regles.h"
#include "deplacement.h"
#include "groupes.h"
#include "jeu.h"
#include "menu.h"
#include "highscore.h"
#include <stdio.h>

#define NIVEAUX 10

int options(void* userdata){
    //int* a = (int*)userdata;
    //printf("Valeur de a : %d\n", *a);
    printf("\nMenu options\n");

    getch();

    cleanArea(0, 40, 6, 20);

    return 1;
}

// Reparti aleatoirement les points parmis les fruits
void repartitionDesObjectifs(int total, int tranche, int* nbS, int* nbF, int* nbP, int* nbO, int* nbM){
    int blocs = total / tranche;

    for (int i = 0; i < blocs; i++) {
        int r = rand() % 5; 

        switch (r) {
            case 0: *nbS += tranche; break;
            case 1: *nbF += tranche; break;
            case 2: *nbP += tranche; break;
            case 3: *nbO += tranche; break;
            case 4: *nbM += tranche; break;
        }
    }
}



int jouer(void* userdata, int niveau){
    char plateau[LIGNES][COLONNES];
    int mask[LIGNES][COLONNES] = {0};

    

    // Paramètres du contrat
    int totalADistribuer = 80 + (niveau-1) * 20; // augmente avec le niveau
    int tranches = 5;

    int nbS = 0, nbF = 0, nbP = 0, nbO = 0, nbM = 0, coupsMax = 20;

    repartitionDesObjectifs(totalADistribuer, tranches, &nbS, &nbF, &nbP, &nbO, &nbM);

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

    int returnValue = 0;
   
    while (1)
    {
        if(isGameOver()) {
            Color(ROUGE_CLAIR, NOIR);
            afficherMessage("Defaite ! Appuyez sur une touche pour continuer.");

            getch();

            if (perdreVie()) {       
                if(getViesRestante() > 0) returnValue = 1; // rejouer ?
                else returnValue = 2; // game over
            }
            else{
                returnValue = 2; // game over
            }
        
            break;
        }

        if(checkVictory()) {
            returnValue = 4; // partie gagnée
            Color(VERT_CLAIR, NOIR);
            afficherMessage("Victoire ! Appuyez sur une touche pour continuer.");
            getch();
            break;
        }
        
        if(deplacerCurseur(plateau) == 1) { returnValue = 3; break; }
    }

    int totalScore = getScoreTotal();
    char* player_name = (char*)userdata;
    int previousHighscore = getHighscore("highscores.txt", player_name);
    if (totalScore > previousHighscore) {
        updateHighscore("highscores.txt", player_name, totalScore);
        afficherMessage("Nouveau record ! Score : %d. Appuyez sur une touche pour continuer.", totalScore);
    } else {
        afficherMessage("Score final : %d. Appuyez sur une touche pour continuer.", totalScore);
    }

    getch();
    
    return returnValue;
}


int choixNiveauMenu(void *userdata) {
    return (int)(intptr_t)userdata;
}


int choixNiveau(char* player_name){
    int unlockedLevel = getUnlockedLevel("levels.txt", player_name);
    int maxScore = getHighscore("highscores.txt", player_name);

    system("cls");
    Color(BLANC, NOIR);
    gotoligcol(0,0);

    printf("Joueur %s : %d\n\n", player_name, maxScore);
    printf("Selection du niveau\n");

    
    Menu choixMenu = create_menu(NIVEAUX); // nombre de niveaux
    for (int i = 1; i <= NIVEAUX; i++) {
        char label[20];
        snprintf(label, sizeof(label), "Niveau %d %s", (i), (i <= unlockedLevel) ? "" : "(lock)");
        menu_add_option(&choixMenu, label, choixNiveauMenu, (i <= unlockedLevel) ? BLANC : ROUGE_CLAIR, (void*)(intptr_t)i);
    }

    int niveauChoisi = 0;
    
    do{

        niveauChoisi = menu_run(&choixMenu, 0, 3);

    }while (niveauChoisi > unlockedLevel);
    
    Color(BLANC, NOIR);

    return niveauChoisi;

}


int replayOption1(void* userdata){ return 0; }
int replayOption2(void* userdata){ return 99; }

int optionsDeJeu(void* userdata){
    printf("\nEntrez votre nom : ");
    char player_name[100];
    scanf("%99s", player_name);
    Sleep(300);

    // Initialisation des vies
    resetVies();


    Color(BLANC, NOIR);

    int niveau = choixNiveau(player_name);

    Menu replayMenu = create_menu(2);
    menu_add_option(&replayMenu, "Oui !", replayOption1, BLANC, NULL);
    menu_add_option(&replayMenu, "Non...", replayOption2, BLANC, NULL);


    int resultatJeu = 0;

    do{
        resultatJeu = jouer(player_name, niveau);

        switch (resultatJeu)
        {
        case 0: 
            break;
        case 1: // rejouer
            printf("\nIl vous reste %d vies, rejouer ?\n", getViesRestante());
            resultatJeu = menu_run(&replayMenu, 0, LIGNES + 6);
            break;
        case 2: // game over
            break;
        case 3: // quitter
            break;
        case 4: // partie gagnée
            updateUnlockedLevel("levels.txt", player_name, niveau + 1);
            break;
        
        default:
            break;
        }

    }while(resultatJeu == 0);

    system("cls");

    return 1;
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
    menu_add_option(&mainMenu, "Nouvelle Partie", optionsDeJeu, BLANC, NULL);
    menu_add_option(&mainMenu, "Leaderboard", leaderboard, BLANC, NULL);
    menu_add_option(&mainMenu, "Options", options, BLANC, NULL);
    menu_add_option(&mainMenu, "Quitter", quit, BLANC, NULL);

    

    int boucle = 1;

    while (boucle)
    {
        boucle = 0;

        gotoligcol(0,0);
        Color(BLANC, NOIR);
        printf("=== MENU PRINCIPAL ===");

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
