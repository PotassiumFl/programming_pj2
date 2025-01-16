#ifndef STRUCT
#define STRUCT
typedef struct play_info
{
    int x;
    int y;
    int manual;
    int manual_spend;
    int treasure_num;
    int treasure_found;
    int can_exit;
} player_info;
typedef struct map_info
{
    int map_height;
    int map_width;
    int map_num[100][100];
    char map_char[100][100];

} map_info;
typedef struct move_info
{
    char input;
    int ifcorrect;
    int column_move;
    int row_move;
    char moveline;
} move_info;
typedef struct game_info
{
    int mode;
    int last_game;
    int passed_game;
    int year;
    int month;
    int day;
    int hour;
    int min;
    int sec;
} game_info;
typedef struct node
{
    struct node *prev;
    player_info player;
    map_info map;
    move_info move;
    struct node *next;
} node;
#endif