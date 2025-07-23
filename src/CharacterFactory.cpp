#include "CharacterFactory.h"

PlayableCharacter *CharacterFactory::createCharacter(CharacterType type, Vector2 position, const PlayerData &playerData)
{
    switch (type) {
        case CharacterType::MARIO:
            return new Mario(position, playerData);
        case CharacterType::LUIGI:
            return new Luigi(position, playerData);
        default:
            return nullptr; // Handle unknown character type
    }   
}
