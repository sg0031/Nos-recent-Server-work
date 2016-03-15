#pragma once
#include"stdafx.h"
enum monsterType
{
	orcwarrior = 200,
	orcarchor,
	orcmaster,
	orcking
};

class Monster
{
protected:
	monsterType type;
	int health;
	int defence;
	int attack;
	int target;
	D3DXVECTOR3 monsterPosition;
	D3DXVECTOR3 monsterDirection;
	double monsterVelocity;
public:
	Monster();
	~Monster();
	//virtual void decreaseHealth() = 0;
	//virtual void changeTarget() = 0;
	//virtual void attackPlayer()=0;
	//virtual D3DXVECTOR3 roamingMap()=0;
};
class OrcWarrior : public Monster
{
public:
	OrcWarrior() 
	{
		type = orcwarrior;
		health=700;
		defence=20;
		attack = 20;
		target = -1;
		monsterVelocity=0.3;
	};
	~OrcWarrior() {};
};
class OrcArchor :public Monster
{
public:
	OrcArchor() 
	{
		type = orcarchor;
		health = 500;
		defence = 10;
		attack = 40;
		target = -1;
		monsterVelocity = 0.3;
	};
	~OrcArchor() {};
};
class OrcMaster : public Monster
{
public:
	OrcMaster() 
	{
		type = orcmaster;
		health = 1000;
		defence = 30;
		attack = 50;
		target = -1;
		monsterVelocity = 0.5;
	};
	~OrcMaster() {};
};
class OrcKing : public Monster
{
public:
	OrcKing() 
	{
		type = orcwarrior;
		health = 3000;
		defence = 50;
		attack = 100;
		target = -1;
		monsterVelocity = 0.3;
	};
	~OrcKing() {};
};
