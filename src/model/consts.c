//
// Created by ������ on 2019/5/15.
//


#ifndef _consts_c
#define _consts_c

#include <genlib.h>

#define BLOCKSIZE 0.5

#define WIDTH 32 //Width in inches
#define HEIGHT 18 //Height in inches

#define MAINTAINER 0

//struct block{
//    int x,y;
//    string color;
//};

typedef struct tetrominoes{
    int x,y;
    int type; //��Ӧһ����ά�����ʾ��״  int shape[][],ͨ������任ʵ����ת 0 ��ʾ�ն���
    string color;
    int direction;
} tetromino;




#endif