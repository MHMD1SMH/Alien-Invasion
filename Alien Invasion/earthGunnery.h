#pragma once
#include "Unit.h"
#include "priQueue.h"
class earthGunnery :
    public Unit
{

public:
    earthGunnery() { setType("EG"); };
    earthGunnery(int h, int p, int ac , int id) {
        setHealth(h);
        setPower(p);
        setAttackCapacity(ac);
        setType("EG");
        setID(id);
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
    gunneryUnites() {};
    earthGunnery* getUnit() {
        int x = 10;
        return *Gunneries.dequeue(x);
    }
    gunneryUnites(int h, int p, int ac,int id) : earthGunnery(h, p, ac,id) {
        tEG = new earthGunnery(h, p, ac,id);
        rank = (h / 100.0) * p;
        Gunneries.enqueue(tEG, rank);

    };
    void addUnit(int h, int p, int ac,int id) {
        double rank = (h / 100.0) * p;
        tEG = new earthGunnery(h, p, ac,id);
        Gunneries.enqueue(tEG, rank);
    };
    void egState() {
        priQueue <earthGunnery*> tGunneries = Gunneries;
        int x = 0;
        cout <<"\n"<< tGunneries.getCounter() << " EG" <<" [";

        while (tGunneries.print(tEG, x)) {
            cout <<'\t' << tEG->getID() <<',';
        }
        cout <<"]";
    };
};
