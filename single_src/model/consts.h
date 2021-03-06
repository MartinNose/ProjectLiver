/*
 * This file contains useful constants
 */

#ifndef _consts_h
#define _consts_h

#include <genlib.h>

extern double BLOCKSIZE;

#define WIDTH 24 //Width in inches
#define HEIGHT 18 //Height in inches
#define LEFTBAR 6 //Left Bar Width
#define RIGHTBAR 10 //RIGHT BAR

#define PreX (LEFTBAR+13)
#define PreY 10

#define HoldX (LEFTBAR+13)
#define HoldY 2

#define LevelX 2
#define LevelY 9

#define ScoreX 2
#define ScoreY 11

#define SpeedX 2
#define SpeedY 10



#define GAME 0
#define CheckerboardFLASH 1
#define GAMEOVER 2
#define DEBUG 3
#define LOADING 4

#define ERA 1000

#define INIT_SPEED 0.07
#define SLOW 0.06
#define FAST 8

#define LevelGap 10000

#define PAUSE 0

#define USERNAMELENGTH 16

typedef struct  {
    int x, y;
    int type; //对应一个二维数组表示形状  int shape[][],通过矩阵变换实现旋转 0 表示空对象
    int direction;
    double yVelocity;
    bool isPaused;
} tetrimino;

typedef struct {
    int block[14][25];
} Checkerboard;

extern int typeInfo[][4][2];

extern string TETRI_COLOR[8];

extern char *const BGM_Path;

extern double leftbar;

#endif