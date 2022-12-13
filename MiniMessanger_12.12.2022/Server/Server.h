#pragma once
#include "Headers.h"

const int MAXSTRLEN = 255;

class Server
{
protected:
	WSADATA wsaData;//структура дл€ хранени€ информации о инициализации сокетов
	SOCKET _socket; //дескриптор слушающего сокета
	SOCKET acceptSocket;//дескриптор сокета, который св€зан с клиентом 
	sockaddr_in addr; //локальный адрес и порт
public:
	Server();
	~Server();
	bool SendData(char*); //метод дл€ отправки данных в сеть
	bool ReceiveData(char*, int);//метод дл€ получени€ данных
	void CloseConnection(); //метод дл€ закрыти€ соединени€
	bool Listen(); //метод дл€ активации "слушающего" сокета
	bool Bind(int port); //метод дл€ прив€зки сокета к порту
	bool StartHosting(int port); //объедин€ет вызов двух предыдущих методов
};


