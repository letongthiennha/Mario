#pragma once
#include "raylib.h"
#include "Entity.h"
#include "Block.h"
#include "ItemFactory.h"


class QuestionBlock : public Block {
    private:
    std::vector<Item*> &itemsContainer; // Container for items spawned by the block
    public:
    std::string reward;
    QuestionBlock(Vector2 pos, Vector2 size, Color color, std::string rewardType,std::vector<Item*> &itemsContainer);
    QuestionBlock(Vector2 pos, Vector2 size, Color color, float frameTime, int maxFrame,
         std::string rewardTypes, std::vector<Item*> &itemsContainer);
    ~QuestionBlock() override;

    void updateStateAndPhysic() override;
    void updateSprite() override;
    void Draw() override;
    void ActiveReward();
};