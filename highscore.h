#ifndef HIGHSCORE_H
#define HIGHSCORE_H

typedef struct {
    char name[100];
    int score;
} ScoreEntry;

int getHighscore(const char *filename, const char *player_name);
void printBestScores(const char *filename, int amount);
void update_highscore(const char *filename, const char *player_name, int new_score);

#endif