//
// Created by ������ on 2019/5/15.
//
#ifndef _consts_h
#define _consts_h

#include <genlib.h>

#define BLOCKSIZE 0.5

#define WIDTH 32 //Width in inches
#define HEIGHT 18 //Height in inches

#define MAINTAINER 0

#define ERA 1000
//struct block{
//    int x,y;
//    string color;
//};

#define DEBUG_SLOW 0.04
#define SLOW 0.08
#define FAST 0.6

typedef struct tetriminoes {
    int x, y;
    int type; //��Ӧһ����ά�����ʾ��״  int shape[][],ͨ������任ʵ����ת 0 ��ʾ�ն���
    string color;
    int direction;
} tetrimino;

struct state {
    bool isFalling;
    bool ifKeyEvent;
    bool ifHardDrop;
    bool isTurn;
    double Velocity;
    int KeyEvent;
    int V;
} STATE;

extern int typeInfo[][4][2];

extern string TETRI_COLOR[8];


#endif