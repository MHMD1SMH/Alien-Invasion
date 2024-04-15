#pragma once
#include "Unit.h"
#include "priQueue.h"
class earthGunnery :
    public Unit
{

public:
    earthGunnery(int h, int p, int ac) {
        setHealth(h);
        setPower(p);
        setAttackCapacity(ac);
        setType("EG");
    };
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

 
class gunneryUnites :public earthGunnery {
private:
    double rank;
    earthGunnery* tEG = NULL;
    priQueue <earthGunnery*> Gunneries;

public: 
    gunneryUnites(int h, int p, int ac) : earthGunnery(h, p, ac) {
        tEG = new earthGunnery(h, p, ac);
        rank = (h / 100.0) * p;
        Gunneries.enqueue(tEG, rank);

    };
    void addUnit(int h, int p, int ac) {
        double rank = (h / 100.0) * p;
        tEG = new earthGunnery(h, p, ac);
        Gunneries.enqueue(tEG, rank);
    };
    void egState() {
        priQueue <earthGunnery*> tGunneries = Gunneries;
        int x = 0;
        cout << "\nEarth Gunneries unites ";
        while (tGunneries.print(tEG, x)) {
            cout <<'\t' << tEG->getAttackCapacity();
        }
        tGunneries.~priQueue();
    };
};
