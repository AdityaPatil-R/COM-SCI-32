#include "GameObject.h"

// **************************
// * CONSTRUCTER/DESTRUCTOR *
// **************************

GameObject::GameObject(int y, int x, string nm, Level* lvl) {
    yPos = y;
    xPos = x;
    name = nm;
    level = lvl;
}

GameObject::~GameObject() { }

// ***********
// * GETTERS *
// ***********

int GameObject::getYPos() { return yPos; }

int GameObject::getXPos() { return xPos; }

string GameObject::getName() { return name; }