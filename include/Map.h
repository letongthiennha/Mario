#pragma once
#include "raylib.h"
#include "Tile.h"
#include "Mario.h"
#include "Coin.h"
#include "Mushroom.h"
#include <vector>
class Map: public DrawableObj {
private:
    int currentMap;
    float width;
    const float height= 900.0f;
    float currBackgroundStarX;
    Texture2D background;
    std::vector<Tile*> interactiveTiles;
    std::vector<Tile*> nonInterativeTile;
    std::vector<Item*> items;
    void LoadFromJsonFile(const std::string& filename);
public:
    std::vector<Tile *> &getInteractiveTiles();
	std::vector<Item*>& getItems();
    float getMapWidth() const;
    Map();
    ~Map();
    void nextMap();
    void LoadMap(int mapNumber);
    void Draw() override;
};
