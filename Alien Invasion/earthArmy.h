#include "earthGunnery.h"
#include "Drone.h"
#include <stdlib.h>
struct Params {
	int minHealth;
	int maxHealth;
	int minPower;
	int maxPower;
	int minAttackCapacity;
	int maxAttackCapacity;
	int n;
	int prob;
};

int random(int min , int max) {
	return min + rand() % max;
}

class earthArmy
{
public:
	gunneryUnites EGs;
	earthArmy() {};

	void Generate(int S, int T, int G ,const Params& par) {
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
			if (B < S)
			{

			}
			else if (B < S+T)
			{

			}
			else
			{

				EGs.addUnit(h,p,c);
			}
		}
	}
};


class alienArmy
{
public:
	Drones ADs;
	alienArmy() {};

	void Generate(int S, int M, int D, const Params& par) {
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
			if (B < S)
			{

			}
			else if (B < S + M)
			{

			}
			else
			{

				ADs.addUnit(h, p, c);
			}
		}
	}
};