#pragma once
#include "Item.h"
#include <memory>
#include <string>
#include "Coin.h"
#include "Mushroom.h"
#include "1UpMushroom.h"
#include "FireFlower.h"
#include "Star.h"
#include "3UpMoon.h"

class ItemFactory {
public:
    static Item* createItem(
        const std::string& type,
        Vector2 pos,
        Vector2 size,
        Color color,
        float frameTime,
        int maxFrame,
        int extra = 0,
        Direction direction = DIRECTION_LEFT
    );
};