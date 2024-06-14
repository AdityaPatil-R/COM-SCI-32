#include "Monster.h"
#include "utilities.h"
#include "Weapon.h"
#include "Level.h"
#include "Player.h"

#include <vector>
#include <iostream>

using namespace std;

// ***********
// * MONSTER *
// ***********

Monster::Monster(int y, int x, int hp, Weapon* wpn, int str, int dex, int arm, string nm, Level* lvl) :
Actor(y, x, hp, hp, wpn, str, dex, arm, 0, lvl) {
    Actor::setName(nm);
}

Monster::~Monster() {
    delete getWeapon();
}

bool isPassable(char cell) {
    return cell == ROOM || cell == WEAPON || cell == SCROLL || cell == STAIRS || cell == IDOL;
}

bool isBlocked(char cell) {
    return cell == WALL || cell == BOGEYMAN || cell == SNAKEWOMAN || cell == DRAGON || cell == GOBLIN;
}

void Monster::move(int dist, int playerYPrev, int playerXPrev, int playerYNext, int playerXNext) {
    int monsterY = getYPos();
    int monsterX = getXPos();

    int playerY = level->getPlayer()->getYPos();
    int playerX = level->getPlayer()->getXPos();

    int distance = abs(monsterX - playerX) + abs(monsterY - playerY);
    
    // Handle goblin movement
    if (dist == level->getGoblinSmellDistance() && distance <= level->getGoblinSmellDistance() && distance > 2) {
        path.clear();

        if (pathExists(monsterY, monsterX, playerY, playerX, level->getGoblinSmellDistance())) {
            Point next = path.back();
            setYPos(next.y);
            setXPos(next.x);
            path.pop_back();
        }

        level->setChar(monsterY, monsterX, ROOM);
        level->setChar(getYPos(), getXPos(), getSymbol());
        
        return;
    }
    
    // Handle bogeyman and snakewoman's movement
    if (distance <= dist && distance > 1) {
        bool playerMovedVertically = (playerYPrev != playerYNext);
        bool playerMovedHorizontally = (playerXPrev != playerXNext);

        if (playerMovedVertically) {
            if (monsterY < playerY && isPassable(level->getChar(monsterY + 1, monsterX)) && !isBlocked(level->getChar(monsterY + 1, monsterX))) {
                setYPos(monsterY + 1);
            } else if (monsterY > playerY && isPassable(level->getChar(monsterY - 1, monsterX)) && !isBlocked(level->getChar(monsterY - 1, monsterX))) {
                setYPos(monsterY - 1);
            } else if (monsterX < playerX && isPassable(level->getChar(monsterY, monsterX + 1)) && !isBlocked(level->getChar(monsterY, monsterX + 1))) {
                setXPos(monsterX + 1);
            } else if (monsterX > playerX && isPassable(level->getChar(monsterY, monsterX - 1)) && !isBlocked(level->getChar(monsterY, monsterX - 1))) {
                setXPos(monsterX - 1);
            }
        } else if (playerMovedHorizontally) {
            if (monsterX < playerX && isPassable(level->getChar(monsterY, monsterX + 1)) && !isBlocked(level->getChar(monsterY, monsterX + 1))) {
                setXPos(monsterX + 1);
            } else if (monsterX > playerX && isPassable(level->getChar(monsterY, monsterX - 1)) && !isBlocked(level->getChar(monsterY, monsterX - 1))) {
                setXPos(monsterX - 1);
            } else if (monsterY < playerY && isPassable(level->getChar(monsterY + 1, monsterX)) && !isBlocked(level->getChar(monsterY + 1, monsterX))) {
                setYPos(monsterY + 1);
            } else if (monsterY > playerY && isPassable(level->getChar(monsterY - 1, monsterX)) && !isBlocked(level->getChar(monsterY - 1, monsterX))) {
                setYPos(monsterY - 1);
            }
        } else {
            int yDistance = abs(monsterY - playerY);
            int xDistance = abs(monsterX - playerX);

            if (yDistance > xDistance) {
                if (monsterX < playerX && isPassable(level->getChar(monsterY, monsterX + 1)) && !isBlocked(level->getChar(monsterY, monsterX + 1))) {
                    setXPos(monsterX + 1);
                } else if (monsterX > playerX && isPassable(level->getChar(monsterY, monsterX - 1)) && !isBlocked(level->getChar(monsterY, monsterX - 1))) {
                    setXPos(monsterX - 1);
                } else if (monsterY < playerY && isPassable(level->getChar(monsterY + 1, monsterX)) && !isBlocked(level->getChar(monsterY + 1, monsterX))) {
                    setYPos(monsterY + 1);
                } else if (monsterY > playerY && isPassable(level->getChar(monsterY - 1, monsterX)) && !isBlocked(level->getChar(monsterY - 1, monsterX))) {
                    setYPos(monsterY - 1);
                }
            } else {
                if (monsterY < playerY && isPassable(level->getChar(monsterY + 1, monsterX)) && !isBlocked(level->getChar(monsterY + 1, monsterX))) {
                    setYPos(monsterY + 1);
                } else if (monsterY > playerY && isPassable(level->getChar(monsterY - 1, monsterX)) && !isBlocked(level->getChar(monsterY - 1, monsterX))) {
                    setYPos(monsterY - 1);
                } else if (monsterX < playerX && isPassable(level->getChar(monsterY, monsterX + 1)) && !isBlocked(level->getChar(monsterY, monsterX + 1))) {
                    setXPos(monsterX + 1);
                } else if (monsterX > playerX && isPassable(level->getChar(monsterY, monsterX - 1)) && !isBlocked(level->getChar(monsterY, monsterX - 1))) {
                    setXPos(monsterX - 1);
                }
            }
        } 

        if (getYPos() == monsterY && getXPos() == monsterX) {
            setMoved(false);

            if (distance == 1) {
                level->battle(this, level->getPlayer());
            }
        }

        level->setChar(monsterY, monsterX, ROOM);
        level->setChar(getYPos(), getXPos(), getSymbol());
    }
}

