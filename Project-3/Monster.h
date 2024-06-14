#ifndef MONSTER_INCLUDED
#define MONSTER_INCLUDED

#include "Actor.h"

#include <vector>

struct Point {
    int y, x;
};


class Monster : public Actor {
    public:
        Monster(int y, int x, int hp, Weapon* wpn, int str, int dex, int arm, string nm, Level* lvl);
        virtual ~Monster();

        virtual char getSymbol() const = 0;
        virtual void move(int playerYPrev, int playerXPrev, int playerYNext, int playerXNext) = 0;
        bool pathExists(int monY, int monX, int playY, int playX, int smell);
        void move(int dist, int playerYPrev, int playerXPrev, int playerYNext, int playerXNext);
    private:
        vector<Point> path;
};

class Bogeyman : public Monster {
    public:
        Bogeyman(int y, int x, Level* lvl);
        string attackMessage();
        char getSymbol() const;
        void move(int playerYPrev, int playerXPrev, int playerYNext, int playerXNext);
    private:
};

class Snakewoman : public Monster {
    public:
        Snakewoman(int y, int x, Level* lvl);
        string attackMessage();
        char getSymbol() const;
        void move(int playerYPrev, int playerXPrev, int playerYNext, int playerXNext);
    private:
};

class Dragon : public Monster {
    public:
        Dragon(int y, int x, Level* lvl);
        string attackMessage();
        char getSymbol() const;
        void move(int playerYPrev, int playerXPrev, int playerYNext, int playerXNext);
    private:
};

class Goblin : public Monster {
    public:
        Goblin(int y, int x, Level* lvl);
        string attackMessage();
        char getSymbol() const;
        void move(int playerYPrev, int playerXPrev, int playerYNext, int playerXNext);
    private:
};

#endif