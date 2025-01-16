#include <stdio.h>
#include <time.h>
#include "struct.h"
#ifndef SAVE_H
#define SAVE_H
void savefile(node *last, game_info *game);
void saveimport(node *head, game_info *game);
void timesave(FILE *file);
#endif