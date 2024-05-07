#pragma once
#include "earthArmy.h"


void readFile(Params& earthdata, Params& aliendata) {
	// Open the file
	ifstream file("gameDesign.txt");

	int c = 0;
	// Check if the file is opened successfully
	if (!file.is_open()) {
		cerr << "Error: Unable to open file gameDesign.txt " << endl;
		return;
	}

	// Read data from the file


	string line;
	int lineCount = 0;
	while (getline(file, line)) {
		istringstream iss(line);
		string token;

		switch (lineCount) {
		case 0: // Number of units
			earthdata.n = stoi(line);
			aliendata.n = stoi(line);
			break;
		case 1: // Earth army percentages
			while (iss >> token) {
				size_t pos = token.find('-');
				if (pos != string::npos) {
					// If it's a range (e.g., "3-50"), ignore for now
					continue;
				}
				else {
					// If it's a single number, convert and store as percentage
					if (c == 0)
					{
						earthdata.unit1 = stoi(token);
					}
					else if (c == 1)
					{
						earthdata.unit2 = stoi(token);
					}
					else if (c == 2)
					{
						earthdata.unit3 = stoi(token);
					}c++;
				}
			}c = 0;
			break;
		case 2: // Alien army percentages
			while (iss >> token) {
				size_t pos = token.find('-');
				if (pos != string::npos) {
					// if it's a range (e.g., "3-50"), ignore for now
					continue;
				}
				else {
					// If it's a single number, convert and store as percentage
					if (c == 0)
					{
						aliendata.unit1 = stoi(token);
					}
					else if (c == 1)
					{
						aliendata.unit2 = stoi(token);
					}
					else if (c == 2)
					{
						aliendata.unit3 = stoi(token);
					}else if (c == 3)
					{
						aliendata.unit4 = stoi(token);
					}c++;
				}
			}c = 0;
			break;
		case 3: // Probabilty
			earthdata.prob = stoi(line);
			aliendata.prob = stoi(line);
			break;
		case 4:
			while (iss >> token) {
				size_t pos = token.find('-');
				if (pos != string::npos) {
					// If it's a range (e.g., "3-50"), extract start and end values
					int start = stoi(token.substr(0, pos));
					int end = stoi(token.substr(pos + 1));
					if (c == 0)
					{
						earthdata.minPower = start;
						earthdata.maxPower = end;
					}
					else if (c == 1)
					{
						earthdata.minHealth = start;
						earthdata.maxHealth = end;
					}
					else if (c == 2)
					{
						earthdata.minAttackCapacity = start;
						earthdata.maxAttackCapacity = end;
					}
					c++;
				}
			}c = 0;
			break;
		case 5:
			while (iss >> token) {
				size_t pos = token.find('-');
				if (pos != string::npos) {
					// If it's a range (e.g., "3-50"), extract start and end values
					int start = stoi(token.substr(0, pos));
					int end = stoi(token.substr(pos + 1));
					if (c == 0)
					{
						aliendata.minPower = start;
						aliendata.maxPower = end;
					}
					else if (c == 1)
					{
						aliendata.minHealth = start;
						aliendata.maxHealth = end;
					}
					else if (c == 2)
					{
						aliendata.minAttackCapacity = start;
						aliendata.maxAttackCapacity = end;
					}c++;
				}
			}
			c = 0;
			break;
		}lineCount++;
	}

	file.close();
}

void earthGenerate(const Params& par , earthArmy* ea ,int timesep) {
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
		ea->setID();
		if (B < par.unit1)
		{
			ea->getESs()->enqueue(ES(h, p, c, ea->getID(), timesep));
		}
		else if (B < par.unit1 + par.unit2)
		{
			ea->getETs()->Push(earthTanks(h, p, c, ea->getID(), timesep));
		}
		else if (B < par.unit1 + par.unit2 + par.unit3)
		{
			double rank = (h / 100.0) * p;
			ea->getEGS()->enqueue(earthGunnery(h, p, c, ea->getID(), timesep), rank);
		}
		else
		{
			ea->getEHUs()->Push(HU(h,p,c, ea->getID(), timesep));
		}
	}
};

void alienGenerate(const Params& par,alienArmy* aa,int timesep) {
	srand(time(NULL));
	int A = random(1, 100);
	if (A > par.prob)
		return;

	for (int i = 0; i < par.n; i++)
	{
		aa->setID();
		int B = random(1, 100);
		int h = random(par.minHealth, par.maxHealth);
		int p = random(par.minPower, par.maxPower);
		int c = random(par.minAttackCapacity, par.maxAttackCapacity);
		if (B < par.unit1)
		{
			aa->getASs()->enqueue(AS(h, p, c, aa->getID(), timesep));
		}
		else if (B < par.unit1 + par.unit2)
		{
			aa->getAMs()->addUnit(h, p, c, aa->getID(), timesep);
		}
		else
		{

			aa->getADs()->enqueue(Drone(h, p, c, aa->getID(), timesep));
		}
	}
}