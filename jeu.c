#include "jeu.h"
#include "deplacement.h"
#include "regles.h"
#include "affichage.h"
#include "groupes.h"

static int estSelectionne = 0;
static int tentativeActive = 0;
static int tmpX, tmpY;

// --- Variables internes à la sélection ---
static int selX = -1;
static int selY = -1;


// --- État de jeu global ---
// Objectifs (contrat) _g pour getter 
static int g_objS = 0, g_objF = 0, g_objP = 0, g_objO = 0, g_objM = 0;
static int g_coupsMax = 0;

// Progression (fruits mangés)
static int g_progS = 0, g_progF = 0, g_progP = 0, g_progO = 0, g_progM = 0;

// Coups utilisés
static int g_coupsUtilises = 0;

// Indicateur de fin de partie
static int g_gameOver = 0;

// Vies restantes
static int g_viesRestantes;
static int g_viesTotales = 3;


// =====================
// Getters état de jeu
// =====================

void initGameState(int nbS, int nbF, int nbP, int nbO, int nbM, int coupsMax) {
    g_objS = nbS;  g_objF = nbF;  g_objP = nbP;  g_objO = nbO;  g_objM = nbM;
    g_coupsMax = coupsMax;

    g_progS = g_progF = g_progP = g_progO = g_progM = 0;
    g_coupsUtilises = 0;
    g_gameOver = 0;
}

int getContratS(void) { return g_objS; }
int getContratF(void) { return g_objF; }
int getContratP(void) { return g_objP; }
int getContratO(void) { return g_objO; }
int getContratM(void) { return g_objM; }
int getCoupsMax(void) { return g_coupsMax; }

int getProgS(void) { return g_progS; }
int getProgF(void) { return g_progF; }
int getProgP(void) { return g_progP; }
int getProgO(void) { return g_progO; }
int getProgM(void) { return g_progM; }
int getCoupsUtilises(void) { return g_coupsUtilises; }

int isGameOver(void) { return g_gameOver; }

int getVies(void) { return g_viesTotales; }
int getViesRestante(void) { return g_viesRestantes; }

int getScoreTotal(void) {
    // somme des fruits mangés
    return g_progS + g_progF + g_progP + g_progO + g_progM;
}


// --- Fonctions d’accès à l’état de sélection ---
int getSelectionEtat() {
    return estSelectionne;
}

int getSelectionX() {
    return selX;
}

int getSelectionY() {
    return selY;
}

void resetVies() {
    g_viesRestantes = g_viesTotales;
}

int perdreVie() {
    if (g_viesRestantes > 0) {
        g_viesRestantes--;
        return 1; // Vie perdue
    }
    return 0; // Pas de vie perdu
}

void resetSelection() {
    estSelectionne = 0;
    tentativeActive = 0;
    selX = selY = tmpX = tmpY = -1;
}

// =============================
// Fonction interne : appliquer un coup
// compte les coups et fait respecter les regles du jeu
// =============================

static void appliquerCoupApresPermutation(char plateau[LIGNES][COLONNES]) {
    int mask[LIGNES][COLONNES] = {0};
    int nbCases = 0;

    // On compte le coup même si aucun groupe n'est formé
    g_coupsUtilises++;

    do{
        memset(mask, 0, sizeof(mask));
        nbCases = TrouverGroupes(plateau, mask);

        if (nbCases > 0) {
            int nbS = 0, nbF = 0, nbP = 0, nbO = 0, nbM = 0;

            // Compter combien de S/F/P/O/M vont être mangés
            CompterFruitsSupprimes(plateau, mask, &nbS, &nbF, &nbP, &nbO, &nbM);

            g_progS += nbS;
            g_progF += nbF;
            g_progP += nbP;
            g_progO += nbO;
            g_progM += nbM;

            // Supprimer et appliquer la gravité (avec animation + refresh)
            Suppression(plateau, mask);
            Gravite(plateau);
        } 
        else {
            // Aucun groupe formé
            afficherMessage("Aucun groupe forme.");
            refreshScreen(plateau);  // pour mettre à jour coups utilisés
        }

    }while(nbCases > 0);

    

    // Vérification fin de partie (défaite simple : plus de coups)
    if (g_coupsUtilises >= g_coupsMax) {
        g_gameOver = 1;
        afficherMessage("DEFAITE : tu as utilise tous tes coups !");
    }
}

