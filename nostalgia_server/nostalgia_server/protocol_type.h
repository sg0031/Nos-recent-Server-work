///Logic Sever///
#define BUF_SIZE 1024
#define WM_SOCKET WM_USER+1
//sc_packet_type
#define SC_MOVE 1
#define SC_MOVE_ERROR_CHECK 30
#define SC_SECTOR 2
#define SC_MONSTER_MOVE 3

//cs_packet_type
#define CS_MOVE 4
#define CS_USE_SKILL_Q 5
#define CS_USE_SKILL_W 6
#define CS_USE_SKILL_E 7
#define CS_USE_ITEM_S 8
#define CS_USE_ITEM_D 9

///Login Sever///

//sc_packet_type
#define SC_LOGIN_SUCCESS 10
#define SC_LOGIN_FAIL 11
#define SC_READY 12
#define SC_ROOM_LIST 13

//cs_packet_type
#define CS_LOGIN_REQUEST 14
#define CS_CREATE_ROOM 15
#define CS_INPUT_READY 16
#define CS_INPUT_START 17
#define CS_INVITE_SHOP 18
#define CS_REGISTER_PORTION 19

#define CS_HEAL_PORTION 20
#define CS_MANA_PORTION 21
#define CS_SPEED_PORTION 22
#define CS_ATTACK_PORTION 23

#define CS_SELECT_WARRIOR 24
#define CS_SELECT_WIZARD 25
#define CS_SELECT_HEALER 26
#define CS_SELECT_ARCHER 27