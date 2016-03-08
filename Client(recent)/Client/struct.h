#include <WinSock2.h>
#pragma pack (push, 1)
enum EOperationType
{
	Sendtype = 1,
	Recvtype = 2
};
struct OverEx//오버렙트구조체 확장
{
	OVERLAPPED overLapped;
	SOCKET s;
	EOperationType operationType;	//패킷의 타입
	int prevSize;	//이전데이타 크기
	int currentSize;//현재데이타 크기
	WSABUF buf;
	char packetBuf[255];
	char iocpBuf[4000];
};
struct Object
{
	int kind;
	double radius;
};
struct Sector
{
	int minX, maxX;
	int minZ, maxZ;
	Object array[100];
};

struct RoomInfo
{
	int roomNum;
//	PlayerInfo maxPlayer[4];
};
struct Monster
{
	int monsterType;
	int attack;
	int health;
	int defence;
	double monsterX, monsterZ;
	double monsterVelocity;
	Monster()
	{
		monsterType = rand() % 4;
		if (monsterType == 0)
		{
			attack = 20;
			defence = 20;
			health = 700;

		}
	}
};
#pragma pack (pop)