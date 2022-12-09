//Main.cpp
#include <iostream>
#include "Socket.h"

using namespace std;

int main()
{
	setlocale(0, "");
	int nChoice;
	int port = 24242; //�������� ����
	string ipAddress; //����� �������
	char receiveMessage[MAXSTRLEN] = "";
	char sendMessage[MAXSTRLEN] = "";

	int steps = 0;
	int amount = 0;

	cout << "1) Start server" << endl;
	cout << "2) Connect to server" << endl;
	cout << "3) Exit" << endl;
	cin >> nChoice;
	if (nChoice == 1)
	{
		ServerSocket server;
		cout << "Starting server..." << endl;
		//��������� ������
		server.StartHosting(port);

		while (steps < 3)
		{
			if (steps == 0)
			{
				server.SendData("1. ������� - 7800���\n2. ������� - 26000���\n3.������� - 9000���\n������� ����� ������: ");
				server.ReceiveData(receiveMessage, MAXSTRLEN);
				cout << receiveMessage << endl;
				if (strcmp(receiveMessage, "1") == 0)
				{
					nChoice = 1;
				}
				else if (strcmp(receiveMessage, "2") == 0)
				{
					nChoice = 2;
				}
				else if (strcmp(receiveMessage, "3") == 0)
				{
					nChoice = 3;
				}
				else
				{
					server.SendData("�������� ����\n\n");
				}
				steps++;
			}
			else if (steps == 1)
			{
				server.SendData("������� ���-�� �������: ");
				server.ReceiveData(receiveMessage, MAXSTRLEN);
				cout << receiveMessage << endl;
				amount = 2;

				if (nChoice == 1)
				{
					sprintf_s(sendMessage, "���������: %d��� \n", 7800 * amount);

					server.SendData(sendMessage);
					server.SendData("\n");
				}
				else if (nChoice == 2)
				{
					sprintf_s(sendMessage, "���������: %d��� \n", 26000 * amount);
					server.SendData(sendMessage);
					server.SendData("\n");
				}
				else if (nChoice == 3)
				{
					sprintf_s(sendMessage, "���������: %d��� \n", 9000 * amount);
					server.SendData(sendMessage);
					server.SendData("\n");
				}
				steps++;
			}
			else if (steps == 2)
			{
				server.ReceiveData(receiveMessage, MAXSTRLEN);
				cin.get();
				cout << receiveMessage << endl;
				strcpy_s(sendMessage, MAXSTRLEN, "end");
				server.SendData(sendMessage);
			}
			if (strcmp(receiveMessage, "end") == 0 ||
				strcmp(sendMessage, "end") == 0)
				break;
		}
		
	}
	else if (nChoice == 2)
	{
		cout << "Enter an IP address: " << endl;
		//����������� IP �������
		cin >> ipAddress;
		ClientSocket client;
		//������������ � �������
		client.ConnectToServer(ipAddress.c_str(), port);
		while (true)
		{
			client.ReceiveData(receiveMessage, MAXSTRLEN);
			cout << receiveMessage << endl;
			client.SendDataMessage();
			if (strcmp(receiveMessage, "end") == 0 ||
				strcmp(sendMessage, "end") == 0)
				break;
		}
		//��������� ����������
		client.CloseConnection();
	}
	else if (nChoice == 3)
		return 0;
}
