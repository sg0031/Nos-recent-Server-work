
#define WM_SOCKET WM_USER+1
#define MAX_SIZE 255

///Logic Sever///
#define BUF_SIZE 1024
#define WM_SOCKET WM_USER+1
#define ROOM_MAX_PLAYER 4

enum
{
	SC_MOVE_POSITION = 1,
	SC_MOVE_ERROR_CHECK,
	SC_SECTOR,
	SC_MONSTER_MOVE,
	SC_LOGIN_SUCCESS,
	SC_LOGIN_FAIL,
	SC_READY,
	SC_ROOM_LIST,
	SC_PLAYER_LIST,

	CS_MOVE = 100,
	CS_USE_SKILL_Q,
	CS_USE_SKILL_W,
	CS_USE_SKILL_E,
	CS_USE_ITEM_S,
	CS_USE_ITEM_D,
	CS_LOGIN_REQUEST,
	CS_CREATE_ROOM,
	CS_INPUT_READY,
	CS_INPUT_START,
	CS_INVITE_SHOP,
	CS_REGISTER_PORTION,
	CS_HEAL_PORTION,
	CS_MANA_PORTION,
	CS_SPEED_PORTION,
	CS_ATTACK_PORTION,
	CS_SELECT_WARRIOR,
	CS_SELECT_WIZARD,
	CS_SELECT_HEALER,
	CS_SELECT_ARCHER
};