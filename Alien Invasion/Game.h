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
	Killedlist* Kl = new Killedlist;
	bool belowThirty = false;
public:

	Game() {
		readFile(earthData, alienData);
		int x = earthData.prob;
		int z = alienData.prob;
		earthData.prob = 100;
		alienData.prob = 100;
		earthGenerate(earthData, ea, timestep);
		alienGenerate(alienData, aa, timestep);
		earthData.prob = x;
		alienData.prob = z;
	}
	void fight(Mode M) {

		/// ET FIGHT LOGIC
		if (!ea->getETs()->isEmpty()) {
			float soldierRatio = 100.0; // default for as = 0

			if (!aa->getASs()->isEmpty())
				soldierRatio = (static_cast <float>(ea->getESs()->getCounter()) / aa->getASs()->getCounter()) * 100.0;
			if (!belowThirty && soldierRatio <= 30) // Tracking the Ratio
				belowThirty = true;
			else if (belowThirty && soldierRatio >= 80)
				belowThirty = false;
			earthTanks* ET = ea->getETs()->Pop();
			if (belowThirty || (aa->getAMs()->counter() == 0 && soldierRatio != 100)) {
				if (M == Interactive)
				{
					cout << "ET " << ET->getID() << " shots [";
				}
				for (int i = 0; i < ET->getAttackCapacity(); i++) {
					if (i % 2 == 0 && (aa->getAMs()->counter() != 0)) {
						Monster* AM = aa->getAMs()->selectRandomMonster();
						ET->Attack(AM);

						if (M == Interactive)
						{
							cout << AM->getID() << ", ";
						}
						if (AM->getHealth() > 0)
						{
							aa->getAMs()->insert(AM);
						}
						else
						{
							Kl->addUnit(AM);
						}
					}
					else {
						AS* AS = aa->getASs()->dequeue();
						ET->Attack(AS);
						if (M == Interactive)
						{
							cout << AS->getID() << ", ";
						}
						if (AS->getHealth() > 0)
						{
							aa->getASs()->enqueue(AS);
						}
						else
						{
							Kl->addUnit(AS);
						}
					}
				}
			}
			else if (aa->getAMs()->counter() > 0) {
				if (M == Interactive)
				{
					cout << "ET " << ET->getID() << " shots [";
				}
				for (int i = 0; i < ET->getAttackCapacity(); i++) {
					Monster* AM = aa->getAMs()->selectRandomMonster();
					ET->Attack(AM);

					if (M == Interactive)
					{
						cout << AM->getID() << ", ";
					}
					if (AM->getHealth() > 0)
					{
						aa->getAMs()->insert(AM);
					}
					else
					{
						Kl->addUnit(AM);
					}

				}

			}

			cout << " ]\n";
			ea->getETs()->Push(ET);
		}
		/// EG FIGHT LOGIC 

		// EG Fight Logic
		if (!ea->getEGS()->isEmpty()) {
			int z = 0;
			earthGunnery* EG = ea->getEGS()->dequeue(z); // Assumes top() gives the highest priority EG based on your criteria

			if (M == Interactive) {
				cout << "EG " << EG->getID() << " shots [";
			}

			// EG can attack drones and monsters according to its attack capacity
			for (int i = 0; i < EG->getAttackCapacity(); ++i) {
				// Handling drone attacks - attacks one from the front and one from the back of the list
				if (i % 2 == 0 && (!aa->getADs()->isEmpty())) {
					Drone* AD1 = aa->getADs()->dequeueFront();
					Drone* AD2;
					if (!aa->getADs()->isEmpty())
						AD2 = aa->getADs()->dequeueBack();
					else
						AD2 = nullptr;


					if (AD1) {
						EG->Attack(AD1);
						if (M == Interactive) {
							cout << AD1->getID() << ", ";
						}
						if (AD1->getHealth() <= 0) {
							Kl->addUnit(AD1);
						}
						else {
							aa->getADs()->enqueue(AD1);
						}
					}

					if (AD2) {
						EG->Attack(AD2);
						if (M == Interactive) {
							cout << AD2->getID() << ", ";
						}
						if (AD2->getHealth() <= 0) {
							Kl->addUnit(AD2);
						}
						else if (AD2 != AD1) {  // Check if it's not the same drone recycled
							///aa->getADs()->enqueueBack(rearDrone);
						}
					}
				}

				// Handling monster attacks - select a random monster to attack
				else if (aa->getAMs()->counter() > 0) {
					Monster* AM = aa->getAMs()->selectRandomMonster();
					EG->Attack(AM);
					if (M == Interactive) {
						cout << AM->getID() << ", ";
					}
					if (AM->getHealth() <= 0) {
						Kl->addUnit(AM);
					}
					else {
						aa->getAMs()->insert(AM);
					}
				}
			}

			cout << " ]\n";
			ea->getEGS()->enqueue(EG, z);
		}




		//Drones Fight
		Drone* AD1 = aa->getADs()->dequeueFront();
		Drone* AD2 = aa->getADs()->dequeueBack();


		if (AD1 != AD2 && !aa->getADs()->isEmpty())
		{
			earthGunnery* EG;
			earthTanks* ET;
			int z = 0;
			if (M == Interactive)
			{
				cout << "AD " << AD1->getID() << " shots [";
			}
			for (int i = 0; i < AD1->getAttackCapacity(); i++) {
				if (ea->getEGS()->isEmpty())
				{
					break;
				}
				EG = ea->getEGS()->dequeue(z);
				AD1->Attack(EG);
				if (M == Interactive)
				{
					cout << EG->getID() << ", ";
				}
				if (EG->getHealth())
				{
					z = (EG->getHealth() / 100.0) * EG->getPower();
					ea->getEGS()->enqueue(EG, z);
				}
				else
				{
					Kl->addUnit(EG);
				}
				EG = NULL;
			}
			cout << " ]\n";


			if (M == Interactive)
			{
				cout << "AD " << AD2->getID() << " shots [";
			}
			for (int i = 0; i < AD1->getAttackCapacity(); i++) {
				if (ea->getETs()->isEmpty())
				{
					break;
				}
				ET = ea->getETs()->Pop();
				AD1->Attack(ET);
				if (M == Interactive)
				{
					cout << ET->getID() << ", ";
				}
				if ((ET->getHealth() / ET->getInHealth() * 100) >= 20)
				{
					ea->getETs()->Push(ET);
				}
				else if (ET->getHealth() <= 0)
				{
					Kl->addUnit(ET);
				}
				else
					ea->addToUML(ET);
				ET = NULL;
			}
			cout << " ]\n";
		}
		if (AD1)
			aa->getADs()->enqueue(AD1);
		if (AD2)
			aa->getADs()->enqueue(AD2);

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

