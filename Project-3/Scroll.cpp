#include "Scroll.h"
#include "Level.h"
#include "Player.h"
#include "utilities.h"

// **********
// * SCROLL *
// **********

Scroll::Scroll(int y, int x, string nm, Level* lvl) : GameObject(y, x, nm, lvl) {}

Scroll::~Scroll() {}

char Scroll::getSymbol() {
    return '?';
}

// ***************************
// * SCROLL OF TELEPORTATION *
// ***************************

ScrollOfTeleportation::ScrollOfTeleportation(int y, int x, Level* lvl) : Scroll(y, x, "scroll of teleportation", lvl) {}

void ScrollOfTeleportation::read() {
    level->teleportPlayer();
}

string ScrollOfTeleportation::extraMessage() {
    return "\nYou feel your body wrenched in space and time.";
}

// ***************************
// * SCROLL OF IMPROVE ARMOR *
// ***************************

ScrollOfImproveArmor::ScrollOfImproveArmor(int y, int x, Level* lvl) : Scroll(y, x, "scroll of improve armor", lvl) {}

void ScrollOfImproveArmor::read() {
    level->getPlayer()->Actor::increaseArmorPoints(randInt(1, 3));
}

string ScrollOfImproveArmor::extraMessage() {
    return "\nYour armor glows blue.";
}

// ****************************
// * SCROLL OF RAISE STRENGTH *
// ****************************

ScrollOfRaiseStrength::ScrollOfRaiseStrength(int y, int x, Level* lvl) : Scroll(y, x, "scroll of raise strength", lvl) {}

void ScrollOfRaiseStrength::read() {
    level->getPlayer()->Actor::increaseStrengthPoints(randInt(1, 3));
}

string ScrollOfRaiseStrength::extraMessage() {
    return "\nYour muscles bulge.";
}

// ****************************
// * SCROLL OF ENHANCE HEALTH *
// ****************************

ScrollOfEnhanceHealth::ScrollOfEnhanceHealth(int y, int x, Level* lvl) : Scroll(y, x, "scroll of enhance health", lvl) {}

void ScrollOfEnhanceHealth::read() {
    level->getPlayer()->Actor::increaseMaximumHitPoints(randInt(3, 8));
}

string ScrollOfEnhanceHealth::extraMessage() {
    return "\nYou feel your heart beating stronger.";
}

// *******************************
// * SCROLL OF ENHANCE DEXTERITY *
// *******************************

ScrollOfEnhanceDexterity::ScrollOfEnhanceDexterity(int y, int x, Level* lvl) : Scroll(y, x, "scroll of enhance dexterity", lvl) {}

void ScrollOfEnhanceDexterity::read() {
    level->getPlayer()->Actor::increaseDexterityPoints(1);
}

string ScrollOfEnhanceDexterity::extraMessage() {
    return "\nYou feel like less of a klutz.";
}