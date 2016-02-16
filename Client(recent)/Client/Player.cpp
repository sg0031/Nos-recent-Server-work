#include "Player.h"


Player::Player()
{
	position=D3DXVECTOR3(-20.0, 0.0, -20.0);
	direction = D3DXVECTOR3(0, 0, 1);
	velocity = 0.5;
	character_type = -1;
	id = -1;
	play = false;

	over_ex.s = NULL;
	over_ex.operationtype = Recvtype;
	over_ex.prevsize = 0;
	over_ex.currentsize = 0;
	over_ex.buf.buf = over_ex.iocpbuf;
	over_ex.buf.len = sizeof(over_ex.iocpbuf);
	ZeroMemory(&over_ex.Overlapped, sizeof(over_ex.Overlapped));
}


Player::~Player()
{
}

bool Player::getPlay()
{
	return play;
}
D3DXVECTOR3 Player::getPlayer_Position()
{
	return position;
}

D3DXVECTOR3 Player::getPlayer_Direction()
{
	return direction;
}
int Player::getPlayerID()
{
	return id;
}
double Player::getPlayer_velocity()
{
	return velocity;
}



void Player::setPlayer_velocity(double velocity)
{
	this->velocity = velocity;
}
void Player::setPlay(bool p)
{
	Play = p;
}
void Player::setPlayerID(int id)
{
	Player_id = id;
}
void Player::setPlayer_Position(D3DXVECTOR3 position)
{
	this->position = position;
}
void Player::setPlayer_Direction(D3DXVECTOR3 direction)
{
	this->direction = direction;
}