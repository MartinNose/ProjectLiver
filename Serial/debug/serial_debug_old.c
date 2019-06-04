#include <windows.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

HANDLE hCom;

int main(void)
{
    hCom = CreateFile(TEXT("com4"),//COM1��
                      GENERIC_READ, //�����
                      0, //ָ���������ԣ����ڴ��ڲ��ܹ������Ըò�������Ϊ0
                      NULL,
                      OPEN_EXISTING, //�򿪶����Ǵ���

                      FILE_ATTRIBUTE_NORMAL, //������������ֵΪFILE_FLAG_OVERLAPPED����ʾʹ���첽I/O���ò���Ϊ0����ʾͬ��I/O����
                      NULL);

    if (hCom == INVALID_HANDLE_VALUE)
    {
        printf("��COMʧ��!\n");
        return FALSE;
    }
    else
    {
        printf("COM�򿪳ɹ���\n");
    }

    SetupComm(hCom, 1024, 1024); //���뻺����������������Ĵ�С����1024

    /*********************************��ʱ����**************************************/
    COMMTIMEOUTS TimeOuts;
    //�趨����ʱ
    TimeOuts.ReadIntervalTimeout = MAXDWORD;//�������ʱ
    TimeOuts.ReadTotalTimeoutMultiplier = 0;//��ʱ��ϵ��
    TimeOuts.ReadTotalTimeoutConstant = 0;//��ʱ�䳣��
    //�趨д��ʱ
    TimeOuts.WriteTotalTimeoutMultiplier = 1;//дʱ��ϵ��
    TimeOuts.WriteTotalTimeoutConstant = 1;//дʱ�䳣��
    SetCommTimeouts(hCom, &TimeOuts); //���ó�ʱ

    /*****************************************���ô���***************************/
    DCB dcb;
    GetCommState(hCom, &dcb);
    dcb.BaudRate = 9600; //������Ϊ9600
    dcb.ByteSize = 8; //ÿ���ֽ���8λ
    dcb.Parity = NOPARITY; //����żУ��λ
    dcb.StopBits = ONESTOPBIT; //һ��ֹͣλ
    SetCommState(hCom, &dcb);

    DWORD wCount;//ʵ�ʶ�ȡ���ֽ���
    bool bReadStat;

    char str[2] = { 0 };

    while (1)
    {
//         PurgeComm(hCom, PURGE_TXCLEAR | PURGE_RXCLEAR); //��ջ�����
        bReadStat = ReadFile(hCom, str, sizeof(str), &wCount, NULL);

        if (!bReadStat)
        {
            printf("������ʧ��!");
            return FALSE;
        }
        else
        {
            //str[1] = '\0';
            if (isalpha(str[0]))
                printf("%c\n", str[0]);
        }
//        Sleep(1);
    }

    CloseHandle(hCom);
}