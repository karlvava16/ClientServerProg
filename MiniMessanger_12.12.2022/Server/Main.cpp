#include "ServerDlg.h"

int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR lpszCmdLine, int nCmdShow)
{
	ServerDlg dlg;
	return DialogBox(hInst, MAKEINTRESOURCE(IDD_SERVER), NULL, ServerDlg::DlgProc);
}