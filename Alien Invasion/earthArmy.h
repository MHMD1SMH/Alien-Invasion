#include "earthGunnery.h"
#include "Drone.h"
#include "earthTanks.h"
#include "Monster.h"
#include "Queue.h"
#include "Soliders.h"
#include <stdlib.h>
struct Params {
	int minHealth;
	int maxHealth;
	int minPower;
	int maxPower;
	int minAttackCapacity;
	int maxAttackCapacity;
	int n;
	int prob;
};


int random(int min , int max) {
	return min + rand() % max;
}

class earthArmy
{
	int id = 0;
public:
	gunneryUnites EGs;
	tanksUnits ETs;
	ESoliders ESs;
	earthArmy() {};

	void Generate(int S, int T, int G, const Params& par) {
		srand(time(NULL));
		int A = random(1, 100);
		if (A > par.prob)
			return;

		for (int i = 0; i < par.n; i++)
		{
			int B = random(1, 100);
			int h = random(par.minHealth, par.maxHealth);
			int p = random(par.minPower, par.maxPower);
			int c = random(par.minAttackCapacity, par.maxAttackCapacity);
			id++;
			if (B < S)
			{
				ESs.addUnit(h,p,c,id);
			}
			else if (B < S + T)
			{
				ETs.addUnit(h, p, c, id);
			}
			else
			{

				EGs.addUnit(h, p, c, id);
			}
		}
	};
	void state() {
		cout << "\n===============Earth Army Alive Units===============" <<"\n";
		ETs.etState();
		EGs.egState();
		ESs.PrintQueue();
	}
};


class alienArmy
{
	int id = 2000;
public:
	
	Drones ADs;
	Monsters AMs;
	ASoliders ASs;
	alienArmy() {};

	void Generate(int S, int M, int D, const Params& par) {
		srand(time(NULL));
		int A = random(1, 100);
		if (A > par.prob)
			return;

		for (int i = 0; i < par.n; i++)
		{
			id++;
			int B = random(1, 100);
			int h = random(par.minHealth, par.maxHealth);
			int p = random(par.minPower, par.maxPower);
			int c = random(par.minAttackCapacity, par.maxAttackCapacity);
			if (B < S)
			{
				ASs.addUnit(h,p,c,id);
			}
			else if (B < S + M)
			{
				AMs.addUnit(h,p,c,id);
			}
			else
			{

				ADs.addUnit(h, p, c,id);
			}
		}
	}
	void state() {
		cout << "\n \n===============Alien Army Alive Units===============" << "\n";
		ADs.PrintQueue();
		AMs.PrintArr();
		ASs.PrintQueue();
	}
};

class Killedlist : public LinkedQueue<Unit*>
{
public:
	void addUnit(Unit * K) {
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