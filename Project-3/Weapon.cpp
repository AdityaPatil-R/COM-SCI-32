#include "Weapon.h"
#include "Level.h"
#include "Player.h"
#include "utilities.h"

// **********
// * WEAPON *
// **********

Weapon::Weapon(int y, int x, string nm, string actStr, int dexBon, int damAmt, Level* lvl) : GameObject(y, x, nm, lvl) {
    actionString = actStr;
    dexterityBonus = dexBon;
    damageAmount = damAmt;
}

Weapon::~Weapon() {}

string Weapon::getActionString() {
    return actionString;
}

char Weapon::getSymbol() {
    return ')';
}

string Weapon::extraMessage() {
    return "";
}

int Weapon::getDexterityBonus() {
    return dexterityBonus;
}

int Weapon::getDamageAmount() {
    return damageAmount;
}

// ********
// * MACE *
// ********

Mace::Mace(int y, int x, Level* lvl) : Weapon(y, x, "mace", "swings", 0, 2, lvl) {}

void Mace::wield() {
    level->getPlayer()->setWeapon(this);
}

// ***************
// * SHORT SWORD *
// ***************

ShortSword::ShortSword(int y, int x, Level* lvl) : Weapon(y, x, "short sword", "slashes", 0, 2, lvl) {}

void ShortSword::wield() {
    level->getPlayer()->setWeapon(this);
}

// **************
// * LONG SWORD *
// **************

LongSword::LongSword(int y, int x, Level* lvl) : Weapon(y, x, "long sword", "swings", 2, 4, lvl) {}

void LongSword::wield() {
    level->getPlayer()->setWeapon(this);
}

// *************
// * MAGIC AXE *
// *************

MagicAxe::MagicAxe(int y, int x, Level* lvl) : Weapon(y, x, "magic axe", "chops", 5, 5, lvl) {}

void MagicAxe::wield() {
    level->getPlayer()->setWeapon(this);
}

// ************************
// * MAGIC FANGS OF SLEEP *
// ************************

MagicFangsOfSleep::MagicFangsOfSleep(int y, int x, Level* lvl) : Weapon(y, x, "magic fangs", "strikes", 3, 2, lvl) {}

void MagicFangsOfSleep::wield() {
    level->getPlayer()->setWeapon(this);
}