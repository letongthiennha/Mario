#pragma once
#include "CharacterType.h"
#include "PlayableCharacter.h"
#include "Mario.h"
#include "Luigi.h"
class CharacterFactory {
public:
    static PlayableCharacter *createCharacter(CharacterType type, Vector2 position, const PlayerData &playerData);
};