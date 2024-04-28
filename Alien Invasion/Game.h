#pragma once
#include "earthArmy.h"
using namespace std;

class Game
{
	Params earthData;
	Params alienData;
	earthArmy* ea = new earthArmy;
	alienArmy* aa = new alienArmy;
public:

	Game() {
		readFile(earthData, alienData);
		int x = earthData.prob;
		int z = alienData.prob;
		earthData.prob = 100;
		alienData.prob = 100;
		ea->Generate(earthData);
		aa->Generate(alienData);
		earthData.prob = x;
		alienData.prob = z;
	}

	void Go() {
		ea->state();
		aa->state();
		cout << "\n \n===============Units fight at current step===============" << "\n";
		Mode M = Interactive;
		aa->fight(ea, M);
	
		ea->state();
		aa->state();
	}
};

