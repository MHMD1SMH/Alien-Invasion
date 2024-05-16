#pragma once
#include "Generator.h"
class GUI
{
public:

	void printTimeStepState(Mode m, earthArmy* ea, alienArmy* aa,int timestep) {

		if (m == Interactive) {
			cout << "current timestep " << timestep;
			ea->state();
			aa->state();
			cout << "\n \n===============Units fight at current step===============" << "\n";
		}


	}
	void startShooting(Mode m, string type, int id) {

		if (m == Interactive) {
			cout << type << " " << id << " " << "shots [";
		}
	}
	void ShootedId(Mode m, int id) {

		if (m == Interactive) {
			cout << id << ", ";
		}
	}
	void endShooting(Mode m) {

		if (m == Interactive) {
			cout << "]";
		}
	}
	void printTimeStepStateKL(Mode m, Killedlist* Kl) {

		if (m == Interactive) {
			Kl->state();
		}
	}
	void printMSG(Mode m, string msg) {

		if (m == Interactive) {
			cout << msg;
		}
	}
	void printWinningMSG(Mode M ,string winnername) {
		if (M==Interactive)
		{
			cout << winnername << " Is The Winner";
		}
	}

};