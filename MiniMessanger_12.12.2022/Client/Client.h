#pragma once
#include "Headers.h"

const int MAXSTRLEN = 255;

class Client
{
protected:
	WSADATA wsaData; //структура для хранения информации о инициализации сокетов
	SOCKET _socket; //дескриптор слушающего сокета
	SOCKET acceptSocket; //дескриптор сокета, который связан с клиентом 
	sockaddr_in addr; //локальный адрес и порт
public:
	Client();
	~Client();
	bool SendData(char*); //метод для отправки данных в сеть
	bool ReceiveData(char*, int); //метод для получения данных
	void CloseConnection(); //метод для закрытия соединения
	void ConnectToServer(const char* ip, int port); //метод для подключения к серверу

};