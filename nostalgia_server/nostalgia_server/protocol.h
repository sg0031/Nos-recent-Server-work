
#include <Windows.h>
#include <D3DX10Math.h>

#include "struct.h"
#include "protocol_type.h"

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
//	Server->DB Server

//	[SDB_Packet]

//sdb_packet_create_id

//	sdb_packet_buy_portion

//	sdb_packet_clear_time

//	sdb_packet_gold

//	sdb_packet_

//	[CDB_Packet]

//cdb_packet_rank_info
#pragma pack (pop)


//#define WM_SOCKET WM_USER+1
//#define MAX_SIZE 1024
//
//#define SC_POS 1
//#define SC_LOGIN 2
//
//#define CS_LEFT 1
//#define CS_RIGHT 2
//#define CS_UP 3
//#define CS_DOWN 4
//#define CS_LOGIN 5
//
//#pragma pack (push, 1)
////서버 -> 클라
//struct sc_packet_move
//{
//	BYTE size;
//	BYTE type;
//	int id;
//	int x;
//	int y;
//	int Sectorx;
//	int Sectory;
//};
//
//struct sc_packet_putplayer
//{
//	BYTE size;
//	BYTE type;
//	int id;
//};
//
//
////클라 -> 서버
//struct cs_packet_move
//{
//	BYTE size;
//	BYTE type;
//};
//
//struct cs_packet_accept
//{
//	BYTE size;
//	BYTE type;
//};
//
//#pragma pack (pop)