#include "Client.h"

Client::Client()
{
	//если инициализация сокетов прошла неуспешно, выводим сообщение об
	//ошибке
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR)
	{
		cout << "WSAStartup error\n";
		system("pause");
		WSACleanup();
		exit(10);
	}

	//создаем потоковый сокет, протокол TCP
	_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	//при неуспешном создании сокета выводим сообщение об ошибке
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
	WSACleanup();//очищаем ресурсы
}

bool Client::SendData(char* buffer)
{
	/*Отправляем сообщение на указанный сокет*/
	send(_socket, buffer, strlen(buffer), 0);
	return true;
}

bool Client::ReceiveData(char* buffer, int size)
{

	/*Получаем сообщение и сохраняем его в буфере.
	Метод является блокирующим!*/
	int i = recv(_socket, buffer, size, 0);
	buffer[i] = '\0';
	return true;
}

void Client::CloseConnection()
{
	//Закрываем сокет
	closesocket(_socket);
}


void Client::ConnectToServer(const char* ipAddress, int port)
{
	addr.sin_family = AF_INET;
	inet_pton(AF_INET, ipAddress, &addr.sin_addr);
	addr.sin_port = htons(port);
	//при неудачном подключении к серверу выводим сообщение про ошибку
	if (connect(_socket, (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR)
	{
		cout << "Failed to connect to server\n";
		system("pause");
		WSACleanup();
		exit(13);
	}
}