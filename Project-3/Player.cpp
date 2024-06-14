#include "Player.h"
#include "Weapon.h"
#include "Actor.h"
#include "Scroll.h"

#include <iostream>

using namespace std;

// **************************
// * CONSTRUCTER/DESTRUCTOR *
// **************************

Player::Player(int y, int x, Level* lvl) : Actor(y, x, 20, 20, new ShortSword(-1, -1, lvl), 2, 2, 2, 0, lvl) {
    inventory.push_back(Actor::getWeapon());
    numItems = 1;
    setName("Player");
}

Player::~Player() {
    for (auto it = inventory.begin(); it != inventory.end(); it++) {
        delete *it;
    }

    inventory.clear();
}

// ***********
// * GETTERS *
// ***********

int Player::getNumItems() {
    return numItems;
}

GameObject* Player::getInventory(int i) {
    return inventory[i];
}

bool Player::isAt(int y, int x) {
    return (Actor::getYPos() == y && Actor::getXPos() == x);
}

// ***********
// * ACTIONS *
// ***********

string Player::attackMessage() {
    return "Player " + Actor::getWeapon()->getActionString();
}

void Player::displayInventory() {
    cout << "Inventory:" << endl;
    for (int i = 0; i < numItems; i++) {
        cout << " " << char('a' + i) << ". " << inventory[i]->getName() << endl;
    }
}

void Player::addToInventory(GameObject* obj) {
    inventory.push_back(obj);
    numItems++;
}

void Player::readScroll(int index) {
    GameObject* item = inventory[index];
    Scroll* scroll = dynamic_cast<Scroll*>(item);

    if (scroll != nullptr) {
        scroll->read();
        inventory.erase(inventory.begin() + index);
        numItems--;
    }
}

void Player::wieldWeapon(int index) {
    GameObject* item = inventory[index];
    Weapon* weapon = dynamic_cast<Weapon*>(item);

    if (weapon != nullptr) {
        weapon->wield();
    }
}