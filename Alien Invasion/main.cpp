#include <iostream>
using namespace std;
#include "earthArmy.h"

int main() {
	Params p;
	p.maxAttackCapacity = 5;
	p.minAttackCapacity = 3;
	p.maxHealth = 50;
	p.minHealth = 10;
	p.minPower = 5;
	p.maxPower = 25;
	p.n = 9;
	p.prob = 100;


	earthArmy ea;
	alienArmy aa;
	Killedlist KL;
	aa.Generate(0,50,90,p);
	ea.Generate(0,50,90,p);
	ea.state();
	aa.state();
	KL.addUnit(aa.ADs.dequeueBack());
	KL.addUnit(aa.ASs.dequeue());
	KL.addUnit(aa.AMs.selectRandomMonster());

	KL.addUnit(ea.EGs.getUnit());
	KL.PrintQueue();
	
	return 0;
}