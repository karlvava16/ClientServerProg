#pragma once
#include "Server.h"

struct ServerDlg
{
	char receiveMessage[MAXSTRLEN];
	char sendMessage[MAXSTRLEN];

	Server server;
	static ServerDlg* ptr;
	ServerDlg(void);
	~ServerDlg(void);
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	void Cls_OnClose(HWND hwnd);
	DWORD WINAPI GetMessages();

	HWND hDialog, hMessages, hEnter, hStart, hStop, hSend;
};									

