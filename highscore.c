#include <stdio.h>
#include <string.h>
#include "highscore.h"

int getHighscore(const char *filename, const char *player_name) {
    FILE *file = fopen(filename, "r");
    if (!file) return -1;  

    char name[100];
    int score;

    while (fscanf(file, "%99s %d", name, &score) == 2) {
        if (strcmp(name, player_name) == 0) {
            fclose(file);
            return score; 
        }
    }

    fclose(file);
    return -1; // Joueur introuvable
}

void printAllScores(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("\nAucun score pour le moment\n");
        return;
    }

    char name[100];
    int score;

    printf("\n=== Classement des Scores ===\n");
    while (fscanf(file, "%99s %d", name, &score) == 2) {
        printf("%s : %d\n", name, score);
    }

    fclose(file);
}

void update_highscore(const char *filename, const char *player_name, int new_score) {
    FILE *file = fopen(filename, "r");
    FILE *temp = fopen("temp.txt", "w");

    int found = 0;
    char name[100];
    int score;

    if (file) {
        while (fscanf(file, "%99s %d", name, &score) == 2) {
            if (strcmp(name, player_name) == 0) {
                found = 1;
                if (new_score > score) score = new_score; // mise à jour
            }
            fprintf(temp, "%s %d\n", name, score);
        }

        fclose(file);
    }

    // Si le joueur n'existait pas -> ajout
    if (!found) {
        fprintf(temp, "%s %d\n", player_name, new_score);
    }

    fclose(temp);

    // Remplacement du fichier original
    remove(filename);
    rename("temp.txt", filename);
}