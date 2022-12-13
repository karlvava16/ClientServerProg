#pragma once
#include "Client.h"

struct ClientDlg
{
	Client client;
	static ClientDlg* ptr;
	ClientDlg(void);
	~ClientDlg(void);
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	void Cls_OnClose(HWND hwnd);
	HWND hDialog, hMessages, hEnter, hConnect, hDisconnect, hSend;
};

