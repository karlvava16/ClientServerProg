#pragma once
#include "Headers.h"

class ClientDlg
{
public:
	char clientBuffer[MAXSTRLEN] = "";
	static ClientDlg* ptr;
	ClientDlg(void);
	~ClientDlg(void);
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	void Cls_OnClose(HWND hwnd);
	void OutputMessages();
	void Send();

	HWND hMessages, hEnter, hConnect, hDisconnect, hSend, hEnterIp;



	WSADATA wsaData;
	SOCKET _socket; 
	sockaddr_in addr;
};

