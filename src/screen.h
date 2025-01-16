#include <stdio.h>
#include <windows.h>
#include <ctype.h>
#include <math.h>
#include <conio.h>
#include "struct.h"
#ifndef SCREEN_H
#define SCREEN_H
void beginscreen(int i, game_info *game);
void modescreen(int i);
int movescreen(int screen, game_info *game, player_info *player);
void savescreen(int i, game_info *game, player_info *player);
void printmap(map_info *info);
#endif