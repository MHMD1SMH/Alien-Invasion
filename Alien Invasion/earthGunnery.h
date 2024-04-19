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


class gunneryUnites :public priQueue<earthGunnery> {

public:
    gunneryUnites() {};


    void addUnit(int h, int p, int ac, int id) {
        double rank = (h / 100.0) * p;
        earthGunnery tEG = new earthGunnery(h, p, ac, id);
        this->enqueue(tEG, rank);
    };
    void egState() {
        earthGunnery K;
        priNode<earthGunnery>* ptr;
        ptr = this->getHead();
        cout << "\n" << this->getCounter() << " EG" << " [";
        while (ptr)
        {
            int z;
            K = ptr->getItem(z);
            cout << K.getID() << ", ";
            ptr = ptr->getNext();
        }
        cout << "]" << endl;
    }
};