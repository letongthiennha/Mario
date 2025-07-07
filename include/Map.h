#pragma once
#include "raylib.h"
#include "Tile.h"
#include "Mario.h"
#include "Coin.h"
#include "Mushroom.h"
#include "1UpMushroom.h"
#include "FireFlower.h"
#include "Star.h"
#include "3UpMoon.h"
#include "Monster.h"
#include <vector>
class Monster;
class Map: public DrawableObj {
private:
    int currentMap;
    float width;
    const float height= 900.0f;
    
    Vector2 startPositionForMario;

    float currBackgroundStarX;
    Texture2D background;

    std::vector<Tile*> interactiveTiles;
    std::vector<Tile*> nonInterativeTile;
    std::vector<Monster *> monsters;
    std::vector<Item*> items;
    void LoadFromJsonFile(const std::string& filename);
    void LoadMap(int mapNumber);    
public:
    std::vector<Tile *> &getInteractiveTiles();
	std::vector<Item*>& getItems();
    std::vector<Monster *> &getMonsters();
    float getMapWidth() const;

    Vector2 getStartPositionForMario() const;

    Map(int mapNumber);  
    ~Map();
    void Draw() override;
};
