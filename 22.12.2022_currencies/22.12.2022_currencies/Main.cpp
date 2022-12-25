#pragma comment (lib, "Ws2_32.lib")
#include <Winsock2.h>
#include <ws2tcpip.h>

#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <iomanip>
#include "json\json.h"



using namespace std;

int main()
{


    //1. ������������� "Ws2_32.dll" ��� �������� ��������
    WSADATA wsaData;
    WORD wVersionRequested = MAKEWORD(2, 2);

    int err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {

        cout << "WSAStartup failed with error: " << err << endl;
        return 1;
    }

    //������������� ���������, ��� �������� ip ������ � ����� ������� � ������� �� ����� �����������

    char hostname[255] = "api.privatbank.ua";

    addrinfo* result = NULL;

    addrinfo hints;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    int iResult = getaddrinfo(hostname, "http", &hints, &result);
    if (iResult != 0) {
        cout << "getaddrinfo failed with error: " << iResult << endl;
        WSACleanup();
        return 3;
    }

    SOCKET connectSocket = INVALID_SOCKET;
    addrinfo* ptr = NULL;

    //������� �������������� � ����������� ������
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

        //2. �������� ����������� ������
        connectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (connectSocket == INVALID_SOCKET) {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            return 1;
        }

        //3. ����������� � ��������
        iResult = connect(connectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(connectSocket);
            connectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    //4. HTTP Request



    string uri = "/p24api/pubinfo?json&exchange&coursid=5";

    string request = "GET " + uri + " HTTP/1.1\n";
    request += "Host: " + string(hostname) + "\n";
    request += "Accept: */*\n";
    request += "Accept-Encoding: gzip, deflate, br\n";
    request += "Connection: close\n";
    request += "\n";

    cout << uri << endl;

    //�������� ���������
    if (send(connectSocket, request.c_str(), request.length(), 0) == SOCKET_ERROR) {
        cout << "send failed: " << WSAGetLastError() << endl;
        closesocket(connectSocket);
        WSACleanup();
        return 5;
    }
    cout << "send data" << endl;

    //5. HTTP Response

    string response;

    const size_t BUFFERSIZE = 1024;
    char resBuf[BUFFERSIZE];

    int respLength;

    do {
        respLength = recv(connectSocket, resBuf, BUFFERSIZE, 0);
        if (respLength > 0) {
            response += string(resBuf).substr(0, respLength);
        }
        else {
            cout << "recv failed: " << WSAGetLastError() << endl;
            closesocket(connectSocket);
            WSACleanup();
            return 6;
        }

    } while (respLength == BUFFERSIZE);

    cout << endl;

    try
    {
        response = &response.c_str()[response.find("{")]; // left only json info

        Json::Reader reader; // reader that parse json file

        Json::Value completeJsonData; // class that contains json info

        reader.parse(response, completeJsonData); // parsing
        string resultString(""); // Result string

        //CITY ID
        resultString += "City ID: ";
        resultString += to_string(completeJsonData["id"].asInt());
        resultString += "\n";
        //CITY
        resultString += "City: ";
        resultString += completeJsonData["name"].asCString();
        resultString += "\n";
        //COUNTRY
        resultString += "Country: ";
        resultString += completeJsonData["sys"]["country"].asCString();
        resultString += "\n";
        //MIN TEMP
        resultString += "Min temp: ";
        resultString += to_string(completeJsonData["main"]["temp_min"].asFloat() - 273.15);
        resultString += "\n";
        //MAX TEMP
        resultString += "Max temp: ";
        resultString += to_string(completeJsonData["main"]["temp_max"].asFloat() - 273.15);
        resultString += "\n";
        //SUNSET
        std::chrono::milliseconds ms(completeJsonData["sys"]["sunset"].asInt());
        resultString += "Sunset : ";
        if (chrono::duration_cast<std::chrono::hours>(ms).count() / 24 < 10)
            resultString += "0";
        resultString += to_string(chrono::duration_cast<std::chrono::hours>(ms).count() / 24);
        resultString += ":";
        if (chrono::duration_cast<std::chrono::minutes> (ms).count() / 60 / 60 < 10)
            resultString += "0";
        resultString += to_string(chrono::duration_cast<std::chrono::minutes> (ms).count() / 60 / 60);
        resultString += "\n";

        // write to file
        ofstream file("Result.txt", ios::app);
        cout << resultString << endl;
        file << resultString << "\n";
        file.close();

    }
    catch (...)
    {
        //cout << str_out.c_str();
        cout << "Inccorect enter\n\n";
    }

    //��������� �������� � ��������� ��������� �������
    iResult = shutdown(connectSocket, SD_BOTH);
    if (iResult == SOCKET_ERROR) {
        cout << "shutdown failed: " << WSAGetLastError() << endl;
        closesocket(connectSocket);
        WSACleanup();
        return 7;
    }

    closesocket(connectSocket);
    WSACleanup();
}