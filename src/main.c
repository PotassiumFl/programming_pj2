#include "data.h"
#include "node.h"
#include "save.h"
#include "screen.h"

int main() // 主函数
{
    // 变量声明
    node *head, *last, *now, *tmp;
    game_info game;
    game_info *game_pointer = &game;
    head = nodecreate();
    head->prev = NULL;
    head->next = NULL;
    last = head;
    now = head;
    int screen = 1;
    int save_screen = 1;
    game.last_game = 0;
    game.passed_game = 0;
    char programinput;
    FILE *inputline;

begin: // 结算跳转,初始化变量
    memset(head->map.map_num, 0, 10000);
    memset(head->map.map_char, '\0', 10000);
    saveimport(head, game_pointer);
    last = head;
    save_screen = 1;

    // 开始界面
    screen = movescreen(4, game_pointer, &head->player);
    if (screen == 4)
        exit(0);
    // 选择模式
    if (screen == game_pointer->last_game && head->player.treasure_found != head->player.treasure_num)
        save_screen = movescreen(3, game_pointer, &head->player);
    if (save_screen == 2 || screen != game_pointer->last_game || head->player.treasure_found == head->player.treasure_num)
    {
        head->player.can_exit = 0;
        head->player.treasure_num = 0;
        head->player.manual = 0;
        head->player.manual_spend = 0;
        head->player.treasure_found = 0;
        head->move.ifcorrect = 1;
        game.mode = movescreen(2, game_pointer, &head->player);
        initialization(screen, head);
    }
    game.last_game = screen;
    inputline = fopen("..\\build\\save.txt", "w+");
    fclose(inputline);
    // 进行游戏
    if (game.mode == 1) // 实时模式
    {
        printmap(&last->map);
        printf("控制方法：按W向上移动，按S向下移动，按A向左移动，按D向右移动，按I原地不动，按Z撤销操作，按Y恢复操作，按Q结束冒险。\n");
        while (last->player.can_exit == 0)
        {
            last->move.ifcorrect = 1;
            last->move.input = toupper(getch());
            movement(&last);
            printmap(&last->map);
            printf("消耗的体力：%d\n", last->player.manual_spend);
            printf("控制方法：按W向上移动，按S向下移动，按A向左移动，按D向右移动，按I原地不动，按Z撤销操作，按Y恢复操作，按Q结束冒险。\n");
            if (last->move.ifcorrect == 0) // 实时模式输入错误
            {
                printf("输入错误，请重新输入！\n");
            }
        }
    }
    else // 编程模式
    {
        printmap(&last->map);
        printf("控制方法：按W向上移动，按S向下移动，按A向左移动，按D向右移动，按I原地不动，按Z撤销操作，按Y恢复操作，按Q结束冒险，按<Enter>输入。\n");
        while (last->player.can_exit == 0)
        {
            inputline = fopen("..\\build\\inputline.txt", "w+"); // 接受输入
            while ((programinput = getch()) != '\r')
            {
                fprintf(inputline, "%c", programinput);
            }
            fflush(NULL);
            fseek(inputline, 0L, 0);                              // 光标重置
            while (fscanf(inputline, "%c", &programinput) != EOF) // 分析输入
            {
                last->move.column_move = last->move.row_move = 0;
                last->move.input = toupper(programinput);
                movement(&last);
                if (last->move.ifcorrect == 0) // 编程模式输入错误直接结束游戏
                    goto close;
            }
            printmap(&last->map);
            printf("消耗的体力：%d\n", last->player.manual_spend);
            printf("控制方法：按W向上移动，按S向下移动，按A向左移动，按D向右移动，按I原地不动，按Z撤销操作，按Y恢复操作，按Q结束冒险，按<Enter>输入。\n");
        }
    }
close:
    fflush(NULL); // 打印结果
    system("cls");
    printf("恭喜你\n\n");
    printf("行动路径：");
    now = head;
    while (1)
    {
        printf("%c", now->move.moveline);
        now = now->next;
        if (now == last->next)
            break;
    }
    printf("\n消耗体力：%d\n", last->player.manual_spend);
    printf("找到的宝箱数量：%d/%d\n\n", last->player.treasure_found, last->player.treasure_num);
    if (last->player.treasure_found == last->player.treasure_num) // 记录关卡完成
    {
        switch (game.last_game)
        {
        case 1:
            game.passed_game = game.passed_game | 0b001;
            break;
        case 2:
            game.passed_game = game.passed_game | 0b010;
            break;
        case 3:
            game.passed_game = game.passed_game | 0b100;
            break;
        default:
            break;
        }
    }
    printf("<按任意键继续>\n");
    savefile(last, game_pointer);

    tmp = last->prev;
    while (tmp != NULL) // 释放内存
    {
        free(last);
        last = tmp;
        tmp = last->prev;
    }
    if (getch() != '\0') // 回到开始
        goto begin;
    return 0;
}