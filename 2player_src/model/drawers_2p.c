//
// Created by 87547 on 2019/5/30.
//

#include <windows.h>
#include <string.h>
#include <math.h>

#include "drawers_2p.h"
#include "consts_2p.h"
#include "model_2p.h"

//#include "handlers.h"


#include "imgui.h"

void drawUI(){
    //TODO
}






void drawShadowBlock (int x, int y, string color)
{
    SetPenColor (color);

    SetPenSize (GetPenSize () + 3);
    MovePen (x * BLOCKSIZE, y * BLOCKSIZE);
    DrawRect (BLOCKSIZE, BLOCKSIZE);

    SetPenColor ("Black");
    SetPenSize (GetPenSize () - 3);
}
void DrawShadow (tetrimino shadow)
{
    switch (shadow.direction) {
        case 0:
            for (int i = 0; i < 4; i++) {
                drawShadowBlock (
                        shadow.x + typeInfo[shadow.type][i][0],
                        shadow.y + typeInfo[shadow.type][i][1], TETRI_COLOR[shadow.type]);
            }
            break;
        case 1:
            for (int i = 0; i < 4; i++) {
                drawShadowBlock (
                        shadow.x - typeInfo[shadow.type][i][1],
                        shadow.y + typeInfo[shadow.type][i][0], TETRI_COLOR[shadow.type]);
            }
            break;
        case 2:
            for (int i = 0; i < 4; i++) {
                drawShadowBlock (
                        shadow.x - typeInfo[shadow.type][i][0],
                        shadow.y - typeInfo[shadow.type][i][1], TETRI_COLOR[shadow.type]);
            }
            break;
        case 3:
            for (int i = 0; i < 4; i++) {
                drawShadowBlock (
                        shadow.x + typeInfo[shadow.type][i][1],
                        shadow.y - typeInfo[shadow.type][i][0], TETRI_COLOR[shadow.type]);
            }
            break;
    }
}

void drawTetri (tetrimino tetri)
{
    switch (tetri.direction) {
        case 0:
            for (int i = 0; i < 4; i++) {
                drawBlock (
                        tetri.x + typeInfo[tetri.type][i][0],
                        tetri.y + typeInfo[tetri.type][i][1], TETRI_COLOR[tetri.type]);
            }
            break;
        case 1:
            for (int i = 0; i < 4; i++) {
                drawBlock (
                        tetri.x - typeInfo[tetri.type][i][1],
                        tetri.y + typeInfo[tetri.type][i][0], TETRI_COLOR[tetri.type]);
            }
            break;
        case 2:
            for (int i = 0; i < 4; i++) {
                drawBlock (
                        tetri.x - typeInfo[tetri.type][i][0],
                        tetri.y - typeInfo[tetri.type][i][1], TETRI_COLOR[tetri.type]);
            }
            break;
        case 3:
            for (int i = 0; i < 4; i++) {
                drawBlock (
                        tetri.x + typeInfo[tetri.type][i][1],
                        tetri.y - typeInfo[tetri.type][i][0], TETRI_COLOR[tetri.type]);
            }
            break;
    }
}


//Tools
void DrawRect (double width, double height)
{
    DrawLine (width, 0);
    DrawLine (0, height);
    DrawLine (-1 * width, 0);
    DrawLine (0, -1 * height);
}

void drawBlock (int x, int y, string color)
{
    SetPenColor (color);
    StartFilledRegion (1);

    MovePen (x * BLOCKSIZE, y * BLOCKSIZE);

    DrawRect (BLOCKSIZE, BLOCKSIZE);

    EndFilledRegion ();

    SetPenColor ("Black");
//    MovePen (x * BLOCKSIZE, y * BLOCKSIZE);
//    DrawRect (BLOCKSIZE, BLOCKSIZE);
}

void drawCheckerBoard(Checkerboard checker){
    {
        for (int i = 1; i < 13; i++) {
            for (int j = 0; j < HEIGHT; j++) {
                drawBlock (i + checker.x - 1, j, TETRI_COLOR[checker.block[i][j + 1]]);
            }
        }
    }
}

void drawCheckerBoardList(Checkerboard *list){
    drawCheckerBoard(list[0]);
    drawCheckerBoard(list[1]);
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