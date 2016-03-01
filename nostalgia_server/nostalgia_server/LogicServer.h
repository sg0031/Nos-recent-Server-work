#pragma once
#include<iostream>
#include<vector>
#include<thread>
#include<queue>
#include<WinSock2.h>
#include"protocol.h"
using namespace std;

class LogicServer
{
	static HANDLE io;	//�� ��Ʈ ����
	static int id;
	static PlayerInfo player[ROOM_MAX_PLAYER];
	static priority_queue<FIFO,vector<FIFO>,Standard> playerID;
public:
	LogicServer();
	~LogicServer();
	static void acceptThread();
	static void lobbyThread();
	static void workerThread();
	static void processPacket(int id, char *ptr);
	static void sendPacket(int client, void* packet);
};

