#include "Level.h"
#include "utilities.h"
#include "Player.h"
#include "Monster.h"
#include "Weapon.h"
#include "Scroll.h"

#include <iostream>

using namespace std;

// **************************
// * CONSTRUCTER/DESTRUCTOR *
// **************************

// Creates first level
Level::Level(int levelNum) : levelNumber(levelNum), player(nullptr), idolTaken(false) {
    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            grid[i][j] = WALL;
            checkFilled[i][j] = WALL;
        }
    }

    generateLevel();
    createGameObjects();
    createObjective(levelNum);
    createMonsters(levelNum);
    createPlayer();
}

Level::Level(int levelNum, Player* p) : levelNumber(levelNum), idolTaken(false) {
    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            grid[i][j] = WALL;
            checkFilled[i][j] = WALL;
        }
    }

    generateLevel();
    createGameObjects();
    createObjective(levelNum);
    createMonsters(levelNum);

    int y, x;

    do {
        y = randInt(1, GRID_HEIGHT - 2);
        x = randInt(1, GRID_WIDTH - 2);
    } while (grid[y][x] != ROOM && grid[y][x] != BOGEYMAN && grid[y][x] != SNAKEWOMAN && grid[y][x] != GOBLIN && grid[y][x] != DRAGON);

    player = new Player(y, x, this);

    // Transfers player's information from last level
    player->setHitPoints(p->getHitPoints());
    player->setMaximumHitpoints(p->getMaximumHitPoints());
    player->setArmorPoints(p->getArmorPoints());
    player->setStrengthPoints(p->getStrengthPoints());
    player->setDexterityPoints(p->getDexterityPoints());
    player->setWeapon(p->getWeapon());
    player->setLevel(this);
}

Level::~Level() {
    delete player;

    for (auto it = monsters.begin(); it != monsters.end(); it++) {
        delete *it;
    }

    for (auto it = gameObjects.begin(); it != gameObjects.end(); it++) {
        delete *it;
    }
}

// ***********
// * GETTERS *
// ***********

Player* Level::getPlayer() {
    return player;
}

char Level::getChar(int y, int x) {
    return grid[y][x];
}

int Level::getGoblinSmellDistance() {
    return goblinSmellDistance;
}

// ***********
// * SETTERS *
// ***********

void Level::setChar(int y, int x, char c) {
    grid[y][x] = c;
}

void Level::setGoblinSmellDistance(int dist) {
    goblinSmellDistance = dist;
}

// **************
// * DISPLAYERS *
// **************

// Displays in correct order to allow actors to be on top of game objects
void Level::displayLevel() {
    for (auto it = gameObjects.begin(); it != gameObjects.end(); it++) {
        grid[(*it)->getYPos()][(*it)->getXPos()] = (*it)->getSymbol();
    }

    if (levelNumber == 4) {
        grid[objectiveY][objectiveX] = IDOL;
    } else {
        grid[objectiveY][objectiveX] = STAIRS;
    }

    for (auto it = monsters.begin(); it != monsters.end(); it++) {
        grid[(*it)->getYPos()][(*it)->getXPos()] = (*it)->getSymbol();
    }

    grid[player->getYPos()][player->getXPos()] = '@';

    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            cout << grid[i][j];
        }

        cout << endl;
    }
}

void Level::displayStats() {
    cout << "Level: " << levelNumber;
    cout << ", Hit points: " << player->getHitPoints();
    cout << ", Armor: " << player->getArmorPoints();
    cout << ", Strength: " << player->getStrengthPoints();
    cout << ", Dexterity: " << player->getDexterityPoints() << endl;
    cout << endl;
}

void Level::displayPickUpMessage() {
    if (player->getNumItems() == inventorySize) {
        cout << "Your knapsack is full; you can't pick that up." << endl;
        return;
    }

    for (auto it = gameObjects.begin(); it != gameObjects.end(); it++) {
        if (player->getYPos() == (*it)->getYPos() && player->getXPos() == (*it)->getXPos()) {
            cout << "You pick up ";

            if ((*it)->getSymbol() == WEAPON) {
                cout << (*it)->getName() << endl;
            } else if ((*it)->getSymbol() == SCROLL) {
                cout << "a scroll called " << (*it)->getName() << endl;
            }

            break;
        }
    }

    cout << pickUpMessage << endl;
}

void Level::displayInventory() {
    player->displayInventory();
}

void Level::displayReadScrollMessage() {
    cout << scrollMessage << endl;
    scrollMessage = "";
}

