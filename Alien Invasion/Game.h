#pragma once
#include <algorithm>
#include <string>
#include"GUI.h"
using namespace std;

class Game
{
	GUI* Gui;
	Mode M =Interactive;
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
	void fight(Mode M, int timestep) {

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
				Gui->startShooting(M, ET->getType(), ET->getID());
				for (int i = 0; i < ET->getAttackCapacity(); i++) {
					if (i % 2 == 0 && (aa->getAMs()->counter() != 0))
					{
						Monster* AM = aa->getAMs()->selectRandomMonster();
						ET->Attack(AM);
						AM->getTime()->setTa(timestep);
						Gui->ShootedId(M, AM->getID());
						if (AM->getHealth() > 0)
						{
							aa->getAMs()->insert(AM);
						}
						else
						{
							AM->getTime()->setTd(timestep);
							Kl->addUnit(AM);
						}
					}
					else if(!aa->getASs()->isEmpty())
					{
						AS* AS = aa->getASs()->dequeue();
						ET->Attack(AS);
						AS->getTime()->setTa(timestep);
						Gui->ShootedId(M, AS->getID());
						if (AS->getHealth() > 0)
						{
							aa->getASs()->enqueue(AS);
						}
						else
						{
							AS->getTime()->setTd(timestep);
							Kl->addUnit(AS);
						}
					}
				}
				Gui->endShooting(M);
			}
			else if (aa->getAMs()->counter() > 0) {
				Gui->startShooting(M, ET->getType(), ET->getID());
				for (int i = 0; i < ET->getAttackCapacity(); i++) {
					Monster* AM = aa->getAMs()->selectRandomMonster();
					ET->Attack(AM);
					AM->getTime()->setTa(timestep);
					Gui->ShootedId(M, AM->getID());
					if (AM->getHealth() > 0)
					{
						aa->getAMs()->insert(AM);
					}
					else
					{
						AM->getTime()->setTd(timestep);
						Kl->addUnit(AM);
					}

				}
				Gui->endShooting(M);

			}


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
				if (i % 2 == 0 && (!aa->getADs()->isEmpty()))
				{
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
						//else if (AD2 != AD1) {  // Check if it's not the same drone recycled
						//	///aa->getADs()->enqueueBack(rearDrone);
						//}
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


		if (!aa->getADs()->isEmpty() && aa->getADs()->getCounter() > 1)
		{
			Drone* AD1 = aa->getADs()->dequeueFront();
			Drone* AD2 = aa->getADs()->dequeueBack();
			earthGunnery* EG;
			earthTanks* ET;
			int z = 0;
			int maxcap = max(AD1->getAttackCapacity(), AD2->getAttackCapacity());
			string ids1 = "";
			string ids2 = "";
			for (int i = 0; i < maxcap; i++) {
				if (ea->getEGS()->isEmpty() && ea->getETs()->isEmpty())
				{
					break;
				}
				if (timestep % 2 == 0 && (!ea->getEGS()->isEmpty()))
				{
					EG = ea->getEGS()->dequeue(z);
					if (i < AD1->getAttackCapacity())
					{
						AD1->Attack(EG);
						ids1 += (to_string(EG->getID()) += ", ");

					}
					if (i < AD2->getAttackCapacity())
					{
						AD2->Attack(EG);
						ids2 += (to_string(EG->getID()) += ", ");

					}
					EG->getTime()->setTa(timestep);
					if (EG->getHealth()>0)
					{
						z = (EG->getHealth() / 100.0) * EG->getPower();
						ea->getEGS()->enqueue(EG, z);
					}
					else
					{
						EG->getTime()->setTd(timestep);
						Kl->addUnit(EG);
					}
					EG = NULL;
				}
				else if (timestep % 2 == 1 && ( !ea->getETs()->isEmpty()))
				{
					ET = ea->getETs()->Pop();
					AD1->Attack(ET);
					if (i < AD1->getAttackCapacity())
					{
						AD1->Attack(ET);
						ids1 += (to_string(ET->getID()) += ", ");

					}
					if (i < AD2->getAttackCapacity())
					{
						AD2->Attack(ET);
						ids2 += (to_string(ET->getID()) += ", ");

					}
					ET->getTime()->setTa(timestep);
					if ((ET->getHealth() / ET->getInHealth() * 100) >= 20)
					{
						ea->getETs()->Push(ET);
					}
					else if (ET->getHealth() <= 0)
					{
						ET->getTime()->setTd(timestep);
						Kl->addUnit(ET);
					}
					else {
						ET->getTime()->setTh(timestep);
						ea->addToUML(ET);
					}
					ET = NULL;

				}
			}
			Gui->startShooting(M, AD1->getType(), AD1->getID());
			Gui->printMSG(M, ids1);
			Gui->endShooting(M);
			Gui->startShooting(M, AD2->getType(), AD2->getID());
			Gui->printMSG(M, ids2);
			Gui->endShooting(M);

			aa->getADs()->enqueue(AD1);
			aa->getADs()->enqueue(AD2);
			cout << " \n";

		}


		Monster* s;
		s = aa->getAMs()->selectRandomMonster();

		if (s && ea->getESs()->isEmpty() && ea->getETs()->isEmpty()) {
			Gui->startShooting(M, s->getType(), s->getID());
			for (int i = 0; i < s->getAttackCapacity(); i++) {

				if (!ea->getETs()->isEmpty()) {

					earthTanks* tank = ea->getETs()->Pop();

					s->Attack(tank);
					tank->getTime()->setTa(timestep);
					Gui->ShootedId(M, tank->getID());
					if ((tank->getHealth() / tank->getInHealth() * 100) >= 20)
					{
						ea->getETs()->Push(tank);
					}
					else if (tank->getHealth() <= 0) {
						tank->getTime()->setTd(timestep);
						Kl->addUnit(tank);
					}
					else {
						tank->getTime()->setTh(timestep);
						ea->addToUML(tank);
					}
				}
				else if (!ea->getESs()->isEmpty()) {
					ES* soldier = ea->getESs()->dequeue();

					s->Attack(soldier);
					soldier->getTime()->setTa(timestep);
					if ((soldier->getHealth() / soldier->getInHealth() * 100) >= 20)
					{
						ea->getETs()->Push(soldier);
					}
					else if (soldier->getHealth() <= 0) {
						soldier->getTime()->setTd(timestep);
						Kl->addUnit(soldier);
					}
					else {
						soldier->getTime()->setTh(timestep);
						ea->addToUML(soldier);
					}
				}
				else {

					break;
				}
				Gui->endShooting(M);
			}
			aa->getAMs()->insert(s);
		}


	}



	void Go() {
		while (!ea->isDead()&&!aa->isDead() )
		{

			Gui->printTimeStepState(M, this->ea, this->aa,timestep);
			fight(M, timestep);
			ea->heal(timestep,Kl);

			Gui->printTimeStepStateKL(M, this->Kl);
			timestep++;
		}

		if (ea->isDead() && aa->isDead() )
		{
			Gui->printWinningMSG(M, "No one");
		}
		else if (ea->isDead() && !aa->isDead()) {
			Gui->printWinningMSG(M, "Alien Army");
		}
		else
		{
			Gui->printWinningMSG(M, "Earth Army");
		}
	}
};