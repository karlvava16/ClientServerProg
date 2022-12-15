#include "ClientDlg.h"

ClientDlg* ClientDlg::ptr = NULL;


ClientDlg::ClientDlg(void)
{
	ptr = this;
}

ClientDlg::~ClientDlg(void)
{
	closesocket(_socket);
	WSACleanup();
}

void ClientDlg::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

BOOL ClientDlg::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	hMessages = GetDlgItem(hwnd, IDC_MESSAGES);
	hEnter = GetDlgItem(hwnd, IDC_ENTER);
	hConnect = GetDlgItem(hwnd, IDC_CONNECT);
	hEnterIp = GetDlgItem(hwnd, IDC_IP);
	return TRUE;
}



void ClientDlg::OutputMessages()
{
	TCHAR buff[256];

	mbstowcs(buff, clientBuffer, 256);

	SendMessage(hMessages, LB_ADDSTRING, 0, LPARAM(buff));

}

DWORD WINAPI GetM(LPVOID lp)
{
	ClientDlg* p = (ClientDlg*)lp;

	while (true) {
		int i = recv(p->_socket, p->clientBuffer, MAXSTRLEN, 0);
		p->clientBuffer[i + 2] = '\0';
		p->clientBuffer[i] = '-';
		p->clientBuffer[i + 1] = 'S';
		p->OutputMessages();
	}
	return 0;
}


void ClientDlg::Send()
{
	send(_socket, clientBuffer, strlen(clientBuffer), 0);
	OutputMessages();

}


void ClientDlg::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if (id == IDC_CONNECT)
	{
		TCHAR buffer[MAXSTRLEN];
		GetWindowText(hEnterIp, buffer, MAXSTRLEN);
		char buffer2[MAXSTRLEN];
		size_t outputSize = wcslen(buffer) + 1;
		wcstombs(buffer2, buffer, MAXSTRLEN);


		WSAStartup(MAKEWORD(2, 2), &wsaData);
		
		_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		
		addr.sin_family = AF_INET;
		
		inet_pton(AF_INET, buffer2, &addr.sin_addr);
		
		addr.sin_port = htons(20000);
		
		connect(_socket, (SOCKADDR*)&addr, sizeof(addr));
		CreateThread(NULL, 0, GetM, this, 0, NULL);

	}
	else if (id == IDC_SEND)
	{
		TCHAR buffer[256];
		GetWindowText(hMessages, buffer, 256);


		wcstombs(clientBuffer, buffer, 256);

		Send();
	}
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