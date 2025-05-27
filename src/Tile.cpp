#include "Tile.h"
#include"ResourceManager.h"
Tile::Tile(Vector2 pos, TileType type,std::string key):Entity(pos,{32,32},WHITE)
{
    this->type = type;
    switch (type)
    {
    case TILE_TYPE_NORMAL:
        sprite =& ResourceManager::getTexture(key + "_NORMAL");
        break;
    case TILE_TYPE_RIGHT_EDGE:
        sprite = &ResourceManager::getTexture(key + "_RIGHT_EDGE");
        break;
    case TILE_TYPE_LEFT_EDGE:
        sprite=& ResourceManager::getTexture(key+"_LEFT_EDGE");
        break;
    }
}

void Tile::Draw(){
    DrawTexture(*sprite, pos.x, pos.y, WHITE);
}
