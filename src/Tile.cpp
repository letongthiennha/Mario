#include "Tile.h"
#include"ResourceManager.h"
Tile::Tile(Vector2 pos,int map,int key):Entity(pos,{32,32},WHITE)
{
    std::string keyStr ="TILE_" + std::to_string(key);
    sprite = &ResourceManager::getInstance().getTexture(keyStr);
}

void Tile::Draw(){
    if(!sprite)
        return;
    DrawTexture(*sprite, pos.x, pos.y, WHITE);
}
