#pragma once
#include "Unit.h"
#include "Stack.h"
class earthTanks :
    public Unit
{
public:
    earthTanks() {};
    earthTanks(int h, int p, int ac,int id) {
        setHealth(h);
        setPower(p);
        setAttackCapacity(ac);
        setType("ET");
        setID(id);
    };
    virtual bool Attack(Unit* target) {
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
class tanksUnits : public earthTanks
{
private:
    earthTanks* tET = NULL;
    LinkedStack <earthTanks*> tanks;
public:
    tanksUnits() {};
    tanksUnits(int h, int p, int ac,int id) : earthTanks(h, p, ac,id) {
        tET = new earthTanks(h, p, ac,id);
        tanks.Push(tET);

    };
    void addUnit(int h, int p, int ac,int id) {
        tET = new earthTanks(h, p, ac,id);
        tanks.Push(tET);
    };
    void etState() {
        LinkedStack <earthTanks*> tTanks = tanks;
        cout << "\nEarth Tanks units ";
        while (tTanks.Print(tET)) {
            cout << '\t' << tET->getAttackCapacity();
        }

    };



};