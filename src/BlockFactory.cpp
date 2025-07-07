#include "BlockFactory.h"
#include "QuestionBlock.h"
#include "EyesOpenedBlock.h"
#include "StoneBlock.h"
#include "EyesClosedBlock.h"
#include "WoodBlock.h"
#include "GlassBlock.h"
#include "CloudBlock.h"
Block* BlockFactory::createBlock(const std::string &type, Vector2 pos,std::vector<Item *> &itemsContainer, std::string rewardType )
{
    if (type == "QuestionBlock") {
        return new QuestionBlock(pos, Vector2{32, 32}, WHITE, rewardType, itemsContainer);
    } else if (type == "EyesClosedBlock") {
        return new EyesOpenedBlock(pos, Vector2{32, 32}, WHITE);
    } else if(type == "StoneBlock") {
        return new StoneBlock(pos, Vector2{32, 32}, WHITE);
    } else if(type == "EyesOpenedBlock") {
        return new EyesOpenedBlock(pos, Vector2{32, 32}, WHITE);
    } else if(type == "WoodBlock") {
        return new WoodBlock(pos, Vector2{32, 32}, WHITE);
    } else if(type == "GlassBlock") {
        return new GlassBlock(pos, Vector2{32, 32}, WHITE);
    } else {
        return nullptr; // Unknown block type
    }
}

Block *BlockFactory::createBlockFromId(int ID, Vector2 pos, std::vector<Item *> &itemsContainer, std::string rewardType)
{
    switch (ID) {
        case 0: // CloudBlock
            return new CloudBlock(pos, Vector2{32, 32}, WHITE);
        case 1: // EyesOpenedBlock
            return new EyesOpenedBlock(pos, Vector2{32, 32}, WHITE);
        case 3: // StoneBlock
            return new StoneBlock(pos, Vector2{32, 32}, WHITE);
        case 4: // WoodBlock
            return new WoodBlock(pos, Vector2{32, 32}, WHITE);
        case 5: // GlassBlock
            return new GlassBlock(pos, Vector2{32, 32}, WHITE);
        case 6: // EyesClosedBlock
            return new EyesClosedBlock(pos, Vector2{32, 32}, WHITE);
        default:
            return nullptr; // Unknown block ID
    }
}
