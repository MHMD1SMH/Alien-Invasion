#pragma once
#include "Unit.h"
class Drone : public Unit
{
public:
	Drone() {
		this->setType("Drone");
	};
	bool Attack(Unit K) {
		if (!(K.getType() == "Tank" || K.getType() == "Gunnery"))
			return false;
		K.setHealth(-this->getPower());
		return true;
	}
};

