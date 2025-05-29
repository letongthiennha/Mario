#pragma once
#include "Entity.h"
#include "ResourceManager.h"
#include "TileType.h"
#include <string>
class Tile : public Entity {
private:
    void updateSprite() override{};

public:
    Tile(Vector2 pos,int map,  int key);
    void Draw() override;
    
};