bool Monster::pathExists(int monY, int monX, int playY, int playX, int smell) {
    if (monY == playY && monX == playX) {
        return true;
    }

    if (smell == 0) {
        return false;
    }

    int directions[4][2];

    // Determine direction priorities
    if (monY > playY && monX > playX) {
        directions[0][0] = -1; 
        directions[0][1] = 0;  
        directions[1][0] = 0;  
        directions[1][1] = -1;
        directions[2][0] = 0;  
        directions[2][1] = 1;  
        directions[3][0] = 1;  
        directions[3][1] = 0;  
    } else if (monY > playY && monX < playX) {
        directions[0][0] = -1; 
        directions[0][1] = 0;  
        directions[1][0] = 0;  
        directions[1][1] = 1;  
        directions[2][0] = 0;  
        directions[2][1] = -1; 
        directions[3][0] = 1;  
        directions[3][1] = 0;  
    } else if (monY < playY && monX > playX) {
        directions[0][0] = 1;  
        directions[0][1] = 0; 
        directions[1][0] = 0;  
        directions[1][1] = -1; 
        directions[2][0] = 0;  
        directions[2][1] = 1;  
        directions[3][0] = -1; 
        directions[3][1] = 0;  
    } else if (monY < playY && monX < playX) {
        directions[0][0] = 1;  
        directions[0][1] = 0;  
        directions[1][0] = 0;  
        directions[1][1] = 1;  
        directions[2][0] = 0;  
        directions[2][1] = -1; 
        directions[3][0] = -1; 
        directions[3][1] = 0;  
    } else if (monY > playY) {
        directions[0][0] = -1; 
        directions[0][1] = 0;  
        directions[1][0] = 0;  
        directions[1][1] = (monX > playX) ? -1 : 1; 
        directions[2][0] = 1;  
        directions[2][1] = 0;  
        directions[3][0] = 0;  
        directions[3][1] = (monX > playX) ? 1 : -1; 
    } else if (monY < playY) {
        directions[0][0] = 1;  
        directions[0][1] = 0;  
        directions[1][0] = 0;  
        directions[1][1] = (monX > playX) ? -1 : 1; 
        directions[2][0] = -1; 
        directions[2][1] = 0; 
        directions[3][0] = 0;  
        directions[3][1] = (monX > playX) ? 1 : -1; 
    } else if (monX > playX) {
        directions[0][0] = 0;  
        directions[0][1] = -1; 
        directions[1][0] = (monY > playY) ? -1 : 1; 
        directions[1][1] = 0;  
        directions[2][0] = 0;  
        directions[2][1] = 1; 
        directions[3][0] = (monY > playY) ? 1 : -1; 
        directions[3][1] = 0;  
    } else if (monX < playX) {
        directions[0][0] = 0;  
        directions[0][1] = 1; 
        directions[1][0] = (monY > playY) ? -1 : 1; 
        directions[1][1] = 0;  
        directions[2][0] = 0;  
        directions[2][1] = -1; 
        directions[3][0] = (monY > playY) ? 1 : -1; 
        directions[3][1] = 0;  
    }

    for (const auto& dir : directions) {
        int newY = monY + dir[0];
        int newX = monX + dir[1];

        if (!isBlocked(level->getChar(newY, newX)) && newX > 0 && newX < 70 && newY > 0 && newY < 18 && pathExists(newY, newX, playY, playX, smell - 1)) {
            Point p;
            p.y = newY;
            p.x = newX;
            path.push_back(p);
            return true;
        }
    }
    
    return false;
}

