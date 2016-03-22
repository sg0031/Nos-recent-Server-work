#include"stdafx.h"
#include "Player.h"


Player::Player()
{
	position=D3DXVECTOR3(-20.0, 0.0, -20.0);
	direction = D3DXVECTOR3(0, 0, 1);
	velocity = 0.5;
	character_type = -1;
	id = -1;
	play = false;

	overEx = new OverEx;
	ZeroMemory(&overEx->iocpBuf, sizeof(overEx->iocpBuf));
	ZeroMemory(&overEx->packetBuf, sizeof(overEx->packetBuf));
	overEx->s = NULL;
	overEx->operationType = Recvtype;
	overEx->prevSize = 0;
	overEx->currentSize = 0;
	overEx->buf.buf = overEx->iocpBuf;
	overEx->buf.len = sizeof(overEx->iocpBuf);
	ZeroMemory(&overEx->overLapped, sizeof(overEx->overLapped));
}


Player::~Player()
{
}

bool Player::getPlay()
{
	return play;
}
D3DXVECTOR3 Player::getPlayerPosition()
{
	return position;
}

D3DXVECTOR3 Player::getPlayerDirection()
{
	return direction;
}
int Player::getPlayerID()
{
	return id;
}
double Player::getPlayerVelocity()
{
	return velocity;
}
SOCKET Player::getPlayerSocket()
{
	return overEx->s;
}



void Player::setPlayerVelocity(double velocity)
{
	this->velocity = velocity;
}
void Player::setPlay(bool p)
{
	play = p;
}
void Player::setPlayerID(int id)
{
	this->id = id;
}
void Player::setPlayerPosition(D3DXVECTOR3 position)
{
	this->position = position;
}
void Player::setPlayerDirection(D3DXVECTOR3 direction)
{
	this->direction = direction;
}