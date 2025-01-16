#include "data.h"
#include "node.h"
#include "save.h"
#include "screen.h"

int main() // ������
{
    // ��������
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

begin: // ������ת,��ʼ������
    memset(head->map.map_num, 0, 10000);
    memset(head->map.map_char, '\0', 10000);
    saveimport(head, game_pointer);
    last = head;
    save_screen = 1;

    // ��ʼ����
    screen = movescreen(4, game_pointer, &head->player);
    if (screen == 4)
        exit(0);
    // ѡ��ģʽ
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
    // ������Ϸ
    if (game.mode == 1) // ʵʱģʽ
    {
        printmap(&last->map);
        printf("���Ʒ�������W�����ƶ�����S�����ƶ�����A�����ƶ�����D�����ƶ�����Iԭ�ز�������Z������������Y�ָ���������Q����ð�ա�\n");
        while (last->player.can_exit == 0)
        {
            last->move.ifcorrect = 1;
            last->move.input = toupper(getch());
            movement(&last);
            printmap(&last->map);
            printf("���ĵ�������%d\n", last->player.manual_spend);
            printf("���Ʒ�������W�����ƶ�����S�����ƶ�����A�����ƶ�����D�����ƶ�����Iԭ�ز�������Z������������Y�ָ���������Q����ð�ա�\n");
            if (last->move.ifcorrect == 0) // ʵʱģʽ�������
            {
                printf("����������������룡\n");
            }
        }
    }
    else // ���ģʽ
    {
        printmap(&last->map);
        printf("���Ʒ�������W�����ƶ�����S�����ƶ�����A�����ƶ�����D�����ƶ�����Iԭ�ز�������Z������������Y�ָ���������Q����ð�գ���<Enter>���롣\n");
        while (last->player.can_exit == 0)
        {
            inputline = fopen("..\\build\\inputline.txt", "w+"); // ��������
            while ((programinput = getch()) != '\r')
            {
                fprintf(inputline, "%c", programinput);
            }
            fflush(NULL);
            fseek(inputline, 0L, 0);                              // �������
            while (fscanf(inputline, "%c", &programinput) != EOF) // ��������
            {
                last->move.column_move = last->move.row_move = 0;
                last->move.input = toupper(programinput);
                movement(&last);
                if (last->move.ifcorrect == 0) // ���ģʽ�������ֱ�ӽ�����Ϸ
                    goto close;
            }
            printmap(&last->map);
            printf("���ĵ�������%d\n", last->player.manual_spend);
            printf("���Ʒ�������W�����ƶ�����S�����ƶ�����A�����ƶ�����D�����ƶ�����Iԭ�ز�������Z������������Y�ָ���������Q����ð�գ���<Enter>���롣\n");
        }
    }
close:
    fflush(NULL); // ��ӡ���
    system("cls");
    printf("��ϲ��\n\n");
    printf("�ж�·����");
    now = head;
    while (1)
    {
        printf("%c", now->move.moveline);
        now = now->next;
        if (now == last->next)
            break;
    }
    printf("\n����������%d\n", last->player.manual_spend);
    printf("�ҵ��ı���������%d/%d\n\n", last->player.treasure_found, last->player.treasure_num);
    if (last->player.treasure_found == last->player.treasure_num) // ��¼�ؿ����
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
    printf("<�����������>\n");
    savefile(last, game_pointer);

    tmp = last->prev;
    while (tmp != NULL) // �ͷ��ڴ�
    {
        free(last);
        last = tmp;
        tmp = last->prev;
    }
    if (getch() != '\0') // �ص���ʼ
        goto begin;
    return 0;
}