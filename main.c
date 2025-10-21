#include "affichage.h"

int main() {
    char plateau[LIGNES][COLONNES];

    initialiserPlateau(plateau);

    afficherPlateau(plateau);

    printf("\n\nAppuyez sur une touche pour quitter...");
    
    getchar();
    return 0;
}
