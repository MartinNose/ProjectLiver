/*
 * This file is used to test the sound module
 */
#include "sound.h"

#include <windows.h>

#include <stdio.h>
#include <time.h>

int main ()
{
    Play_Sound_Demo (); // ���̣߳���������������
    Play_Sound (); // ���̣߳�ͬʱ����ִ�к����printf()
//    Play_Sound_Demo (); // ���̣߳���������������
//    PlaySound(NULL,NULL,SND_FILENAME); // ����ֹͣ���ŵ�����
    while (1)
        printf ("233\n");
}
