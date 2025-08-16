#pragma once
#include "raylib.h"
#include "Tile.h"
#include "PlayableCharacter.h"
#include "Coin.h"
#include "Mushroom.h"
#include "1UpMushroom.h"
#include "FireFlower.h"
#include "Star.h"
#include "3UpMoon.h"
#include "Monster.h"
#include "Block.h"
#include <vector>
class Block;
class Monster;
class Map: public DrawableObj {
private:
    int currentMap;
    float width;
    const float height= 900.0f;
    
    Vector2 startPositionForPlayer;

    float currBackgroundStarX;
    Texture2D background;


    int sectionWidth; // Width of each section
    int maxSection; // Maximum number of sections
    std::vector<std::vector<Tile*>> interactiveTilesSection;
    std::vector<std::vector<Tile*>> nonInteractiveTilesSection;
    std::vector<std::vector<Block*>> blocksSection;
    std::vector<std::vector<Item*>> itemsSection;
    std::vector<std::vector<Monster*>> monstersSection;

    void LoadFromJsonFile(const std::string& filename);
    void LoadMap(int mapNumber);    
public:

    std::vector<std::vector<Tile *>> &getInteractiveTilesSection();
    std::vector<std::vector<Tile *>> &getNonInteractiveTilesSection();
    std::vector<std::vector<Block *>> &getBlocksSection();
    std::vector<std::vector<Item *>> &getItemsSection();
    std::vector<std::vector<Monster *>> &getMonstersSection();
    int getSectionWidth() const;
    float getMapWidth() const;

    Vector2 getStartPositionForPlayer() const;

    Map(int mapNumber);  
    ~Map();
    void Draw() override;
};
