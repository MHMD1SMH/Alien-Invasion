#pragma once
#include <string>
using namespace std;
#include <iostream>
class Unit
{
private:
	static int Id;
	string Type;
	int Health;
	int Power;
	int AttackCapacity;
public:
	Unit() {};
	void setType(string type) { Type = type; };
	string getType() const { return Type; };

	static void IncID() { Id += 1; };
	int getID() const { return Id; };

	void setPower(int Power) { this->Power = Power; };
	int getPower() const { return Power; };

	void setHealth(int Health) { this->Health = Health; };
	int getHealth() const { return Health; };

	void setAttackCapacity(int Cap) { this->AttackCapacity = Cap; };
	int getAttackCapacity() const { return AttackCapacity; };

	virtual bool Attack(Unit* K) = 0;
	
};

