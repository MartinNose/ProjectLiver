#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
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

#include "imgui.h"
#include "file_system_linked_list.h"

// ȫ�ֱ���
static double winwidth, winheight;   // ���ڳߴ�
static int enable_rotation = 1;   // ������ת
static int show_more_buttons = 0; // ��ʾ���ఴť
userNode* head = NULL;


static char *const head_str = "Leader Board";
// ����������provided in libgraphics
void DisplayClear (void);

// �û�����ʾ����
void display (void);

void DrawBasic ();
void RefreshDisplay();
void drawMenu();

void Init_Rank_Data();
void PrintList(userNode* head, double x, double y, int num);

void drawButtons();

void DrawGrid(double x, double y, double width, double height,
              int columns, int rows);

void DrawBox(double x, double y, double width, double height);

// �û��ļ����¼���Ӧ����
void KeyboardEventProcess (int key, int event)
{
    uiGetKeyboard (key, event); // GUI��ȡ����
    display (); // ˢ����ʾ
}

// �û�������¼���Ӧ����
void MouseEventProcess (int x, int y, int button, int event)
{
    uiGetMouse (x, y, button, event); //GUI��ȡ���
    display (); // ˢ����ʾ
}

// �û����������
// ����ʼ��ִ��һ��
void Main ()
{
    // ��ʼ�����ں�ͼ��ϵͳ
    SetWindowTitle (head_str);
    //SetWindowSize(10, 10); // ��λ - Ӣ��
    //SetWindowSize(20, 10);
    //SetWindowSize(10, 20);  // �����Ļ�ߴ粻�����򰴱�����С
    InitGraphics ();

    // ��ô��ڳߴ�
    winwidth = GetWindowWidth ();
    winheight = GetWindowHeight ();

    setMenuColors("Black", "White", "Gray", "White", 1);

    // ע��ʱ����Ӧ����
    registerKeyboardEvent (KeyboardEventProcess);// ����
    registerMouseEvent (MouseEventProcess);      // ���

    // �򿪿���̨���������������Ϣ�����ڵ���
//    InitConsole();

    Init_Rank_Data();
    DrawBasic ();
    drawMenu ();
}

// �˵���ʾ����
void drawMenu ()
{
    static char *menuListFile[] = {"File",
                                   "Refresh | Ctrl-R", // ��ݼ��������[Ctrl-X]��ʽ�������ַ����Ľ�β
//                                    "Close",
                                   "Exit       | Ctrl-E"};
    static char *menuListTool[] = {"Tool",
                                   "Triangle",
                                   "Circle",
                                   "Stop Rotation | Ctrl-T"};
    static char *menuListHelp[] = {"Help",
                                   "Show More  | Ctrl-M",
                                   "About"};
    static char *selectedLabel = NULL;

    double fH = GetFontHeight ();
    double x = 0; //fH/8;
    double y = winheight;
    double h = fH * 1.5; // �ؼ��߶�
//    double w = TextStringWidth (menuListHelp[0]) * 2; // �ؼ����
    double w = winwidth / 3;
    double wlist = TextStringWidth (menuListTool[3]) * 1.2;
    double xindent = winheight / 20; // ����
    int selection;

    // File �˵�
    selection = menuList (GenUIID(0), x,
                          y - h, w, wlist, h, menuListFile, sizeof (menuListFile) / sizeof (menuListFile[0]));
    if (selection > 0) selectedLabel = menuListFile[selection];
    if (selection == 1)
        Init_Rank_Data ();
    if (selection == 2)
        exit (-1); // choose to exit

    // Tool �˵�
    menuListTool[3] = enable_rotation ? "Stop Rotation | Ctrl-T" : "Start Rotation | Ctrl-T";
    selection = menuList (GenUIID(0),
                          x + w, y - h, w, wlist, h, menuListTool, sizeof (menuListTool) / sizeof (menuListTool[0]));
    if (selection > 0) selectedLabel = menuListTool[selection];
    if (selection == 3)
        enable_rotation = !enable_rotation;

    // Help �˵�
    menuListHelp[1] = show_more_buttons ? "Show Less | Ctrl-M" : "Show More | Ctrl-M";
    selection = menuList (GenUIID(0),
                          x + 2 * w,
                          y - h, w, wlist, h, menuListHelp, sizeof (menuListHelp) / sizeof (menuListHelp[0]));
    if (selection > 0) selectedLabel = menuListHelp[selection];
    if (selection == 1)
        show_more_buttons = !show_more_buttons;
    if (selection == 2)
        MessageBoxA (NULL, "�������ǵĴ���ҵ��", "���� | About", MB_ICONINFORMATION);;
}

void display ()
{
    // ����
    RefreshDisplay ();
    // ���ƺʹ���˵�
    drawMenu ();
}

void RefreshDisplay ()
{
    DisplayClear ();
    DrawBasic ();
}

void DrawBasic ()
{
    SetFont ("΢���ź�");
    drawButtons ();
    SetPenColor ("Black");
    SetPointSize(64);
    MovePen (winwidth/2 - TextStringWidth(head_str) / 2, winheight / 2 + 2.4);
    DrawTextString (head_str);
    SetPointSize (13);
//    DrawGrid (winwidth/2 - 3, winheight/2 - 3, 2, 0.5, 3, 10);
    double x = winwidth/2 -3;
    double y = winheight/2 - 3;
    DrawBox (x , y, 6, 5);
    PrintList (head, x, y + 5, ((show_more_buttons) ? 20 : 10));
}

void drawButtons()
{
    double fH = GetFontHeight();
    double h = fH*2;  // �ؼ��߶�
    double x = winwidth/2.5;
    double y = winheight/2-h;
    double w = winwidth/5; // �ؼ����

    x = winwidth / 2 - 1;
    y = winheight / 2 - 0.6;
    setButtonColors("Black", "White", "Gray", "White", 1);
//    if (button(GenUIID(0), x, y, 2, 1.2, "Single Mode"))
//    {
//        WinExec("single_main.exe", SW_SHOW);
//    }

}

void DrawBox(double x, double y, double width, double height)
{
    MovePen(x, y);
    DrawLine(0, height);
    DrawLine(width, 0);
    DrawLine(0, -height);
    DrawLine(-width, 0);
}

void DrawGrid(double x, double y, double width, double height,
              int columns, int rows)
{
    int i, j;

    for (i = 0; i < columns; i++) {
        for (j = 0; j < rows; j++) {
            DrawBox(x + i * width, y + j * height,
                    width, height);
        }
    }
}

void Init_Rank_Data()
{
    head = Load_Rank ();
}

void PrintList(userNode* head, double x, double y, int num)
{
    char buffer[200];
    userNode* p;
    int cnt = 0;
    SetPenColor ("Black");
    SetPointSize (16);
    for (p = head; p && cnt < num; p = p->next)
    {
        cnt++;
        sprintf (buffer, "%10d %30s %10d", cnt, p->name, p->score);
        printf ("%s\n", buffer);
        MovePen (x, y - cnt * 0.4);
        DrawTextString (buffer);
    }
}