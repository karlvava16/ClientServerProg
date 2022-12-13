#include "Client.h"

Client::Client()
{
	//���� ������������� ������� ������ ���������, ������� ��������� ��
	//������
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR)
	{
		cout << "WSAStartup error\n";
		system("pause");
		WSACleanup();
		exit(10);
	}

	//������� ��������� �����, �������� TCP
	_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	//��� ���������� �������� ������ ������� ��������� �� ������
	if (_socket == INVALID_SOCKET)
	{
		cout << "Client create error." << endl;	
		system("pause");
		WSACleanup();
		exit(11);
	}
}

Client::~Client()
{
	WSACleanup();//������� �������
}

bool Client::SendData(char* buffer)
{
	/*���������� ��������� �� ��������� �����*/
	send(_socket, buffer, strlen(buffer), 0);
	return true;
}

bool Client::ReceiveData(char* buffer, int size)
{

	/*�������� ��������� � ��������� ��� � ������.
	����� �������� �����������!*/
	int i = recv(_socket, buffer, size, 0);
	buffer[i] = '\0';
	return true;
}

void Client::CloseConnection()
{
	//��������� �����
	closesocket(_socket);
}


void Client::ConnectToServer(const char* ipAddress, int port)
{
	addr.sin_family = AF_INET;
	inet_pton(AF_INET, ipAddress, &addr.sin_addr);
	addr.sin_port = htons(port);
	//��� ��������� ����������� � ������� ������� ��������� ��� ������
	if (connect(_socket, (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR)
	{
		cout << "Failed to connect to server\n";
		system("pause");
		WSACleanup();
		exit(13);
	}
}