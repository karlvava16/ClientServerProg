#include "ServerDlg.h"

ServerDlg* ServerDlg::ptr = NULL;


ServerDlg::ServerDlg(void)
{
	ptr = this;
}

ServerDlg::~ServerDlg(void)
{
	closesocket(acceptSocket);
	closesocket(_socket);
	WSACleanup();
}

void ServerDlg::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

BOOL ServerDlg::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	hMessages = GetDlgItem(hwnd, IDC_MESSAGES);
	hStart = GetDlgItem(hwnd, IDC_START);
	hEnter = GetDlgItem(hwnd, IDC_ENTER);
	return TRUE;
}


void ServerDlg::OutputMessage()
{
	TCHAR buff[258];

	mbstowcs(buff, serverBuffer, MAXSTRLEN);


	SendMessage(hMessages, LB_ADDSTRING, 0, LPARAM(buff));

}
void ServerDlg::Send()
{


	send(acceptSocket, serverBuffer, strlen(serverBuffer), 0);

	OutputMessage();
}

DWORD WINAPI GetM(LPVOID lp)
{
	ServerDlg* p = (ServerDlg*)lp;
	while (true) {

		int i = recv(p->acceptSocket, p->serverBuffer, MAXSTRLEN, 0);
		p->serverBuffer[i] = '-';
		p->serverBuffer[i + 1] = 'C';
		p->serverBuffer[i + 2] = '\0';

		p->OutputMessage();
	}
	return 0;
}


void ServerDlg::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if (id == IDC_START)
	{
		WSAStartup(MAKEWORD(2, 2), &wsaData);
		_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		addr.sin_family = AF_INET;

		inet_pton(AF_INET, "0.0.0.0", &addr.sin_addr);
		



		addr.sin_port = htons(20000);
		
		bind(_socket, (SOCKADDR*)&addr, sizeof(addr));
		
		listen(_socket, 1);


		EnableWindow(hStart, FALSE);
		
		acceptSocket = accept(_socket, NULL, NULL);
		CreateThread(NULL, 0, GetM, this, 0, NULL);
		
	}
	else if (id == IDC_SEND)
	{
		TCHAR buff[MAXSTRLEN];
		GetWindowText(hMessages, buff, MAXSTRLEN);

		size_t outputSize = wcslen(buff) + 1;
		wcstombs(serverBuffer, buff, MAXSTRLEN);

		Send();
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