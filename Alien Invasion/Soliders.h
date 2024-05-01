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
	};
	ES(ES* K) {
		this->setType(K->getType());
		this->setAttackCapacity(K->getAttackCapacity());
		this->setHealth(K->getHealth());
		this->setPower(K->getPower());
		this->setID(K->getID());
	}
	virtual bool Attack(Unit* K) override {
		if (K->getType() == "AS") {
			float Damage = (this->getPower() * (this->getHealth() / 100)) / (sqrt(K->getHealth()));

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
	};
	AS(AS* K) {
		this->setType(K->getType());
		this->setAttackCapacity(K->getAttackCapacity());
		this->setHealth(K->getHealth());
		this->setPower(K->getPower());
		this->setID(K->getID());
	}
	virtual bool Attack(Unit* K) override {
		if (K->getType() == "AS") {
			float Damage = (this->getPower() * (this->getHealth() / 100)) / (sqrt(K->getHealth()));

			K->decHel(Damage);

			return true;
		}
		else
		{
			return false;
		}
	}
};

