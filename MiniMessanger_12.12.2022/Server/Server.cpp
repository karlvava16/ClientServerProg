#include "Server.h"

Server::Server()
{
	//если инициализация сокетов прошла неуспешно, выводим сообщение об
	//ошибке
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR)
	{
		MessageBox(0, TEXT("error"), TEXT("WSAStartup error"), MB_OK || MB_ICONERROR);
		WSACleanup();
		exit(10);
	}

	//создаем потоковый сокет, протокол TCP
	_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	//при неуспешном создании сокета выводим сообщение об ошибке
	if (_socket == INVALID_SOCKET)
	{
		MessageBox(0, TEXT("error"), TEXT("Server create error"), MB_OK || MB_ICONERROR);
		WSACleanup();
		exit(11);
	}
}

Server::~Server()
{
	WSACleanup();//очищаем ресурсы
}

bool Server::SendData(char* buffer)
{
	/*Отправляем сообщение на указанный сокет*/
	send(_socket, buffer, strlen(buffer), 0);
	return true;
}

bool Server::ReceiveData(char* buffer, int size)
{
	/*Получаем сообщение и сохраняем его в буфере.
	Метод является блокирующим!*/
	int i = recv(_socket, buffer, size, 0);
	buffer[i] = '\0';
	return true;
}

void Server::CloseConnection()
{
	//Закрываем сокет
	closesocket(_socket);
}

bool Server::StartHosting(int port)
{
	Bind(port);
	Listen();
}

bool Server::Listen()
{
	//При ошибке активации сокета в режиме прослушивания
	//выводим ошибку
	if (listen(_socket, 1) == SOCKET_ERROR)
	{
		MessageBox(0, TEXT("error"), TEXT("Server activate error"), MB_OK || MB_ICONERROR);
		WSACleanup();
		exit(15);
		return false;
	}
	/*
	Метод является блокирующим. Ожидаем подключение клиента.
	Как только клиент подключился, функция accept возвращает
	новый сокет, через который происходит обмен данными.
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
	//Указываем семейство адресов IPv4
	addr.sin_family = AF_INET;
	/*Преобразуем адрес "0.0.0.0"в правильную
	структуру хранения адресов, результат сохраняем в поле sin_addr */
	inet_pton(AF_INET, "0.0.0.0", &addr.sin_addr);
	//Указываем порт. 
	//Функиця htons выполняет преобразование числа в
	//сетевой порядок байт
	addr.sin_port = htons(port);

	//При неудачном биндинге к порту, выводим сообщение про ошибку
	if (bind(_socket, (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR)
	{
		MessageBox(0, TEXT("error"), TEXT("Failed to bind to port"), MB_OK || MB_ICONERROR);

		WSACleanup();
		exit(14);
		return false;
	}
	return true;
}
