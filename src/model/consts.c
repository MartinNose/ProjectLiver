//
// Created by ������ on 2019/5/15.
//
#include <genlib.h>

#define BLOCKSIZE 0.5

#define WIDTH 32 //Width in inches
#define HEIGHT 18 //Height in inches

#define MAINTAINER 0

struct block{
    int x,y;
    string color;
};

struct tetrominoes{
    int x,y;
    int type; //��Ӧһ����ά�����ʾ��״  int shape[][],ͨ������任ʵ����ת 0 ��ʾ�ն���
    string color;
    int direction;
};

typedef struct tetrominoes tetromino;
string COLOR[8] = {
        "",//for null
        "BLUE",
        "DarkBlue",
        "Orange",
        "Yellow",
        "Green",
        "Purple",
        "Red"
};

tetromino NaT;//Not a Tetromino
