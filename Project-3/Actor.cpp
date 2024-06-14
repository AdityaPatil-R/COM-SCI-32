#include "Actor.h"

// **************************
// * CONSTRUCTER/DESTRUCTOR *
// **************************

Actor::Actor(int y, int x, int hp, int mhp, Weapon* wpn, int arm, int str, int dex, int slp, Level* lvl) : level(lvl) {
    yPos = y;
    xPos = x;
    hitPoints = hp;
    maxHitPoints = mhp;
    weapon = wpn;
    armorPoints = arm;
    strengthPoints = str;
    dexterityPoints = dex;
    sleepTime = slp;

    moved = true;
}

Actor::~Actor() { }

// ***********
// * GETTERS *
// ***********

int Actor::getYPos() { return yPos; }

int Actor::getXPos() { return xPos; }

int Actor::getHitPoints() { return hitPoints; }

int Actor::getMaximumHitPoints() { return maxHitPoints; }

Weapon* Actor::getWeapon() { return weapon; }

int Actor::getArmorPoints() { return armorPoints; }

int Actor::getStrengthPoints() { return strengthPoints; }

int Actor::getDexterityPoints() { return dexterityPoints; }

int Actor::getSleepTime() { return sleepTime; }

Level* Actor::getLevel() { return this->level; }

string Actor::getActorName() { return name; }

bool Actor::getMoved() { return moved; }

// ***********
// * SETTERS *
// ***********

void Actor::setYPos(int y) { yPos = y; }

void Actor::setXPos(int x) { xPos = x; }

void Actor::setHitPoints(int hp) { hitPoints = hp; }

void Actor::setMaximumHitpoints(int mhp) { maxHitPoints = mhp; }

void Actor::setWeapon(Weapon* w) { weapon = w; }

void Actor::setArmorPoints(int arm) { armorPoints = arm; }

void Actor::setStrengthPoints(int str) { strengthPoints = str; }

void Actor::setDexterityPoints(int dex) { dexterityPoints = dex; }

void Actor::setSleepTime(int slp) { sleepTime = slp; }

void Actor::setLevel(Level* lvl) { level = lvl; }

void Actor::setName(string nm) { name = nm; }

void Actor::setMoved(bool m) {moved = m; }

// ****************
// * INCREMENTERS *
// ****************

void Actor::increaseArmorPoints(int amount) { armorPoints += amount; }

void Actor::increaseStrengthPoints(int amount) { strengthPoints += amount; }

void Actor::increaseMaximumHitPoints(int amount) { maxHitPoints += amount; }

void Actor::increaseDexterityPoints(int amount) { dexterityPoints += amount; }

// *********
// * OTHER *
// *********

bool Actor::isAsleep() { return sleepTime != 0; }