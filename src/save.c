#include "save.h"
void savefile(node *last, game_info *game)
{
    FILE *save;
    save = fopen("..\\build\\save.txt", "w+");
    fprintf(save, "%d %d\n", last->map.map_width, last->map.map_height);
    fprintf(save, "%d %d\n", last->player.x, last->player.y);
    for (int i = 0; i < last->map.map_height; i++)
    {
        for (int j = 0; j < last->map.map_width; j++)
        {
            fprintf(save, "%d", last->map.map_num[i][j]);
            if (j != last->map.map_width - 1)
                fprintf(save, "%c", ' ');
        }
        fprintf(save, "\n");
    }
    fprintf(save, "%d %d\n", last->player.manual, last->player.manual_spend);
    fprintf(save, "%d %d\n", last->player.treasure_found, last->player.treasure_num);
    fprintf(save, "%d %d %d\n", game->mode, game->last_game, game->passed_game);
    for (int i = 0; i < last->map.map_height; i++)
    {
        for (int j = 0; j < last->map.map_width; j++)
        {
            fprintf(save, "%c", last->map.map_char[i][j]);
        }
        fprintf(save, "\n");
    }
    timesave(save);
    fclose(save);
    return;
}
void saveimport(node *head, game_info *game)
{
    FILE *save;
    char buffer;
    save = fopen("..\\build\\save.txt", "a+");
    fscanf(save, "%d %d", &head->map.map_width, &head->map.map_height);
    fscanf(save, "%d %d", &head->player.x, &head->player.y);
    for (int j = 0; j < head->map.map_height; j++)
        for (int k = 0; k < head->map.map_width; k++)
            fscanf(save, "%d", &head->map.map_num[j][k]);
    fscanf(save, "%d %d", &head->player.manual, &head->player.manual_spend);
    fscanf(save, "%d %d", &head->player.treasure_found, &head->player.treasure_num);
    fscanf(save, "%d %d %d", &game->mode, &game->last_game, &game->passed_game);
    for (int i = 0; i < head->map.map_height; i++)
        for (int j = 0; j < head->map.map_width; j++)
            while (1)
            {
                fscanf(save, "%c", &buffer);
                if (buffer != '\n')
                {
                    head->map.map_char[i][j] = buffer;
                    break;
                }
            }
    fscanf(save, "%d %d %d %d %d %d", &game->year, &game->month, &game->day, &game->hour, &game->min, &game->sec);
    fclose(save);
    return;
}
void timesave(FILE *file)
{
    time_t present;
    present = time(NULL);
    struct tm *ptm = localtime(&present);
    int year = ptm->tm_year + 1900;
    int month = ptm->tm_mon + 1;
    int day = ptm->tm_mday;
    int hour = ptm->tm_hour;
    int min = ptm->tm_min;
    int second = ptm->tm_sec;
    fprintf(file, "%d %d %d %d %d %d", year, month, day, hour, min, second);
    return;
}