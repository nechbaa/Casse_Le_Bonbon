#include "affichage.h"
#include <stdarg.h>
#include <time.h>

// --- Fonction pour changer la couleur du texte ---
static inline void Color(int texte, int fond) {
    static HANDLE H = NULL;
    if (!H) H = GetStdHandle(STD_OUTPUT_HANDLE); // évite de rappeler GetStdHandle à chaque fois
    SetConsoleTextAttribute(H, (fond << 4) | texte);
}
// --- Fonction pour déplacer le curseur ---
static inline void gotoligcol(int lig, int col) {
    COORD mycoord = { (SHORT)col, (SHORT)lig };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), mycoord);
}
// --- Initialisation aléatoire du plateau ---
void initialiserPlateau(char plateau[LIGNES][COLONNES]) {
    static const char items[] = {'S', 'F', 'P', 'O', 'M'};
    srand((unsigned)time(NULL));

    for (int i = 0; i < LIGNES; i++) {
        for (int j = 0; j < COLONNES; j++) {
            plateau[i][j] = items[rand() % (sizeof(items)/sizeof(items[0]))];
        }
    }
}

// --- Affichage coloré du plateau ---
void afficherPlateau(char plateau[LIGNES][COLONNES]) {
    system("cls"); // nettoyage console

    // Bordure supérieure
    putchar(0xC9);
    for (int j = 0; j < COLONNES; j++) putchar(0xCD);
    putchar(0xBB);
    putchar('\n');

    // Corps du plateau
    for (int i = 0; i < LIGNES; i++) {
        putchar(0xBA);
        for (int j = 0; j < COLONNES; j++) {
            switch (plateau[i][j]) {
                case 'S': Color(JAUNE, NOIR); break;
                case 'F': Color(ROUGE, NOIR); break;
                case 'P': Color(VERT, NOIR); break;
                case 'O': Color(CYAN, NOIR); break;
                case 'M': Color(MAGENTA, NOIR); break;
                default:  Color(BLANC, NOIR); break;
            }
            putchar(plateau[i][j]);
        }
        Color(BLANC, NOIR);
        putchar(0xBA);
        putchar('\n');
    }

    // Bordure inférieure
    putchar(0xC8);
    for (int j = 0; j < COLONNES; j++) putchar(0xCD);
    putchar(0xBC);
}
// --- Affichage du contrat ---
void afficherContrat(int nbS, int nbF, int nbP, int nbO, int nbM, int coupsMax) {
    Color(BLANC, NOIR);
    gotoligcol(1, COLONNES + 5);
    printf("=== CONTRAT ===");

    const char* labels[] = {
        "Soleils   (S) : %d",
        "Fraises   (F) : %d",
        "Pommes    (P) : %d",
        "Oignons   (O) : %d",
        "Mandarines(M) : %d"
    };
    int values[] = { nbS, nbF, nbP, nbO, nbM };

    for (int i = 0; i < 5; i++) {
        gotoligcol(3 + i, COLONNES + 5);
        printf(labels[i], values[i]);
    }

    // --- Effacer message ---
void effacerMessage(void) {
    gotoligcol(LIGNES + 4, 0);
    printf("%*s", 100, ""); // efface 100 caractères
}
// --- Afficher message ---
void afficherMessage(const char* fmt, ...) {
    effacerMessage();
    gotoligcol(LIGNES + 4, 0);
    va_list ap; va_start(ap, fmt);
    vprintf(fmt, ap);
    va_end(ap);
    Color(BLANC, NOIR);
}
    
    gotoligcol(9, COLONNES + 5);
    printf("Coups max : %d", coupsMax);
    Color(BLANC, NOIR);
}
// --- Rafraîchir écran ---
void refreshScreen(char plateau[LIGNES][COLONNES],
                   int nbS, int nbF, int nbP, int nbO, int nbM, int coupsMax) {
    afficherPlateau(plateau);
    afficherContrat(nbS, nbF, nbP, nbO, nbM, coupsMax);

    gotoligcol(LIGNES + 3, 0);
    Color(BLANC, NOIR);
    puts("Utilise Z Q S D pour te deplacer, ESPACE pour selectionner, ECHAP pour quitter.");
}
