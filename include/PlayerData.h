#pragma once
#include "Mario.h"
class PlayerData {
private:
int lives;
int coins;
int score;
public:
    PlayerData(int lives, int coins, int score);
    // Add other persistent data as needed
    friend class Mario; // Allow Mario to access private members
};