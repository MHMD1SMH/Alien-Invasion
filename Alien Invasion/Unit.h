#pragma once
#include <string>
using namespace std;
#include <iostream>

class Unit
{
private:
	int Id;
	string Type;
	int Health;
	int Power;
	int AttackCapacity;
public:
	Unit() {};
	Unit(Unit* K) {
		this->setType(K->getType());
		this->setAttackCapacity(K->getAttackCapacity());
		this->setHealth(K->getHealth());
		this->setPower(K->getPower());
		this->setID(K->getID());
	}
	void setType(string type) { Type = type; };
	string getType() const { return Type; };

	void setID(int n) { Id = n; }
	int getID() const { return Id; };	

	void setPower(int Power) { this->Power = Power; };
	int getPower() const { return Power; };

	void setHealth(int Health) { this->Health = Health; };
	void decHel(int n) { this->Health -= n; };
	int getHealth() const { return Health; };

	void setAttackCapacity(int Cap) { this->AttackCapacity = Cap; };
	int getAttackCapacity() const { return AttackCapacity; };

	virtual bool Attack(Unit* K) =0;
	
};

