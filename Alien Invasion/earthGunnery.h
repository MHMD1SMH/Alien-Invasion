#pragma once
#include "Unit.h"
#include "priQueue.h"
class earthGunnery :
    public Unit
{

public:
    earthGunnery() { setType("EG"); };
    earthGunnery(int h, int p, int ac, int id) {
        setHealth(h);
        setPower(p);
        setAttackCapacity(ac);
        setType("EG");
        setID(id);
    };
    earthGunnery(earthGunnery* K) {
        this->setType(K->getType());
        this->setAttackCapacity(K->getAttackCapacity());
        this->setHealth(K->getHealth());
        this->setPower(K->getPower());
        this->setID(K->getID());
    }
    virtual bool Attack(Unit* target) override {
        float Damage = (this->getPower() * (this->getHealth() / 100)) / (sqrt(target->getHealth()));
        if (target) {
            target->decHel(Damage);
            return true;
        }
        else {
            return false;
        }
    };

};


