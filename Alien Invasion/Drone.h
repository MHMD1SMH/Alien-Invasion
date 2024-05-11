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
	Drone(int h, int p, int ac,int id,int timejoin) {
		setHealth(h);
		setPower(p);
		setAttackCapacity(ac);
		setID(id);
		setType("Drone");
		this->getTime()->setTj(timejoin);
		this->setInHealth(h);
	};
	Drone(Unit* K) {
		this->setType(K->getType());
		this->setAttackCapacity(K->getAttackCapacity());
		this->setHealth(K->getHealth());
		this->setPower(K->getPower());
		this->setID(K->getID());
		this->setInHealth(K->getInHealth());
	}
	virtual bool Attack(Unit* K) override {
		float Damage = (this->getPower() * (this->getHealth())/100.0) / (sqrt(K->getHealth()));
		if (!K)
			return false;

		K->decHel(Damage);

		return true;
	}
};

