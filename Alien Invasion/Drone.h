#pragma once
#include "Unit.h"
#include "DoubleQueue.h"

class Drone : public Unit
{
public:
	Drone() {
		this->setType("Drone");
	};
	bool Attack(Unit K) {
		if (!(K.getType() == "Tank" || K.getType() == "Gunnery"))
			return false;

		K.decHel((this->getPower()));

		return true;

	}
};

class Drones {
private:
	DoubleQueue<Drone> drones;
public:
	Drones();
	bool isEmpty() { return drones.isEmpty(); }
	void enqueue(Drone& x) { drones.enqueue(x); }
	bool deqfront(){}
};