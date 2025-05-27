#pragma once
#include "Entity.h"
#include "ResourceManager.h"
#include "TileType.h"
#include <string>
class Tile : public Entity {
private:
    void updateSprite() override{};
    TileType type;

public:
    Tile(Vector2 pos, TileType type, std::string key);
    void Draw() override;
    
};
