#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include "Level.h"
#include "utilities.h"

class Game {
    public:
        Game(int gobSmellDist);
        ~Game();

        void play();
    private:
        Level* level;
        int gobSmellDistance;
        int levelNum;
};

#endif