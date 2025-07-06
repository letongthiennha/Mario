#include "raylib.h"
#include "Entity.h"
#include "QuestionBlock.h"

QuestionBlock::QuestionBlock(Vector2 pos, Vector2 size, Color color, QuestionBlockReward rewardType) :
    QuestionBlock(pos, size, color, 0.1f, 3, rewardType)  {
        reward = rewardType;
        hit = false;
    }

QuestionBlock::QuestionBlock(Vector2 pos, Vector2 size, Color color, float frameTime, int maxFrame, 
    QuestionBlockReward rewardType) :
    Block(pos, size, color, frameTime, maxFrame, 0) {
        reward = rewardType;
        hit = false;
        currFrame = 0;
        frameAcum = 0;
        sprite = &ResourceManager::getInstance().getTexture("Question_Block_0");
    }

QuestionBlock::~QuestionBlock() = default;   

void QuestionBlock::updateStateAndPhysic() {
    Entity::updateStateAndPhysic();
    frameAcum += GetFrameTime();
    if (frameAcum > frameTime) {
        currFrame++;
        if (currFrame > maxFrame) currFrame = 0;
        frameAcum -= frameTime;
    }
}

void QuestionBlock::updateSprite() {
    std::string key = "Question_Block_" + std::to_string(currFrame);
    sprite = &ResourceManager::getInstance().getTexture(key);
}

void QuestionBlock::Draw() {
    updateSprite();
    if (!sprite) {
        printf("QuestionBlock sprite is null!\n");
        return;
    }
    DrawTexture(*sprite, pos.x, pos.y, WHITE);
}

void QuestionBlock::doHit(Mario& mario, Map& map) {
    if (!hit) {
        hit = true;
        switch (reward) {
            case REWARD_MUSHROOM:
                // Create mushroom
                break;
            case REWARD_FIRE_FLOWER:
                // Create fire flower
                break;
            case REWARD_1UP_FLOWER:
                // Create 1 up flower
                break;
        }
    }
}
