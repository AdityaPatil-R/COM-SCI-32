#ifndef GAMEOBJECT_INCLUDED
#define GAMEOBJECT_INCLUDED

#include <string>

using namespace std;

class Level;

class GameObject {
    public:
        GameObject(int y, int x, string nm, Level* lvl);
        virtual ~GameObject();
        
        int getYPos();
        int getXPos();
        virtual char getSymbol() = 0;
        string getName();
        virtual string extraMessage() = 0;
    private:
        int yPos;
        int xPos;
        string name;
    protected:
        Level* level;
};

#endif