void Level::displayWieldWeaponMessage() {
    cout << weaponMessage << endl;
    weaponMessage = "";
}

void Level::displayBattleMessage() {
    if (player->getHitPoints() <= 0) {
        battleString += "Press q to exit game.\n";
    }

    cout << battleString << endl;
    battleString = "";
}

void Level::displayEndGameMessage() {
    cout << "You pick up the golden idol\nCongratulations, you won!\nPress q to exit game." << endl;
}

// ************
// * CREATORS *
// ************

void Level::createPlayer() {
    int y, x;

    do {
        y = randInt(1, GRID_HEIGHT - 2);
        x = randInt(1, GRID_WIDTH - 2);
    } while (grid[y][x] != ROOM && grid[y][x] != BOGEYMAN && grid[y][x] != SNAKEWOMAN && grid[y][x] != GOBLIN && grid[y][x] != DRAGON);

    player = new Player(y, x, this);
}

void Level::createMonsters(int levelNum) {
    numMonsters = randInt(2, 5 * (levelNum + 1) + 1);

    switch (levelNum) {
        case 0:
        case 1:
            for (int i = 0; i < numMonsters; i++) {
                int y, x;

                do {
                    y = randInt(1, GRID_HEIGHT - 2);
                    x = randInt(1, GRID_WIDTH - 2);
                } while (grid[y][x] == BOGEYMAN || grid[y][x] == SNAKEWOMAN || grid[y][x] == DRAGON || grid[y][x] == GOBLIN || grid[y][x] == PLAYER || grid[y][x] == WALL);

                int decide = randInt(1, 2);

                if (decide == 1) {
                    monsters.push_back(new Goblin(y, x, this));
                } else if (decide == 2) {
                    monsters.push_back(new Snakewoman(y, x, this));
                }
            }

            break;
        case 2:
            for (int i = 0; i < numMonsters; i++) {
                int y, x;

                do {
                    y = randInt(1, GRID_HEIGHT - 2);
                    x = randInt(1, GRID_WIDTH - 2);
                } while (grid[y][x] == BOGEYMAN || grid[y][x] == SNAKEWOMAN || grid[y][x] == DRAGON || grid[y][x] == GOBLIN || grid[y][x] == PLAYER || grid[y][x] == WALL);

                int decide = randInt(1, 3);

                if (decide == 1) {
                    monsters.push_back(new Goblin(y, x, this));
                } else if (decide == 2){
                    monsters.push_back(new Snakewoman(y, x, this));
                } else if (decide == 3) {
                    monsters.push_back(new Bogeyman(y, x, this));
                }
            }

            break;
        case 3:
        case 4:
            for (int i = 0; i < numMonsters; i++) {
                int y, x;

                do {
                    y = randInt(1, GRID_HEIGHT - 2);
                    x = randInt(1, GRID_WIDTH - 2);
                } while (grid[y][x] == BOGEYMAN || grid[y][x] == SNAKEWOMAN || grid[y][x] == DRAGON || grid[y][x] == GOBLIN || grid[y][x] == PLAYER || grid[y][x] == WALL);

                int decide = randInt(1, 4);

                if (decide == 1) {
                    monsters.push_back(new Goblin(y, x, this));
                } else if (decide == 2){
                    monsters.push_back(new Snakewoman(y, x, this));
                } else if (decide == 3) {
                    monsters.push_back(new Bogeyman(y, x, this));
                } else if (decide == 4) {
                    monsters.push_back(new Dragon(y, x, this));
                }
            }

            break;
    }
}

void Level::createGameObjects() {
    int numObjects = randInt(2, 3);

    for (int i = 0; i < numObjects; i++) {
        int y, x;

        do {
            y = randInt(1, GRID_HEIGHT - 2);
            x = randInt(1, GRID_WIDTH - 2);
        } while (grid[y][x] != ROOM && grid[y][x] != WEAPON && grid[y][x] != SCROLL);

        int decide = randInt(1, 2);

        if (decide == 1) {
            int decideWeapon = randInt(1, 3);

            if (decideWeapon == 1) {
                gameObjects.push_back(new Mace(y, x, this));
            } else if (decideWeapon == 2) {
                gameObjects.push_back(new ShortSword(y, x, this));
            } else if (decideWeapon == 3) {
                gameObjects.push_back(new LongSword(y, x, this));
            }
        } else if (decide == 2) {
            int decideScroll = randInt(1, 4);

            if (decideScroll == 1) {
                gameObjects.push_back(new ScrollOfImproveArmor(y, x, this));
            } else if (decideScroll == 2) {
                gameObjects.push_back(new ScrollOfRaiseStrength(y, x, this));
            } else if (decideScroll == 3) {
                gameObjects.push_back(new ScrollOfEnhanceHealth(y, x, this));
            } else if (decideScroll == 4) {
                gameObjects.push_back(new ScrollOfEnhanceDexterity(y, x, this));
            }
        }
    }
}

