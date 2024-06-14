#ifndef PLAYER_INCLUDED
#define PLAYER_INCLUDED

#include "Actor.h"
#include <vector>

class GameObject;
class Level;

class Player : public Actor {
    public:
        Player(int y, int x, Level* lvl);
        virtual ~Player();

        string attackMessage();
        void displayInventory();
        void addToInventory(GameObject* obj);
        void readScroll(int index);
        void wieldWeapon(int index);
        
        int getNumItems();
        GameObject* getInventory(int i);
        bool isAt(int y, int x);
    private:
        vector<GameObject*> inventory;
        int numItems;
};

#endif