#include <iostream>
using namespace std;

#include "Game.h"
void action(earthArmy& ea, alienArmy& aa, Killedlist& kl) {

	int x = random(1,60);
	if (x > 0 && x < 10) {
		ea.getESs()->enqueue(ea.getESs()->dequeue());
	}
	else if (x < 20) {

		kl.addUnit(ea.getETs()->Pop());
	}
	else if (x < 30) {
		int z;
		priNode<earthGunnery>* ptr = ea.getEGS()->getHead();
		if (ptr)
		{
			earthGunnery item = ptr->getItem(z);
			while (ptr)
			{
				item = ptr->getItem(z);
				cout << "earthGunnery " << item.getID() << " Health is " << item.getHealth() << " before \n";
				item.decHel(item.getHealth() / 2);
				cout << "earthGunnery " << item.getID() << " Health is " << item.getHealth() << " after \n";
				ptr = ptr->getNext();
			}
		}
	}
	else if (x < 40) {
		int counter = 0;
		while (aa.getASs()->getCounter() >= counter && counter <= 5) {
			aa.getASs()->enqueue(aa.getASs()->dequeue());
			counter++;
		}

	}
	else if (x < 50) {
		Monsters temp;
		for (int i = 0; i < 5; ++i) {
			temp.insert(aa.getAMs()->selectRandomMonster());
		}
		for (int i = 0; i < 5; ++i) {
			aa.getAMs()->insert(temp.selectRandomMonster());
		}
	}
	else if (x < 60) {
		for (int i = 0; i < 3; i++) {
			kl.addUnit(aa.getADs()->dequeueFront());
		}
		for (int i = 0; i < 3; i++) {
			kl.addUnit(aa.getADs()->dequeueBack());
		}
	}
};
int main() {
	/*Params earthData;
	Params alenData;

	readFile(earthData, alenData);

	earthArmy ea(earthData);
	alienArmy aa(alenData);
	Killedlist KL;
	ea.state();
	aa.state();
	for (int i = 0; i < 50; i++)
	{
		action(ea,aa,KL);
		ea.Generate(earthData);
		aa.Generate(alenData);
	}
	ea.state();
	aa.state();
	KL.PrintQueue();*/
	/*Game g;
	g.Go();*/

	Params earthData;
	Params alenData;
	Killedlist* KL = new Killedlist;
	readFile(earthData, alenData);
	earthArmy *aa = new earthArmy;
	earthGenerate(earthData,aa,10);
	ES* es = new ES(50, 20, 5, 50,5);
	aa->addToUML(es);
	es->decHel(48);
	es->getTime()->setTh(7);
	aa->heal(10,KL);

	KL->state();

	return 0;
}