#pragma once
#include "Unit.h"
#include "DoubleQueue.h"
#include <iostream>

class Drone : public Unit
{
public:
	Drone() {
		this->setType("Drone");
	};
	Drone(int h, int p, int ac,int id) {
		setHealth(h);
		setPower(p);
		setAttackCapacity(ac);
		setID(id);
		setType("Drone");
	};
	Drone(Drone* K) {
		this->setType(K->getType());
		this->setAttackCapacity(K->getAttackCapacity());
		this->setHealth(K->getHealth());
		this->setPower(K->getPower());
	}
	virtual bool Attack(Unit* K) override {
		float Damage = (this->getPower() * (this->getHealth() / 100)) / (sqrt(K->getHealth()));
		if (!(K->getType() == "Tank" || K->getType() == "Gunnery"))
			return false;

		K->decHel(Damage);

		return true;
	}
};

class Drones : public DoubleQueue<Drone>
{
public:
	void addUnit(int h, int p, int ac,int id) {
		
		Drone tAD = new Drone(h, p, ac,id);
		this->enqueue(tAD);
	};
	void PrintQueue() {
		Drone K;
		DoubleNode<Drone>* ptr;
		ptr = this->getFrnt();
		cout << "Drones Army\n";
		while (ptr)
		{
			K = ptr->getItem();
			cout << K.getType() << " ID :"<<  "power :" << K.getPower() << endl;
			ptr =ptr->getNext();
		}
		cout << endl;
	}
};

