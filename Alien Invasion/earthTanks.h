#pragma once
#include "Unit.h"
class earthTanks :
    public Unit
{
private:

public:
    earthTanks(int h, int p, int ac);
    virtual bool Attack(Unit* target);


};

earthTanks::earthTanks(int h, int p, int ac) {
    setHealth(h);
    setPower(p);
    setAttackCapacity(ac);
    setType("ET");
};
bool earthTanks::Attack(Unit* target) {
    float Damage = (this->getPower() * (this->getHealth() / 100.0)) / (sqrt(target->getHealth()));
    if (target) {
        target->decHel(Damage);
        return true;
    }
    else {
        return false;
    }
};