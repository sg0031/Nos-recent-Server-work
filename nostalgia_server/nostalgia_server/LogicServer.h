#pragma once
#include<iostream>
#include<vector>
#include<thread>
#include<WinSock2.h>
#include"protocol.h"
using namespace std;

class LogicServer
{
	static HANDLE io;	//ºó Æ÷Æ® »ý¼º
	static int id;
	static PlayerInfo player[4];
public:
	LogicServer();
	~LogicServer();
	static void acceptThread();
	static void lobbyThread();
	static void workerThread();
	static void processPacket(int id, char *ptr);
	static void sendPacket(int client, void* packet);
};

