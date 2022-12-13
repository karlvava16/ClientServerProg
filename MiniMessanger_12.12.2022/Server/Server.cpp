#include "Server.h"

Server::Server()
{
	//���� ������������� ������� ������ ���������, ������� ��������� ��
	//������
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR)
	{
		MessageBox(0, TEXT("error"), TEXT("WSAStartup error"), MB_OK || MB_ICONERROR);
		WSACleanup();
		exit(10);
	}

	//������� ��������� �����, �������� TCP
	_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	//��� ���������� �������� ������ ������� ��������� �� ������
	if (_socket == INVALID_SOCKET)
	{
		MessageBox(0, TEXT("error"), TEXT("Server create error"), MB_OK || MB_ICONERROR);
		WSACleanup();
		exit(11);
	}
}

Server::~Server()
{
	WSACleanup();//������� �������
}

bool Server::SendData(char* buffer)
{
	/*���������� ��������� �� ��������� �����*/
	send(_socket, buffer, strlen(buffer), 0);
	return true;
}

bool Server::ReceiveData(char* buffer, int size)
{
	/*�������� ��������� � ��������� ��� � ������.
	����� �������� �����������!*/
	int i = recv(_socket, buffer, size, 0);
	buffer[i] = '\0';
	return true;
}

void Server::CloseConnection()
{
	//��������� �����
	closesocket(_socket);
}

bool Server::StartHosting(int port)
{
	Bind(port);
	Listen();
}

bool Server::Listen()
{
	//��� ������ ��������� ������ � ������ �������������
	//������� ������
	if (listen(_socket, 1) == SOCKET_ERROR)
	{
		MessageBox(0, TEXT("error"), TEXT("Server activate error"), MB_OK || MB_ICONERROR);
		WSACleanup();
		exit(15);
		return false;
	}
	/*
	����� �������� �����������. ������� ����������� �������.
	��� ������ ������ �����������, ������� accept ����������
	����� �����, ����� ������� ���������� ����� �������.
	*/
	acceptSocket = accept(_socket, NULL, NULL);
	while (acceptSocket == SOCKET_ERROR)
	{
		acceptSocket = accept(_socket, NULL, NULL);
	}
	_socket = acceptSocket;
	return true;
}

bool Server::Bind(int port)
{
	//��������� ��������� ������� IPv4
	addr.sin_family = AF_INET;
	/*����������� ����� "0.0.0.0"� ����������
	��������� �������� �������, ��������� ��������� � ���� sin_addr */
	inet_pton(AF_INET, "0.0.0.0", &addr.sin_addr);
	//��������� ����. 
	//������� htons ��������� �������������� ����� �
	//������� ������� ����
	addr.sin_port = htons(port);

	//��� ��������� �������� � �����, ������� ��������� ��� ������
	if (bind(_socket, (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR)
	{
		MessageBox(0, TEXT("error"), TEXT("Failed to bind to port"), MB_OK || MB_ICONERROR);

		WSACleanup();
		exit(14);
		return false;
	}
	return true;
}
