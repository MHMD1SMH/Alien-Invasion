#include <iostream>
using namespace std;
#include "Drone.h"
#include "earthArmy.h"

int main() {
	Params p;
	p.maxAttackCapacity = 5;
	p.minAttackCapacity = 3;
	p.maxHealth = 50;
	p.minHealth = 10;
	p.minPower = 5;
	p.maxPower = 25;
	p.n = 7;
	p.prob = 100;


	earthArmy ea;
	alienArmy aa;
	aa.Generate(0,50,90,p);
	ea.Generate(0,50,90,p);
	ea.EGs.egState();
	aa.ADs.PrintQueue();
	return 0;
}