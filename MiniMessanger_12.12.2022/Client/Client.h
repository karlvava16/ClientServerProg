#pragma once
#include "Headers.h"

const int MAXSTRLEN = 255;

class Client
{
protected:
	WSADATA wsaData; //��������� ��� �������� ���������� � ������������� �������
	SOCKET _socket; //���������� ���������� ������
	SOCKET acceptSocket; //���������� ������, ������� ������ � �������� 
	sockaddr_in addr; //��������� ����� � ����
public:
	Client();
	~Client();
	bool SendData(char*); //����� ��� �������� ������ � ����
	bool ReceiveData(char*, int); //����� ��� ��������� ������
	void CloseConnection(); //����� ��� �������� ����������
	void ConnectToServer(const char* ip, int port); //����� ��� ����������� � �������

};