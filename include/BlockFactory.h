#pragma once 
#include "Block.h"
class BlockFactory {
public:
    static Block* createBlock(const std::string &type, Vector2 pos,std::vector<Item *> &itemsContainer, std::string rewardType = "");
    static Block *createBlockFromId(int ID, Vector2 pos, std::vector<Item *> &itemsContainer, std::string rewardType = "");
};