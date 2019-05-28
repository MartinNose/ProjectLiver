//
// Created by Tao Chiang on 5/17/2019.
//
#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <math.h>

#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>


#include "model.h"
#include "consts.h"
#include "drawers.h"

#include "imgui.h"

#include "file_system.h"

Checkerboard checkerboard;
// store the colors of block, white as 0, (x,y),  extended space are for easier(lazier) check...
tetrimino ctetri;

int Score = 0;
static int Mark[4] = {-1,-1,-1,-1};
static Checkerboard lastCheckerboard;
static Checkerboard clearCheckerboard;
tetrimino que[2];
tetrimino HoldedTetri;
bool is_game_over = FALSE;
bool isHoldLegal = TRUE;
double globalSpeed;
void drawMenu();

//MenuBar============================================
bool isDisplayMenu1 = FALSE;
//===================================================


static int countScore(int num);

static void game ();
static void flash ();
static Checkerboard ClearLine(Checkerboard checkerboard,int row);
static Checkerboard ClearLines(Checkerboard checkerboard);
static Checkerboard RemoveLines(Checkerboard checkerboard1);
static Checkerboard RemoveLine (Checkerboard checkerboard1,int row);
static tetrimino NextTetri();


tetrimino generateTetrimino (int type, int direction)
{
    tetrimino tetri;

    tetri.x = WIDTH / 2;
    tetri.y = HEIGHT;
    tetri.type = type;
    tetri.direction = direction;
    tetri.color = TETRI_COLOR[type];
    tetri.yVelocity = 0;
    tetri.isPulsed = FALSE;

    return tetri;
}
void timerEventHandler (int timerID){
    switch(timerID){
        case MAINTAINER:
            game();
            break;
        case CheckerboardFLASH :
            flash();
            break;
    }
   drawMenu();
}
static void game ()
{
    static int time = 0;
    static bool pause = 0;
    if (ctetri.yVelocity == 0 && !ctetri.isPulsed) {
        ctetri = NextTetri ();
        ctetri = tetriMaintainer_on_gravity (time, ctetri);
    }

    time = (time + 1) % ERA; // !!!
    Clean ();

    drawCheckerBoard(checkerboard);
    ctetri = tetriMaintainer_on_gravity (time, ctetri);
    DrawShadow(HardDrop(ctetri));

    drawTetri (ctetri);
    drawInit (Score,que[1]);

    if(ctetri.yVelocity == 0 && !ctetri.isPulsed){
        Settle(ctetri); //add tetri to checker board
        globalSpeed = INIT_SPEED + INIT_SPEED * (Score/LevelGap); //update speed
        isHoldLegal = TRUE;
    }
    if(ctetri.isPulsed){
        DrawPulse();
    }
    if(is_game_over){
        cancelTimer(MAINTAINER);
        userNode* rank_list = Load_Rank ();
        rank_list = Add_Node (rank_list, Score, "game_debug");
        write_Rank (rank_list);
        char buffer[32];
        sprintf (buffer, "%d", Score);
        MessageBoxA (NULL, buffer, "Display", MB_ICONINFORMATION);
    }
}
static void flash (){
    static int times = 0;
    if(times %2 == 0){
        drawCheckerBoard(lastCheckerboard);
    }else{
        drawCheckerBoard(clearCheckerboard);
    }
    drawInit (Score,que[1]);
    times++;
    if(times >= 6){
        cancelTimer(CheckerboardFLASH);
        startTimer(MAINTAINER,10);
        times = 0;
    }
}

tetrimino tetriMaintainer_on_gravity (int time, tetrimino tetri)
{
    static int curTime = 0;
    static double dy = 0;
    int dt;
    if (tetri.yVelocity == 0 && !tetri.isPulsed) {
        tetri.yVelocity = globalSpeed;
    }
    tetrimino last = tetri;
    if (time > curTime) {
        dt = (time - curTime);
    } else {
        dt = (time + ERA - curTime);
    }

    dy += tetri.yVelocity * dt;
    if (dy >= 1) {
        tetri.y -= 1;
        dy = 0;
    }

    curTime = time;

    if (!check_collision (tetri)) {
        return tetri;
    } else {
        last.yVelocity = 0;
        return last;
    }

}


void Settle(tetrimino tetri){
    checkerboard = Settle_Tetri (tetri,checkerboard);
    lastCheckerboard = checkerboard;
    clearCheckerboard = ClearLines(checkerboard);
    if(Mark[0]!=-1) {
        cancelTimer(MAINTAINER);
        startTimer(CheckerboardFLASH, 100);
    }
    checkerboard = RemoveLines(checkerboard);
    if (CheckTop () == FALSE) {
        is_game_over = TRUE;
    }
}

