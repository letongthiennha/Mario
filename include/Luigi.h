#pragma once
#include "PlayableCharacter.h"

class Luigi : public PlayableCharacter {
private:
public:
    // Constructor
    Luigi(Vector2 pos, int lives = 3, PlayerState form = PLAYER_STATE_SMALL);
    Luigi(Vector2 pos, const PlayerData &playerData);

    void updateSprite() override;
};