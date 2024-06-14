#ifndef LEVEL_INCLUDED
#define LEVEL_INCLUDED

#include <vector>
#include <string>

using namespace std;

class Player;
class Monster;
class Actor;
class GameObject;

struct Room {
    int x;
    int y;
    int width;
    int height;
};

// ********************
// * GLOBAL VARIABLES *
// ********************

const int GRID_WIDTH = 70;
const int GRID_HEIGHT = 18;
const int MIN_ROOMS = 3;
const int MAX_ROOMS = 6;
const int MAX_MONSTERS = 26;
const int MAX_GAME_OBJECTS = 3;

const char WALL = '#';
const char ROOM = ' ';
const char BOGEYMAN = 'B';
const char SNAKEWOMAN = 'S';
const char DRAGON = 'D';
const char GOBLIN = 'G';
const char WEAPON = ')';
const char SCROLL = '?';
const char STAIRS = '>';
const char PLAYER = '@';
const char IDOL = '&';

const char CHECK = 'O';

class Level {
    public:
        Level(int levelNum);
        Level(int levelNum, Player* p);
        ~Level();

        Player* getPlayer();
        char getChar(int y, int x);
        int getGoblinSmellDistance();

        void setChar(int y, int x, char c);
        void setGoblinSmellDistance(int dist);

        void displayLevel();
        void displayStats();
        void displayPickUpMessage();
        void displayInventory();
        void displayReadScrollMessage();
        void displayWieldWeaponMessage();
        void displayBattleMessage();
        void displayEndGameMessage();

        void createPlayer();
        void createMonsters(int levelNum);
        void createGameObjects();
        void createObjective(int levelNum);

        bool playerCanDescend();
        bool playerIsAlive();
        bool goldenIdolTaken();
        bool isGoldenIdolBeingTaken();
        bool isNextTo(Actor* a, Actor* b);

        void updateBoard(char move);
        void movePlayer(char move);
        void moveMonsters(int playerYPrev, int playerXPrev, int playerYNext, int playerXNext);
        void pickUpItem();
        void attemptReadScroll(char c);
        void attemptWieldWeapon(char c);
        void teleportPlayer();
        void cheat();
        void battle(Actor* attacker, Actor* defender);
        void dropItem(Monster* m);

        void generateLevel();
        int distance(Actor* a, Actor* b);
        int max(int a, int b);
    private:
        void fillRoom(int y, int x);
        bool isConnected();
        bool overlap(Room room);
        void generateRoom(Room& room);
        void makeCorridor(int y1, int x1, int y2, int x2);
        void connectRooms(Room& room);

        int levelNumber;
        int numRooms;
        int numMonsters;
        int inventorySize;

        Room rooms[MAX_ROOMS];
        char grid[GRID_HEIGHT][GRID_WIDTH];
        char checkFilled[GRID_HEIGHT][GRID_WIDTH];

        Player* player;
        vector<Monster*> monsters;
        vector<GameObject*> gameObjects;

        int goblinSmellDistance;
        int objectiveY;
        int objectiveX;

        string scrollMessage;
        string weaponMessage;
        string pickUpMessage;

        char mostRecentMove;
        char previousLocation;

        string battleString;
        bool idolTaken;
};

#endif