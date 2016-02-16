#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<WinSock2.h>
#include<iostream>
#include<time.h>
#include"Player.h"


using namespace std;

#pragma pack()

class Server
{
	HWND Socket_HWND;
	HINSTANCE g_hInst;


	SOCKET sock;
	WSABUF WSA_send_buf;
	char Send_buf[MAX_SIZE];
	WSABUF WSA_recv_buf;
	char Recv_buf[MAX_SIZE];
	WSABUF WSA_Complete_buf;
	char Complete_buf[MAX_SIZE];
	int in_packet_size;
	int save_packet_size;

	int my_id;
public:
	Player Player[8];
	LPCTSTR IpszClass = "Test Client";
//--------------------------------------------
	void setSocket_HWND(HWND s);
	void setHINSTANCE(HINSTANCE g);
//--------------------------------------
	static Server* getInstangce()
	{
		static Server inst;
		return &inst;
	}
//---------------------------------------
	Server();
	int socketinit(); 
	void ReadPacket();

	void ProcessPacket(char* buf);
	void SendPacket(SOCKET s, void* buf);
	void KeyDown(WPARAM wParam);
	int GetMy_id();
	~Server();
};

