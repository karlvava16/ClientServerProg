
#define WIN32_LEAN_AND_MEAN

#include <ws2tcpip.h>
#include <windows.h>
#include <iostream>
#include <string>
using namespace std;

#pragma comment (lib, "Ws2_32.lib")

#define DEFAULT_BUFLEN 4096

#define DEFAULT_PORT "8888"

SOCKET client_socket;

string nickname;
char color;



void SetConsoleText(int color)
{
    
}

DWORD WINAPI Sender(void* param)
{
    string query = "";


    while (true) {
        //cout << "Please insert your query for server: ";
        //cin.getline(query, DEFAULT_BUFLEN);
        //send(client_socket, query, strlen(query), 0);

        // альтернативный вариант ввода данных стрингом
         getline(cin, query);
         query = color + nickname + ": " + query + "\n";
         send(client_socket, query.c_str(), query.size(), 0);
    }
}

DWORD WINAPI Receiver(void* param)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    while (true) {
        char response[DEFAULT_BUFLEN];
        int result = recv(client_socket, response, DEFAULT_BUFLEN, 0);
        response[result] = '\0';
        // cout << "...\nYou have new response from server: " << response << "\n";
        SetConsoleTextAttribute(hConsole, (response[0] - 40));
        cout << &(response[1]);
        SetConsoleTextAttribute(hConsole, ('7' - 40));

        // cout << "Please insert your query for server: ";
    }
}

BOOL ExitHandler(DWORD whatHappening)
{
    switch (whatHappening)
    {
    case CTRL_C_EVENT: // closing console by ctrl + c
    case CTRL_BREAK_EVENT: // ctrl + break
    case CTRL_CLOSE_EVENT: // closing the console window by X button
      return(TRUE);
        break;
    default:
        return FALSE;
    }
}

int main()
{
    string ip = "172.23.112.1";
    // обработчик закрытия окна консоли
    //SetConsoleCtrlHandler((PHANDLER_ROUTINE)ExitHandler, true);

    system("title Client:");

    // initialize Winsock
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }
    addrinfo hints = {};
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    system("cls");

    //cout << "Enter server IP: ";
    //cin >> ip;
    //cin.clear();
    //cin.ignore();
    

    // разрешить адрес сервера и порт
    addrinfo* result = nullptr;
    iResult = getaddrinfo(ip.c_str(), DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 2;
    }

    addrinfo* ptr = nullptr;
    // пытаться подключиться к адресу, пока не удастся
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {
        // создать сокет на стороне клиента для подключения к серверу
        client_socket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

        if (client_socket == INVALID_SOCKET) {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            return 3;
        }

        // connect to server
        iResult = connect(client_socket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(client_socket);
            client_socket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    if (client_socket == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        WSACleanup();
        return 5;
    }

    cout << "Enter nickname: ";
    getline(cin, nickname);

   system((string("title Client: ") + nickname).c_str());


    cout << "Enter message color: ";
    cin >> color;
    cin.clear();
    cin.ignore();
    system("cls");


    CreateThread(0, 0, Sender, 0, 0, 0);
    CreateThread(0, 0, Receiver, 0, 0, 0);

    Sleep(INFINITE);
}