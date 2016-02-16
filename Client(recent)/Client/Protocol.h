
#include <D3DX10Math.h>

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

#pragma pack (push, 1)
// Game Logic Server 
// SC_Packet
struct sc_packet_move
{
	int packet_size;
	BYTE packet_type;
	int id;
	D3DXVECTOR3 position;
};
struct sc_packet_sector
{
	int packet_size;
	BYTE packet_type;
	int id;
	sector area[9];
};
struct sc_packet_monster_roaming
{
	int packet_size;
	BYTE packet_type;
	int kind;
	D3DXVECTOR3 position;
};
//  CS_Packet
struct cs_packet_move
{
	int packet_size;
	BYTE packet_type;
	int id;
	D3DXVECTOR3 direction;
	D3DXVECTOR3 position;
};
struct cs_packet_attack
{
	int packet_size;
	BYTE packet_type;
	int id;
	//이때 충돌체크 여부 판별
};
struct cs_packet_use_skill
{
	int packet_size;
	BYTE packet_type;
	int id;
	char keyboard_skill;
};
struct cs_packet_use_item
{
	int packet_size;
	BYTE packet_type;
	int id;
	int item_num;
};
//		Login & Lobby Server

//		SC_Packet
struct sc_packet_login
{
	int packet_size;
	BYTE packet_type;
	int id;
};

struct sc_packet_ready_player
{
	int packet_size;
	BYTE packet_type;
	int id;
};

struct sc_packet_room_list
{
	int packet_size;
	BYTE packet_type;
	int room_num;
};
//  CS_Packet

struct cs_packet_login
{
	int packet_size;
	BYTE packet_type;
	char ID[20];
	char Password[20];
};
struct cs_packet_create_room
{
	int packet_size;
	BYTE packet_type;
	BYTE limit_player_num;
};
struct cs_packet_input_ready
{
	int packet_size;
	BYTE packet_type;
	int room_num;
};
struct cs_packet_input_start
{
	int packet_size;
	BYTE packet_type;
};
struct cs_packet_invite_shop
{
	int packet_size;
	BYTE packet_type;
};
struct cs_packet_buy_portion
{
	int packet_size;
	BYTE packet_type;
	int amount;
};
struct cs_packet_register_portion
{
	int packet_size;
	BYTE packet_type;
	char keyboard_s;
	char keyboard_d;
};
struct cs_packet_select_character
{
	int packet_size;
	BYTE packet_type;
};


#pragma pack (pop)




