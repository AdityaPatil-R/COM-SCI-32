#include "Game.h"
#include "Player.h"

Game::Game(int gobSmellDist) {
    levelNum = 0;
    gobSmellDistance = gobSmellDist;
    level = new Level(levelNum); 
    level->setGoblinSmellDistance(gobSmellDist);
}

Game::~Game() {
    delete level; 
}

void Game::play() {
    level->displayLevel();
    level->displayStats();

    char input = getCharacter();
    char end;

    while (input != 'q' && level->playerIsAlive() && !level->goldenIdolTaken()) {
        switch (input) {
            // Move
            case ARROW_UP:
            case ARROW_DOWN:
            case ARROW_LEFT:
            case ARROW_RIGHT:
                level->updateBoard(input);
                clearScreen();
                level->displayLevel();
                level->displayStats();
                level->displayBattleMessage();

                break;
            // Check inventory
            case 'i':
                clearScreen();

                if (level->getPlayer()->getSleepTime() == 0) {
                    level->displayInventory();
                    end = getCharacter();
                } else {
                    level->getPlayer()->setSleepTime(level->getPlayer()->getSleepTime() - 1);
                }

                level->updateBoard(input);
                clearScreen();
                level->displayLevel();
                level->displayStats();
                level->displayBattleMessage();

                break;
            // Pick up item
            case 'g':
                if (level->getPlayer()->getSleepTime() == 0) {
                    level->pickUpItem();
                    if (!level->goldenIdolTaken()) {
                        level->updateBoard(input);
                        clearScreen();
                        level->displayLevel();
                        level->displayStats();
                        level->displayPickUpMessage();
                        level->displayBattleMessage();
                    } else {
                        clearScreen();
                        level->displayLevel();
                        level->displayStats();
                        level->displayEndGameMessage();
                    }
                } else {
                    level->getPlayer()->setSleepTime(level->getPlayer()->getSleepTime() - 1);
                }

                break;
            // Read scroll
            case 'r':
                clearScreen();

                if (level->getPlayer()->getSleepTime() == 0) {
                    level->displayInventory();
                    end = getCharacter();
                    level->attemptReadScroll(end);
                } else {
                    level->getPlayer()->setSleepTime(level->getPlayer()->getSleepTime() - 1);
                }

                level->updateBoard(input);
                clearScreen();
                level->displayLevel();
                level->displayStats();
                level->displayReadScrollMessage();
                level->displayBattleMessage();

                break;
            // Wield weapon
            case 'w':
                clearScreen();

                if (level->getPlayer()->getSleepTime() == 0) {
                    level->displayInventory();
                    end = getCharacter();
                    level->attemptWieldWeapon(end);
                } else {
                    level->getPlayer()->setSleepTime(level->getPlayer()->getSleepTime() - 1);
                }

                level->updateBoard(input);
                clearScreen();
                level->displayLevel();
                level->displayStats();
                level->displayWieldWeaponMessage();
                level->displayBattleMessage();

                break;
            // Take stairs
            case '>':
                if (level->playerCanDescend()) {
                    if (level->getPlayer()->getSleepTime() == 0) {
                        clearScreen();
                        levelNum++;
                        level = new Level(levelNum, level->getPlayer());
                        level->setGoblinSmellDistance(gobSmellDistance);
                        level->displayLevel();
                        level->displayStats();  
                    } else {
                        level->getPlayer()->setSleepTime(level->getPlayer()->getSleepTime() - 1);
                    }
                } else {
                    level->updateBoard(input);
                    clearScreen();
                    level->displayLevel();
                    level->displayStats();
                    level->displayBattleMessage();
                }

                break;
            // Cheat
            case 'c':
                if (level->getPlayer()->getSleepTime() == 0) {
                    level->cheat();
                } else {
                    level->getPlayer()->setSleepTime(level->getPlayer()->getSleepTime() - 1);
                }

                level->updateBoard(input);
                clearScreen();
                level->displayLevel();
                level->displayStats();
                level->displayBattleMessage();

                break;
            // Invalid input
            default:
                level->updateBoard(input);
                clearScreen();
                level->displayLevel();
                level->displayStats();
                level->displayBattleMessage();

                break;
        }

        if (!level->playerIsAlive()) {
            break;
        }

        if (!level->goldenIdolTaken()) {
            input = getCharacter();
        }
    }

    char endGame;

    if (level->goldenIdolTaken()) {
        while (endGame != 'q') {
            endGame = getCharacter();
        }
    }  
}
