#pragma once
#include "Generator.h"
using namespace std;

class Game
{
	Params earthData;
	Params alienData;
	int timestep = 0;
	earthArmy* ea = new earthArmy;
	alienArmy* aa = new alienArmy;
public:

	Game() {
		readFile(earthData, alienData);
		int x = earthData.prob;
		int z = alienData.prob;
		earthData.prob = 100;
		alienData.prob = 100;
		earthGenerate(earthData,ea,timestep);
		alienGenerate(alienData,aa,timestep);
		earthData.prob = x;
		alienData.prob = z;
	}
	void fight(Mode M) {
	





		//Drones Fight
		Drone* AD1 = aa->getADs()->dequeueFront();
		Drone* AD2 = aa->getADs()->dequeueBack();
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
					z = (EG->getHealth() / 100.0) * EG->getPower();
					ea->getEGS()->enqueue(EG, z);
				}
				EG = NULL;
			}
			cout << " ]\n";


			if (M == Interactive)
			{
				cout << "AD " << AD2->getID() << " shots [";
			}
			for (int i = 0; i < AD1->getAttackCapacity(); i++) {
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
	void Go() {
		ea->state();
		aa->state();
		cout << "\n \n===============Units fight at current step===============" << "\n";
		Mode M = Interactive;
		fight(M);
	
		ea->state();
		aa->state();
	}
};

