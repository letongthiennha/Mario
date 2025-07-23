#pragma once
#include "PlayableCharacter.h"

class Mario : public PlayableCharacter {
private:
public:
    // Constructor
    Mario(Vector2 pos, int lives = 3, PlayerState form = PLAYER_STATE_SMALL);
    Mario(Vector2 pos, const PlayerData &playerData);

    void updateSprite() override;
};