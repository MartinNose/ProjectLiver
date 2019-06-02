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

static bool isDisplayMenu = FALSE;

#define TIMER_BLINK10  1     /*10ms��ʱ���¼���־��*/
const int mseconds10 = 10;

// ����������provided in libgraphics
void DisplayClear (void);

// �û�����ʾ����
void display (void);

void DrawBasic ();
void RefreshDisplay ();

void drawButtons ();

void Refresh_Display_On_Timer ();

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
//    if (isDisplayMenu)
//        display (); // ˢ����ʾ
//    else {
//        RefreshDisplay ();
//    }
}

// �û�������¼���Ӧ����
void MouseEventProcess (int x, int y, int button, int event)
{
    uiGetMouse (x, y, button, event); //GUI��ȡ���
//    if (isDisplayMenu) {
//        display (); // ˢ����ʾ
//    } else {
//        RefreshDisplay ();
//    }
}

void TimerEventProcess (int timerID)
{
    switch (timerID) {
        case TIMER_BLINK10: { /*50ms�����˸��ʱ��*/
            Refresh_Display_On_Timer ();
            break;
        }
        default: break;
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

    setMenuColors ("Black", "White", "Gray", "White", 1);

    // ע��ʱ����Ӧ����
    registerKeyboardEvent (KeyboardEventProcess);// ����
    registerMouseEvent (MouseEventProcess);      // ���
    registerTimerEvent (TimerEventProcess);

    startTimer (TIMER_BLINK10, mseconds10);

    DrawBasic ();
    // �򿪿���̨���������������Ϣ�����ڵ���
    // InitConsole();
    PlaySound ("..\\Sound\\assets\\8bit.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

// �˵���ʾ����
void DrawMenu ()
{
    static char *menuListFile[] = {"File",
                                   "Leader Board  | Ctrl-B", // ��ݼ��������[Ctrl-X]��ʽ�������ַ����Ľ�β
//                                    "Close",
                                   "Exit             | Ctrl-E"};
    static char *menuListHelp[] = {"Help",
                                   "About"};
    static char *selectedLabel = NULL;

    double fH = GetFontHeight ();
    double x = 0; //fH/8;
    double y = GetWindowHeight ();
    double h = fH * 1.5; // �ؼ��߶�
//    double w = TextStringWidth (menuListHelp[0]) * 2; // �ؼ����
    double w = GetWindowWidth () / 2;
//    double wlist = TextStringWidth (menuListHelp[0]) * 1.2;
    double wlist = w;
    double xindent = GetWindowHeight () / 20; // ����
    int selection;

    // File �˵�
    selection = menuList (GenUIID(0), x,
                          y - h, w, wlist, h, menuListFile, sizeof (menuListFile) / sizeof (menuListFile[0]));
    if (selection > 0) selectedLabel = menuListFile[selection];
    if (selection == 1)
        WinExec ("leaderboard.exe", SW_SHOW);
    if (selection == 2) {
        MessageBoxA (NULL, "Thanks for playing!", "Bye", MB_ICONINFORMATION);
        exit (-1); // choose to exit
    }



    // Help �˵�
    selection = menuList (GenUIID(0),
                          x + w,
                          y - h, w, wlist, h, menuListHelp, sizeof (menuListHelp) / sizeof (menuListHelp[0]));
    if (selection > 0) selectedLabel = menuListHelp[selection];
    if (selection == 1)
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
    MovePen (GetWindowWidth () / 2 - TextStringWidth (title_str) / 2, GetWindowHeight () / 2 + 1);
    DrawTextString (title_str);
    SetPointSize (13);
}

void drawButtons ()
{
    double fH = GetFontHeight ();
    double h = fH * 2;  // �ؼ��߶�
    double x = GetWindowWidth () / 2.5;
    double y = GetWindowHeight () / 2 - h;
    double w = GetWindowWidth () / 5; // �ؼ����

    x = GetWindowWidth () / 2 - 1;
    y = GetWindowHeight () / 2 - 0.6;
    setButtonColors ("Black", "White", "Gray", "White", 1);
    if (button (GenUIID(0), x, y, 2, 1.2, "Single Mode")) {
        WinExec ("single_main.exe", SW_SHOW);
        exit (0);
    }
    if (button (GenUIID(0), x, y - 0.8, 2, 0.6, "Leader Board")) {
        WinExec ("leaderboard.exe", SW_SHOW);
    }

}

void Refresh_Display_On_Timer ()
{
    if (isDisplayMenu)
        display (); // ˢ����ʾ
    else {
        RefreshDisplay ();
    }
}