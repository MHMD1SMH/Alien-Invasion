#pragma once
#include "Unit.h"
#include "Queue.h"
#include <iostream>

class ES : public Unit
{
public:
	ES() {
		this->setType("ES");
	};
	ES(int h, int p, int ac, int id, int timejoin) {
		setHealth(h);
		setPower(p);
		setAttackCapacity(ac);
		setID(id);
		setType("ES");
		this->getTime()->setTj(timejoin);
		this->setInHealth(h);
	};
	
	ES(Unit* K) {
		this->setType(K->getType());
		this->setAttackCapacity(K->getAttackCapacity());
		this->setHealth(K->getHealth());
		this->setPower(K->getPower());
		this->setID(K->getID());
		this->setInHealth(K->getInHealth());
	}
	virtual bool Attack(Unit* K) override {
		if (K->getType() == "AS") {
			float Damage = (this->getPower() * (this->getHealth() / 100.0)) / (sqrt(K->getHealth()));

			K->decHel(Damage);

			return true;
		}
		else
		{
			return false;
		}
	}
};

class AS : public Unit
{
public:
	AS() {
		this->setType("AS");
	};
	AS(int h, int p, int ac, int id,int timejoin) {
		setHealth(h);
		setPower(p);
		setAttackCapacity(ac);
		setID(id);
		setType("AS");
		this->getTime()->setTj(timejoin);
		this->setInHealth(h);
	};
	AS(Unit* K) {
		this->setType(K->getType());
		this->setAttackCapacity(K->getAttackCapacity());
		this->setHealth(K->getHealth());
		this->setPower(K->getPower());
		this->setID(K->getID());
		this->setInHealth(K->getInHealth());
	}
	virtual bool Attack(Unit* K) override {
		if (K->getType() == "AS") {
			float Damage = (this->getPower() * (this->getHealth() / 100.0)) / (sqrt(K->getHealth()));

			K->decHel(Damage);

			return true;
		}
		else
		{
			return false;
		}
	}
};

