#pragma once
#include "Protocol.h"

class Player
{
	Over_ex over_ex;
	int id;
	int character_type;
	D3DXVECTOR3 position;
	D3DXVECTOR3 direction;
	double velocity;
	int attack;
	int health;
	int mana;
	int defence;
	int current_sector;
	char item_q;
	char item_w;
	int the_number_of_player;
	double clear_time;
	bool play;

public:
	Player();
	~Player();

	bool getPlay();
	D3DXVECTOR3 getPlayer_Position();
	D3DXVECTOR3 getPlayer_Direction();
	double getPlayer_velocity();
	int getPlayerID();

	void setPlayer_velocity(double velocity);
	void setPlay(bool p);
	void setPlayerID(int id);
	void setPlayer_Position(D3DXVECTOR3 position);
	void setPlayer_Direction(D3DXVECTOR3 direction);
};

