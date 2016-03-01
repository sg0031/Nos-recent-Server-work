#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<iostream>
#include<time.h>
#include"Player.h"


using namespace std;

#pragma pack()

class Server
{
	HWND socketHWND;
	HINSTANCE ghInst;


	SOCKET sock;
	WSABUF wsaSendBuf;
	char sendBuf[MAX_SIZE];
	WSABUF wsaRecvBuf;
	char recvBuf[MAX_SIZE];
	WSABUF wsaCompleteBuf;
	char completeBuf[MAX_SIZE];
	int inPacketSize;
	int savePacketSize;

	int count;
	int myId;
public:
	Player Player[ROOM_MAX_PLAYER];
	LPCTSTR IpszClass = "Test Client";
//--------------------------------------------
	void setSocketHWND(HWND s);
	void setHINSTANCE(HINSTANCE g);
//--------------------------------------
	static Server* getInstangce()
	{
		static Server inst;
		return &inst;
	}
//---------------------------------------
	Server();
	int socketInit(); 
	void readPacket();

	void processPacket(char* buf);
	void sendPacket(SOCKET s, void* buf);
	void keyDown(WPARAM wParam);
	int getMyId();
	~Server();
};

