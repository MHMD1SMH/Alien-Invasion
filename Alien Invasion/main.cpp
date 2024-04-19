#include <iostream>
using namespace std;
#include "earthArmy.h"


void action(earthArmy& ea, alienArmy& aa, Killedlist& kl) {

	int x = random(1,60);
	if (x > 0 && x < 10) {
		ea.ESs.enqueue(ea.ESs.dequeue());
	}
	else if (x < 20) {

		kl.addUnit(ea.ETs.Pop());
	}
	else if (x < 30) {
		int z;
		priNode<earthGunnery>* ptr = ea.EGs.getHead();
		if (ptr)
		{
			earthGunnery item = ptr->getItem(z);
			while (ptr)
			{
				cout << "earthGunnery" << item.getID() << "Health is " << item.getHealth() << " before \n";
				item.decHel(item.getHealth() / 2);
				cout << "earthGunnery" << item.getID() << "Health is " << item.getHealth() << " after \n";
				ptr = ptr->getNext();
			}
		}
	}
	else if (x < 40) {
		int counter = 0;
		while (aa.ASs.getCounter() >= counter && counter <= 5) {
			aa.ASs.enqueue(aa.ASs.dequeue());
			counter++;
		}

	}
	else if (x < 50) {
		Monsters temp;
		for (int i = 0; i < 5; ++i) {
			temp.insert(aa.AMs.selectRandomMonster());
		}
		for (int i = 0; i < 5; ++i) {
			aa.AMs.insert(temp.selectRandomMonster());
		}
	}
	else if (x < 60) {
		for (int i = 0; i < 3; i++) {
			kl.addUnit(aa.ADs.dequeueFront());
		}
		for (int i = 0; i < 3; i++) {
			kl.addUnit(aa.ADs.dequeueBack());
		}
	}
};
int main() {
	Params earthData;
	Params alenData;

	readFile(earthData, alenData);

	earthArmy ea(earthData);
	alienArmy aa(alenData);
	Killedlist KL;
	ea.state();
	aa.state();
	for (int i = 0; i < 50; i++)
	{
		action(ea, aa, KL);
		ea.Generate(earthData);
		aa.Generate(alenData);
	}
	ea.state();
	aa.state();
	KL.PrintQueue();

	return 0;
}