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
	earthArmy(Params p) { p.prob = 100; this->Generate(p); };

	priQueue<earthGunnery>* getEGS() { return EGs; }
	LinkedQueue<ES>* getESs() { return ESs; }
	LinkedStack<earthTanks>* getETs() { return ETs; }

	void Generate(const Params& par) {
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
			if (B < par.unit1)
			{
				ESs->enqueue(ES(h, p, c, id));
			}
			else if (B < par.unit1 + par.unit2)
			{
				ETs->Push(earthTanks(h, p, c, id));
			}
			else
			{
				double rank = (h / 100.0) * p;
				EGs->enqueue(earthGunnery(h, p, c, id), rank);
			}
		}
	};
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
	alienArmy(Params p) { p.prob = 100; this->Generate(p); };

	DoubleQueue<Drone>* getADs() { return ADs; }
	LinkedQueue<AS>* getASs() { return ASs; }
	Monsters* getAMs() { return AMs; }

	void Generate(const Params& par) {
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
			if (B < par.unit1)
			{
				ASs->enqueue(AS(h, p, c, id));
			}
			else if (B < par.unit1 + par.unit2)
			{
				AMs->addUnit(h, p, c, id);
			}
			else
			{

				ADs->enqueue(Drone(h, p, c, id));
			}
		}
	}
	void state() {
		cout << "\n \n===============Alien Army Alive Units===============" << "\n";

		cout << "\n" << ADs->getCounter() << "AD";
		ADs->PrintQueue();

		AMs->PrintArr();

		cout << "\n" << ASs->getCounter() << "AS";
		ASs->PrintQueue();
	}
	void fight(earthArmy* ea, const Mode& M) {






		//Drones Fight
		Drone* AD1 = this->ADs->dequeueFront();
		Drone* AD2 = this->ADs->dequeueBack();
		if (AD1 && AD2)
		{
			int z = 0;
			if (M == Interactive)
			{
				cout << "AD " << AD1->getID() << " shots [";
			}
			for (int i = 0; i < AD1->getAttackCapacity(); i++) {
				earthGunnery* EG = ea->getEGS()->dequeue(z);
				AD1->Attack(EG);
				if (M == Interactive)
				{
					cout << EG->getID() << ", ";
				}
				if (EG->getHealth() > 0)
				{

					ea->getEGS()->enqueue(EG, z);
				}
				EG = NULL;
			}
			cout << " ]\n";


			if (M == Interactive)
			{
				cout << "AD " << AD2->getID() << " shots [";
			}
			for (int i = 0; i<AD1->getAttackCapacity(); i++) {
				earthTanks* ET = ea->getETs()->Pop();
				AD1->Attack(ET);
				if (M == Interactive)
				{
					cout << ET->getID() << ", ";
				}
				if (ET->getHealth() > 0)
				{


					ea->getETs()->Push(ET);
				}
				ET = NULL;
			}
			cout << " ]\n";
		}
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



void readFile(Params& earthdata, Params& aliendata) {
	// Open the file
	ifstream file("gameDesign.txt");

	int c = 0;
	// Check if the file is opened successfully
	if (!file.is_open()) {
		cerr << "Error: Unable to open file gameDesign.txt " << endl;
		return;
	}

	// Read data from the file


	string line;
	int lineCount = 0;
	while (getline(file, line)) {
		istringstream iss(line);
		string token;

		switch (lineCount) {
		case 0: // Number of units
			earthdata.n = stoi(line);
			aliendata.n = stoi(line);
			break;
		case 1: // Earth army percentages
			while (iss >> token) {
				size_t pos = token.find('-');
				if (pos != string::npos) {
					// If it's a range (e.g., "3-50"), ignore for now
					continue;
				}
				else {
					// If it's a single number, convert and store as percentage
					if (c == 0)
					{
						earthdata.unit1 = stoi(token);
					}
					else if (c == 1)
					{
						earthdata.unit2 = stoi(token);
					}
					else if (c == 2)
					{
						earthdata.unit3 = stoi(token);
					}c++;
				}
			}c = 0;
			break;
		case 2: // Alien army percentages
			while (iss >> token) {
				size_t pos = token.find('-');
				if (pos != string::npos) {
					// if it's a range (e.g., "3-50"), ignore for now
					continue;
				}
				else {
					// If it's a single number, convert and store as percentage
					if (c == 0)
					{
						aliendata.unit1 = stoi(token);
					}
					else if (c == 1)
					{
						aliendata.unit2 = stoi(token);
					}
					else if (c == 2)
					{
						aliendata.unit3 = stoi(token);
					}c++;
				}
			}c = 0;
			break;
		case 3: // Probabilty
			earthdata.prob = stoi(line);
			aliendata.prob = stoi(line);
			break;
		case 4:
			while (iss >> token) {
				size_t pos = token.find('-');
				if (pos != string::npos) {
					// If it's a range (e.g., "3-50"), extract start and end values
					int start = stoi(token.substr(0, pos));
					int end = stoi(token.substr(pos + 1));
					if (c == 0)
					{
						earthdata.minPower = start;
						earthdata.maxPower = end;
					}
					else if (c == 1)
					{
						earthdata.minHealth = start;
						earthdata.maxHealth = end;
					}
					else if (c == 2)
					{
						earthdata.minAttackCapacity = start;
						earthdata.maxAttackCapacity = end;
					}
					c++;
				}
			}c = 0;
			break;
		case 5:
			while (iss >> token) {
				size_t pos = token.find('-');
				if (pos != string::npos) {
					// If it's a range (e.g., "3-50"), extract start and end values
					int start = stoi(token.substr(0, pos));
					int end = stoi(token.substr(pos + 1));
					if (c == 0)
					{
						aliendata.minPower = start;
						aliendata.maxPower = end;
					}
					else if (c == 1)
					{
						aliendata.minHealth = start;
						aliendata.maxHealth = end;
					}
					else if (c == 2)
					{
						aliendata.minAttackCapacity = start;
						aliendata.maxAttackCapacity = end;
					}c++;
				}
			}
			c = 0;
			break;
		}lineCount++;
	}

	file.close();
}