static int countScore(int num){
    int ds = 0;
    switch (num){
        case 0: break;
        case 1:
            ds = 100;
            break;
        case 2:
            ds = 200;
            break;
        case 3:
            ds = 500;
            break;
        case 4:
            ds = 1000;
            break;
        default:break;
    }
    return ds;
}

bool CheckTop ()
{
    bool isTopped = 0;
    for (int i = 1; i <= 12; i++) {
        if (checkerboard.block[i][19]){
            isTopped = 1;
        }
    }
    if (isTopped){
        return FALSE;
    }else{
        return TRUE;
    }
}

static Checkerboard ClearLines(Checkerboard checkerboard1)
{
    int num = 0;
    int i, j , line_ok;
    for (i = 1; i <= 18;i++ ) {
        line_ok = TRUE;
        for (j = 1; j <= 12; j++) {
            if (!checkerboard1.block[j][i]) {
                line_ok = FALSE;
                break;
            }
        }
        if (line_ok) {
            checkerboard1 = ClearLine(checkerboard1,i);
            Mark[num++] = i;
        }
    }
    Score += countScore(num);
    return checkerboard1;
}

static Checkerboard ClearLine(Checkerboard checkerboard1,int row){
    int  j;
        for (j = 1; j <= 12; j++)
            checkerboard1.block[j][row] = 0;

    return checkerboard1;
}
static Checkerboard RemoveLines(Checkerboard checkerboard1){
    int i, j ;
    for (i = 1,j = 0; i <= 18; ) {
        if (i == Mark[j] - j) {
            checkerboard1 = RemoveLine(checkerboard1,i);
            Mark[j] = -1;
            j++;
        }
        else
        {
            i++;
        }
    }
    return checkerboard1;
}
static Checkerboard RemoveLine (Checkerboard checkerboard1,int row)
{
    int i, j;
    for (i = row; i <= 18; i++) {
        for (j = 1; j <= 12; j++)
            checkerboard1.block[j][i] = checkerboard1.block[j][i + 1];
    }
    return checkerboard1;
}

tetrimino NextTetri()
{
        que[0] = que[1];
        que[1] = tetriRandom();
        return que[0];
}

tetrimino tetriRandom ()
{
    static int last = 0;
    int type;
    do {
        type = rand () % 7;
        if (type == 0) type = 7;
    } while (last == type);
    last = type;
    int direction = rand () % 2;
    return generateTetrimino (type, direction);
}


static Checkerboard generateInitCheckerboard(){
    int i,j;
    Checkerboard EmptyCheckerboard;
    for(i = 0;i<14;i++)
        for(j = 0;j<25;j++)
            EmptyCheckerboard.block[i][j] = 0;
    for (i = 0; i < 20; i++)
        EmptyCheckerboard.block[0][i] = EmptyCheckerboard.block[13][i] = 1;
    for (i = 1; i < 13; i++)
        EmptyCheckerboard.block[i][0] = 1; // block_color[i][19] =
    // rewrite the boundary as 1
    for (i = 1; i <= 12; i++)
    {
        for (j = 1; j < 20; j++)
            EmptyCheckerboard.block[i][j] = 0;
    }

    return EmptyCheckerboard;
}

void InitModel ()
{
    checkerboard = generateInitCheckerboard();

    Score = 0;
    globalSpeed = INIT_SPEED;

    que[0] = tetriRandom();
    que[1] = tetriRandom();
    //For MenuBar
    //For Game STATE
}

bool check_collision (tetrimino tetri)
{
    switch (tetri.direction) {
        case 0:
            for (int i = 0; i < 4; i++) {
                if (checkerboard.block[tetri.x + typeInfo[tetri.type][i][0] - 9][tetri.y + typeInfo[tetri.type][i][1] + 1])
                    return TRUE;
            }
            return FALSE;
            break;
        case 1:
            for (int i = 0; i < 4; i++) {
                if (checkerboard.block[tetri.x - typeInfo[tetri.type][i][1] - 9][tetri.y + typeInfo[tetri.type][i][0] + 1])
                    return TRUE;
            }
            return FALSE;
            break;
        case 2:
            for (int i = 0; i < 4; i++) {
                if (checkerboard.block[tetri.x - typeInfo[tetri.type][i][0] - 9][tetri.y - typeInfo[tetri.type][i][1] + 1])
                    return TRUE;
            }
            return FALSE;
            break;
        case 3:
            for (int i = 0; i < 4; i++) {
                if (checkerboard.block[tetri.x + typeInfo[tetri.type][i][1] - 9][tetri.y - typeInfo[tetri.type][i][0] + 1])
                    return TRUE;
            }
            return FALSE;
            break;
    }
}

