#ifndef HIGHSCORE_H
#define HIGHSCORE_H

int getHighscore(const char *filename, const char *player_name);
void update_highscore(const char *filename, const char *player_name, int new_score);

#endif