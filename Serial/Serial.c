#include "Serial.h"
#include <Windows.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#include "graphics.h"

#include "handlers.h"

HANDLE hCom;

void ReadSerial ();

void InitSerial ()
{
    hCom = CreateFile (TEXT("com4"),//COM1��
                       GENERIC_READ, //�����
                       0, //ָ���������ԣ����ڴ��ڲ��ܹ������Ըò�������Ϊ0
                       NULL,
                       OPEN_EXISTING, //�򿪶����Ǵ���

                       FILE_ATTRIBUTE_NORMAL, //������������ֵΪFILE_FLAG_OVERLAPPED����ʾʹ���첽I/O���ò���Ϊ0����ʾͬ��I/O����
                       NULL);

    if (hCom == INVALID_HANDLE_VALUE) {
        printf ("Open COM Failed!\n");
        return;
    } else {
        printf ("Open COM Succeed!\n");
    }

    SetupComm (hCom, 1024, 1024); //���뻺����������������Ĵ�С����1024

    /*********************************��ʱ����**************************************/
    COMMTIMEOUTS TimeOuts;
    //�趨����ʱ
    TimeOuts.ReadIntervalTimeout = MAXDWORD;//�������ʱ
    TimeOuts.ReadTotalTimeoutMultiplier = 0;//��ʱ��ϵ��
    TimeOuts.ReadTotalTimeoutConstant = 0;//��ʱ�䳣��
    //�趨д��ʱ
    TimeOuts.WriteTotalTimeoutMultiplier = 1;//дʱ��ϵ��
    TimeOuts.WriteTotalTimeoutConstant = 1;//дʱ�䳣��
    SetCommTimeouts (hCom, &TimeOuts); //���ó�ʱ

    /*****************************************���ô���***************************/
    DCB dcb;
    GetCommState (hCom, &dcb);
    dcb.BaudRate = 9600; //������Ϊ9600
    dcb.ByteSize = 8; //ÿ���ֽ���8λ
    dcb.Parity = NOPARITY; //����żУ��λ
    dcb.StopBits = ONESTOPBIT; //һ��ֹͣλ
    SetCommState (hCom, &dcb);
}

DWORD WINAPI Serial_Func (LPVOID lpParam)
{
    ReadSerial ();
}

void Serial_Background ()
{
    CreateThread (
        NULL,   // default security attributes
        0, // use default stack size
        Serial_Func, // thread function
        NULL,// argument to thread function
        0, // use default creation flags
        NULL);// returns the thread identifier
}

void ReadSerial ()
{
    DWORD wCount;//ʵ�ʶ�ȡ���ֽ���
    bool bReadStat;
    static int cnt[4];

    char str[2] = {0};

    while (1) {
        // PurgeComm(hCom, PURGE_TXCLEAR | PURGE_RXCLEAR); //��ջ�����
        bReadStat = ReadFile (hCom, str, sizeof (str), &wCount, NULL);

        if (!bReadStat) {
            printf ("Read error!");
            return;
        } else {
            //str[1] = '\0';
            if (isalpha (str[0])) {
                printf ("%c\n", str[0]);
                switch (str[0]) {
                    case 'I'://up
                        keyboardEventHandler (VK_UP, KEY_DOWN);
                        break;
                    case 'J'://down
                        keyboardEventHandler (VK_SPACE, KEY_DOWN);
                        break;
                    case 'K'://left
                        keyboardEventHandler (VK_LEFT, KEY_DOWN);
                        break;
                    case 'L'://right
                        keyboardEventHandler (VK_RIGHT, KEY_DOWN);
                        break;
                    case 'A':
                        cnt[0] ++;
                        if (cnt[0] == 3)
                        {
                            cnt[0] = 0;
                            keyboardEventHandler (VK_UP, KEY_DOWN);
                        }
                        break;
                    case 'B':
                        cnt[1] ++;
                        if (cnt[1] == 3)
                        {
                            cnt[1] = 0;
                            keyboardEventHandler (VK_SPACE, KEY_DOWN);
                        }
                        break;
                    case 'C':
                        cnt[2] ++;
                        if (cnt[2] == 3)
                        {
                            cnt[2] = 0;
                            keyboardEventHandler (VK_LEFT, KEY_DOWN);
                        }
                        break;
                    case 'D':
                        cnt[3] ++;
                        if (cnt[3] == 3)
                        {
                            cnt[3] = 0;
                            keyboardEventHandler (VK_RIGHT, KEY_DOWN);
                        }
                        break;

                }
            }
        }
//        Sleep(1);
    }
}