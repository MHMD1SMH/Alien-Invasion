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
	ES(int h, int p, int ac, int id) {
		setHealth(h);
		setPower(p);
		setAttackCapacity(ac);
		setID(id);
		setType("ES");
		
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
class ESoliders : public LinkedQueue<ES>
{
public:
	void addUnit(int h, int p, int ac, int id) {

		this->enqueue(new ES(h, p, ac, id));
	}
	
	void PrintQueue() {
		ES K;
		Node<ES>* ptr;
		ptr = this->getFrnt();
		cout << "\n" << this->getCounter() << " ES" << " [";
		while (ptr)
		{
			K = ptr->getItem();
			cout << K.getID() << ", ";
			ptr = ptr->getNext();
		}
		cout << "]" << endl;
	}
};

class AS : public Unit
{
public:
	AS() {
		this->setType("AS");
	};
	AS(int h, int p, int ac, int id) {
		setHealth(h);
		setPower(p);
		setAttackCapacity(ac);
		setID(id);
		setType("AS");
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
class ASoliders : public LinkedQueue<AS>
{
public:
	void addUnit(int h, int p, int ac, int id) {
		this->enqueue(AS(h, p, ac, id));
	}

	void PrintQueue() {
		AS K;
		Node<AS>* ptr;
		ptr = this->getFrnt();
		cout << "\n" << this->getCounter() << " AS" << " [";
		while (ptr)
		{
			K = ptr->getItem();
			cout << K.getID() << ", ";
			ptr = ptr->getNext();
		}
		cout << "]" << endl;
	}
};
