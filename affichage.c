#include "affichage.h"
#include <stdarg.h>

// --- Fonction pour changer la couleur du texte ---
void Color(int texte, int fond) {
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, fond * 16 + texte);
}

// --- Fonction pour déplacer le curseur ---
void gotoligcol(int lig, int col) {
    COORD mycoord;
    mycoord.X = col;
    mycoord.Y = lig;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), mycoord);
}

// --- Initialisation aléatoire du plateau ---
void initialiserPlateau(char plateau[LIGNES][COLONNES]) {
    char items[] = {'S', 'F', 'P', 'O', 'M'};
    srand(time(NULL));

    for (int i = 0; i < LIGNES; i++) {
        for (int j = 0; j < COLONNES; j++) {
            plateau[i][j] = items[rand() % 5];
        }
    }
}

// --- Affichage coloré du plateau ---
void afficherPlateau(char plateau[LIGNES][COLONNES]) {
    system("cls"); // nettoie la console

    // Bordure supérieure
    char bord_tl = 0xC9;
    printf("%c",bord_tl);
    for (int j = 0; j < COLONNES; j++) printf("%c",0xCD);
    char bord_tr = 0xBB;
    printf("%c\n",bord_tr);

    // Corps du plateau
    for (int i = 0; i < LIGNES; i++) {
        printf("%c",0xBA);
        for (int j = 0; j < COLONNES; j++) {
            switch (plateau[i][j]) {
                case 'S': Color(JAUNE, NOIR); break;    // Soleil
                case 'F': Color(ROUGE, NOIR); break;    // Fraise
                case 'P': Color(VERT, NOIR); break;     // Pomme
                case 'O': Color(CYAN, NOIR); break;     // Oignon
                case 'M': Color(MAGENTA, NOIR); break;  // Mandarine
                default: Color(BLANC, NOIR); break;
            }
            printf("%c", plateau[i][j]);
        }
        Color(BLANC, NOIR);
        printf("%c\n",0xBA);
    }

    // Bordure inférieure
    char bord_bl = 0xC8;
    printf("%c",bord_bl);
    for (int j = 0; j < COLONNES; j++)printf("%c",0xCD);
    char bord_br = 0xBC;
    printf("%c",bord_br);
}


void afficherContrat(int nbS, int nbF, int nbP, int nbO, int nbM, int coupsMax) {
    Color(BLANC, NOIR);
    gotoligcol(1, COLONNES + 5);
    printf("=== CONTRAT ===");

    gotoligcol(3, COLONNES + 5); printf("Soleils   (S) : %d", nbS);
    gotoligcol(4, COLONNES + 5); printf("Fraises   (F) : %d", nbF);
    gotoligcol(5, COLONNES + 5); printf("Pommes    (P) : %d", nbP);
    gotoligcol(6, COLONNES + 5); printf("Oignons   (O) : %d", nbO);
    gotoligcol(7, COLONNES + 5); printf("Mandarines(M) : %d", nbM);
    gotoligcol(9, COLONNES + 5); printf("Coups max : %d", coupsMax);

    Color(BLANC, NOIR);
}



void effacerMessage(void) {
    gotoligcol(LIGNES + 4, 0);
    // efface large (adapte si besoin)
    printf("                                                                                                    ");
}

void afficherMessage(const char* fmt, ...) {
    effacerMessage();
    gotoligcol(LIGNES + 4, 0);
    va_list ap; va_start(ap, fmt);
    vprintf(fmt, ap);
    va_end(ap);
    Color(BLANC, NOIR);
}


// --- Fonction utilitaire : rafraîchir entièrement l'écran ---
void refreshScreen(char plateau[LIGNES][COLONNES],int nbS, int nbF, int nbP, int nbO, int nbM, int coupsMax)
{
    // affiche le plateau (fait déjà un cls)
    afficherPlateau(plateau);

    // affiche le contrat à droite
    afficherContrat(nbS, nbF, nbP, nbO, nbM, coupsMax);

    // message d'instructions sous le plateau
    gotoligcol(LIGNES + 3, 0);
    Color(BLANC, NOIR);
    printf("Utilise Z Q S D pour te deplacer, ESPACE pour selectionner, ECHAP pour quitter.\n");
}
