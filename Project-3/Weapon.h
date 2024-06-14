#ifndef WEAPON_INCLUDED
#define WEAPON_INCLUDED

#include "GameObject.h"

class Weapon : public GameObject {
    public:
        Weapon(int y, int x, string nm, string actStr, int dexBon, int damAmt, Level* lvl);
        ~Weapon();
        
        string getActionString();
        char getSymbol();
        string extraMessage();
        virtual void wield() = 0;
        int getDexterityBonus();
        int getDamageAmount();
    private:
        string actionString;
        int dexterityBonus;
        int damageAmount;
};

class Mace : public Weapon {
    public:
        Mace(int y, int x, Level* lvl);
        virtual void wield();
    private:

};

class ShortSword : public Weapon {
    public:
        ShortSword(int y, int x, Level* lvl);
        virtual void wield();
    private:

};

class LongSword : public Weapon {
    public:
        LongSword(int y, int x, Level* lvl);
        virtual void wield();
    private:

};

class MagicAxe : public Weapon {
    public:
        MagicAxe(int y, int x, Level* lvl);
        virtual void wield();
    private:

};

class MagicFangsOfSleep : public Weapon {
    public:
        MagicFangsOfSleep(int y, int x, Level* lvl);
        virtual void wield();
    private:

};

#endif