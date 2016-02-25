
#define WM_SOCKET WM_USER+1
#define MAX_SIZE 255

///Logic Sever///
#define BUF_SIZE 1024
#define WM_SOCKET WM_USER+1
//sc_packet_type
#define SC_MOVE 1
#define SC_MOVE_ERROR_CHECK 2
#define SC_SECTOR 3
#define SC_MONSTER_MOVE 4

//cs_packet_type
#define CS_MOVE 1
#define CS_USE_SKILL_Q 2
#define CS_USE_SKILL_W 3
#define CS_USE_SKILL_E 4
#define CS_USE_ITEM_S 5
#define CS_USE_ITEM_D 6

///Login Sever///

//sc_packet_type
#define SC_LOGIN_SUCCESS 1
#define SC_LOGIN_FAIL 2
#define SC_READY 3
#define SC_ROOM_LIST 4	

//cs_packet_type
#define CS_LOGIN_REQUEST 1
#define CS_CREATE_ROOM 2
#define CS_INPUT_READY 3
#define CS_INPUT_START 4
#define CS_INVITE_SHOP 5
#define CS_REGISTER_PORTION 6

#define CS_HEAL_PORTION 1
#define CS_MANA_PORTION 2
#define CS_SPEED_PORTION 3
#define CS_ATTACK_PORTION 4

#define CS_SELECT_WARRIOR 1
#define CS_SELECT_WIZARD 2
#define CS_SELECT_HEALER 3
#define CS_SELECT_ARCHER 4