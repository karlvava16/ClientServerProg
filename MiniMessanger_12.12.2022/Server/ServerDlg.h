#pragma once
#include "Headers.h"

class ServerDlg
{
public:
	ServerDlg(void);
public:
	~ServerDlg(void);
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static ServerDlg* ptr;
	void Cls_OnClose(HWND hwnd);
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	void Send();
	void OutputMessage();

	HWND hStart, hStop, hSend;
	HWND hEnter, hMessages;

	char serverBuffer[MAXSTRLEN];

	WSADATA wsaData;
	SOCKET _socket;
	SOCKET acceptSocket;
	sockaddr_in addr;


};