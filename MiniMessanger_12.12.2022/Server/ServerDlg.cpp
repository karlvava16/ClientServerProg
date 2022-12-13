#include "ServerDlg.h"

ServerDlg* ServerDlg::ptr = NULL;


ServerDlg::ServerDlg(void)
{
	ptr = this;
}

ServerDlg::~ServerDlg(void)
{
}

void ServerDlg::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, IDCANCEL);
}

BOOL ServerDlg::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	//set HWND for main dialog
	hDialog = hwnd;
	hMessages = GetDlgItem(hwnd, IDC_MESSAGES);
	hEnter = GetDlgItem(hwnd, IDC_ENTER);
	hStart = GetDlgItem(hwnd, IDC_START);
	hStop = GetDlgItem(hwnd, IDC_STOP);
	hSend = GetDlgItem(hwnd, IDC_SEND);

	return TRUE;
}

DWORD WINAPI ServerDlg::GetMessages()
{
	server.ReceiveData();
}


void ServerDlg::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if (id == IDC_START)
	{
		if (!server.StartHosting(20000))
		{
			SetWindowText(hMessages, NULL);
			EnableWindow(hStart, FALSE);
			EnableWindow(hSend, TRUE);
			EnableWindow(hEnter, TRUE);
			EnableWindow(hStop, TRUE);
		}
		CreateThread(NULL, 0, , this, 0, NULL);
	}
	if (id == IDC_STOP)
	{
		server.CloseConnection();
		EnableWindow(hStart, TRUE);
		EnableWindow(hSend, FALSE);
		EnableWindow(hEnter, FALSE);
		EnableWindow(hStop, FALSE);
	}
}

BOOL CALLBACK ServerDlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}