void Level::createObjective(int levelNum) {
    do {
        objectiveY = randInt(1, GRID_HEIGHT - 2);
        objectiveX = randInt(1, GRID_WIDTH - 2);
    } while (grid[objectiveY][objectiveX] != ROOM && grid[objectiveY][objectiveX] != WEAPON && grid[objectiveY][objectiveX] != SCROLL);

    if (levelNum == 4) {
        grid[objectiveY][objectiveX] = IDOL;
    } else {
        grid[objectiveY][objectiveX] = STAIRS;
    }
}

// ****************
// * CONDITIONALS *
// ****************

bool Level::playerCanDescend() {
    return player->getYPos() == objectiveY && player->getXPos() == objectiveX;
}

bool Level::playerIsAlive() {
    return player->getHitPoints() > 0;
}

bool Level::goldenIdolTaken() {
    return idolTaken;
}

bool Level::isGoldenIdolBeingTaken() {
    if (levelNumber == 5 && grid[objectiveY][objectiveX] == PLAYER) {
        objectiveY = -1;
        objectiveX = -1;

        return true;
    }
    
    return false;
}

bool Level::isNextTo(Actor* a, Actor* b) {
    return (abs(a->getYPos() - b->getYPos()) == 1 && a->getXPos() == b->getXPos()) || 
    (abs(a->getXPos() - b->getXPos()) == 1 && a->getYPos() == b->getYPos());
}

// ****************
// * MANIPULATORS *
// ****************

void Level::updateBoard(char move) {
    int playerYPrev = player->getYPos();
    int playerXPrev = player->getXPos();

    movePlayer(move);

    int playerYNext = player->getYPos();
    int playerXNext = player->getXPos();

    if (playerYPrev == playerYNext && playerXPrev == playerXNext) {
        player->setMoved(false);
    } else {
        player->setMoved(true);
    }
    
    moveMonsters(playerYPrev, playerXPrev, playerYNext, playerXNext);
}

void Level::movePlayer(char move) {
    int dx = 0, dy = 0;
    
    switch (move) {
        case ARROW_UP: 
            dy = -1; 
            
            break;
        case ARROW_DOWN: 
            dy = 1; 

            break;
        case ARROW_LEFT: 
            dx = -1; 

            break;
        case ARROW_RIGHT: 
            dx = 1; 

            break;
        default:
            for (int i = 0; i < monsters.size(); ++i) {
                if (isNextTo(monsters[i], player)) {
                    battle(monsters[i], player);
                }
            }

            return;
    }

    int newX = player->getXPos() + dx;
    int newY = player->getYPos() + dy;
    char nextPosChar = grid[newY][newX];

    bool isPassable = (nextPosChar == ROOM || nextPosChar == WEAPON || nextPosChar == SCROLL || nextPosChar == STAIRS || nextPosChar == IDOL);
    bool isMonsterOrWall = (nextPosChar == BOGEYMAN || nextPosChar == SNAKEWOMAN || nextPosChar == DRAGON || nextPosChar == GOBLIN || nextPosChar == WALL);

    if (isPassable) {
        if (player->getSleepTime() == 0) {
            player->setXPos(newX);
            player->setYPos(newY);
            grid[newY - dy][newX - dx] = ROOM;
        } else {
            player->setSleepTime(player->getSleepTime() - 1);
        }
    }
    
    if (isMonsterOrWall) {
        for (int i = 0; i < monsters.size(); ++i) {
            if (monsters[i]->getYPos() == newY && monsters[i]->getXPos() == newX) {
                if (player->getSleepTime() == 0) {
                    if (randInt(1, 10) == 1 && player->getHitPoints() < player->getMaximumHitPoints()) {
                        player->setHitPoints(player->getHitPoints() + 1);
                    }
                    battle(player, monsters[i]);
                } else {
                    player->setSleepTime(player->getSleepTime() - 1);
                }
            }
        }
    }

    for (int i = 0; i < monsters.size(); ++i) {
        if (isNextTo(monsters[i], player)) {
            battle(monsters[i], player);
        }
    }
}

