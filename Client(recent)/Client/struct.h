
#pragma pack (push, 1)
enum
{
	Sendtype = 1,
	Recvtype = 2
};
struct Over_ex	//오버렙트구조체 확장
{
	OVERLAPPED Overlapped;
	SOCKET s;
	int operationtype;	//패킷의 타입
	int prevsize;	//이전데이타 크기
	int currentsize;//현재데이타 크기
	WSABUF buf;
	char Packetbuf[255];
	char iocpbuf[4000];
};
struct Object
{
	int kind;
	double radius;
};
struct sector
{
	int min_x, max_x;
	int min_z, max_z;
	Object array[100];
};
struct room_info
{
	int room_num;
	Player max_player[4];
};
struct monster
{
	int monster_type;
	int attack;
	int health;
	int defence;
	double monster_x, monster_z;
	double monster_velocity;
	monster()
	{
		monster_type = rand() % 4;
		if (monster_type == 0)
		{
			attack = 20;
			defence = 20;
			health = 700;

		}
	}
};
#pragma pack (pop)