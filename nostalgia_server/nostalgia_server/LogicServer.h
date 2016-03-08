#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<iostream>
#include<vector>
#include<thread>
#include<mutex>
#include<queue>
#include<WinSock2.h>
#include"protocol.h"
using namespace std;

class LogicServer
{
	static HANDLE io;	//ºó Æ÷Æ® »ý¼º
	static int id;
	static int count;
	static PlayerInfo player[ROOM_MAX_PLAYER];
	static priority_queue<FIFO,vector<FIFO>,Standard> playerID;
	static mutex myLock;
public:
	LogicServer();
	~LogicServer();
	static void acceptThread();
	static void lobbyThread();
	static void workerThread();
	static void processPacket(int id, char *ptr);
	static void sendPacket(int client, void* packet);
};