Checkerboard Settle_Tetri (tetrimino tetri, Checkerboard checker)
{
    switch (tetri.direction) {
        case 0:
            for (int i = 0; i < 4; i++) {
                checker.block[tetri.x + typeInfo[tetri.type][i][0] - 9][tetri.y + typeInfo[tetri.type][i][1] + 1] = tetri.type;
            }
            break;
        case 1:
            for (int i = 0; i < 4; i++) {
                checker.block[tetri.x - typeInfo[tetri.type][i][1] - 9][tetri.y + typeInfo[tetri.type][i][0] + 1] = tetri.type;
            }
            break;
        case 2:
            for (int i = 0; i < 4; i++) {
                checker.block[tetri.x - typeInfo[tetri.type][i][0] - 9][tetri.y - typeInfo[tetri.type][i][1] + 1] = tetri.type;
            }
            break;
        case 3:
            for (int i = 0; i < 4; i++) {
                checker.block[tetri.x + typeInfo[tetri.type][i][1] - 9][tetri.y - typeInfo[tetri.type][i][0] + 1] = tetri.type;
            }
            break;
    }
    return checker;

}

tetrimino HardDrop (tetrimino tetri)
{
    while (!check_collision (tetri)) {
        tetri.y--;
    }
    tetri.y++;
    return tetri;
}

tetrimino Restart ()
{
    if(is_game_over) {
        is_game_over = FALSE;
        startTimer(MAINTAINER,10);
    }

    tetrimino tetri;
    InitModel ();
    drawInit (0,que[1]);
    tetri = NextTetri();
    HoldedTetri = generateTetrimino(0,0);
    return tetri;
}

tetrimino HoldEventHandler(tetrimino temp){
    if(isHoldLegal) {
        if (HoldedTetri.type == 0) {
            HoldedTetri = temp;
            temp = que[1];
        } else {
            temp = HoldedTetri;
            temp.yVelocity = globalSpeed;
            HoldedTetri = ctetri;
        }
        HoldedTetri.y = 18;
        isHoldLegal = FALSE;
    }
    return temp;
}

tetrimino PulseEventHandler(tetrimino temp){
    if(!temp.isPulsed){
        temp.isPulsed = TRUE;
        temp.yVelocity = 0;
    }else{
        temp.yVelocity = globalSpeed;
        temp.isPulsed = FALSE;
    }
    return temp;
}

/*==================================================================*/

/*On GUI and Menu Bar*/

void drawMenu()
{
    static char * menuListFile[] = {
            "File",
            "Open  | Ctrl-O",
            "Close",
            "Exit   | Ctrl-E"};
    static char * menuListTool[] = {
            "Tool",
            "Triangle",
            "Circle",
            "Stop Rotation | Ctrl-T"};
    static char * menuListHelp[] = {"Help",
                                    "Show More  | Ctrl-M",
                                    "About"};
    static char * selectedLabel = NULL;

    double fH = GetFontHeight();
    double x = 0;
    double y = GetWindowHeight();
    double h = fH*1.5;
    double w = TextStringWidth(menuListHelp[0])*2;
    double wlist = TextStringWidth(menuListTool[3])*1.2;
    double xindent = GetWindowWidth()/20;
    int    selection;

    // File �˵�
    selection = menuList(GenUIID(0), x, y-h, w, wlist, h, menuListFile, sizeof(menuListFile)/sizeof(menuListFile[0]));
    if( selection>0 ) selectedLabel = menuListFile[selection];
    if( selection==3 )
        exit(-1); // choose to exit

    // Tool �˵�
    menuListTool[3] =  "Start Rotation | Ctrl-T";
    selection = menuList(GenUIID(0),x+w,  y-h, w, wlist,h, menuListTool,sizeof(menuListTool)/sizeof(menuListTool[0]));
    if( selection>0 ) selectedLabel = menuListTool[selection];

    // Help �˵�
    menuListHelp[1] = "Show Less | Ctrl-M" ;
    selection = menuList(GenUIID(0),x+2*w,y-h, w, wlist, h, menuListHelp,sizeof(menuListHelp)/sizeof(menuListHelp[0]));
    if( selection>0 ) selectedLabel = menuListHelp[selection];
}