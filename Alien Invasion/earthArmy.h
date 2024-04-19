#include "earthGunnery.h"
#include "Drone.h"
#include "earthTanks.h"
#include "Monster.h"
#include "Queue.h"
#include "Soliders.h"
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
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
public:
	gunneryUnites EGs;
	tanksUnits ETs;
	ESoliders ESs;
	earthArmy() {};
	earthArmy(Params p) { p.prob = 100; this->Generate(p); };

	void Generate(const Params& par) {
		srand(time(NULL));
		int A = random(1, 100);
		if (A > par.prob)
			return;

		for (int i = 0; i < par.n; i++)
		{
			int B = random(1,100);
			int h = random(par.minHealth, par.maxHealth);
			int p = random(par.minPower, par.maxPower);
			int c = random(par.minAttackCapacity, par.maxAttackCapacity);
			id++;
			if (B < par.unit1)
			{
				ESs.addUnit(h, p, c, id);
			}
			else if (B < par.unit1 + par.unit2)
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
		cout << "\n===============Earth Army Alive Units===============" << "\n";
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
	alienArmy(Params p) { p.prob = 100; this->Generate(p); };

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
				ASs.addUnit(h, p, c, id);
			}
			else if (B < par.unit1 + par.unit2)
			{
				AMs.addUnit(h, p, c, id);
			}
			else
			{

				ADs.addUnit(h, p, c, id);
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



void readFile(Params& earthdata, Params &aliendata) {
	// Open the file
	ifstream file("gameDesign.txt");
	int c = 0;
	// Check if the file is opened successfully
	if (!file.is_open()) {
		cerr << "Error: Unable to open file gameDesign.txt "  << endl;
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
				}
				c++;
				
				}
			}
			c = 0;
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
				}
				c++;
				}
			}
			c = 0;
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
			}
			c = 0;
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
					}
					c++;
				}
			}
			c = 0;
			break;
		}

		lineCount++;
	}

	// Close the file
	file.close();
}