void Level::moveMonsters(int playerYPrev, int playerXPrev, int playerYNext, int playerXNext) {
    for (auto it = monsters.begin(); it != monsters.end(); it++) {
        if ((*it)->getSleepTime() == 0) {
            (*it)->setMoved(true);
            if ((*it)->getActorName() == "the Dragon" && randInt(1, 10) == 1 && (*it)->getHitPoints() < (*it)->getMaximumHitPoints()) {
                (*it)->setHitPoints((*it)->getHitPoints() + 1);
            }
            
            (*it)->move(playerYPrev, playerXPrev, playerYNext, playerXNext);
        } else {
            (*it)->setSleepTime((*it)->getSleepTime() - 1);
        }
    }
}

void Level::pickUpItem() {
    pickUpMessage = "";

    if (levelNumber == 4 && player->getYPos() == objectiveY && player->getXPos() == objectiveX) {
        idolTaken = true;
        return;
    }

    for (auto it = gameObjects.begin(); it != gameObjects.end(); it++) {
        if (player->getYPos() == (*it)->getYPos() && player->getXPos() == (*it)->getXPos()) {
            if (player->getNumItems() == inventorySize) {
                pickUpMessage = "Your knapsack is full; you can't pick that up.\n";
            } else {
                pickUpMessage = "You pick up ";

                if ((*it)->getSymbol() == WEAPON) {
                    pickUpMessage += (*it)->getName() + "\n";
                } else if ((*it)->getSymbol() == SCROLL) {
                    pickUpMessage += "a scroll called " + (*it)->getName() + "\n";
                }
            }

            player->addToInventory(*it);
            gameObjects.erase(it);
            break;
        }
    }
}

void Level::attemptReadScroll(char c) {
    int index = c - 'a';

    if (index >= 0 && index < player->getNumItems()) {
        Scroll* scroll = dynamic_cast<Scroll*>(player->getInventory(index));

        if (scroll != nullptr) {
            scrollMessage = "You read a scroll called " + player->getInventory(index)->getName() + player->getInventory(index)->extraMessage();
            player->readScroll(index);
        } else {
            scrollMessage = "You can't read a " + player->getInventory(index)->getName();
        }
    }
}

void Level::attemptWieldWeapon(char c) {
    int index = c - 'a';

    if (index >= 0 && index < player->getNumItems()) {
        Weapon* weapon = dynamic_cast<Weapon*>(player->getInventory(index));

        if (weapon != nullptr) {
            weaponMessage = "You are wielding " + player->getInventory(index)->getName();
            player->wieldWeapon(index);
        } else {
            weaponMessage = "You can't wield a " + player->getInventory(index)->getName();
        }
    }
}

void Level::teleportPlayer() {
    int y, x;

    do {
        y = randInt(1, GRID_HEIGHT - 2);
        x = randInt(1, GRID_WIDTH - 2);
    } while (grid[y][x] != ROOM && grid[y][x] != BOGEYMAN && grid[y][x] != SNAKEWOMAN && grid[y][x] != GOBLIN && grid[y][x] != DRAGON && grid[y][x] != PLAYER);

    player->setYPos(y);
    player->setXPos(x);
}

void Level::cheat() {
    player->setStrengthPoints(9);
    player->setMaximumHitpoints(50);
    player->setHitPoints(50);
}

void Level::battle(Actor* attacker, Actor* defender) {
    int attackerPoints = attacker->getDexterityPoints() + attacker->getWeapon()->getDexterityBonus();
    int defenderPoints = defender->getDexterityPoints() + defender->getArmorPoints();

    battleString += attacker->getActorName() + " " + attacker->getWeapon()->getActionString() + " " + attacker->getWeapon()->getName() + " at " + defender->getActorName();
    
    if (randInt(1, attackerPoints) >= randInt(1, defenderPoints)) {
        int damage = randInt(0, player->getStrengthPoints() + player->getWeapon()->getDamageAmount() - 1);
        defender->setHitPoints(defender->getHitPoints() - damage);
        
        if (defender->getHitPoints() <= 0) {
            battleString += " dealing a final blow.\n";
            setChar(defender->getYPos(), defender->getXPos(), ROOM);

            if (dynamic_cast<Monster*>(defender) != nullptr) {
                dropItem(dynamic_cast<Monster*>(defender));
            }

            for (auto it = monsters.begin(); it != monsters.end(); it++) {
                if ((*it)->getYPos() == defender->getYPos() && (*it)->getXPos() == defender->getXPos()) {
                    monsters.erase(it);
                    break;
                }
            }
        } else {
            battleString += " and hits, ";

            if (attacker->getWeapon()->getName() == "magic fangs" && randInt(1, 5) == 1) {
                battleString += "putting " + defender->getActorName() + " to sleep.\n";
                    
                if (defender->isAsleep()) {
                    defender->setSleepTime(max(defender->getSleepTime(), randInt(2, 6)));
                } else {
                    defender->setSleepTime(randInt(2, 6));
                }
            } else {
                battleString += "dealing " + to_string(damage) + " damage.\n";
            }
        }
    } else {
        battleString += " and misses.\n";
    }
}

