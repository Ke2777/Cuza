// try_server1.cpp : Defines the entry point for the console application.
//
/*
#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}
*/



// ������ �������� TCP����������
#include <locale.h>
#include <stdio.h>
#include <winsock2.h> // Wincosk2.h ������ ���� ������ windows!
#pragma comment(lib, "Ws2_32.lib")


#define MY_PORT 48000 // ����, ������� ������� ������
// ������ ��� ������ ���������� �������� �������������
#define PRINTNUSERS if (nclients) printf("%d user online\n",nclients);else printf("No User online\n");
// �������� �������, ������������� �������������� �������������
DWORD WINAPI SexToClient(LPVOID client_socket);
// ���������� ���������� � ���������� �������� �������������
char nclients = 0;
int main(int argc, char* argv[])
{
	char buff[1024]; // ����� ��� ��������� ����
	printf("TCP SERVER DEMO\n");
	// ��� 1  ������������� ���������� �������
	// �. �. ������������ �������� ���������� �� ������������
	// �� ���������� ��������� �� ������� �����, ������������� � ���������
	// �� ��������� WSADATA.
	// ����� ����� ��������� ���������� ���� ����������, ������, �����
	// ������ ���� �� ����� ������������ �������� (��������� WSADATA
	// �������� 400 ����)

	if (WSAStartup(0x0202,(WSADATA *) &buff[0]))
	{
		// ������!
		printf("Error WSAStartup %d\n",WSAGetLastError());
		return 1;
	}
	// ��� 2 �������� ������
	SOCKET mysocket;
	// AF_INET  ����� ���������
	// SOCK_STREAM  ��������� ����� (� ���������� ����������)
	// 0  �� ��������� ���������� TCP ��������
	if ((mysocket=socket(AF_INET,SOCK_STREAM,0))<0)
	{
		// ������!
		printf("Error socket %d\n",WSAGetLastError());
		WSACleanup(); // �������������� ���������� Winsock
		return 1;
	}
	// ��� 3 ���������� ������ � ��������� �������
	sockaddr_in local_addr;
	local_addr.sin_family=AF_INET;
	local_addr.sin_port=htons(MY_PORT); // �� �������� � ������� �������!!!
	local_addr.sin_addr.s_addr=0; // ������ ��������� �����������
	// �� ��� ���� IP ������
	// �������� bind ��� ����������
	if (bind(mysocket,(sockaddr *) &local_addr, sizeof(local_addr)))
	{
		// ������
		printf("Error bind %d\n",WSAGetLastError());
		closesocket(mysocket); // ��������� �����!
		WSACleanup();
		return 1;
	}
	// ��� 4 �������� �����������
	// ������ ������� � 0x100
	if (listen(mysocket, 0x100))
	{
		// ������
		printf("Error listen %d\n",WSAGetLastError());
		closesocket(mysocket);
		WSACleanup();
		return 1;
	}
	printf("�������� �����������\n", 
		setlocale(LC_ALL,"Russian"));
	// ��� 5 ��������� ��������� �� �������
	SOCKET client_socket; // ����� ��� �������
	sockaddr_in client_addr; // ����� ������� (����������� ��������)

	// ������� accept ���������� �������� ������ ���������
	int client_addr_size=sizeof(client_addr);
	// ���� ���������� �������� �� ����������� �� �������
	while((client_socket=accept(mysocket, (sockaddr *) &client_addr, &client_addr_size)))
	{
		nclients++; // ����������� ������� �������������� ��������
		// �������� �������� ��� �����
		HOSTENT *hst;
		hst=gethostbyaddr((char *) &client_addr.sin_addr.s_addr,4,AF_INET);
		// ����� �������� � �������

		printf("+%s [%s] new connect!\n",(hst)?hst->h_name:"",inet_ntoa(client_addr.sin_addr));
		PRINTNUSERS
			// ����� ������ ������ ��� ����������� �������
			// ��, ��� ����� ������������� ������������ _beginthreadex
			// ��, ��������� ������� ����� ������� ����������� �� ����������
			// ����� �� ������, ����� �������� � CreateThread
			DWORD thID;
		CreateThread(NULL,NULL,SexToClient,&client_socket,NULL,&thID);
	}
	return 0;
}

//char gamebuff[4] = { 0 };

// gamebuff[0] - gamebuff[1] - gamebuff[2] - gamebuff[3] 
//  x1 - y1 - x2 - y2

// ��� ������� ��������� � ��������� ������
// � ���������� ���������� ��������������� ������� ���������� �� ���������
DWORD WINAPI SexToClient(LPVOID client_socket)
{
	SOCKET my_sock;
	my_sock = ((SOCKET *)client_socket)[0];
	char buff[3];
	char sHELLO[32];
//#define sHELLO "Hello, Sailor\r\n  you number is "
	sprintf_s(sHELLO, "%d..", nclients);
	// ���������� ������� �����������
	send(my_sock, sHELLO, sizeof(sHELLO), 0);
	send(my_sock, (char *)nclients, 4, 0);
	// ���� ��� �������: ����� ������ �� ������� � ����������� �� �������
	int bytes_recv;
	while ((bytes_recv = recv(my_sock, &buff[0], sizeof(buff), 0)) && bytes_recv != SOCKET_ERROR)
	{
		printf("gamebuff: %c %d %d %d %d\n", buff[1], buff[2], buff[3], buff[4], buff[5]);

		send(my_sock, &buff[0], 2, 0);
	}
	// ���� �� �����, �� ��������� ����� �� ����� �� �������
	// ���������� �������� recv ������ � ���������� � �������� ���������
	nclients--; // ��������� ������� �������� ��������
	printf("disconnect\n"); PRINTNUSERS
		// ��������� �����
		closesocket(my_sock);
	return 0;
}
