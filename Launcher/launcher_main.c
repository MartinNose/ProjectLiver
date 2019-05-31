/*
 * This file generates the launcher
 */
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

static char *const title_str = "Tetris";
// ȫ�ֱ���
static double win_width, win_height;   // ���ڳߴ�
static int show_more_buttons = 0; // ��ʾ���ఴť

static bool isDisplayMenu = FALSE;

// ����������provided in libgraphics
void DisplayClear (void);

// �û�����ʾ����
void display (void);

void DrawBasic ();
void RefreshDisplay ();

void drawButtons ();

// �û��ļ����¼���Ӧ����
void KeyboardEventProcess (int key, int event)
{
//    printf ("%d\n", key);
    switch (event) {
        case KEY_DOWN:
            switch (key) {
                case 16:isDisplayMenu ^= 1;
//                    printf ("%d\n", isDisplayMenu);
                    break;
                default:uiGetKeyboard (key, event); // GUI��ȡ����
                    break;
            }
            break;
        case KEY_UP:
            switch (key) {
                case 16:break;
                default:uiGetKeyboard (key, event); // GUI��ȡ����
                    break;
            }
        default:break;
    }
    if (isDisplayMenu)
        display (); // ˢ����ʾ
    else {
        RefreshDisplay ();
    }
}

// �û�������¼���Ӧ����
void MouseEventProcess (int x, int y, int button, int event)
{
    uiGetMouse (x, y, button, event); //GUI��ȡ���
    if (isDisplayMenu) {
        display (); // ˢ����ʾ
    } else {
        RefreshDisplay ();
    }
}

// �û����������
// ����ʼ��ִ��һ��
void Main ()
{
    // ��ʼ�����ں�ͼ��ϵͳ
    SetWindowTitle ("Teris Launcher");
    //SetWindowSize(10, 10); // ��λ - Ӣ��
    //SetWindowSize(20, 10);
    //SetWindowSize(10, 20);  // �����Ļ�ߴ粻�����򰴱�����С
    InitGraphics ();

    // ��ô��ڳߴ�
    win_width = GetWindowWidth ();
    win_height = GetWindowHeight ();

    setMenuColors ("Black", "White", "Gray", "White", 1);

    // ע��ʱ����Ӧ����
    registerKeyboardEvent (KeyboardEventProcess);// ����
    registerMouseEvent (MouseEventProcess);      // ���


    DrawBasic ();
    // �򿪿���̨���������������Ϣ�����ڵ���
    // InitConsole();
    PlaySound ("..\\Sound\\assets\\8bit.wav", NULL, SND_FILENAME | SND_ASYNC);
}

// �˵���ʾ����
void DrawMenu ()
{
    static char *menuListFile[] = {"File",
                                   "Leader Board  | Ctrl-B", // ��ݼ��������[Ctrl-X]��ʽ�������ַ����Ľ�β
//                                    "Close",
                                   "Exit             | Ctrl-E"};
    static char *menuListHelp[] = {"Help",
                                   "Show More  | Ctrl-M",
                                   "About"};
    static char *selectedLabel = NULL;

    double fH = GetFontHeight ();
    double x = 0; //fH/8;
    double y = win_height;
    double h = fH * 1.5; // �ؼ��߶�
//    double w = TextStringWidth (menuListHelp[0]) * 2; // �ؼ����
    double w = win_width / 2;
//    double wlist = TextStringWidth (menuListHelp[0]) * 1.2;
    double wlist = w;
    double xindent = win_height / 20; // ����
    int selection;

    // File �˵�
    selection = menuList (GenUIID(0), x,
                          y - h, w, wlist, h, menuListFile, sizeof (menuListFile) / sizeof (menuListFile[0]));
    if (selection > 0) selectedLabel = menuListFile[selection];
    if (selection == 1)
        WinExec ("leaderboard.exe", SW_SHOW);
    if (selection == 2)
    {
        MessageBoxA (NULL, "Thanks for playing!", "Bye", MB_ICONINFORMATION);
        exit (-1); // choose to exit
    }



    // Help �˵�
    menuListHelp[1] = show_more_buttons ? "Show Less | Ctrl-M" : "Show More | Ctrl-M";
    selection = menuList (GenUIID(0),
                          x + w,
                          y - h, w, wlist, h, menuListHelp, sizeof (menuListHelp) / sizeof (menuListHelp[0]));
    if (selection > 0) selectedLabel = menuListHelp[selection];
    if (selection == 1)
        show_more_buttons = !show_more_buttons;
    if (selection == 2)
        MessageBoxA (NULL, "�������ǵĴ���ҵ��", "���� | About", MB_ICONINFORMATION);
}

void display ()
{
    // ����
    RefreshDisplay ();
    // ���ƺʹ���˵�
    DrawMenu ();
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
//    printf("%s\n", GetFont ());
    SetFont ("΢���ź�");
    SetPointSize (64);
    MovePen (win_width / 2 - TextStringWidth (title_str) / 2, win_height / 2 + 1);
    DrawTextString (title_str);
    SetPointSize (13);
}

void drawButtons ()
{
    double fH = GetFontHeight ();
    double h = fH * 2;  // �ؼ��߶�
    double x = win_width / 2.5;
    double y = win_height / 2 - h;
    double w = win_width / 5; // �ؼ����

    x = win_width / 2 - 1;
    y = win_height / 2 - 0.6;
    setButtonColors ("Black", "White", "Gray", "White", 1);
    if (button (GenUIID(0), x, y, 2, 1.2, "Single Mode")) {
        WinExec ("single_main.exe", SW_SHOW);
        exit (0);
    }
    if (button (GenUIID(0), x, y - 0.8, 2, 0.6, "Leader Board")) {
        WinExec ("leaderboard.exe", SW_SHOW);
    }

}