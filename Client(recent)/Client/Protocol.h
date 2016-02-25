
#include "struct.h"
#include "Protocol_type.h"
#include <D3DX10Math.h>

#pragma pack (push, 1)
// Game Logic Server 
// SC_Packet

struct ScPacketMove
{
	int packetSize;
	BYTE packetType;
	int id;
	D3DXVECTOR3 position;
};
struct ScPacketSector
{
	int packetSize;
	BYTE packetType;
	int id;
	Sector area[9];
};
struct ScPacketMonsterRoaming
{
	int packetSize;
	BYTE packetType;
	int kind;
	D3DXVECTOR3 position;
};
//  CS_Packet
struct CsPacketMove
{
	int packetSize;
	BYTE packetType;
	int id;
	D3DXVECTOR3 direction;
	D3DXVECTOR3 position;
};
struct CsPacketAttack
{
	int packetSize;
	BYTE packetType;
	int id;
	//�̶� �浹üũ ���� �Ǻ�
};
struct CsPacketUseSkill
{
	int packetSize;
	BYTE packetType;
	int id;
	char keyboardSkill;
};
struct CsPacketUseItem
{
	int packetSize;
	BYTE packetType;
	int id;
	int itemNum;
};
//		Login & Lobby Server

//		SC_Packet
struct ScPacketLogin
{
	int packetSize;
	BYTE packetType;
	int id;
};

struct ScPacketReadyPlayer
{
	int packetSize;
	BYTE packetType;
	int id;
};

struct ScPacketRoomList
{
	int packetSize;
	BYTE packetType;
	int roomNum;
};
//  CS_Packet

struct CsPacketLogin
{
	int packetSize;
	BYTE packetType;
	//char ID[20];
	//char Password[20];
};
struct CsPacketCreateRoom
{
	int packetSize;
	BYTE packetType;
	BYTE limitPlayerNum;
};
struct CsPacketInputReady
{
	int packetSize;
	BYTE packetType;
	int roomNum;
};
struct CsPacketInputStart
{
	int packetSize;
	BYTE packetType;
};
struct CsPacketInviteShop
{
	int packetSize;
	BYTE packetType;
};
struct CsPacketBuyPortion
{
	int packetSize;
	BYTE packetType;
	int amount;
};
struct CsPacketRegisterPortion
{
	int packetSize;
	BYTE packetType;
	char keyboardS;
	char keyboardD;
};
struct CsPacketSelectCharacter
{
	int packetSize;
	BYTE packetType;
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
////���� -> Ŭ��
//struct ScPacketMove
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
////Ŭ�� -> ����
//struct CsPacketMove
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



