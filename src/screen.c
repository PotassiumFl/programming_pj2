#include "screen.h"
void beginscreen(int i, game_info *game) // 开始屏幕输出
{
    system("cls");
    printf("小黄的冒险之旅\n\n");

    if (i == 1)
        printf("> ");
    else
        printf("  ");
    printf("开始<平凡之路>");
    if (game->passed_game & 0b001)
        printf("(通关)");
    if (game->last_game == 1)
        printf("(上次)");
    printf("\n");

    if (i == 2)
        printf("> ");
    else
        printf("  ");
    printf("开始<康庄大道>");
    if (game->passed_game & 0b010)
        printf("(通关)");
    if (game->last_game == 2)
        printf("(上次)");
    printf("\n");

    if (i == 3)
        printf("> ");
    else
        printf("  ");
    printf("开始<魔王之旅>");
    if (game->passed_game & 0b100)
        printf("(通关)");
    if (game->last_game == 3)
        printf("(上次)");
    printf("\n");

    if (i == 4)
        printf("> 结束游戏\n");
    else
        printf("  结束游戏\n");
    printf("操作方式：用w向上移动，用s向下移动，用<Enter>确定选择\n");
    return;
}
void modescreen(int i) // 模式选择屏幕输出
{
    system("cls");
    printf("请选择控制模式：\n");

    switch (i)
    {
    case 1:
        printf("> 0：实时模式\n");
        printf("  1：编程模式\n");
        break;
    case 2:
        printf("  0：实时模式\n");
        printf("> 1：编程模式\n");
        break;
    }
    printf("操作方式：用w向上移动，用s向下移动，用<Enter>确定选择\n");
    return;
}
int movescreen(int screen, game_info *game, player_info *player) // 屏幕变化
{
    int screen_num = 1;
    int max_screen_num;
    char input;
    while (1)
    {
        switch (screen)
        {
        case 4:
            max_screen_num = 4;
            beginscreen(screen_num, game);
            break;
        case 2:
            max_screen_num = 2;
            modescreen(screen_num);
            break;
        case 3:
            max_screen_num = 2;
            savescreen(screen_num, game, player);
            break;
        }

        input = toupper(getch());
        switch (input)
        {
        case 'W':
            screen_num = max(1, screen_num - 1);
            break;
        case 'S':
            screen_num = min(screen_num + 1, max_screen_num);
            break;
        case '\r':
            return screen_num;
        }
    }
}
void savescreen(int i, game_info *game, player_info *player) // 开始屏幕输出
{
    system("cls");
    printf("是否加载上次的进度？\n");
    printf("上次游玩时间：%d-%d-%d %d:%02d:%02d\n", game->year, game->month, game->day, game->hour, game->min, game->sec);
    printf("寻得的宝箱数：%d/%d\n", player->treasure_found, player->treasure_num);

    switch (i)
    {
    case 1:
        printf("> 是\n");
        printf("  否\n");
        break;
    case 2:
        printf("  是\n");
        printf("> 否\n");
        break;
    }
    printf("操作方式：用w向上移动，用s向下移动，用<Enter>确定选择\n");
    return;
}
void printmap(map_info *info) // 地图打印
{
    system("cls");
    for (int i = 0; i < info->map_height; i++)
    {
        for (int j = 0; j < info->map_width; j++)
        {
            printf("%c ", info->map_char[i][j]);
        }
        printf("\n");
    }
    return;
}