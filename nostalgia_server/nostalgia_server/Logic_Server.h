#pragma once
#include<iostream>
#include<vector>
#include<thread>
#include<WinSock2.h>
#include"protocol.h"
using namespace std;

class Logic_Server
{
	static HANDLE io;	//ºó Æ÷Æ® »ý¼º
	static int ID;
	static Player_info Player[4];
public:
	Logic_Server();
	~Logic_Server();
	static void AcceptThread();
	static void LobbyThread();
	static void WorkerThread();
	static void ProcessPacket(int id, char *ptr);
	static void Send_Packet(int client, void* packet);
};

