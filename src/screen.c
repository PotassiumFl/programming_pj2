#include "screen.h"
void beginscreen(int i, game_info *game) // ��ʼ��Ļ���
{
    system("cls");
    printf("С�Ƶ�ð��֮��\n\n");

    if (i == 1)
        printf("> ");
    else
        printf("  ");
    printf("��ʼ<ƽ��֮·>");
    if (game->passed_game & 0b001)
        printf("(ͨ��)");
    if (game->last_game == 1)
        printf("(�ϴ�)");
    printf("\n");

    if (i == 2)
        printf("> ");
    else
        printf("  ");
    printf("��ʼ<��ׯ���>");
    if (game->passed_game & 0b010)
        printf("(ͨ��)");
    if (game->last_game == 2)
        printf("(�ϴ�)");
    printf("\n");

    if (i == 3)
        printf("> ");
    else
        printf("  ");
    printf("��ʼ<ħ��֮��>");
    if (game->passed_game & 0b100)
        printf("(ͨ��)");
    if (game->last_game == 3)
        printf("(�ϴ�)");
    printf("\n");

    if (i == 4)
        printf("> ������Ϸ\n");
    else
        printf("  ������Ϸ\n");
    printf("������ʽ����w�����ƶ�����s�����ƶ�����<Enter>ȷ��ѡ��\n");
    return;
}
void modescreen(int i) // ģʽѡ����Ļ���
{
    system("cls");
    printf("��ѡ�����ģʽ��\n");

    switch (i)
    {
    case 1:
        printf("> 0��ʵʱģʽ\n");
        printf("  1�����ģʽ\n");
        break;
    case 2:
        printf("  0��ʵʱģʽ\n");
        printf("> 1�����ģʽ\n");
        break;
    }
    printf("������ʽ����w�����ƶ�����s�����ƶ�����<Enter>ȷ��ѡ��\n");
    return;
}
int movescreen(int screen, game_info *game, player_info *player) // ��Ļ�仯
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
void savescreen(int i, game_info *game, player_info *player) // ��ʼ��Ļ���
{
    system("cls");
    printf("�Ƿ�����ϴεĽ��ȣ�\n");
    printf("�ϴ�����ʱ�䣺%d-%d-%d %d:%02d:%02d\n", game->year, game->month, game->day, game->hour, game->min, game->sec);
    printf("Ѱ�õı�������%d/%d\n", player->treasure_found, player->treasure_num);

    switch (i)
    {
    case 1:
        printf("> ��\n");
        printf("  ��\n");
        break;
    case 2:
        printf("  ��\n");
        printf("> ��\n");
        break;
    }
    printf("������ʽ����w�����ƶ�����s�����ƶ�����<Enter>ȷ��ѡ��\n");
    return;
}
void printmap(map_info *info) // ��ͼ��ӡ
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