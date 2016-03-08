#include <WinSock2.h>
#pragma pack (push, 1)
enum EOperationType
{
	Sendtype = 1,
	Recvtype = 2
};
struct OverEx//������Ʈ����ü Ȯ��
{
	OVERLAPPED overLapped;
	SOCKET s;
	EOperationType operationType;	//��Ŷ�� Ÿ��
	int prevSize;	//��������Ÿ ũ��
	int currentSize;//���絥��Ÿ ũ��
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