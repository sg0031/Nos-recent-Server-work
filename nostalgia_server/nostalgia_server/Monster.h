#pragma once
class Monster
{
	int monsterType;
	int attack;
	int health;
	int defence;
	int target;
	double monsterX, monsterZ;
	double monsterVelocity;
public:
	Monster();
	~Monster();
};
class OrcWarrior : public Monster
{
public:

};
class OrcArchor :public Monster
{
public:

};
class OrcMaster : public Monster
{
public:

};
class OrcKing : public Monster
{
public:

};