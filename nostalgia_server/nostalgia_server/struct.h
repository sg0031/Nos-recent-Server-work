#include <Windows.h>
#pragma pack (push, 1)
enum
{
	Sendtype = 1,
	Recvtype = 2
};
struct OverEx	//오버렙트구조체 확장
{
	OVERLAPPED overLapped;
	SOCKET s;
	int operationType;	//패킷의 타입
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
struct PlayerInfo
{
	OverEx overEx;
	int id;
	int characterType;
	D3DXVECTOR3 playerPosition;
	D3DXVECTOR3 playerDirection;
	double playerVelocity;
	int attack;
	int health;
	int mana;
	int deFence;
	int currentSector;
	char itemQ;
	char itemW;
	int theNumberOfPlayer;
	double clearTime;
	bool play;
	PlayerInfo()
	{
		playerPosition.x = (rand() % 60) * 10;
		playerPosition.y = 0;
		playerPosition.z = (rand() % 60) * 10;
		playerDirection.x = 0;
		playerDirection.y = 0;
		playerDirection.z = 1;
		playerVelocity = 0.5;
		characterType = -1;
		id = -1;
		play = false;

		overEx.s = NULL;
		overEx.operationType = Recvtype;
		overEx.prevSize = 0;
		overEx.currentSize = 0;
		overEx.buf.buf = overEx.iocpBuf;
		overEx.buf.len = sizeof(overEx.iocpBuf);
		ZeroMemory(&overEx.overLapped, sizeof(overEx.overLapped));
	}
};

struct RoomInfo
{
	int roomNum;
	PlayerInfo maxPlayer[4];
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
		monsterType = rand()%4;
		if (monsterType == 0)
		{
			attack = 20;
			defence = 20;
			health = 700;

		}
	}
};
#pragma pack (pop)