#pragma once
#include "Headers.h"

const int MAXSTRLEN = 255;

class Server
{
protected:
	WSADATA wsaData;//��������� ��� �������� ���������� � ������������� �������
	SOCKET _socket; //���������� ���������� ������
	SOCKET acceptSocket;//���������� ������, ������� ������ � �������� 
	sockaddr_in addr; //��������� ����� � ����
public:
	Server();
	~Server();
	bool SendData(char*); //����� ��� �������� ������ � ����
	bool ReceiveData(char*, int);//����� ��� ��������� ������
	void CloseConnection(); //����� ��� �������� ����������
	bool Listen(); //����� ��� ��������� "����������" ������
	bool Bind(int port); //����� ��� �������� ������ � �����
	bool StartHosting(int port); //���������� ����� ���� ���������� �������
};


