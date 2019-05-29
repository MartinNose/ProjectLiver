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

// ȫ�ֱ���
static double winwidth, winheight;   // ���ڳߴ�
static int enable_rotation = 1;   // ������ת
static int show_more_buttons = 0; // ��ʾ���ఴť

static bool isDisplayMenu = FALSE;

// ����������provided in libgraphics
void DisplayClear (void);

// �û�����ʾ����
void display (void);

void DrawBasic ();
void RefreshDisplay();

void drawButtons();

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
    else
    {
        RefreshDisplay();
    }
}

// �û�������¼���Ӧ����
void MouseEventProcess (int x, int y, int button, int event)
{
    uiGetMouse (x, y, button, event); //GUI��ȡ���
    if (isDisplayMenu) {
        display (); // ˢ����ʾ
    } else {
        RefreshDisplay();
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
    winwidth = GetWindowWidth ();
    winheight = GetWindowHeight ();

    setMenuColors("Black", "White", "Gray", "White", 1);

    // ע��ʱ����Ӧ����
    registerKeyboardEvent (KeyboardEventProcess);// ����
    registerMouseEvent (MouseEventProcess);      // ���


    DrawBasic ();
    // �򿪿���̨���������������Ϣ�����ڵ���
    // InitConsole();
    PlaySound("C:\\Users\\Tao Chiang\\Desktop\\Skyworld.wav", NULL, SND_FILENAME | SND_ASYNC);
}

// �˵���ʾ����
void drawMenu ()
{
    static char *menuListFile[] = {"File",
                                   "Leader Board  | Ctrl-B", // ��ݼ��������[Ctrl-X]��ʽ�������ַ����Ľ�β
//                                    "Close",
                                   "Exit             | Ctrl-E"};
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
        WinExec("leaderboard.exe", SW_SHOW);
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
//    SetPenColor ("Black");
//    DrawLine (1,1);
    SetFont ("΢���ź�");
    drawButtons ();
    SetPenColor ("Black");
//    printf("%s\n", GetFont ());
    SetFont ("΢���ź�");
    SetPointSize(64);
    MovePen (winwidth/2 - TextStringWidth("Teris")/2, winheight/2 + 1);
    DrawTextString ("Teris");
    SetPointSize (13);
}

void drawButtons()
{
    double fH = GetFontHeight();
    double h = fH*2;  // �ؼ��߶�
    double x = winwidth/2.5;
    double y = winheight/2-h;
    double w = winwidth/5; // �ؼ����
//
//    if (button(GenUIID(0), x, y, w, h, show_more_buttons ? "Show Less Buttons" : "Show More Buttons"))
//        show_more_buttons = ! show_more_buttons;
//
//    if( show_more_buttons ) {
//        int k;
//        for( k = 0; k<3; k++ ) {
//            char name[128]; sprintf(name, "Button Array %d", k);
//            // use GenUIID(k) to have different ID for multiple buttons by the same code
//            button(GenUIID(k), x + w*1.2, y - k*h*2, w, h, name);
//        }
//    }

    x = winwidth / 2 - 1;
    y = winheight / 2 - 0.6;
    setButtonColors("Black", "White", "Gray", "White", 1);
    if (button(GenUIID(0), x, y, 2, 1.2, "Single Mode"))
    {
        WinExec("single_main.exe", SW_SHOW);
    }
    if (button(GenUIID(0), x, y - 0.8, 2, 0.6, "Leader Board"))
    {
        WinExec("leaderboard.exe", SW_SHOW);
    }

}