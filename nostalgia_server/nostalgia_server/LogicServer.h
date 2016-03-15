#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include"stdafx.h"
#include"protocol.h"
#include"Monster.h"
using namespace std;

class LogicServer
{
	static HANDLE io;	//�� ��Ʈ ����
	static int id;
	static int count;
	static PlayerInfo player[ROOM_MAX_PLAYER];
	static priority_queue<FIFO,vector<FIFO>,Standard> playerID;
	static mutex myLock;
	static Sector sector[SECTOR_WIDETH][SECTOR_LENGTH];
public:
	LogicServer();
	~LogicServer();
	static void acceptThread();
	static void lobbyThread();
	static void workerThread();
	static void processPacket(int id, char *ptr,double deltTime);
	static void sendPacket(int client, void* packet);
};

