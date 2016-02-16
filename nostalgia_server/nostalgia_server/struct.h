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
struct Player_info
{
	Over_ex over_ex;
	int id;
	int character_type;
	D3DXVECTOR3 player_position;
	D3DXVECTOR3 player_direction;
	double player_velocity;
	int attack;
	int health;
	int mana;
	int defence;
	int current_sector;
	char item_q;
	char item_w;
	int the_number_of_player;
	double clear_time;
	Player_info()
	{
		player_position.x = (rand() % 60) * 10;
		player_position.y = 0;
		player_position.z = (rand() % 60) * 10;
		player_direction.x = 0;
		player_direction.y = 0;
		player_direction.z = 1;
		player_velocity = 0.5;
		character_type = -1;
		id = -1;

		over_ex.s = NULL;
		over_ex.operationtype = Recvtype;
		over_ex.prevsize = 0;
		over_ex.currentsize = 0;
		over_ex.buf.buf = over_ex.iocpbuf;
		over_ex.buf.len = sizeof(over_ex.iocpbuf);
		ZeroMemory(&over_ex.Overlapped, sizeof(over_ex.Overlapped));
	}
};

struct room_info
{
	int room_num;
	Player_info max_player[4];
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
		monster_type = rand()%4;
		if (monster_type == 0)
		{
			attack = 20;
			defence = 20;
			health = 700;

		}
	}
};
#pragma pack (pop)