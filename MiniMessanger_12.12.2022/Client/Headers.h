#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "WinSock2.h" //����� ��������� ����������, �����������
//��� Winsock 2 API.
#include <ws2tcpip.h> //�������� ������� ��� ������ � ��������
//����. inet_pton
#pragma comment(lib, "Ws2_32.lib") //������� ���������� Windows Sockets

#include <windows.h>
#include <windowsX.h>
#include <tchar.h>
#include <commctrl.h>
#include <string>
#include <math.h>
#include "resource.h"
#include <iostream>

const int MAXSTRLEN = 256;

using namespace std;
