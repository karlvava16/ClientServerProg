#include "ClientDlg.h"

ClientDlg* ClientDlg::ptr = NULL;


ClientDlg::ClientDlg(void)
{
	ptr = this;
}

ClientDlg::~ClientDlg(void)
{

}

void ClientDlg::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, IDCANCEL);
}

BOOL ClientDlg::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	//set HWND for main dialog
	hDialog = hwnd;
	hMessages = GetDlgItem(hwnd, IDC_MESSAGES);
	hEnter = GetDlgItem(hwnd, IDC_ENTER);
	hConnect = GetDlgItem(hwnd, IDC_CONNECT);
	hDisconnect = GetDlgItem(hwnd, IDC_DISCONNECT);
	hSend = GetDlgItem(hwnd, IDC_SEND);

	return TRUE;
}


void ClientDlg::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{

}

BOOL CALLBACK ClientDlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}