// ************
// * BOGEYMAN *
// ************

Bogeyman::Bogeyman(int y, int x, Level* lvl) :
Monster(y, x, randInt(5, 10), new ShortSword(y, x, level), randInt(2, 3), randInt(2, 3), 2, "the Bogeyman", lvl) {
}

string Bogeyman::attackMessage() {
    return "slashes short sword at Player";
}

char Bogeyman::getSymbol() const {
    return 'B';
}

void Bogeyman::move(int playerYPrev, int playerXPrev, int playerYNext, int playerXNext) {
    Monster::move(5, playerYPrev, playerXPrev, playerYNext, playerXNext);
}

// **************
// * SNAKEWOMAN *
// **************

Snakewoman::Snakewoman(int y, int x, Level* lvl) :
Monster(y, x, randInt(3, 6), new MagicFangsOfSleep(y, x, level), 2, 3, 3, "the Snakewoman", lvl) {
}

string Snakewoman::attackMessage() {
    return "strikes magic fangs of sleep at Player";
}

char Snakewoman::getSymbol() const {
    return 'S';
}

void Snakewoman::move(int playerYPrev, int playerXPrev, int playerYNext, int playerXNext) {
    Monster::move(3, playerYPrev, playerXPrev, playerYNext, playerXNext);
}

// **********
// * DRAGON *
// **********

Dragon::Dragon(int y, int x, Level* lvl) :
Monster(y, x, randInt(20, 25), new LongSword(y, x, level), 4, 4, 4, "the Dragon", lvl) {
}

string Dragon::attackMessage() {
    return "swings long sword at Player";
}

char Dragon::getSymbol() const {
    return 'D';
}

void Dragon::move(int playerYPrev, int playerXPrev, int playerYNext, int playerXNext) {}

// **********
// * GOBLIN *
// **********

Goblin::Goblin(int y, int x, Level* lvl) : 
Monster(y, x, randInt(15, 20), new ShortSword(y, x, level), 3, 1, 1, "the Goblin", lvl) {
}

string Goblin::attackMessage() {
    return "slashes short sword at Player";
}

char Goblin::getSymbol() const {
    return 'G';
}

void Goblin::move(int playerYPrev, int playerXPrev, int playerYNext, int playerXNext) {
    Monster::move(level->getGoblinSmellDistance(), playerYPrev, playerXPrev, playerYNext, playerXNext);
}