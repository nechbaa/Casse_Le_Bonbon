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

void printBestScores(const char *filename, int amount) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("\nAucun score disponible.\n");
        return;
    }

    ScoreEntry scores[100];
    int count = 0;

    while (fscanf(file, "%99s %d", scores[count].name, &scores[count].score) == 2) {
        count++;
    }
    fclose(file);

    // Tri des scores
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (scores[j].score > scores[i].score) {
                ScoreEntry temp = scores[i];
                scores[i] = scores[j];
                scores[j] = temp;
            }
        }
    }

    printf("\n=== Meilleurs Scores ===\n");
    for (int i = 0; i < count && i < amount; i++) {
        printf("%d. %s : %d\n", i + 1, scores[i].name, scores[i].score);
    }
}


void updateHighscore(const char *filename, const char *player_name, int new_score) {
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


int getUnlockedLevel(const char *filename, const char *player_name) {
    FILE *file = fopen(filename, "r");
    if (!file) return 1;  // Aucun fichier -> niveau 1 

    char name[100];
    int level;

    while (fscanf(file, "%99s %d", name, &level) == 2) {
        if (strcmp(name, player_name) == 0) {
            fclose(file);
            return level;
        }
    }

    fclose(file);
    return 1; // Joueur inconnu -> niveau 1
}


void updateUnlockedLevel(const char *filename, const char *player_name, int new_level) {

    // Assure que le fichier existe
    FILE *test = fopen(filename, "a");
    if (!test) {
        printf("Erreur : impossible de créer %s\n", filename);
        return;
    }
    fclose(test);

    FILE *file = fopen(filename, "r");
    FILE *temp = fopen("temp.txt", "w");

    char name[100];
    int level;
    int found = 0;

    if (file) {
        while (fscanf(file, "%99s %d", name, &level) == 2) {
            if (strcmp(name, player_name) == 0) {
                found = 1;
                if (new_level > level)
                    level = new_level; // On met à jour
            }
            fprintf(temp, "%s %d\n", name, level);
        }
        fclose(file);
    }

    // Si nouveau joueur -> ajout
    if (!found) {
        fprintf(temp, "%s %d\n", player_name, new_level);
    }

    fclose(temp);

    remove(filename);
    rename("temp.txt", filename);
}