void gererSelection(char plateau[LIGNES][COLONNES], int x, int y) {
    // Aucun fruit sélectionné -> on sélectionne la case courante
    if (!estSelectionne) {
        estSelectionne = 1;
        selX = x; selY = y;
        afficherSelection(plateau, selX, selY, 1); // minuscule
        gotoligcol(LIGNES + 4, 0);
        Color(JAUNE, NOIR); printf("Fruit selectionne (%d,%d).", selX, selY); Color(BLANC, NOIR);
        return;
    }

    // Un fruit est sélectionné
    if (tentativeActive) {
        // ESPACE = valider la permutation temporaire
        // -> remettre les deux cases en “non sélectionné” (maj), vider les états
        afficherSelection(plateau, selX, selY, 0);   // majuscule
        afficherSelection(plateau, tmpX, tmpY, 0);   // majuscule


        estSelectionne = 0;
        tentativeActive = 0;
        selX = selY = tmpX = tmpY = -1;

        gotoligcol(LIGNES + 4, 0);
        Color(VERT, NOIR); afficherMessage("Permutation validee."); Color(BLANC, NOIR);

        appliquerCoupApresPermutation(plateau);

        return;
    }

    // Pas de tentative, on a rappuyé ESPACE sur la même case -> désélection simple
    if (x == selX && y == selY) {
        afficherSelection(plateau, selX, selY, 0);   // majuscule
        estSelectionne = 0;
        selX = selY = -1;

        gotoligcol(LIGNES + 4, 0);
        Color(BLANC, NOIR); afficherMessage("Deselection."); 
        return;
    }

    // Sinon (sélection active mais pas de tentative et autre case) : on ne fait rien ici.
    // C’est le déplacement (ZQSD/flèches) qui déclenchera la tentative sur voisin.
}


void gererDeplacementAvecSelection(char plateau[LIGNES][COLONNES],int oldX, int oldY, int newX, int newY) {
    if (!estSelectionne) return;

    int distance = abs(newX - selX) + abs(newY - selY);

    // Aucune tentative en cours : on autorise uniquement le déplacement SUR un voisin de (selX,selY)
    if (!tentativeActive) {
        if (distance == 1) {
            // Lancer la permutation temporaire (sel <-> voisin)
            permuterItems(plateau, selX, selY, newX, newY);

            // Visuel : la case d'origine RESTE la sélection (minuscule),
            //          le voisin doit être en non-sélection (majuscule).
            afficherSelection(plateau, selX, selY, 1);   // minuscule à l'origine (quel que soit le symbole après swap)
            afficherSelection(plateau, newX, newY, 0);   // majuscule sur le voisin

            tmpX = newX; tmpY = newY;
            tentativeActive = 1;

            gotoligcol(LIGNES + 4, 0);
            Color(JAUNE, NOIR); afficherMessage("Permutation temporaire (%d,%d). Valide avec ESPACE ou reviens a l'origine.", newX, newY);
            Color(BLANC, NOIR);
        
        }
        return;
    }

    // Tentative en cours
    // 1) Revenir exactement sur la case d’origine -> annuler la permutation temporaire
    if (distance == 0) {
        // annuler le swap
        permuterItems(plateau, selX, selY, tmpX, tmpY);

        // visuel : origine reste sélection (minuscule), voisin redevient non-sélection
        afficherSelection(plateau, selX, selY, 1);
        afficherSelection(plateau, tmpX, tmpY, 0);

        tentativeActive = 0;
        tmpX = tmpY = -1;

        gotoligcol(LIGNES + 4, 0);
        Color(BLEU, NOIR); afficherMessage("Permutation annulee. Tu peux tenter un autre voisin.");
        Color(BLANC, NOIR);
        return;
    }

}


int checkVictory(void) {
    if (getProgS() >= getContratS() &&
        getProgF() >= getContratF() &&
        getProgP() >= getContratP() &&
        getProgO() >= getContratO() &&
        getProgM() >= getContratM()) {
            return 1;
    }
    return 0;
}



// --- Fonction de permutation de deux fruits ---
int permuterItems(char plateau[LIGNES][COLONNES], int x1, int y1, int x2, int y2) {
    

    // Échange les deux fruits
    char temp = plateau[y1][x1];
    plateau[y1][x1] = plateau[y2][x2];
    plateau[y2][x2] = temp;

    // Réaffiche uniquement les deux cases échangées
    gotoligcol(y1 + 1, x1 + 1);
    switch (plateau[y1][x1]) {
        case 'S': Color(JAUNE, NOIR); break;
        case 'F': Color(ROUGE, NOIR); break;
        case 'P': Color(VERT, NOIR); break;
        case 'O': Color(CYAN, NOIR); break;
        case 'M': Color(MAGENTA, NOIR); break;
        case 'B': Color(ROSE, NOIR); break;
        default: Color(BLANC, NOIR); break;
    }
    printf("%c", plateau[y1][x1]);

    gotoligcol(y2 + 1, x2 + 1);
    switch (plateau[y2][x2]) {
        case 'S': Color(JAUNE, NOIR); break;
        case 'F': Color(ROUGE, NOIR); break;
        case 'P': Color(VERT, NOIR); break;
        case 'O': Color(CYAN, NOIR); break;
        case 'M': Color(MAGENTA, NOIR); break;
        case 'B': Color(ROSE, NOIR); break;
        default: Color(BLANC, NOIR); break;
    }
    printf("%c", plateau[y2][x2]);

    Color(BLANC, NOIR);
    gotoligcol(LIGNES + 3, 0);

    return 1; // succès
}
