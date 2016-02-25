#pragma once
#include "Protocol.h"

class Player
{
	OverEx overEx;
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
	D3DXVECTOR3 getPlayerPosition();
	D3DXVECTOR3 getPlayerDirection();
	double getPlayerVelocity();
	int getPlayerID();

	void setPlayerVelocity(double velocity);
	void setPlay(bool p);
	void setPlayerID(int id);
	void setPlayerPosition(D3DXVECTOR3 position);
	void setPlayerDirection(D3DXVECTOR3 direction);
};

