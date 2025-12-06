#include "affichage.h"
#include "jeu.h"
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
    srand(time(NULL));

    int newMask[LIGNES][COLONNES] = {0};

    for (int i = 0; i < LIGNES; i++) {
        for (int j = 0; j < COLONNES; j++) {
            newMask[i][j] = 1;
        }
    }

    remplirPlateau(plateau, newMask);
}

// --- Remplissage du tableau avec le mask ---
void remplirPlateau(char plateau[LIGNES][COLONNES], int mask[LIGNES][COLONNES]) {
    char items[] = {'S', 'F', 'P', 'O', 'M'};

    for (int i = 0; i < LIGNES; i++) {
        for (int j = 0; j < COLONNES; j++) {
            if(mask[i][j] == 1)
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
    for (int j = 0; j < COLONNES; j++) printf("%c",0xCD);
    char bord_br = 0xBC;
    printf("%c",bord_br);
}

// --- Affiche la progression par fruit + coups utilisés ---
void afficherProgression(void) {
    int pS = getProgS();
    int pF = getProgF();
    int pP = getProgP();
    int pO = getProgO();
    int pM = getProgM();
    int coups = getCoupsUtilises();

    Color(BLANC, NOIR);
    gotoligcol(1, COLONNES + 5);
    printf("=== PROGRESSION ===");

    gotoligcol(3, COLONNES + 5); Color((pS < getContratS() ? BLANC : VERT), NOIR); printf("Soleils   (S) : %d", pS);
    gotoligcol(4, COLONNES + 5); Color((pF < getContratF() ? BLANC : VERT), NOIR); printf("Fraises   (F) : %d", pF);
    gotoligcol(5, COLONNES + 5); Color((pP < getContratP() ? BLANC : VERT), NOIR); printf("Pommes    (P) : %d", pP);
    gotoligcol(6, COLONNES + 5); Color((pO < getContratO() ? BLANC : VERT), NOIR); printf("Oignons   (O) : %d", pO);
    gotoligcol(7, COLONNES + 5); Color((pM < getContratM() ? BLANC : VERT), NOIR); printf("Mandarines(M) : %d", pM);
    gotoligcol(9, COLONNES + 5); Color(BLANC, NOIR); printf("Coups joues : %d", coups);

    Color(BLANC, NOIR);
}

// --- Affiche le contrat (objectifs) ---
void afficherContrat(void) {
    int nbS = getContratS();
    int nbF = getContratF();
    int nbP = getContratP();
    int nbO = getContratO();
    int nbM = getContratM();
    int coupsMax = getCoupsMax();

    Color(BLANC, NOIR);
    gotoligcol(1, COLONNES + 28);
    printf("=== CONTRAT ===");

    gotoligcol(3, COLONNES + 28); printf("Soleils   (S) : %d", nbS);
    gotoligcol(4, COLONNES + 28); printf("Fraises   (F) : %d", nbF);
    gotoligcol(5, COLONNES + 28); printf("Pommes    (P) : %d", nbP);
    gotoligcol(6, COLONNES + 28); printf("Oignons   (O) : %d", nbO);
    gotoligcol(7, COLONNES + 28); printf("Mandarines(M) : %d", nbM);
    gotoligcol(9, COLONNES + 28); printf("Coups max : %d", coupsMax);

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


void afficherVies() {
    
    gotoligcol(11, COLONNES + 5);

    int vies = getViesRestante();
    int viesTotal = getVies();
    
    for (int i = 0; i < viesTotal; i++)
    {
        Color(i < vies ? ROUGE_CLAIR : GRIS_FONCE, NOIR);
        printf("<3 ");
    }
    Color(BLANC, NOIR);
}


// --- Fonction utilitaire : rafraîchir entièrement l'écran ---
void refreshScreen(char plateau[LIGNES][COLONNES])
{
    afficherPlateau(plateau);
    afficherProgression();
    afficherContrat();
    afficherVies();

    gotoligcol(LIGNES + 3, 0);
    Color(BLANC, NOIR);
    printf("Utilise Z Q S D pour te deplacer, ESPACE pour selectionner, ECHAP pour quitter.\n");
}

void cleanArea(int x1, int x2, int y1, int y2) {
    for (int i = y1; i <= y2; i++) {
        gotoligcol(i, x1);
        for (int j = x1; j <= x2; j++) {
            printf(" ");
        }
    }
}