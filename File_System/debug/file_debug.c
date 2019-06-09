/*
 * This file is used to test the file module
 */

#include "file_system_linked_list.h"
#include "file_system_username_cache.h"

#include <Windows.h>
#include <CommDlg.h>

static OPENFILENAME ofn;

void PopFileInitialize (HWND hwnd)
{
    static TCHAR szFilter[] = TEXT ("Tetris Game File (*.tetris_game)\0*.tetris_game\0\0");

    ofn.lStructSize       = sizeof (OPENFILENAME) ;
    ofn.hwndOwner         = hwnd ;
    ofn.hInstance         = NULL ;
    ofn.lpstrFilter       = szFilter ;
    ofn.lpstrCustomFilter = NULL ;
    ofn.nMaxCustFilter    = 0 ;
    ofn.nFilterIndex      = 0 ;
    ofn.lpstrFile         = NULL ;          // Set in Open and Close functions
    ofn.nMaxFile          = MAX_PATH ;
    ofn.lpstrFileTitle    = NULL ;          // Set in Open and Close functions
    ofn.nMaxFileTitle     = MAX_PATH ;
    ofn.lpstrInitialDir   = NULL ;
    ofn.lpstrTitle        = NULL ;
    ofn.Flags             = 0 ;             // Set in Open and Close functions
    ofn.nFileOffset       = 0 ;
    ofn.nFileExtension    = 0 ;
    ofn.lpstrDefExt       = TEXT ("jpg") ;
    ofn.lCustData         = 0L ;
    ofn.lpfnHook          = NULL ;
    ofn.lpTemplateName    = NULL ;
}

BOOL PopFileOpenDlg (HWND hwnd, PTSTR pstrFileName, PTSTR pstrTitleName)
{
    ofn.hwndOwner         = hwnd ;
    ofn.lpstrFile         = pstrFileName ;
    ofn.lpstrFileTitle    = pstrTitleName ;
    ofn.Flags             = OFN_HIDEREADONLY | OFN_CREATEPROMPT ;

    return GetOpenFileName (&ofn) ;
}

BOOL PopFileSaveDlg (HWND hwnd, PTSTR pstrFileName, PTSTR pstrTitleName)
{
    ofn.hwndOwner         = hwnd ;
    ofn.lpstrFile         = pstrFileName ;
    ofn.lpstrFileTitle    = pstrTitleName ;
    ofn.Flags             = OFN_HIDEREADONLY | OFN_CREATEPROMPT ;

    return GetSaveFileName (&ofn) ;
}

int main()
{
    static TCHAR     szFileName[MAX_PATH], szTitleName[MAX_PATH] ;
    HWND      hwnd;
    hwnd=GetForegroundWindow(); //��ȡǰ̨���ھ�����������е�ǰ̨���ھ��ǿ���̨���ڡ�
    PopFileInitialize (hwnd);  //��ʼ��ofn
    PopFileOpenDlg(hwnd, szFileName, szTitleName);//���ļ��Ի���
    printf("%s\n",szFileName);  //�ڿ���̨����ʾѡ���ļ���·��
    PopFileSaveDlg(hwnd, szFileName, szTitleName);
    printf("%s\n",szFileName);  //�ڿ���̨����ʾѡ���ļ���·��
    return 0;
}

//
//int main ()
//{
//
////    userNode *rank_list;
////    rank_list = Load_Rank ();
////    rank_list = Add_Node (rank_list, 996, "007");
////    Write_Rank (rank_list);
//
////    Save_Username ("test");
////    printf ("%s\n", Load_Last_Username ());
//    return 0;
//}