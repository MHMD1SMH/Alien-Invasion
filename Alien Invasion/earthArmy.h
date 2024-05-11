#pragma once
#include "earthGunnery.h"
#include "Drone.h"
#include "earthTanks.h"
#include "Monster.h"
#include "Soliders.h"
#include "HU.h"

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
	int unit4 = 0;
};

int random(int min, int max) {
	return min + rand() % max;
}
class Killedlist : public LinkedQueue<Unit*>
{
public:
	void addUnit(Unit* K) {
		if (K)
		{
			this->enqueue(K);
		}
	}

	void state() {

		Node<Unit*>* temp = frontPtr;

		cout << "\n Killed List\n";
		cout << this->counter << " Units [";
		while (temp)
		{
			cout << temp->getItem()->getID() << ", ";
			temp = temp->getNext();
		}
		cout << "]" << endl;
	}
};
class earthArmy
{
	int id = 0;
	priQueue<earthGunnery>* EGs = new priQueue<earthGunnery>;
	LinkedQueue<ES>* ESs = new LinkedQueue<ES>;
	LinkedStack<earthTanks>* ETs = new LinkedStack<earthTanks>;

	LinkedStack<Unit*>* templist = new LinkedStack<Unit*>;

	LinkedStack<HU>* EHUs = new LinkedStack<HU>;
	priQueue<Unit*>* UML = new priQueue<Unit*>;


public:
	earthArmy() {};
	earthArmy(Params p) { };

	priQueue<earthGunnery>* getEGS() { return EGs; }
	LinkedQueue<ES>* getESs() { return ESs; }
	LinkedStack<earthTanks>* getETs() { return ETs; }

	LinkedStack<HU>* getEHUs() { return EHUs; }

	void addToUML(Unit* K) {
		int piriority;
		if (!K)
			return;

		if (K->getType() == "ES")
		{
			piriority = 100 - K->getHealth();
			UML->enqueue(K, piriority);
		}
		else if (K->getType() == "ET")
		{
			piriority = 0;
			UML->enqueue(K, piriority);

		}
	}
	void heal(int timestep,Killedlist * KL) {
		HU* temp = NULL;
		Unit** tempu = NULL;
		Unit** injurd = NULL;
		int x = 0;
		for (int i = 0; i < EHUs->getCounter(); i++)
		{
			temp = EHUs->Pop();
			for (int i = 0; i < temp->getAttackCapacity(); i++)
			{
				if (UML->isEmpty())
				{
					break;
				}
				injurd = UML->dequeue(x);

				if (timestep-(*injurd)->getTime()->getTh() >=10)
				{
					KL->addUnit(*injurd);
				}
				else {
					temp->Attack(*injurd);
					if (((*injurd)->getHealth() / (*injurd)->getInHealth()) * 100 >= 20)
					{
						if ((*injurd)->getType() == "ES")
						{
							ESs->enqueue((*injurd));
						}
						else if ((*injurd)->getType() == "ES")
						{
							ETs->Push((*injurd));
						}
					}
					else
						templist->Push(*injurd);
				}

			}
			KL->addUnit(temp);
			if (UML->isEmpty())
			{
				break;
			}
		}
		for (int i = 0; i < templist->getCounter(); i++)
		{
			this->addToUML((*templist->Pop()));
		}
	}

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

		cout << "\n" << EHUs->getCounter() << "EHU";
		EHUs->PrintStack();

	}
	bool isDead() {
		return !(EGs->isEmpty() && ESs->isEmpty() && ETs->isEmpty());
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

		cout << "\n";
		AMs->PrintArr();

		cout << "\n" << ASs->getCounter() << "AS";
		ASs->PrintQueue();
	}
	bool isDead() {
		return !(ADs->isEmpty() && ASs->isEmpty());
	}
};





