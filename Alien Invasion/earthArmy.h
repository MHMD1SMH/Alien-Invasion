#pragma once
#include "earthGunnery.h"
#include "Drone.h"
#include "earthTanks.h"
#include "Monster.h"
#include "Soliders.h"

#include "Queue.h"
#include "DoubleQueue.h"
#include "Stack.h"
#include "priQueue.h"

#include <fstream>
#include <sstream>
#include <string>

#include <stdlib.h>

enum Mode
{
	Interactive,
	Silent
};



struct Params {
	int minHealth = 0;
	int maxHealth = 0;
	int minPower = 0;
	int maxPower = 0;
	int minAttackCapacity = 0;
	int maxAttackCapacity = 0;
	int n = 0;
	int prob = 0;
	int unit1 = 0;
	int unit2 = 0;
	int unit3 = 0;
};

int random(int min, int max) {
	return min + rand() % max;
}

class earthArmy
{
	int id = 0;
	priQueue<earthGunnery>* EGs = new priQueue<earthGunnery>;
	LinkedQueue<ES>* ESs = new LinkedQueue<ES>;
	LinkedStack<earthTanks>* ETs = new LinkedStack<earthTanks>;
public:
	earthArmy() {};
	earthArmy(Params p) { };

	priQueue<earthGunnery>* getEGS() { return EGs; }
	LinkedQueue<ES>* getESs() { return ESs; }
	LinkedStack<earthTanks>* getETs() { return ETs; }

	void setID() { id += 1; }
	int getID() const { return id; }
	void state() {
		cout << "\n===============Earth Army Alive Units===============" << "\n";
		cout << EGs->getCounter() << "EG";
		EGs->print();


		cout << "\n" << ETs->getCounter() << "ET";

		ETs->PrintStack();



		cout << "\n" << ESs->getCounter() << "ES";
		ESs->PrintQueue();
	}

};


class alienArmy
{
	int id = 2000;
	DoubleQueue<Drone>* ADs = new DoubleQueue<Drone>;
	LinkedQueue<AS>* ASs = new LinkedQueue<AS>;
	Monsters* AMs = new Monsters;
public:


	alienArmy() {};
	alienArmy(Params p) { };

	DoubleQueue<Drone>* getADs() { return ADs; }
	LinkedQueue<AS>* getASs() { return ASs; }
	Monsters* getAMs() { return AMs; }

	void setID() { id += 1; }
	int getID()const { return id; }

	void state() {
		cout << "\n \n===============Alien Army Alive Units===============" << "\n";

		cout << "\n" << ADs->getCounter() << "AD";
		ADs->PrintQueue();

		AMs->PrintArr();

		cout << "\n" << ASs->getCounter() << "AS";
		ASs->PrintQueue();
	}
	void fight(earthArmy* ea, const Mode& M) {






		
	}
};

class Killedlist : public LinkedQueue<Unit*>
{
public:
	void addUnit(Unit* K) {
		if (K)
		{
			this->enqueue(K);
		}
	}

	void PrintQueue() {

		Node<Unit*>* temp = frontPtr;

		cout << "\n Killed List\n";
		while (temp)
		{


			cout << temp->getItem()->getType() << " ID :" << temp->getItem()->getID() << " ,";
			temp = temp->getNext();
		}
		cout << endl;
	}
};



