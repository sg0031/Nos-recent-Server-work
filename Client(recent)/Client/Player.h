#pragma once
#include"Protocol.h"
#include"Protocol_type.h"

class Player
{
	D3DXVECTOR3 position;
	D3DXVECTOR3 direction;
	double velocity;
	int Player_id;
	bool Play;

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

