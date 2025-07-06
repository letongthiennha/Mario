#pragma once
#include "raylib.h"
#include "Entity.h"
#include "Block.h"

enum QuestionBlockReward {
    REWARD_MUSHROOM,
    REWARD_FIRE_FLOWER,
    REWARD_1UP_FLOWER
};

class QuestionBlock : public Block {
    public:
    QuestionBlockReward reward;
    QuestionBlock(Vector2 pos, Vector2 size, Color color, QuestionBlockReward rewardType);
    QuestionBlock(Vector2 pos, Vector2 size, Color color, float frameTime, int maxFrame,
         QuestionBlockReward rewardTypes);
    ~QuestionBlock() override;

    void updateStateAndPhysic() override;
    void updateSprite() override;
    void Draw() override;
    void doHit(Mario& mario, Map& map) override;
};