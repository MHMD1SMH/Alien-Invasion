#pragma once
#include "Unit.h"
#include "Stack.h"
class earthTanks :
    public Unit
{
public:
    earthTanks() { setType("ET"); };
    earthTanks(int h, int p, int ac, int id) {
        setHealth(h);
        setPower(p);
        setAttackCapacity(ac);
        setID(id);
        setType("ET");
    };
    earthTanks(earthTanks* K) {
        this->setType(K->getType());
        this->setAttackCapacity(K->getAttackCapacity());
        this->setHealth(K->getHealth());
        this->setPower(K->getPower());
        this->setID(K->getID());
    }
    virtual bool Attack(Unit* target) override {
        float Damage = (this->getPower() * (this->getHealth() / 100.0)) / (sqrt(target->getHealth()));
        if (target) {
            target->decHel(Damage);
            return true;
        }
        else {
            return false;
        }
    };


};

