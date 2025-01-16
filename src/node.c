#include "node.h"
void movenode(node **last)
{
    node *tmp;
    (*last)->next = nodecreate();
    tmp = *last;
    *last = (*last)->next;
    (*last)->prev = tmp;
    (*last)->move.column_move = (*last)->move.row_move = 0;
    (*last)->player.can_exit = 0;
    (*last)->move.ifcorrect = 1;
    passinfo((*last)->prev, (*last));
    return;
}
node *nodecreate()
{
    node *p = (node *)malloc(sizeof(node));
    return p;
}
void passinfo(node *prev, node *now)
{
    for (int j = 0; j < prev->map.map_height; j++)
        for (int k = 0; k < prev->map.map_width; k++)
        {
            now->map.map_num[j][k] = prev->map.map_num[j][k];
            now->map.map_char[j][k] = prev->map.map_char[j][k];
        }
    now->map.map_height = prev->map.map_height;
    now->map.map_width = prev->map.map_width;
    now->player.manual = prev->player.manual;
    now->player.manual_spend = prev->player.manual_spend;
    now->player.treasure_found = prev->player.treasure_found;
    now->player.treasure_num = prev->player.treasure_num;
    now->player.x = prev->player.x;
    now->player.y = prev->player.y;
    return;
}