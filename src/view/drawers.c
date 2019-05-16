#include "graphics.h"
#include "extgraph.h"
#include <stdio.h>

#include "consts.c"


int typeInfo[][4][2] = { // ÿ����״���һ�����飬��ÿ�������а���һ����ά���飨���ڿ��Կ���״̬ѹ������ע��ÿ�������ʵ����4��block
    {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{0, -2}, {0, -1}, {0, 0}, {0, 1}}, // 0, ����
    {{-1, 2}, {-1, 1}, {0, 1}, {1, 1}}, // 1, L1
    {{1, 2}, {-1, 1}, {0, 1}, {1, 1}}, // 2, L2
    {{-1, 1}, {-1, 0}, {0, 0}, {0, 1}}, // 3, Square
    {{-1, 0}, {0, 0}, {0, 1}, {1, 1}}, // 4, Snake1
    {{-1, 0}, {0, 0}, {0, 1}, {1, 0}}, // 5, Up
    {{-1, 1}, {0, 1}, {0, 0}, {1, 0}}, // 6, Snack2
};


void DrawRect (double width, double height)
{
    DrawLine (width, 0);
    DrawLine (0, height);
    DrawLine (-1 * width, 0);
    DrawLine (0, -1 * height);
}

void Clean ()
{
    SetEraseMode (1);
    StartFilledRegion (1);
    MovePen (0, 0);
    DrawRect (GetWindowWidth (), GetWindowHeight ());
    EndFilledRegion ();
    SetEraseMode (0);
}

void drawBlock (int x, int y, string color)
{

    SetPenColor (color);
    StartFilledRegion (1);

    MovePen (x * BLOCKSIZE, y * BLOCKSIZE);

    DrawRect (BLOCKSIZE, BLOCKSIZE);

    EndFilledRegion ();
}

void drawTetri (tetrimino tetri)
{
//    if (tetri.direction == 0) {
//        for (int i = 0; i < 4; i++) {
//            drawBlock (tetri.x + typeInfo[tetri.type][i][0], tetri.y + typeInfo[tetri.type][i][1], tetri.color);
//        }
//    }
    switch (tetri.direction)
    {
        case 0:
            for (int i = 0; i < 4; i++) {
                drawBlock (tetri.x + typeInfo[tetri.type][i][0], tetri.y + typeInfo[tetri.type][i][1], tetri.color);
            }
            break;
        case 1:
            for (int i = 0; i < 4; i++) {
                drawBlock (tetri.x - typeInfo[tetri.type][i][1], tetri.y + typeInfo[tetri.type][i][0], tetri.color);
            }
            break;
        case 2:
            for (int i = 0; i < 4; i++) {
                drawBlock (tetri.x - typeInfo[tetri.type][i][0], tetri.y - typeInfo[tetri.type][i][1], tetri.color);
            }
            break;
        case 3:
            for (int i = 0; i < 4; i++) {
                drawBlock (tetri.x + typeInfo[tetri.type][i][1], tetri.y - typeInfo[tetri.type][i][0], tetri.color);
            }
            break;
    }
}

void drawInit ()
{
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            drawBlock (i, j, "Gray");
        }
    }
    for (int i = 10; i < 22; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            drawBlock (i, j, "White");
        }
    }
    for (int i = 22; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            drawBlock (i, j, "Gray");
        }
    }
}