void Level::dropItem(Monster* m) {
    if (m->getActorName() == "the Bogeyman") {
        if (randInt(1, 10) == 1) {
            bool spaceAlreadyOccupied = false;

            for (auto it = gameObjects.begin(); it != gameObjects.end(); it++) {
                if ((*it)->getYPos() == m->getYPos() && (*it)->getXPos() == m->getXPos()) {
                    spaceAlreadyOccupied = true;
                }
            }

            if (!spaceAlreadyOccupied) {
                gameObjects.push_back(new MagicAxe(m->getYPos(), m->getXPos(), this));
            }
        }
    }

    if (m->getActorName() == "the Snakewoman") {
        if (randInt(1, 3) == 1) {
            bool spaceAlreadyOccupied = false;

            for (auto it = gameObjects.begin(); it != gameObjects.end(); it++) {
                if ((*it)->getYPos() == m->getYPos() && (*it)->getXPos() == m->getXPos()) {
                    spaceAlreadyOccupied = true;
                }
            }

            if (!spaceAlreadyOccupied) {
                gameObjects.push_back(new MagicFangsOfSleep(m->getYPos(), m->getXPos(), this));
            }
        }
    }

    if (m->getActorName() == "the Dragon") {
        bool spaceAlreadyOccupied = false;

        for (auto it = gameObjects.begin(); it != gameObjects.end(); it++) {
            if ((*it)->getYPos() == m->getYPos() && (*it)->getXPos() == m->getXPos()) {
                spaceAlreadyOccupied = true;
            }
        }

        if (!spaceAlreadyOccupied) {
            int decider = randInt(1, 5);

            switch (decider) {
                case 1:
                    gameObjects.push_back(new ScrollOfTeleportation(m->getYPos(), m->getXPos(), this));
                    break;
                case 2:
                    gameObjects.push_back(new ScrollOfImproveArmor(m->getYPos(), m->getXPos(), this));
                    break;
                case 3:
                    gameObjects.push_back(new ScrollOfRaiseStrength(m->getYPos(), m->getXPos(), this));
                    break;
                case 4:
                    gameObjects.push_back(new ScrollOfEnhanceHealth(m->getYPos(), m->getXPos(), this));
                    break;
                case 5:
                    gameObjects.push_back(new ScrollOfEnhanceDexterity(m->getYPos(), m->getXPos(), this));
                    break;
            }
        }
    }

    if (m->getActorName() == "the Goblin") {
        if (randInt(1, 3) == 1) {
            bool spaceAlreadyOccupied = false;

            for (auto it = gameObjects.begin(); it != gameObjects.end(); it++) {
                if ((*it)->getYPos() == m->getYPos() && (*it)->getXPos() == m->getXPos()) {
                    spaceAlreadyOccupied = true;
                }
            }

            if (!spaceAlreadyOccupied) {
                int decider = randInt(1, 2);

                switch (decider) {
                    case 1:
                        gameObjects.push_back(new MagicAxe(m->getYPos(), m->getXPos(), this));
                        break;
                    case 2:
                        gameObjects.push_back(new MagicFangsOfSleep(m->getYPos(), m->getXPos(), this));
                        break;
                }
            }
        }
    }
}

// ***********
// * HELPERS *
// ***********

void Level::generateLevel() {
    bool connected = false;

    while (!connected) {
        for (int i = 0; i < GRID_HEIGHT; ++i) {
            for (int j = 0; j < GRID_WIDTH; ++j) {
                grid[i][j] = WALL;
            }
        }

        for (int i = 0; i < randInt(MIN_ROOMS, MAX_ROOMS); i++) {
            generateRoom(rooms[i]);

            for (int y = rooms[i].y; y < rooms[i].y + rooms[i].height; y++) {
                for (int x = rooms[i].x; x < rooms[i].x + rooms[i].width; x++) {
                    grid[y][x] = ROOM;
                }
            }

            connectRooms(rooms[i]);
        }

        if (isConnected()) {
            connected = true;
        }
    }
}

