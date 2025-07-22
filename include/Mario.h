#include "PlayableCharacter.h"

class Mario : public PlayableCharacter {
private:
public:
    // Constructor
    Mario(Vector2 pos, int lives = 3, PlayerState form = PLAYER_STATE_SMALL);


    void updateSprite() override;
};