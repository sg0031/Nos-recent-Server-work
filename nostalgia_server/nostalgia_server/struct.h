#pragma once
#include "stdafx.h"
//#include <Windows.h>
#include "Monster.h"


#pragma pack (push, 1)
struct FIFO
{
	int data;
	int turn;
};
struct Standard
{
	bool operator()(FIFO t, FIFO u)
	{
		return t.turn > u.turn;
	}
};
enum EOperationType
{
	Sendtype = 1,
	Recvtype = 2
};

struct OverEx	//오버렙트구조체 확장
{
	OVERLAPPED overLapped;
	SOCKET s;
	EOperationType operationType;	//패킷의 타입
	int prevSize;	//이전데이타 크기
	int currentSize;//현재데이타 크기
	WSABUF buf;
	char packetBuf[256];
	char iocpBuf[4096];
};
struct Object
{
	int kind;
	D3DXVECTOR3 objectPosition;
	double radius;
};
struct sectorPosition
{
	int sectorNumX;
	int sectorNumY;
};
struct Sector
{
	sectorPosition sectorNum;
	D3DXVECTOR3 startSectorPosition;
	D3DXVECTOR3 endSectorPosition;
	Object arrayObject[MAX_OBJECT];
	OrcArchor archorArr[MAX_MONSTER];
	OrcWarrior warriorArr[MAX_MONSTER];
	OrcMaster masterArr[MAX_MONSTER];
	OrcKing king;
	Sector()
	{
		startSectorPosition.x = 0.0;
		startSectorPosition.y = 0.0;
		startSectorPosition.z = 0.0;
		endSectorPosition.x = 0.0;
		endSectorPosition.y = 0.0;
		endSectorPosition.z = 0.0;
		sectorNum.sectorNumX = 0;
		sectorNum .sectorNumY=0;
	}
};


struct PlayerInfo
{
	OverEx* overEx;
	int id;
	sectorPosition currentSector;
	int characterType;
	D3DXVECTOR3 playerPosition;
	D3DXVECTOR3 playerDirection;
	double playerVelocity;
	int attack;
	int health;
	int mana;
	int deFence;
	char itemQ;
	char itemW;
	int theNumberOfPlayer;
	double clearTime;
	bool play;
	bool acceptPlayer;
	PlayerInfo()
	{
		playerPosition.x = (rand() % 60) * 10;
		playerPosition.y = 0;
		playerPosition.z = (rand() % 60) * 10;
		playerDirection.x = 0;
		playerDirection.y = 0;
		playerDirection.z = 1;
		playerVelocity = 10;
		characterType = -1;
		id = -1;
		play = false;
		acceptPlayer = false;

		currentSector.sectorNumX = 0;
		currentSector.sectorNumY = 0;

		overEx = new OverEx;
		ZeroMemory(&overEx->iocpBuf, sizeof(overEx->iocpBuf));
		ZeroMemory(&overEx->packetBuf, sizeof(overEx->packetBuf));
		overEx->s = NULL;
		overEx->operationType = Recvtype;
		overEx->prevSize = 0;
		overEx->currentSize = 0;
		overEx->buf.buf = overEx->iocpBuf;
		overEx->buf.len = sizeof(overEx->iocpBuf);
		ZeroMemory(&overEx->overLapped, sizeof(overEx->overLapped));
	}
};

struct RoomInfo
{
	int roomNum;
	PlayerInfo maxPlayer[4];
};
//struct Monster
//{
//	int monsterType;
//	int attack;
//	int health;
//	int defence;
//	double monsterX, monsterZ;
//	double monsterVelocity;
//	Monster()
//	{
//		monsterType = rand()%4;
//		if (monsterType == 0)
//		{
//			attack = 20;
//			defence = 20;
//			health = 700;
//
//		}
//	}
//};
#pragma pack (pop)