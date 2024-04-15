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
	Drone(Drone* K) {
		this->setType(K->getType());
		this->setAttackCapacity(K->getAttackCapacity());
		this->setHealth(K->getHealth());
		this->setPower(K->getPower());
	}
	virtual bool Attack(Unit* K) override {
		if (!(K->getType() == "Tank" || K->getType() == "Gunnery"))
			return false;

		K->decHel((this->getPower()));

		return true;

	}
};

class Drones : public DoubleQueue<Drone>
{
public:
	void PrintQueue() {
		Drone K;
		DoubleNode<Drone>* ptr;
		ptr = this->getFrnt();
		while (ptr)
		{
			K = ptr->getItem();
			cout << K.getType() << " ID :"  << "power :" << K.getPower() << endl;
			ptr =ptr->getNext();
		}
		cout << endl;
	}
};

