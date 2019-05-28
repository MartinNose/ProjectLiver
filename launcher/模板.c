#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "random.h"
#include "strlib.h"
#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>
#define SYSCOLOR "Red" 
#define TIMER_BLINK500  1  
typedef struct {/*��������*/
	double x1, y1;/*���½�����*/
    double x2, y2;/*���Ͻ�����*/
    int PenSize; /*��ϸ*/
    string color; /*��ɫ*/
} *RectT;
void DrawRect(void *rect)
{
	RectT r = (RectT)rect;
	int pensize = GetPenSize();/*���浱ǰϵͳ�ʻ���ϸ*/
	string color = GetPenColor();/*���浱ǰϵͳ��ɫ*/

	SetPenSize(r->PenSize);/*���ô�ϸ*/
	SetPenColor(r->color);/*������ɫ*/
	MovePen(r->x1, r->y1);
	DrawLine(r->x2-r->x1, 0);
	DrawLine(0, r->y2-r->y1);
	DrawLine(r->x1-r->x2, 0);
	DrawLine(0, r->y1-r->y2);
	SetPenSize(pensize); /*�ָ���ϸ*/
	SetPenColor(color);/*�ָ���ɫ*/
}
void fillRectangle(double x, double y, double w, double h)
{
    MovePen(x, y);
    StartFilledRegion(1); // ��ʼ
        DrawLine(0, h);
        DrawLine(w, 0);
        DrawLine(0, -h);
        DrawLine(-w, 0);
    EndFilledRegion();   // ����
}
void Main(){
	InitGraphics();
	double x,y;
	 x = GetWindowWidth()/36;
     y = GetWindowHeight()/41;
    	SetPenColor("Red"); 
    	MovePen(16*x,25*y);
   fillRectangle(0,0,36*x,41*y);
   /*���»���Tetris!*/ 
   SetPenColor("White");
   fillRectangle(6*x,26*y,3*x,y);
   fillRectangle(7*x,19*y,x,7*y);
   fillRectangle(10*x,19*y,x,6*y);
   fillRectangle(10*x,19*y,3*x,y);
   fillRectangle(12*x,20*y,x,y);
   fillRectangle(10*x,22*y,3*x,y);
   fillRectangle(10*x,24*y,3*x,y);
   fillRectangle(12*x,22*y,x,2*y);
   fillRectangle(14*x,19*y,x,9*y);
   fillRectangle(14*x,19*y,2*x,y);
   fillRectangle(14*x,24*y,2*x,y);
   fillRectangle(17*x,19*y,x,6*y);
   fillRectangle(17*x,24*y,2*x,y);  
   fillRectangle(20*x,19*y,x,6*y);
   fillRectangle(20*x,26*y,x,y);
   fillRectangle(22*x,19*y,3*x,1*y);
   fillRectangle(22*x,21*y,1*x,4*y);
   fillRectangle(22*x,21*y,3*x,2*y);
   fillRectangle(24*x,20*y,1*x,1*y);
   fillRectangle(22*x,24*y,3*x,1*y);
   fillRectangle(26*x,19*y,1*x,1*y);
   fillRectangle(26*x,21*y,1*x,6*y);
   
   /*���Ʒָ���*/ 
   fillRectangle(0,10*y,36*x,1*y); 
   /*���Ƶײ��ʿ�*/ 
   SetPenColor("Yellow");
   fillRectangle(0*x,7*y,5*x,3*y);
   fillRectangle(2*x,4*y,6*x,3*y);
   SetPenColor("Blue");
   fillRectangle(0*x,0*y,8*x,4*y);
   fillRectangle(0*x,0*y,2*x,7*y);
   SetPenColor("Green");
   fillRectangle(5*x,7*y,6*x,3*y);
   fillRectangle(8*x,0*y,3*x,7*y);
   SetPenColor("Gray");
   fillRectangle(11*x,7*y,12*x,3*y);
   SetPenColor("Black");
   fillRectangle(11*x,0*y,3*x,7*y);
   fillRectangle(11*x,0*y,9*x,4*y);
   SetPenColor("Red");
   fillRectangle(14*x,4*y,12*x,3*y);
   SetPenColor("Green");
   fillRectangle(20*x,0*y,9*x,4*y);
   fillRectangle(26*x,0*y,3*x,7*y);
   SetPenColor("Yellow");
   fillRectangle(23*x,7*y,6*x,3*y);
   fillRectangle(29*x,4*y,3*x,6*y);
   SetPenColor("Blue");
   fillRectangle(29*x,0*y,7*x,4*y);
   SetPenColor("Green");
   fillRectangle(32*x,4*y,6*x,6*y);
 




    	
}
