//
// Created by Tao Chiang on 5/28/2019.
//
#include "sound.h"

#include <windows.h>
#include "Mmsystem.h"

#include <stdio.h>
#include <time.h>

int main ()
{
    Play_Sound_Demo (); // ���̣߳���������������
    Play_Sound(); // ���̣߳�ͬʱ����ִ�к����printf()
    PlaySound("C:\\Users\\87547\\Documents\\Tencent Files\\875477433\\FileRecv\\res\\5980.wav", NULL, SND_FILENAME | SND_ASYNC);
    Play_Sound_Demo (); // ���̣߳���������������
    PlaySound(NULL,NULL,SND_FILENAME); // ����ֹͣ���ŵ�����
    while(1)
        printf ("233\n");
}
