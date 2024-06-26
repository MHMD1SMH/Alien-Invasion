#pragma once
#include <iostream>
#include "Unit.h"


using namespace std;



class Monster : public Unit
{
public:
	Monster() {
		this->setType("Monster");
	};
	Monster(int h, int p, int ac, int id ,int timejoin) {
		setHealth(h);
		setPower(p);
		setAttackCapacity(ac);
		setType("Monster");
		setID(id);
		this->getTime()->setTj(timejoin);
		this->setInHealth(h);
	};
	Monster(Unit* K) {
		this->setType(K->getType());
		this->setAttackCapacity(K->getAttackCapacity());
		this->setHealth(K->getHealth());
		this->setPower(K->getPower());
		this->setID(K->getID());
		this->setInHealth(K->getInHealth());
	}
	virtual bool Attack(Unit* K) override {
		float Damage = (this->getPower() * (this->getHealth() / 100.0)) / (sqrt(K->getHealth()));
		

		K->decHel(Damage);

		return true;

	}



};
class Monsters

{

	int arrsize = 0;
	Monster** arrofmonsters = new Monster * [100];
public:

	int counter ()const { return arrsize; }
	Monster* selectRandomMonster() {
		if (!arrsize)
			return NULL;

		int randomIndex = rand() % arrsize;
		Monster* temp;
		temp = arrofmonsters[randomIndex];

		arrofmonsters[randomIndex] = arrofmonsters[arrsize - 1];
		arrofmonsters[arrsize - 1] = NULL;
		arrsize--;
		return temp;

	}

	void insert(Monster* m) {
		if (m)
		{
			arrofmonsters[arrsize] = m;
			arrsize++;
		}
	};




	void addUnit(int h, int p, int ac, int id,int timesep) {

		Monster* AM = new Monster(h, p, ac, id, timesep);
		if (arrsize == 100)
		{
			return;
		}
		this->insert(AM);
	};
	void PrintArr() {

		cout << arrsize << " AM [";
		for (int i = 0; i < arrsize; i++)
		{
			cout << this->arrofmonsters[i]->getID() << ", ";
		}
		cout << "]";
	}
};