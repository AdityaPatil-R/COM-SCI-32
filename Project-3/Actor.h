#ifndef ACTOR_INCLUDED
#define ACTOR_INCLUDED

#include <string>

using namespace std;

class Weapon;
class Level;

class Actor {
    public:
        // Constructor/Destructor
        Actor(int y, int x, int hp, int mhp, Weapon* wpn, int arm, int str, int dex, int slp, Level* lvl);
        virtual ~Actor();
        virtual string attackMessage() = 0;

        // Getters
        int getYPos();
        int getXPos();
        int getHitPoints();
        int getMaximumHitPoints();
        Weapon* getWeapon();
        int getArmorPoints();
        int getStrengthPoints();
        int getDexterityPoints();
        int getSleepTime();
        Level* getLevel();
        string getActorName();
        bool getMoved();

        // Setters
        void setYPos(int y);
        void setXPos(int x);
        void setHitPoints(int hp);
        void setMaximumHitpoints(int mhp);
        void setWeapon(Weapon* w);
        void setArmorPoints(int arm);
        void setStrengthPoints(int str);
        void setDexterityPoints(int dex);
        void setSleepTime(int slp);
        void setLevel(Level* lvl);
        void setName(string nm);
        void setMoved(bool m);

        // Actions
        void increaseArmorPoints(int amount);
        void increaseStrengthPoints(int amount);
        void increaseMaximumHitPoints(int amount);
        void increaseDexterityPoints(int amount);

        bool isAsleep();
    private:
        int yPos;
        int xPos;
        int hitPoints;
        int maxHitPoints;
        Weapon* weapon;
        int armorPoints;
        int strengthPoints;
        int dexterityPoints;
        int sleepTime;
        string name;
        bool moved;
    protected:
        Level* level;
};

#endif 