#include "data.h"
void initialization(int i, node *head) // 初始化
{
    // 初始化地图
    mapimport(i, head);

    // 地图字符化
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
    // 初始化玩家位置
    head->map.map_char[head->player.x][head->player.y] = 'Y';
    system("cls");
    return;
}
void iftreasure(node *last) // 宝藏判断
{
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (i * j != 0) // 非上下左右跳过判断
                continue;
            if (last->map.map_char[last->player.x + i][last->player.y + j] == 'T') // 字符性地图T替换为空格
            {
                last->map.map_char[last->player.x + i][last->player.y + j] = ' ';
                treasurechange(last);
            }
        }
    }
    if (last->player.treasure_found == last->player.treasure_num) // 宝藏全部获取
        last->player.can_exit = 1;
    return;
}
void manualcal(node *last) // 体力计算
{
    if (last->move.input == 'I') // 原地不动跳过体力计算
        return;
    if (last->map.map_num[last->player.x][last->player.y] == 2) // 陷阱判断
        last->player.manual++;
    else
        last->player.manual = 1;
    last->player.manual_spend += last->player.manual; // 体力计算
    return;
}
void mapimport(int i, node *head) // 地图导入
{
    FILE *mapfile;
    // 打开地图文件
    switch (i)
    {
    case 1:
        mapfile = fopen("..\\src\\平凡之路.map", "a+");
        break;
    case 2:
        mapfile = fopen("..\\src\\康庄大道.map", "a+");
        break;
    case 3:
        mapfile = fopen("..\\src\\魔王之旅.map", "a+");
        break;
    }
    // 输入数据
    fscanf(mapfile, "%d %d", &head->map.map_width, &head->map.map_height);
    fscanf(mapfile, "%d %d", &head->player.y, &head->player.x);
    for (int j = 0; j < head->map.map_height; j++)
        for (int k = 0; k < head->map.map_width; k++)
            fscanf(mapfile, "%d", &head->map.map_num[j][k]);
    // 关闭文件
    fclose(mapfile);
    return;
}
void mapupdate(node *last) // 地图更新
{
    if (last->move.column_move != 0 || last->move.row_move != 0)
    {
        last->map.map_char[last->player.x][last->player.y] = (last->map.map_num[last->player.x][last->player.y] == 2) ? 'D' : ' ';
        // 玩家移动
        last->player.x += last->move.row_move;
        last->player.y += last->move.column_move;
        last->map.map_char[last->player.x][last->player.y] = 'Y';
    }
    return;
}
void movement(node **last) // 移动操作
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
void treasurechange(node *last) // 宝藏计数
{
    last->player.treasure_found += 1;
    return;
}