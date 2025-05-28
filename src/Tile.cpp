#include "Tile.h"
#include"ResourceManager.h"
Tile::Tile(Vector2 pos,int map,char key):Entity(pos,{32,32},WHITE)
{
    std::string keyStr = "MAP_" + std::to_string(map) + "_TILE_" + key;
    sprite = &ResourceManager::getTexture(keyStr);
}

void Tile::Draw(){
    if(!sprite)
        return;
    DrawTexture(*sprite, pos.x, pos.y, WHITE);
}
