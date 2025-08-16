#include "raylib.h"
#include "Entity.h"
#include "QuestionBlock.h"

QuestionBlock::QuestionBlock(Vector2 pos, Vector2 size, Color color, std::string rewardType, std::vector<Item*> &itemsContainer) :
    QuestionBlock(pos, size, color, 0.2f, 3, rewardType,itemsContainer)  {
        reward = rewardType;
        hit = false;
    }

QuestionBlock::QuestionBlock(Vector2 pos, Vector2 size, Color color, float frameTime, int maxFrame, 
    std::string rewardType, std::vector<Item*> &itemsContainer) :
    Block(pos, size, color, frameTime, maxFrame, 0), itemsContainer(itemsContainer) {
        reward = rewardType;
        hit = false;
        currFrame = 0;
        frameAcum = 0;
        sprite = &ResourceManager::getInstance().getTexture("Question_Block_0");
    }

QuestionBlock::~QuestionBlock() = default;   

void QuestionBlock::updateStateAndPhysic() {
    if (!hit) {
        Entity::updateStateAndPhysic();
        frameAcum += GameClock::getInstance().DeltaTime;
        if (frameAcum > frameTime) {
            currFrame++;
            if (currFrame > maxFrame) currFrame = 0;
            frameAcum -= frameTime;
        }
    }
}

void QuestionBlock::updateSprite() {
    if(hit) {
        // If the block has been hit, use a different sprite
        sprite = &ResourceManager::getInstance().getTexture("Eyes_Closed_Block");
        return;
    }
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

void QuestionBlock::ActiveReward() {
    if (hit) {
        return ; // If the block has already been hit, return nullptr
    }
    Item* item = ItemFactory::createItem(reward, pos, DIRECTION_RIGHT);
    item->setState(ItemState::POP_UP);

    if (auto coin = dynamic_cast<Coin*>(item)) {
        coin->isItem = true;
    }

    itemsContainer.push_back(item); // Add the item to the container
    hit = true; // Mark the block as hit
}