int Level::distance(Actor* a, Actor* b) {
    return abs(a->getYPos() - b->getYPos()) + abs(a->getXPos() - b->getXPos());
}

int Level::max(int a, int b) {
    if (a > b) {
        return a;
    }

    return b;
}

// ******************
// * LEVEL CREATION *
// ******************

void Level::fillRoom(int y, int x) {
    if (y < 0 || y >= GRID_HEIGHT || x < 0 || x >= GRID_WIDTH) {
        return;
    }

    if (grid[y][x] == ROOM && checkFilled[y][x] != CHECK) {
        checkFilled[y][x] = CHECK;

        fillRoom(y + 1, x);
        fillRoom(y - 1, x);
        fillRoom(y, x + 1);
        fillRoom(y, x - 1);
    }
}

bool Level::isConnected() {
    int yStart = -1;
    int xStart = -1;

    for (int y = 0; y < GRID_HEIGHT; y++) {
        for (int x = 0; x < GRID_WIDTH; x++) {
            if (grid[y][x] == ROOM) {
                yStart = y;
                xStart = x;
                break;
            }
        }

        if (yStart != -1) {
            break;
        }
    }

    if (yStart == -1 || xStart == -1) {
        return false;
    }

    for (int y = 0; y < GRID_HEIGHT; y++) {
        for (int x = 0; x < GRID_WIDTH; x++) {
            if (grid[y][x] == WALL) {
                checkFilled[y][x] = WALL;
            } else {
                checkFilled[y][x] = ROOM;
            
            }
        }
    }

    fillRoom(yStart, xStart);

    for (int y = 0; y < GRID_HEIGHT; y++) {
        for (int x = 0; x < GRID_WIDTH; x++) {
            if (checkFilled[y][x] == ROOM) {
                return false;
            }
        }
    }

    return true;
}

bool Level::overlap(Room room) {
    for (int y = room.y - 1; y < room.y + room.height + 1; y++) {
        for (int x = room.x - 1; x < room.x + room.width + 1; x++) {
            if (grid[y][x] == ROOM) {
                return true;
            }
        }
    }
    return false;
}

void Level::generateRoom(Room& room) {
    do {
        room.width = randInt(8, 15);
        room.height = randInt(3, 8);
        room.x = randInt(1, GRID_WIDTH - room.width - 2);
        room.y = randInt(1, GRID_HEIGHT - room.height - 2);
    } while (overlap(room));
}

void Level::makeCorridor(int y1, int x1, int y2, int x2) {
    if (y1 == y2) {
        if (x1 < x2) {
            for (int x = x1; x <= x2; x++) {
                grid[y1][x] = ROOM;
            }
        } else {
            for (int x = x1; x >= x2; x--) {
                grid[y1][x] = ROOM;
            }
        }
    } else if (x1 == x2) {
        if (y1 < y2) {
            for (int y = y1; y <= y2; y++) {
                grid[y][x1] = ROOM;
            }
        } else {
            for (int y = y1; y >= y2; y--) {
                grid[y][x1] = ROOM;
            }
        }
    }
}

void Level::connectRooms(Room& room) {
    int centerX = room.x + room.width / 2;
    int centerY = room.y + room.height / 2;

    for (int y = centerY; y <= centerY; y++) {
        int left = room.x - 1;
        int right = room.x + room.width;

        while (left >= 0 && grid[y][left] != ROOM) {
            left--;
        }

        while (right < GRID_WIDTH && grid[y][right] != ROOM) {
            right++;
        }

        if (left >= 0) {
            makeCorridor(y, room.x, y, left + 1);
        } else if (right < GRID_WIDTH) {
            makeCorridor(y, room.x + room.width - 1, y, right - 1);
        }
    }

    for (int x = centerX; x <= centerX; x++) {
        int up = room.y - 1;
        int down = room.y + room.height;

        while (up >= 0 && grid[up][x] != ROOM) {
            up--;
        }

        while (down < GRID_HEIGHT && grid[down][x] != ROOM) {
            down++;
        }

        if (up >= 0) {
            makeCorridor(room.y, x, up + 1, x);
        } else if (down < GRID_HEIGHT) {
            makeCorridor(room.y + room.height - 1, x, down - 1, x);
        }
    }
}