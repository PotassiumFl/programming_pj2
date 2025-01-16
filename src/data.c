#include "data.h"
void initialization(int i, node *head) // ��ʼ��
{
    // ��ʼ����ͼ
    mapimport(i, head);

    // ��ͼ�ַ���
    for (int i = 0; i < head->map.map_height; i++)
    {
        for (int j = 0; j < head->map.map_width; j++)
        {
            switch (head->map.map_num[i][j])
            {
            case 0:
                head->map.map_char[i][j] = ' ';
                break;
            case 1:
                head->map.map_char[i][j] = 'W';
                break;
            case 2:
                head->map.map_char[i][j] = 'D';
                break;
            case 3:
                head->map.map_char[i][j] = 'T';
                head->player.treasure_num += 1;
                break;
            }
        }
    }
    // ��ʼ�����λ��
    head->map.map_char[head->player.x][head->player.y] = 'Y';
    system("cls");
    return;
}
void iftreasure(node *last) // �����ж�
{
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (i * j != 0) // ���������������ж�
                continue;
            if (last->map.map_char[last->player.x + i][last->player.y + j] == 'T') // �ַ��Ե�ͼT�滻Ϊ�ո�
            {
                last->map.map_char[last->player.x + i][last->player.y + j] = ' ';
                treasurechange(last);
            }
        }
    }
    if (last->player.treasure_found == last->player.treasure_num) // ����ȫ����ȡ
        last->player.can_exit = 1;
    return;
}
void manualcal(node *last) // ��������
{
    if (last->move.input == 'I') // ԭ�ز���������������
        return;
    if (last->map.map_num[last->player.x][last->player.y] == 2) // �����ж�
        last->player.manual++;
    else
        last->player.manual = 1;
    last->player.manual_spend += last->player.manual; // ��������
    return;
}
void mapimport(int i, node *head) // ��ͼ����
{
    FILE *mapfile;
    // �򿪵�ͼ�ļ�
    switch (i)
    {
    case 1:
        mapfile = fopen("..\\src\\ƽ��֮·.map", "a+");
        break;
    case 2:
        mapfile = fopen("..\\src\\��ׯ���.map", "a+");
        break;
    case 3:
        mapfile = fopen("..\\src\\ħ��֮��.map", "a+");
        break;
    }
    // ��������
    fscanf(mapfile, "%d %d", &head->map.map_width, &head->map.map_height);
    fscanf(mapfile, "%d %d", &head->player.y, &head->player.x);
    for (int j = 0; j < head->map.map_height; j++)
        for (int k = 0; k < head->map.map_width; k++)
            fscanf(mapfile, "%d", &head->map.map_num[j][k]);
    // �ر��ļ�
    fclose(mapfile);
    return;
}
void mapupdate(node *last) // ��ͼ����
{
    if (last->move.column_move != 0 || last->move.row_move != 0)
    {
        last->map.map_char[last->player.x][last->player.y] = (last->map.map_num[last->player.x][last->player.y] == 2) ? 'D' : ' ';
        // ����ƶ�
        last->player.x += last->move.row_move;
        last->player.y += last->move.column_move;
        last->map.map_char[last->player.x][last->player.y] = 'Y';
    }
    return;
}
void movement(node **last) // �ƶ�����
{
    switch ((*last)->move.input)
    {
    case 'Q':
        (*last)->player.can_exit = 1;
        break;
    case 'W':
        movenode(last);
        switch ((*last)->map.map_char[(*last)->player.x - 1][(*last)->player.y])
        {
        case 'W':
            (*last)->move.moveline = '\0';
            break;
        default:
            (*last)->move.row_move = -1;
            (*last)->move.moveline = 'U';
            break;
        }
        break;
    case 'A':
        movenode(last);
        switch ((*last)->map.map_char[(*last)->player.x][(*last)->player.y - 1])
        {
        case 'W':
            (*last)->move.moveline = '\0';
            break;
        default:
            (*last)->move.column_move = -1;
            (*last)->move.moveline = 'L';
            break;
        }
        break;
    case 'S':
        movenode(last);
        switch ((*last)->map.map_char[(*last)->player.x + 1][(*last)->player.y])
        {
        case 'W':
            (*last)->move.moveline = '\0';
            break;
        default:
            (*last)->move.row_move = +1;
            (*last)->move.moveline = 'D';
            break;
        }
        break;
    case 'D':
        movenode(last);
        switch ((*last)->map.map_char[(*last)->player.x][(*last)->player.y + 1])
        {
        case 'W':
            (*last)->move.moveline = '\0';
            break;
        default:
            (*last)->move.column_move = +1;
            (*last)->move.moveline = 'R';
            break;
        }
        break;
    case 'I':
        movenode(last);
        (*last)->move.moveline = 'I';
        break;
    case 'Y':
        switch ((int)(*last)->next)
        {
        case 0:
            (*last)->move.ifcorrect = 0;
            return;
        default:
            (*last) = (*last)->next;
            (*last)->move.ifcorrect = 2;
            return;
        }
        break;
    case 'Z':
        switch ((int)(*last)->prev)
        {
        case 0:
            (*last)->move.ifcorrect = 0;
            return;
        default:
            (*last) = (*last)->prev;
            (*last)->move.ifcorrect = 2;
            return;
        }
        break;
    default:
        (*last)->move.ifcorrect = 0;
        return;
    }
    if ((*last)->player.can_exit == 0)
    {
        manualcal((*last));
        mapupdate((*last));
        iftreasure((*last));
    }
    return;
}
void treasurechange(node *last) // ���ؼ���
{
    last->player.treasure_found += 1;
    return;
}