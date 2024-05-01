#pragma once
#include <string>
using namespace std;
#include <iostream>
#include "Time.h"
class Unit
{
private:
	int Id;
	string Type;
	int Health;
	int Power;
	int AttackCapacity;
	Time* T = new Time;
public:
	Unit() {};
	Unit(Unit* K) {
		this->setType(K->getType());
		this->setAttackCapacity(K->getAttackCapacity());
		this->setHealth(K->getHealth());
		this->setPower(K->getPower());
		this->setID(K->getID());
	}
	Unit(int h, int p, int ac, int id , int timejoin) {
		setHealth(h);
		setPower(p);
		setAttackCapacity(ac);
		setID(id);
		T->setTj(timejoin);
	};
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

	Time* getTime() { return T; }
	
	virtual bool Attack(Unit* K) =0;
	friend ostream& operator << (ostream& os, const Unit& K) {
		cout << (K).getID();
		return os;
	}
};



