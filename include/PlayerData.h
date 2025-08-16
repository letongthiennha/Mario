#pragma once
#include "PlayableCharacter.h"
class PlayerData {
private:
int lives;
int coins;
int score;
public:
    PlayerData(int lives, int coins, int score);
    // Add other persistent data as needed
    int getLives() const { return lives; }
    int getCoins() const { return coins; }
    int getScore() const { return score; }
    friend class PlayableCharacter; // Allow PlayableCharacter to access private members
};