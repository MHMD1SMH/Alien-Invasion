#pragma once
#include "Unit.h"
class HU :public Unit
{
public:
	HU() {
		this->setType("HU");
	};
	HU(int h, int p, int ac, int id, int timejoin) {
		setHealth(h);
		setPower(p);
		setAttackCapacity(ac);
		setID(id);
		setType("Drone");
		this->getTime()->setTj(timejoin);
		this->setInHealth(h);
	};
	HU(HU* K) {
		this->setType(K->getType());
		this->setAttackCapacity(K->getAttackCapacity());
		this->setHealth(K->getHealth());
		this->setPower(K->getPower());
		this->setID(K->getID());
		this->setInHealth(K->getInHealth());
	}
	virtual bool Attack(Unit* K) override {
		float Heal = (this->getPower() * (this->getHealth())/100.1) / (sqrt(K->getHealth()));
		if (!K)
			return false;

		K->incHel(Heal);

		return true;
	}
};

